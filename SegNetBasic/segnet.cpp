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

#include "SegNetBasic_gen.h"
#include "util_draw.h"
#include "util_input.h"
#include "demo_common.h"

using namespace std;
using namespace dmp;
using namespace util;

#define SCREEN_W (get_screen_width())
#define SCREEN_H (get_screen_height())

#define IMAGE_W 320
#define IMAGE_H 240
#define IMAGE_NUM 367

#define FILENAME_WEIGHTS "SegNetBasic_weights.bin"

// Define CNN network model object
CSegNetBasic network;

// Buffer for pre-processed image data
uint16_t imgProc[IMAGE_W * IMAGE_H * 3];

// Post-processing functions, defined in segnet_post.cpp
void convertimage(uint16_t *imgProc, COverlayRGB& overlay);
void visualize(void *netoutCPU, COverlayRGB& overlay);

int main(int argc, char **argv) {
  // Initialize FB
  if (!init_fb()) {
    fprintf(stderr, "init_fb() failed\n");
    return 1;
  }

  // Open input images
  const char input_image_file[] = "segnet_image.bin";
  FILE *fimg = fopen(input_image_file, "rb");
  if (!fimg) {
    fprintf(stderr, "Could not open segnet_image.bin for reading\n");
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

  // Get HW module frequency
  string conv_freq, fc_freq;
  conv_freq = std::to_string(network.get_dv_info().conv_freq);
  fc_freq = std::to_string(network.get_dv_info().fc_freq);

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

  // Get FPGA input and output buffer
  void *ddr_buf_a_cpu = network.get_network_input_addr_cpu();
  void *ddr_buf_b_cpu = network.get_io_ptr() + network.get_layer(15).output_offs;

  int exit_code = -1;
  int image_nr = 0;
  bool pause = false;
  vector<float> networkOutput;
  // Enter main loop
  while (exit_code == -1) {
    // If not pause, get next image and pre-processed image
    if (!pause) {
      // Get pre-processed image data
      fseek(fimg, IMAGE_W * IMAGE_H * 6 * image_nr, SEEK_SET);
      if (fread(imgProc, 2, IMAGE_W * IMAGE_H * 3, fimg) != IMAGE_W * IMAGE_H * 3) {
        fprintf(stderr, "WARNING: Incomplete fread() at line %d of file %s\n", __LINE__, __FILE__);
        fflush(stderr);
      }
      ++image_nr;
      image_nr %= IMAGE_NUM;
    }

    // Run network in HW
    memcpy(ddr_buf_a_cpu, (void *)imgProc, IMAGE_W * IMAGE_H * 6);
    network.RunNetwork();

    // Handle output and draw results
    convertimage(imgProc, overlay_movie);
    overlay_movie.print_to_display((SCREEN_W / 2 - IMAGE_W), 185);
    visualize(ddr_buf_b_cpu, overlay_result);
    overlay_movie.blend_from(overlay_result, 0.5);
    overlay_movie.print_to_display((SCREEN_W / 2), 185);

    // Output HW processing times
    int conv_time_tot = network.get_conv_usec();
    print_conv_time(bg_overlay, 3 * SCREEN_H / 4, conv_time_tot, conv_freq);

    swap_buffer();

    handle_keyboard_input(exit_code, pause);
  }

  shutdown();

  return exit_code;
}
