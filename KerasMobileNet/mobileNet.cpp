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

#include "imagenet_1000_categories.h"

#include "util_draw.h"
#include "util_input.h"

#include "KerasMobileNet_gen.h"
CKerasMobileNet network;

#define FILENAME_WEIGHTS "KerasMobileNet_weights.bin"

using namespace std;
using namespace dmp;
using namespace util;

#define SCREEN_W (dmp::util::get_screen_width())
#define SCREEN_H (dmp::util::get_screen_height())

#define IMAGE_W 224
#define IMAGE_H 224

// Frame counter
uint32_t fc = 0;

std::vector<std::string> catstr_vec(categories, categories + 1000);

uint32_t imgView[IMAGE_W * IMAGE_H];
__fp16 imgProc[IMAGE_W * IMAGE_H * 3];

// 2ND THREAD FOR HW CONTROL

volatile uint64_t sync_cnn_in = 0;
volatile uint64_t sync_cnn_out = 0;

volatile int conv_time_tot = 0;

volatile bool g_should_stop = false;

void* hwacc_thread_func(void* targ) {
  while (!g_should_stop) {
    if (sync_cnn_in == sync_cnn_out) {
      usleep(1000);  // sleep 1 ms
      continue;
    }

    network.RunNetwork();

    conv_time_tot = network.get_conv_usec();

    sync_cnn_out++;
  }
  return NULL;
}

