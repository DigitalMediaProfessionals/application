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
CSegNetBasic network;

#define FILENAME_WEIGHTS "SegNetBasic_weights.bin"

using namespace std;
using namespace dmp;
using namespace util;

#define SCREEN_W (dmp::util::get_screen_width())
#define SCREEN_H (dmp::util::get_screen_height())

#define IMAGE_W 320
#define IMAGE_H 240
#define IMAGE_NUM 367
#define CLASS_NUM 12

uint32_t imgView[IMAGE_W * IMAGE_H];
uint16_t imgProc[IMAGE_W * IMAGE_H * 3];

uint32_t fc = 0;

// 2ND THREAD FOR HW CONTROL

volatile uint64_t sync_cnn_in = 0;
volatile uint64_t sync_cnn_out = 0;

volatile int conv_time_tot = 0;
volatile int fc_time_tot = 0;

volatile bool g_should_stop = false;

#if 0
const uint32_t class_color[] = {
  0x80FFFF00,		//Sky
  0x80808000,		//Bulding
  0xC0C08000,		//Pole
  0x80408000,		//Road
  0x4030C000,		//Pavement
  0x00C00000,		//Tree
  0xC0808000,		//Sign_symbol
  0x40408000,		//Fence
  0xC0008000,		//Car
  0x40400000,		//Pedestrian
  0x0080C000,		//Bicyclist
  0x00000000,		//Unlabelled
};
#else
const uint32_t class_color[] = {
    0x40808000,  // Sky
    0x40404000,  // Bulding
    0x60604000,  // Pole
    0x40204000,  // Road
    0x40204000,  // Pavement
    0x00600000,  // Tree
    0x60404000,  // Sign_symbol
    0x20204000,  // Fence
    0x60004000,  // Car
    0x00406000,  // Pedestrian
    0x00406000,  // Bicyclist
    0x00000000,  // Unlabelled
};
#endif

void convertimage(uint16_t *imgProc, COverlayRGB& overlay) {
  unsigned char c[3];
  uint16_t t;
  for (int y = 0; y < IMAGE_H; y++) {
    for (int x = 0; x < IMAGE_W; x++) {
      for (int i = 0; i < 3; i++) {
        t = imgProc[(x * IMAGE_H + y) * 3 + i];
        c[i] = ((t & 0x3FF) + 0x400) >> (26 - ((t & 0xFC00) >> 10));
      }
      overlay.set_pixel(x, y, c[2]<<1, c[1]<<1, c[0]<<1);
    }
  }
}

void visualize(void *netoutCPU, COverlayRGB& overlay) {
  short *networkOutput = reinterpret_cast<short *>(netoutCPU);
  for (int y = 0; y < IMAGE_H; y++) {
    for (int x = 0; x < IMAGE_W; x++) {
      int maxIndex = 0;
      short maxVal = networkOutput[(y * IMAGE_W + x) * CLASS_NUM];
      for (int i = 1; i < CLASS_NUM; i++) {
        if (networkOutput[(y * IMAGE_W + x) * CLASS_NUM + i] > maxVal) {
          maxVal = networkOutput[(y * IMAGE_W + x) * CLASS_NUM + i];
          maxIndex = i;
        }
      }
      overlay.set_pixel(x, y, (class_color[maxIndex]>>24), 
          ((class_color[maxIndex] & 0x00ff0000)>>16),
    		  ((class_color[maxIndex] & 0x0000ff00)>>8));
    }
  }
}

