/*
 *  Copyright 2018 Digital Media Professionals Inc.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
#include <pthread.h>

#include "SegNetBasic_gen.h"
#include "util_draw.h"
#include "util_input.h"
#include "demo_common.h"
#define DMP_MEASURE_TIME
#include "util_time.h"

using namespace std;
using namespace dmp;
using namespace util;

#define SCREEN_W (get_screen_width())
#define SCREEN_H (get_screen_height())

#define IMAGE_W 320
#define IMAGE_H 240
#define IMAGE_NUM 367

#define FILENAME_WEIGHTS "SegNetBasic_weights.bin"


CSegNetBasic network;

#define USLEEP_TIME 50000
#define RING_BUF_SIZE 4
// Buffer for pre-processed image data
uint16_t imgProc[RING_BUF_SIZE][IMAGE_W * IMAGE_H * 3];
vector<float> netout[RING_BUF_SIZE];
int imgProcIdx[RING_BUF_SIZE];

unsigned preproc_rbuf_idx   = 0;
unsigned inference_rbuf_idx = 0;
unsigned postproc_rbuf_idx  = 0;

int exit_code = -1;
bool do_pause = false;

// Post-processing functions, defined in segnet_post.cpp
void convertimage(uint16_t *imgProc, COverlayRGB &overlay);
void visualize(vector<float> &netoutCPU, COverlayRGB &overlay);

void increment_circular_variable(unsigned &v, unsigned max) {
  v++;
  if(v > max) {
    v = 0;
  }
}

static void *preproc(void*) {
  unsigned &rbuf_idx = preproc_rbuf_idx;
  // Open input images
  const char input_image_file[] = "segnet_image.bin";
  FILE *fimg = fopen(input_image_file, "rb");
  if (!fimg) {
    fprintf(stderr, "Could not open segnet_image.bin for reading\n");
    exit_code = 1;
  }

  int image_nr = 0;
  while(exit_code == -1) {
    while ((rbuf_idx + 1) % RING_BUF_SIZE == postproc_rbuf_idx) {
      usleep(USLEEP_TIME);
    }
    DECLARE_TVAL(preproc);
    GET_TVAL_START(preproc);
    // If not pause, get next image and pre-processed image
    if (!do_pause) {
      // Get pre-processed image data
      fseek(fimg, IMAGE_W * IMAGE_H * 6 * image_nr, SEEK_SET);
      if (fread(imgProc[rbuf_idx], 2, IMAGE_W * IMAGE_H * 3, fimg) != IMAGE_W * IMAGE_H * 3) {
        exit_code = 1;
      }
      ++image_nr;
      if (image_nr == IMAGE_NUM) {
        image_nr = 0;
      }
      imgProcIdx[rbuf_idx] = rbuf_idx;
    } else {
      imgProcIdx[rbuf_idx] = imgProcIdx[(rbuf_idx ? rbuf_idx : RING_BUF_SIZE) - 1];
    }
    GET_SHOW_TVAL_END(preproc);
    increment_circular_variable(rbuf_idx, RING_BUF_SIZE - 1);
  }

  return NULL;
}

static void *inference(void*) {
  unsigned &rbuf_idx = inference_rbuf_idx;
  void *net_inbuf_cpu = network.get_network_input_addr_cpu();
  while (exit_code == -1) {
    while (rbuf_idx == preproc_rbuf_idx) {
      usleep(USLEEP_TIME);
    }
    DECLARE_TVAL(inference);
    GET_TVAL_START(inference);

    // Run network in HW
    memcpy(net_inbuf_cpu, (void *)imgProc[imgProcIdx[rbuf_idx]], IMAGE_W * IMAGE_H * 6);
    network.RunNetwork();

    network.get_final_output(netout[rbuf_idx]);

    GET_SHOW_TVAL_END(inference);
    increment_circular_variable(rbuf_idx, RING_BUF_SIZE - 1);
  }

  return NULL;
}

static void *postproc(void*) {
  unsigned &rbuf_idx = postproc_rbuf_idx;

  // Get HW module frequency
  string conv_freq, fc_freq;
  conv_freq = to_string(network.get_dv_info().conv_freq);
  fc_freq   = to_string(network.get_dv_info().fc_freq);

  // Create background, image, and result image overlay
  COverlayRGB bg_overlay(SCREEN_W, SCREEN_H);
  bg_overlay.alloc_mem_overlay(SCREEN_W, SCREEN_H);
  bg_overlay.load_ppm_img("fpgatitle");
  COverlayRGB overlay_movie(SCREEN_W, SCREEN_H);
  overlay_movie.alloc_mem_overlay(IMAGE_W, IMAGE_H);
  COverlayRGB overlay_result(SCREEN_W, SCREEN_H);
  overlay_result.alloc_mem_overlay(IMAGE_W, IMAGE_H);

  // Draw background two times for front and back buffer
  const char *titles[] = {
    "CNN - SegNet Basic",
    "Per-Pixel Object Class detection",
  };
  for (int i = 0; i < 2; ++i) {
    bg_overlay.print_to_display(0, 0);
    print_demo_title(bg_overlay, titles);
    swap_buffer();
  }

  while (exit_code == -1) {
    while(rbuf_idx == inference_rbuf_idx) {
      usleep(USLEEP_TIME);
    }

    DECLARE_TVAL(postproc);
    GET_TVAL_START(postproc);

    // Handle output and draw results
    convertimage(imgProc[imgProcIdx[rbuf_idx]], overlay_movie);
    overlay_movie.print_to_display((SCREEN_W / 2 - IMAGE_W), 185);
    visualize(netout[rbuf_idx], overlay_result);
    overlay_movie.blend_from(overlay_result, 0.5);
    overlay_movie.print_to_display((SCREEN_W / 2), 185);

    // Output HW processing times
    int conv_time_tot = network.get_conv_usec();
    print_conv_time(bg_overlay, 3 * SCREEN_H / 4, conv_time_tot, conv_freq);

    swap_buffer();

    handle_keyboard_input(exit_code, do_pause);

    GET_SHOW_TVAL_END(postproc);
    cout << endl;

    increment_circular_variable(rbuf_idx, RING_BUF_SIZE - 1);
  }

  return NULL;
}

int main(int argc, char **argv) {
  // Initialize FB
  if (!init_fb()) {
    fprintf(stderr, "init_fb() failed\n");
    return 1;
  }
 
  // Initialize network object
  network.Verbose(0);
  if (!network.Initialize()) {
    return -1;
  }
  if (!network.LoadWeights(FILENAME_WEIGHTS)) {
    return -1;
  }
  if (!network.Commit()) {
    return -1;
  }

  pthread_t pre_th;
  pthread_t inf_th;
  pthread_t post_th;

  pthread_create(&pre_th, NULL, preproc, NULL);
  pthread_create(&inf_th, NULL, inference, NULL);
  pthread_create(&post_th, NULL, postproc, NULL);

  pthread_join(pre_th, NULL);
  pthread_join(inf_th, NULL);
  pthread_join(post_th, NULL);

  // Enter main loop
  shutdown();

  return exit_code;
}
