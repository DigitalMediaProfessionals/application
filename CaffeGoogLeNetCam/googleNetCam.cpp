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

#include "CaffeGoogLeNet_gen.h"
#include "util_draw.h"
#include "util_input.h"
CCaffeGoogLeNet network;

#define FILENAME_WEIGHTS "CaffeGoogLeNet_weights.bin"

using namespace std;

#define SCREEN_W (dmp::util::get_screen_width())
#define SCREEN_H (dmp::util::get_screen_height())

#define CAM_CAPTURE_W 640
#define CAM_CAPTURE_H 480

#define IMAGE_W 224
#define IMAGE_H 224

#define TEXT_XOFS (((SCREEN_W - IMAGE_W) / 2) / 24 + 4)  // 8x8 characters
#define TEXT_YOFS ((512 + 48) / 8 + 2 + 3 + 2)           // 8x8 characters

#define BARS_XOFS (512)       // pixels
#define BARS_YOFS (512 + 48)  // pixels

std::vector<std::string> catstr_vec(categories, categories + 1000);

uint32_t fc = 0;

uint32_t imgView[IMAGE_W * IMAGE_H];
__fp16 imgProc[IMAGE_W * IMAGE_H * 3];

// 2ND THREAD FOR HW CONTROL

volatile uint64_t sync_cnn_in = 0;
volatile uint64_t sync_cnn_out = 0;

volatile int conv_time_tot = 0;
volatile int fc_time_tot = 0;

volatile bool g_should_stop = false;

void* hwacc_thread_func(void* targ) {
  while (!g_should_stop) {
    if (sync_cnn_in == sync_cnn_out) {
      usleep(1000);  // sleep 1 ms
      continue;
    }

    network.RunNetwork();

    conv_time_tot = network.get_conv_usec();
    fc_time_tot = network.get_fc_usec();

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

  dmp::util::open_cam(CAM_CAPTURE_W, CAM_CAPTURE_H,
                      20);  // fps = 0 means as fast as possible

  dmp::util::set_inputImageSize(IMAGE_W, IMAGE_H);
  dmp::util::createBackgroundImage();

  if (!dmp::util::load_background_image("fpgatitle_googleNet.ppm")) return 1;

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

  bool pause = false;

  pthread_t hwacc_thread;
  pthread_create(&hwacc_thread, NULL, hwacc_thread_func, NULL);

  while (exit_code == -1) {
    // Static Images
    if (fc < 2) {
      dmp::util::print_background_image_toDisplay();
    }

    // HW processing times
    if (conv_time_tot != 0 && fc_time_tot != 0) {
      dmp::util::print_time_toDisplay(
          TEXT_XOFS, TEXT_YOFS + 0,
          "Convolution (" + conv_freq + " MHz HW ACC)     : ", conv_time_tot,
          9999, 0xff00ff00, 0x00000001);
      dmp::util::print_time_toDisplay(
          TEXT_XOFS, TEXT_YOFS + 2,
          "Fully Connected (" + fc_freq + " MHz HW ACC) : ", fc_time_tot, 9999,
          0xff00ff00, 0x00000001);
      dmp::util::print_time_toDisplay(
          TEXT_XOFS, TEXT_YOFS + 4,
          "Total Processing Time           : ", conv_time_tot + fc_time_tot,
          9999, 0xffff0000, 0x00000001);
    }

    if (!pause) {
      dmp::util::capture_cam(imgView, CAM_CAPTURE_W, CAM_CAPTURE_H,
                             (CAM_CAPTURE_W - IMAGE_W) / 2,
                             (CAM_CAPTURE_H - IMAGE_H) / 2, IMAGE_W, IMAGE_H);
    }
    dmp::util::print_image_toDisplay((SCREEN_W - IMAGE_W) / 2, 185, imgView);

    if (sync_cnn_out == sync_cnn_in) {
      if (sync_cnn_out != 0) network.get_final_output(networkOutput);

      // Preprocess and copy image to FPGA memory
      dmp::util::preproc_image(imgView, imgProc, IMAGE_W, IMAGE_H, -128.0,
                               -128.0, -128.0, 1.0, true);
      memcpy(ddr_buf_a_cpu, (void*)imgProc, IMAGE_W * IMAGE_H * 3 * 2);

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

      if (exit_code == -1) {  // do not start new HW ACC runs if about to exit...
        sync_cnn_in++;
      }
    }

    if (sync_cnn_out != 0)
      dmp::util::print_result(catstr_vec, TEXT_XOFS, TEXT_YOFS - 13, dmp::util::catrank(&networkOutput.front()),
                   0x88ff8800, 0x00ff0000, 0x00000001);

    if (democonf_display) {
      string s = democonf[democonf_sel].second;
      s.resize(democonf_string_max, ' ');
      dmp::util::print8x8_toDisplay((SCREEN_W / 8 - democonf_string_max) / 2,
                                    SCREEN_H / 8 - 1, s, 0x00ff0000,
                                    0x00000001);
    }

    dmp::util::swap_buffer();
    fc++;
  }

  g_should_stop = true;
  pthread_join(hwacc_thread, NULL);

  dmp::util::shutdown();
  dmp::util::close_cam();

  return exit_code;
}
