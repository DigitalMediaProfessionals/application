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
#include <sys/stat.h>
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

#include "DeconvNetBasic_gen.h"
#include "util_draw.h"
#include "util_input.h"
#include "demo_common.h"
#define DMP_MEASURE_TIME
#include "util_time.h"

//#define DUMP

using namespace std;
using namespace dmp;
using namespace util;

#define SCREEN_W (get_screen_width())
#define SCREEN_H (get_screen_height())

#define IMAGE_W 480
#define IMAGE_H 320

#define FILENAME_WEIGHTS "DeconvNetBasic.bin"


CDeconvNetBasic network;

#define USLEEP_TIME 50000
#define RING_BUF_SIZE 4
// Buffer for pre-processed image data
COverlayRGB *cam_overlay[RING_BUF_SIZE];
uint32_t imgView[IMAGE_W * IMAGE_H * 3];
__fp16 imgProc[RING_BUF_SIZE][IMAGE_W * IMAGE_H * 3];
vector<float> netout[RING_BUF_SIZE];

unsigned preproc_rbuf_idx   = 0;
unsigned inference_rbuf_idx = 0;
unsigned postproc_rbuf_idx  = 0;

int exit_code = -1;
bool do_pause = false;

static __attribute__((unused)) void save_out (CDeconvNetBasic &net) {
  std::string d("network_inout");
  mkdir(d.c_str(), 0777);
  for(int i = 0; i < net.get_total_layer_count(); i++) {
    fpga_layer &layer = net.get_layer(i);
	char f[100];
	snprintf(f, sizeof(f), "%s/layer%03d.bin", d.c_str(), i);

    int fd = open(f, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
      std::cerr << "fail to open " << f << ":" << strerror(errno) << std::endl;
      return;
    }
    size_t size = (layer.is_f32_output ? 4 : 2);
    for (int i = 0; i < layer.output_dim_size; i++) {
      size *= layer.output_dim[i];
    }
    if (write(fd, layer.output.data(), size) < static_cast<ssize_t>(size)) {
      std::cerr << "fail to write to " <<  f << ":" << strerror(errno) << std::endl;
      return;
    }
    close(fd);
  }
}


// Post-processing functions, defined in segnet_post.cpp
void visualize(vector<float> &netoutCPU, COverlayRGB &overlay);

void increment_circular_variable(unsigned &v, unsigned max) {
  v++;
  if (v > max) {
    v = 0;
  }
}

static void *preproc(void*) {
  unsigned &rbuf_idx = preproc_rbuf_idx;

  // Get input images filenames
  vector<string> image_names;
  unsigned image_nr = 0;
  get_jpeg_image_names("./images_segmentation/", image_names);
  int num_images = image_names.size();
  if (num_images == 0) {
    cout << "No input images." << endl;
    exit_code = 1;
    return NULL;
  }

  while (exit_code == -1) {
    while ((rbuf_idx + 1) % RING_BUF_SIZE == postproc_rbuf_idx) {
      usleep(USLEEP_TIME);
    }
    DECLARE_TVAL(preproc);
    GET_TVAL_START(preproc);
    // If not pause, get next image and pre-processed image
    if (!do_pause) {
      // Get pre-processed image data
      decode_jpg_file(image_names[image_nr], imgView, IMAGE_W, IMAGE_H);
    }
	cam_overlay[rbuf_idx]->convert_to_overlay_pixel_format(imgView, IMAGE_W*IMAGE_H);
	preproc_image(imgView, imgProc[rbuf_idx], IMAGE_W, IMAGE_H,
				  0.0f, 0.0f, 0.0f, 1.0f / 255.0f, true, false);

	increment_circular_variable(image_nr, num_images - 1);

    GET_SHOW_TVAL_END(preproc);
    increment_circular_variable(rbuf_idx, RING_BUF_SIZE - 1);

#ifdef DUMP
    // TODO: remove
    break;
#endif
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
    memcpy(net_inbuf_cpu, (void *)imgProc[rbuf_idx], IMAGE_W * IMAGE_H * 6);
    network.RunNetwork();

#ifdef DUMP
    save_out(network);
#endif	

    network.get_final_output(netout[rbuf_idx]);

    GET_SHOW_TVAL_END(inference);
    increment_circular_variable(rbuf_idx, RING_BUF_SIZE - 1);

#ifdef DUMP
    // TODO: remove
    break;
#endif
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
  COverlayRGB overlay_result(SCREEN_W, SCREEN_H);
  overlay_result.alloc_mem_overlay(IMAGE_W, IMAGE_H);

  // Draw background two times for front and back buffer
  const char *titles[] = {
    "CNN - DeconvNetBasic",
    "Semantic Segmentation"
  };
  for (int i = 0; i < 2; ++i) {
    bg_overlay.print_to_display(0, 0);
    print_demo_title(bg_overlay, titles);
    swap_buffer();
  }

  while (exit_code == -1) {
    while (rbuf_idx == inference_rbuf_idx) {
      usleep(USLEEP_TIME);
    }

    DECLARE_TVAL(postproc);
    GET_TVAL_START(postproc);

    // Handle output and draw results
    COverlayRGB *overlay_movie = cam_overlay[rbuf_idx];
    overlay_movie->print_to_display((SCREEN_W / 2 - IMAGE_W), 185);
    visualize(netout[rbuf_idx], overlay_result);
    overlay_movie->blend_from(overlay_result, 0.5);
    overlay_movie->print_to_display((SCREEN_W / 2), 185);

    // Output HW processing times
    int conv_time_tot = network.get_conv_usec();
    print_conv_time(bg_overlay, 3 * SCREEN_H / 4, conv_time_tot, conv_freq);

    swap_buffer();

    handle_keyboard_input(exit_code, do_pause);

    GET_SHOW_TVAL_END(postproc);
    cout << endl;

    increment_circular_variable(rbuf_idx, RING_BUF_SIZE - 1);

#ifdef DUMP
    // TODO: remove
    break;
#endif
  }

  return NULL;
}

int main(int argc, char **argv) {
  // Initialize FB
  if (!init_fb()) {
    fprintf(stderr, "init_fb() failed\n");
    return 1;
  }

  for(int i = 0; i < RING_BUF_SIZE; i++) {
    cam_overlay[i] = new COverlayRGB(SCREEN_W, SCREEN_H);
    cam_overlay[i]->alloc_mem_overlay(IMAGE_W, IMAGE_H);
  }
 
  // Initialize network object
  network.Verbose(0);
#ifdef DUMP
  network.WantLayerOutputs();
#endif
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