void *hwacc_thread_func(void *targ) {
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

void print_demo_title(COverlayRGB &bg_overlay)
{
  unsigned text_size = 30;
  string font_file = "font/NotoSerif-Black.ttf";
  string text = "CNN - SegNet Basic";
  unsigned w = 0;
  unsigned h = 0;
  
  COverlayRGB::calculate_boundary_text_with_font(font_file, text, text_size, w, h);
  int x = ((SCREEN_W - w) / 2);
  int y = 25;
  COverlayRGB bg_text(SCREEN_W, SCREEN_H);
  bg_text.alloc_mem_overlay(w, h);
  bg_text.copy_overlay(bg_overlay, x, y);
  bg_text.set_text_with_font(font_file, text, 0, 3*h/4, text_size, 0x00ffffff);
  bg_text.print_to_display(x, y);

  
  text = "FPGA Demonstration";
  COverlayRGB::calculate_boundary_text_with_font(font_file, text, text_size, w, h);
  x = ((SCREEN_W - w) / 2);
  y = 65;
  bg_text.delete_overlay();
  bg_text.alloc_mem_overlay(w, h);
  bg_text.copy_overlay(bg_overlay, x, y);
  bg_text.set_text_with_font(font_file, text, 0, 3*h/4, text_size, 0x00ffffff);
  bg_text.print_to_display(x, y);

  text_size = 11;
  text = "Copyright 2018. Digital Media Professionals Inc.";
  COverlayRGB::calculate_boundary_text_with_font(font_file, text, text_size, w, h);
  x = 5;
  y = SCREEN_H - 20;
  bg_text.delete_overlay();
  bg_text.alloc_mem_overlay(w, h);
  bg_text.copy_overlay(bg_overlay, x, y);
  bg_text.set_text_with_font(font_file, text, 0, 3*h/4, text_size, 0x00ffffff);
  bg_text.print_to_display(x, y);
}

int main(int argc, char **argv) {
  if (!dmp::util::init_fb()) {
    fprintf(stderr, "dmp::util::init_fb() failed\n");
    return 1;
  }

  const char input_image_file[] = "segnet_image.bin";
  FILE *fimg = fopen(input_image_file, "rb");
  if (!fimg) {
    fprintf(stderr, "Could not open segnet_image.bin for reading\n");
    return 1;
  }

  vector<float> networkOutput;

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
  bg_overlay.load_ppm_img("fpgatitle");
  COverlayRGB overlay_movie(SCREEN_W, SCREEN_H);
  overlay_movie.alloc_mem_overlay(IMAGE_W, IMAGE_H);
  COverlayRGB overlay_result(SCREEN_W, SCREEN_H);
  overlay_result.alloc_mem_overlay(IMAGE_W, IMAGE_H);

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

  string conv_freq, fc_freq;
  conv_freq = std::to_string(network.get_dv_info().conv_freq);
  fc_freq = std::to_string(network.get_dv_info().fc_freq);

  void *ddr_buf_a_cpu = network.get_network_input_addr_cpu();
  void *ddr_buf_b_cpu = network.get_io_ptr() + network.get_layer(15).output_offs;

  int exit_code = -1;

  int image_nr = 0;

  bool pause = false;

  pthread_t hwacc_thread;
  pthread_create(&hwacc_thread, NULL, hwacc_thread_func, NULL);

  while (exit_code == -1) {
    // Static Images
    if (fc < 2) {
      bg_overlay.print_to_display(0, 0);
      print_demo_title(bg_overlay);
      dmp::util::swap_buffer();
      fc++;  // Frame Counter
      continue;
    }

    // HW processing times
    if (conv_time_tot != 0) {
      string text = COverlayRGB::convert_time_to_text("Convolution (" + 
                            conv_freq + " MHz HW ACC)     : ", conv_time_tot);
      unsigned text_size = 14;

      unsigned w = 0;
      unsigned h = 0;
      COverlayRGB::calculate_boundary_text(text, text_size, w, h);

      int x = ((SCREEN_W - w) / 2);
      int y = 3*SCREEN_H/4;

      COverlayRGB overlay_time(SCREEN_W, SCREEN_H);
      overlay_time.alloc_mem_overlay(w, h);
      overlay_time.copy_overlay(bg_overlay,x, y);
      overlay_time.set_text(0, 0, text, text_size, 0x00f4419d);
      overlay_time.print_to_display(x, y);
    }

    if (sync_cnn_out == sync_cnn_in) {
      if (sync_cnn_out != 0) {
        // network.get_final_output(networkOutput);
        convertimage(imgProc, overlay_movie);
        int x = (SCREEN_W / 2 - IMAGE_W);
        int y = (293 - 128) + 20;
        overlay_movie.print_to_display(x, y);

        visualize(ddr_buf_b_cpu, overlay_result);
        overlay_movie.blend_from(overlay_result, 0.5);

        x = (SCREEN_W / 2);
        y = (293 - 128) + 20;
        overlay_movie.print_to_display(x, y);
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
        fseek(fimg, IMAGE_W * IMAGE_H * 6 * image_nr, SEEK_SET);
        if (fread(imgProc, 2, IMAGE_W * IMAGE_H * 3, fimg) != IMAGE_W * IMAGE_H * 3) {
          fprintf(stderr, "WARNING: Incomplete fread() at line %d of file %s\n", __LINE__, __FILE__);
          fflush(stderr);
        }
        if (image_nr == IMAGE_NUM - 1) {
          image_nr = 0;
        } else {
          image_nr++;
        }
      }

      // Copy image to FPGA memory
      memcpy(ddr_buf_a_cpu, (void *)imgProc, IMAGE_W * IMAGE_H * 3 * 2);

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
