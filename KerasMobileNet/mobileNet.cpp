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

#include "KerasMobileNet_gen.h"
#include "util_draw.h"
#include "util_input.h"
#include "demo_common.h"
#include "imagenet_1000_categories.h"

using namespace std;
using namespace dmp;
using namespace util;

#define SCREEN_W (get_screen_width())
#define SCREEN_H (get_screen_height())

#define IMAGE_W 224
#define IMAGE_H 224

#ifdef __aarch64__
#define CIMAGE_W 640
#define CIMAGE_H 480
#else
#define CIMAGE_W 320
#define CIMAGE_H 240
#endif

#define FILENAME_WEIGHTS "KerasMobileNet_weights.bin"

// Define CNN network model object
CKerasMobileNet network;

// Categories strings
std::vector<std::string> catstr_vec(categories, categories + 1000);

// Buffer for decoded image data
uint32_t imgView[IMAGE_W * IMAGE_H];
// Buffer for pre-processed image data
__fp16 imgProc[IMAGE_W * IMAGE_H * 3];

int main(int argc, char** argv) {
  bool use_camera = false;
  vector<string> image_names;
  int num_images = 0;

  // Determine if use camera input
  if (argc > 1 && strcmp(argv[1], "-c") == 0)
    use_camera = true;

  // Initialize FB
  if (!init_fb()) {
    cout << "init_fb() failed." << endl;
    return 1;
  }

  if (use_camera) {
    // Initialize WebCam
    if (open_cam(CIMAGE_W, CIMAGE_H, 20)) {
      return -1;
    }
  } else {
    // Get input images filenames
    get_jpeg_image_names("./images/", image_names);
    num_images = image_names.size();
    if (num_images == 0) {
      cout << "No input images." << endl;
      return 1;
    }
  }

  // Initialize network object
  network.Verbose(0);
  if (!network.Initialize()) {
    return -1;
  }
  if (!network.LoadWeights(FILENAME_WEIGHTS)) {
    return -1;
  }
  if (!network.SetConvertPolicy(CP_MINUS_127_5_DIV_128, true)) {
    return -1;
  }
  if (!network.Commit()) {
    return -1;
  }

  // Get HW module frequency
  string conv_freq, fc_freq;
  conv_freq = std::to_string(network.get_dv_info().conv_freq);
  fc_freq = std::to_string(network.get_dv_info().fc_freq);

  // Create background and image overlay
  COverlayRGB bg_overlay(SCREEN_W, SCREEN_H);
  bg_overlay.alloc_mem_overlay(SCREEN_W, SCREEN_H);
  bg_overlay.load_ppm_img("fpgatitle");
  COverlayRGB overlay_input(SCREEN_W, SCREEN_H);
  overlay_input.alloc_mem_overlay(IMAGE_W, IMAGE_H);

  // Draw background two times for front and back buffer
  const char *titles[] = {
    "CNN - MobileNet",
    "Object Class Identification",
  };
  for (int i = 0; i < 2; ++i) {
    bg_overlay.print_to_display(0, 0);
    print_demo_title(bg_overlay, titles);
    swap_buffer();
  }

  int exit_code = -1;
  int image_nr = 0;
  bool pause = false;
  std::vector<float> network_output;
  // Enter main loop
  while (exit_code == -1) {
    if (!pause) {
      if (use_camera) {
        // If not pause, get next image from WebCam and do pre-processing
        if (capture_cam(imgView, CIMAGE_W, CIMAGE_H, (CIMAGE_W - IMAGE_W) >> 1,
                        (CIMAGE_H - IMAGE_H) >> 1, IMAGE_W, IMAGE_H)) {
          break;
        }
      } else {
        // If not pause, decode next JPEG image and do pre-processing
        decode_jpg_file(image_names[image_nr], imgView, IMAGE_W, IMAGE_H);
        ++image_nr;
        image_nr %= num_images;
      }
      overlay_input.convert_to_overlay_pixel_format(imgView, IMAGE_W * IMAGE_H);
      //preproc_image(imgView, imgProc, IMAGE_W, IMAGE_H, -127.5, -127.5, -127.5,
      //               0.0078431, false);
    }

    // Run network in HW
    uint8_t *input_buf = (uint8_t*)network.get_network_input_addr_cpu();
    uint8_t *u8_img = (uint8_t*)imgView;
    for (int y = 0; y < IMAGE_H; ++y) {
      for (int x = 0; x < IMAGE_W; ++x) {
        memcpy(input_buf + (y * IMAGE_W + x) * 3, u8_img + (y * IMAGE_W + x) * 4 + 1, 3);
      }
    }
    //memcpy(network.get_network_input_addr_cpu(), imgView, IMAGE_W * IMAGE_H * 3);
    network.RunNetwork();

    // Handle output from HW
    network.get_final_output(network_output);
    overlay_input.print_to_display((SCREEN_W - IMAGE_W) / 2, 185);

    // Print identification result to screen
    // print_result and catrank functions are defined in util_draw.cpp
    print_result(catstr_vec, (SCREEN_W / 5), IMAGE_W + 245,
                 catrank(&network_output.front()), bg_overlay);

    // Output HW processing times
    int conv_time_tot = network.get_conv_usec();
    print_conv_time(bg_overlay, 7 * SCREEN_H / 8, conv_time_tot, conv_freq);

    swap_buffer();

    handle_keyboard_input(exit_code, pause);
  }

  shutdown();

  return exit_code;
}
