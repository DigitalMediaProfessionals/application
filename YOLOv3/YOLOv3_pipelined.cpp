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

#include "YOLOv3_gen.h"
#include "util_draw.h"
#include "util_input.h"
#include "demo_common.h"
#include "YOLOv3_param.h"

#define DMP_MEASURE_TIME
#include "util_time.h"


using namespace std;
using namespace dmp;
using namespace util;

#define SCREEN_W (get_screen_width())
#define SCREEN_H (get_screen_height())

#define USLEEP_TIME 1000

// Define CNN network model object
CYOLOv3 network;

#define RING_BUF_SIZE 3
// Buffer for detection result image
COverlayRGB *cam_overlay[RING_BUF_SIZE];
// Buffer for decoded image data
uint32_t imgView[RING_BUF_SIZE][IMAGE_W * IMAGE_H];
int imgViewIdx[RING_BUF_SIZE];
// Buffer for pre-processed image data
__fp16 imgProc[RING_BUF_SIZE][PROC_W * PROC_H * 3];
// Buffer for network output
vector<float> net_output[RING_BUF_SIZE];

unsigned loadimg_rbuf_idx = 0;
unsigned preproc_rbuf_idx = 0;
unsigned inference_rbuf_idx = 0;
unsigned postproc_rbuf_idx = 0;

bool do_pause = false;
int exit_code = -1;


// Post-processing functions, defined in YOLOv3_post.cpp
void get_bboxes(const vector<float> &tensor, vector<float> &boxes);
void draw_bboxes(const vector<float> &boxes, COverlayRGB &overlay);

void *loadimg(void*) {
  unsigned &rbuf_idx = loadimg_rbuf_idx;  // alias

  // Get input images filenames
  vector<string> image_names;
  int image_nr = 0;
  get_jpeg_image_names("./images_yolo/", image_names);
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

    // If not do_pause, decode next JPEG image and do pre-processing
    if (!do_pause) {
      DECLARE_TVAL(loadimg);
      GET_TVAL_START(loadimg);
      decode_jpg_file(image_names[image_nr], imgView[rbuf_idx], IMAGE_W, IMAGE_H);
      GET_SHOW_TVAL_END(loadimg);
      ++image_nr;
      image_nr %= num_images;
      imgViewIdx[rbuf_idx] = rbuf_idx;
    } else {
      imgViewIdx[rbuf_idx] = imgViewIdx[(rbuf_idx ? rbuf_idx : RING_BUF_SIZE) - 1];
    }

    // to next
    rbuf_idx += 1;
    if (rbuf_idx == RING_BUF_SIZE) {
      rbuf_idx = 0;
    }
  }

  return NULL;
}

void *preproc(void*) {
  unsigned &rbuf_idx = preproc_rbuf_idx;  // alias

  while (exit_code == -1) {
    while (rbuf_idx == loadimg_rbuf_idx) {
      usleep(USLEEP_TIME);
    }


    DECLARE_TVAL(preproc);
    GET_TVAL_START(preproc);

    // If not do_pause, decode next JPEG image and do pre-processing
    cam_overlay[rbuf_idx]->convert_to_overlay_pixel_format(imgView[imgViewIdx[rbuf_idx]], IMAGE_W*IMAGE_H);
    // Pre-process the image data
    preproc_image(imgView[imgViewIdx[rbuf_idx]], imgProc[rbuf_idx], IMAGE_W, IMAGE_H, PROC_W, PROC_H,
        0.0f, 0.0f, 0.0f, 1.0f / 255.0f, true, false);

    GET_SHOW_TVAL_END(preproc);

    // to next
    rbuf_idx += 1;
    if (rbuf_idx == RING_BUF_SIZE) {
      rbuf_idx = 0;
    }
  }

  return NULL;
}