int main(int argc, char** argv) {
  if (!dmp::util::init_fb()) {
    fprintf(stderr, "dmp::util::init_fb() failed\n");
    return 1;
  }

  const std::string input_image_path = "./images/";
  const std::vector<std::string> input_image_suffix = {".jpg", ".jpeg", ".JPG",
                                                       ".JPEG"};

  vector<string> image_names =
      dmp::util::get_input_image_names(input_image_path, input_image_suffix);
  int num_images = image_names.size();
  if (num_images == 0) {
    cout << "No input images." << endl;
    return 1;
  }

  std::vector<float> networkOutput;

  int my_number = 0;
  bool has_democonf = false;
  if (argc >= 2) {
    my_number = atoi(argv[1]);
    has_democonf = true;
  }
  vector<pair<int, string> > democonf;
  int democonf_sel = 0;  // currencly selected element index (0 .. num-1)
  int democonf_num = 0;  // number of elements in democonf
  int democonf_string_max = -1;
  bool democonf_display = false;
  if (has_democonf) {
    ifstream democonf_file("democonf.txt");
    int count = 0;
    int c_int;
    string c_string;
    while (democonf_file >> c_int >> c_string) {
      democonf.push_back(make_pair(c_int, c_string));
      int c_string_size = c_string.size();
      if (c_string_size > democonf_string_max)
        democonf_string_max = c_string_size;
      if (c_int == my_number) democonf_sel = count;
      count++;
    }
    democonf_num = count;
  }

  COverlayRGB bg_overlay(SCREEN_W, SCREEN_H);
  bg_overlay.alloc_mem_overlay(SCREEN_W, SCREEN_H);
  bg_overlay.load_ppm_img("fpgatitle_mobileNet");
  COverlayRGB overlay_input(SCREEN_W, SCREEN_H);
  overlay_input.alloc_mem_overlay(IMAGE_W, IMAGE_H);

  network.Verbose(0);
  if (!network.Initialize()) {
    return -1;
  }
  if (!network.LoadWeights(FILENAME_WEIGHTS)) {
    return -1;
  }

  string conv_freq, fc_freq;
  conv_freq = std::to_string(network.get_dv_info().conv_freq);
  fc_freq = std::to_string(network.get_dv_info().fc_freq);

  void* ddr_buf_a_cpu = network.get_network_input_addr_cpu();

  int exit_code = -1;

  int image_nr = 0;

  bool pause = false;

  pthread_t hwacc_thread;
  pthread_create(&hwacc_thread, NULL, hwacc_thread_func, NULL);

  while (exit_code == -1) {
    // Static Images
    if (fc < 2) {
      bg_overlay.print_to_display(0, 0);
      dmp::util::swap_buffer();
      fc++;  // Frame Counter
      continue;
    }

    // HW processing times
    if (conv_time_tot != 0) {
      string text = COverlayRGB::convert_time_to_text("Convolution (" + conv_freq + " MHz HW ACC)      : ", conv_time_tot);
      unsigned text_size = 14;

      unsigned w = 0;
      unsigned h = 0;
      COverlayRGB::calculate_boundary_text(text, text_size, w, h);

      int x = ((SCREEN_W - w) / 2);
      int y = 7*SCREEN_H/8;

      COverlayRGB overlay_time(SCREEN_W, SCREEN_H);
      overlay_time.alloc_mem_overlay(w, h);
      overlay_time.copy_overlay(bg_overlay,x, y);
      overlay_time.set_text(0, 0, text, text_size, 0x00f4419d);
      overlay_time.print_to_display(x, y);

      text = COverlayRGB::convert_time_to_text("Total Processing Time               : ", conv_time_tot);
      COverlayRGB::calculate_boundary_text(text, text_size, w, h);

      y = 7*SCREEN_H/8 + 28;

      COverlayRGB overlay_processingtime(SCREEN_W, SCREEN_H);
      overlay_processingtime.alloc_mem_overlay(w, h);
      overlay_processingtime.copy_overlay(bg_overlay,x, y);
      overlay_processingtime.set_text(0, 0, text, text_size, 0x00f4419d);
      overlay_processingtime.print_to_display(x, y);
    }

    if (sync_cnn_out == sync_cnn_in) {
      if (sync_cnn_out != 0) {
        network.get_final_output(networkOutput);

        int x = (SCREEN_W - IMAGE_W) / 2;
        int y = (293 - 128) + 20;
        overlay_input.print_to_display(x, y);

        x = (SCREEN_W / 5);
        y = (293 - 128) + IMAGE_W + 80;

        print_result(catstr_vec, x, y,
                    dmp::util::catrank(&networkOutput.front()), bg_overlay);

        dmp::util::swap_buffer();
        fc++;

        int key = getchar();
        switch (key) {
          case 27:  // ESC
          {
            int next_key = getchar();
            switch (next_key) {
              case 91:  // there are more value to read: UP/DOWN/LEFT/RIGHT pressed
                break;
              case 79:  // F3 pressed
                break;
              default:  // nothing special was pressed, will exit
                exit_code = 0;
                break;
            }
            break;
          }
          case '3':  // exit demo with exit code of selected next demo
            if (has_democonf) {
              int sel_num = democonf[democonf_sel].first;
              if (sel_num != my_number) {
                exit_code = sel_num;
              }
              else {
                exit_code = my_number;
              }
            }
            break;

          case '2':  // cycle through demo configuratom list
            if (has_democonf) {
              democonf_display = true;
              if (democonf_sel == democonf_num - 1) {
                democonf_sel = 0;
              }
              else {
                democonf_sel++;
              }
            }
            break;

          case '1':
          case 32:  // SPACE
            pause = !pause;
            break;
        }
      }

      if (!pause) {
        dmp::util::decode_jpg_file(input_image_path + image_names[image_nr],
                                   imgView, IMAGE_W, IMAGE_H);
        overlay_input.convert_to_overlay_pixel_format(imgView, IMAGE_W*IMAGE_H);
        dmp::util::preproc_image(imgView, imgProc, IMAGE_W, IMAGE_H, -127.5,
                                 -127.5, -127.5, 0.0078431, true);

        if (image_nr == num_images - 1) {
          image_nr = 0;
        } else {
          image_nr++;
        }
      }

      memcpy(ddr_buf_a_cpu, (void*)imgProc, IMAGE_W * IMAGE_H * 3 * 2);

      if (exit_code == -1) {  // do not start new HW ACC runs if about to exit...
        sync_cnn_in++;
      }
    }

    if (democonf_display) {
      string s = democonf[democonf_sel].second;
      s.resize(democonf_string_max, ' ');
      unsigned text_size = 12;
      unsigned w = 0;
      unsigned h = 0;
      COverlayRGB::calculate_boundary_text(s, text_size, w, h);

      int x = 7*SCREEN_W / 8;
      int y = 7*SCREEN_H / 8;

      COverlayRGB overlay_democonf(SCREEN_W, SCREEN_H);
      overlay_democonf.alloc_mem_overlay(w, h);
      overlay_democonf.copy_overlay(bg_overlay,x, y);
      overlay_democonf.set_text(0, 0, s, text_size, 0x00f4419d);
      overlay_democonf.print_to_display(x, y);
    }
  }

  g_should_stop = true;
  pthread_join(hwacc_thread, NULL);

  dmp::util::shutdown();

  return exit_code;
}