void *inference(void*) {
  unsigned &rbuf_idx = inference_rbuf_idx;  // alias

  // Initialize network object
  network.Verbose(0);
  if (!network.Initialize()) {
    exit_code = 1;
    return NULL;
  }
  if (!network.LoadWeights(FILENAME_WEIGHTS)) {
    exit_code = 1;
    return NULL;
  }
  if (!network.Commit()) {
    exit_code = 1;
    return NULL;
  }

  while (exit_code == -1) {
    while (rbuf_idx == preproc_rbuf_idx) {
      usleep(USLEEP_TIME);
    }

    DECLARE_TVAL(inference);
    GET_TVAL_START(inference);

    // Run network in HW
    memcpy(network.get_network_input_addr_cpu(), imgProc[rbuf_idx], PROC_W * PROC_H * 6);
    network.RunNetwork();

    // Handle output from HW
    network.get_final_output(net_output[rbuf_idx]);

    GET_SHOW_TVAL_END(inference);

    // to next
    rbuf_idx += 1;
    if (rbuf_idx == RING_BUF_SIZE) {
      rbuf_idx = 0;
    }
  }

  return NULL;
}

void *postproc(void*) {

  // Create background and image overlay
  COverlayRGB bg_overlay(SCREEN_W, SCREEN_H);
  bg_overlay.alloc_mem_overlay(SCREEN_W, SCREEN_H);
  bg_overlay.load_ppm_img("fpgatitle");

  // Draw background two times for front and back buffer
  const char *titles[] = {
    "CNN - Object Detection",
    "Bounding Box and Object Class detection",
  };
  for (int i = 0; i < 2; ++i) {
    bg_overlay.print_to_display(0, 0);
    print_demo_title(bg_overlay, titles);
    swap_buffer();
  }

  // Get HW module frequency
  string conv_freq;
  conv_freq = std::to_string(network.get_dv_info().conv_freq);

  unsigned &rbuf_idx = postproc_rbuf_idx;  // alias

#ifdef DMP_MEASURE_TIME
  DECLARE_TVAL(swap_buffer);
  TVAL_START(swap_buffer).tv_sec = 0;
#endif
  while (exit_code == -1) {
    while (rbuf_idx == inference_rbuf_idx) {
      usleep(USLEEP_TIME);
    }

    DECLARE_TVAL(postproc);
    GET_TVAL_START(postproc);

    // Draw bboxes
    vector<float> boxes;
    get_bboxes(net_output[rbuf_idx], boxes);
    draw_bboxes(boxes, *cam_overlay[rbuf_idx]);

    // Draw detection result to screen
    cam_overlay[rbuf_idx]->print_to_display(((SCREEN_W - IMAGE_W) / 2), 150);

    // Output HW processing times
    int conv_time_tot = network.get_conv_usec();
    print_conv_time(bg_overlay, (SCREEN_H - 100), conv_time_tot, conv_freq);

    swap_buffer();
#ifdef DMP_MEASURE_TIME
    GET_TVAL_END(swap_buffer);
    if (TVAL_START(swap_buffer).tv_sec) {
      SHOW_TIME(swap_buffer);
    }
    TVAL_START(swap_buffer).tv_sec = TVAL_END(swap_buffer).tv_sec;
    TVAL_START(swap_buffer).tv_usec = TVAL_END(swap_buffer).tv_usec;
#endif

    handle_keyboard_input(exit_code, do_pause);

    GET_SHOW_TVAL_END(postproc);

    // to next
    rbuf_idx += 1;
    if (rbuf_idx == RING_BUF_SIZE) {
      rbuf_idx = 0;
    }
    cout << endl;
  }

  return NULL;
}

int main(int argc, char **argv) {
  // Initialize FB
  if (!init_fb()) {
    cout << "init_fb() failed." << endl;
    return 1;
  }

  for(int i = 0; i < RING_BUF_SIZE; i++) {
    cam_overlay[i] = new COverlayRGB(SCREEN_W, SCREEN_H);
    cam_overlay[i]->alloc_mem_overlay(IMAGE_W, IMAGE_H);
  }

  pthread_t loadimg_th;
  pthread_t pre_th;
  pthread_t inf_th;
  pthread_t post_th;

  pthread_create(&loadimg_th, NULL, loadimg, NULL);
  pthread_create(&pre_th,     NULL, preproc, NULL);
  pthread_create(&inf_th,     NULL, inference, NULL);
  pthread_create(&post_th,    NULL, postproc, NULL);

  pthread_join(loadimg_th, NULL);
  pthread_join(pre_th,     NULL);
  pthread_join(inf_th,     NULL);
  pthread_join(post_th,    NULL);

  for(int i = 0; i < RING_BUF_SIZE; i++) {
    delete cam_overlay[i];
  }
  shutdown();

  return exit_code;
}
