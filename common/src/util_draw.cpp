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

#include "util_draw.h"
#include "../include/font/Arial_round_16x24.h"
#include "../include/font/GroteskBold24x48.h"
#include "../include/font/font8x8_basic.h"
#include "../include/font/font8x8_ext_latin.h"
#include "../include/font/hallfetica_normal.h"
#include "hw_module_manager.h"

#include <math.h>

using namespace dmp;
using namespace util;

namespace dmp {
namespace util {

unsigned int* background_image = NULL;
unsigned int* textbuf8 = NULL;   //[SCREEN_W*8];
unsigned int* textbuf16 = NULL;  //[SCREEN_W*16];
unsigned int* barbuf = NULL;

unsigned int* imgTmp;

static unsigned int SCREEN_W = 0;
static unsigned int SCREEN_H = 0;

static unsigned int IMAGE_W = 0;
static unsigned int IMAGE_H = 0;

void set_inputImageSize(unsigned w, unsigned int h) {
  IMAGE_W = w;
  IMAGE_H = h;
}

void createBackgroundImage(int screen_w, int screen_h) {
  background_image = new unsigned int[screen_w * screen_h];
  SCREEN_W = screen_w;
  SCREEN_H = screen_h;

  textbuf8 = new unsigned int[SCREEN_W * 8];
  textbuf16 = new unsigned int[SCREEN_W * 16];
  barbuf = new unsigned int[SCREEN_W];

  imgTmp = new unsigned int[IMAGE_W * IMAGE_H];
}

bool load_background_image(std::string filename) {
  char px[3];

  std::ifstream dfs(filename.c_str());  //"fpgatitle_yolo.ppm");
  if (!dfs.is_open()) {
    std::cout << "Failed to open backgound image file." << std::endl;
    return false;
  } else {
    for (unsigned int i = 0; i < 54 - 15; i++) dfs.read((char*)px, 1);
    for (unsigned int j = 0; j < SCREEN_H; j++) {
      for (unsigned int i = 0; i < SCREEN_W; i++) {
        dfs.read((char*)px, 3);
        background_image[j * SCREEN_W + i] =
            (px[0] << 24) | (px[1] << 16) | (px[2] << 8);
      }
    }
    dfs.close();
    return true;
  }
}

void deleteBackgroundImage() {
  if (background_image) delete background_image;
  if (textbuf8) delete textbuf8;
  if (textbuf16) delete textbuf16;
  if (barbuf) delete barbuf;
  if (imgTmp) delete imgTmp;
}

int string2bitmap(std::string s, unsigned int* b, unsigned int fcol,
                  unsigned int bcol, int x, int y) {
  int n = 0;
  while (s[n]) {
    char c = s[n];
    unsigned int* a = b;
    for (int i = 0; i < 8; i++) {
      char bits = c < 0xA0 ? font8x8_basic[short(c)][i]
                           : font8x8_ext_latin[short(c - 0xA0)][i];
      for (int j = 0; j < 8; j++) {
        *a = (bits & 0x1)
                 ? fcol
                 : ((bcol & 0x1) ? (background_image[SCREEN_W * (8 * y + i) +
                                                     (8 * (x + n) + j)])
                                 : bcol);
        a++;
        bits = bits >> 1;
      }
      a += SCREEN_W - 8;
    }
    b += 8;
    n++;
  }
  return n;
}

int string2bitmap_xy(std::string s, unsigned int* b, unsigned int fcol,
                     unsigned int bcol, int x, int y) {
  int n = 0;
  while (s[n]) {
    char c = s[n];
    unsigned int* a = b;
    for (int i = 0; i < 8; i++) {
      char bits = c < 0xA0 ? font8x8_basic[short(c)][i]
                           : font8x8_ext_latin[short(c - 0xA0)][i];
      for (int j = 0; j < 8; j++) {
        *a = (bits & 0x1) ? fcol : ((bcol & 0x1)
                                        ? (background_image[SCREEN_W * (y + i) +
                                                            ((x + 8 * n) + j)])
                                        : bcol);
        a++;
        bits = bits >> 1;
      }
      a += SCREEN_W - 8;
    }
    b += 8;
    n++;
  }
  return n;
}

int string2bitmap16x16(std::string s, unsigned int* b, unsigned int fcol,
                       unsigned int bcol, int x, int y) {
  int n = 0;
  while (s[n]) {
    unsigned short c = (unsigned short)(s[n]) - 0x20;
    unsigned int* a = b;
    for (int i = 0; i < 16; i++) {
      unsigned short bits = font16x16[16 * 2 * c + 2 * i] << 8;
      bits = bits | font16x16[16 * 2 * c + 2 * i + 1];
      for (int j = 0; j < 16; j++) {
        *a = (bits & 0x8000)
                 ? fcol
                 : ((bcol & 0x1) ? (background_image[SCREEN_W * (8 * y + i) +
                                                     (8 * (x + 2 * n) + j)])
                                 : bcol);
        a++;
        bits = bits << 1;
      }
      a += SCREEN_W - 16;
    }
    b += 16;
    n++;
  }
  return n;
}

void print16x16_toDisplay(int x, int y, std::string s, unsigned int fcol,
                          unsigned int bcol) {
  unsigned int addr = dmp::modules::get_iomap_ddr() + dmp::modules::get_fbA();
  int n = string2bitmap16x16(s, textbuf16, fcol, bcol, x, y);
  for (int i = 0; i < 16; i++)
    memcpy((void*)(addr + x * 8 * 4 + (y * 8 + i) * SCREEN_W * 4),
           (void*)(textbuf16 + i * SCREEN_W), 2 * n * 8 * 4);
}

void print16x24_toDisplay(int x, int y, std::string s, unsigned int fcol,
                          unsigned int bcol) {
  unsigned int addr = dmp::modules::get_iomap_ddr() + dmp::modules::get_fbA();
  unsigned int textbuf[SCREEN_W * 24];

  int n = string2bitmap16x24(s, textbuf, fcol, bcol, x, y);

  for (int i = 0; i < 24; i++)
    memcpy((void*)(addr + 2 * x * 8 * 4 + (3 * y * 8 + i) * SCREEN_W * 4),
           (void*)(textbuf + i * SCREEN_W), 2 * n * 8 * 4);
}

void print8x8_toDisplay(int x, int y, std::string s, unsigned int fcol,
                        unsigned int bcol) {
  unsigned int addr = dmp::modules::get_iomap_ddr() + dmp::modules::get_fbA();
  int n = string2bitmap(s, textbuf8, fcol, bcol, x, y);
  for (int i = 0; i < 8; i++)
    memcpy((void*)(addr + x * 8 * 4 + (y * 8 + i) * SCREEN_W * 4),
           (void*)(textbuf8 + i * 8 * (SCREEN_W / 8)), n * 8 * 4);
}

void print24x48_toDisplay(int x, int y, std::string s, unsigned int fcol,
                          unsigned int bcol) {
  unsigned int addr = dmp::modules::get_iomap_ddr() + dmp::modules::get_fbA();
  unsigned int textbuf[SCREEN_W * 48];

  int n = string2bitmap24x48(s, textbuf, fcol, bcol, x, y);

  for (int i = 0; i < 48; i++)
    memcpy((void*)(addr + x * 8 * 4 + (y * 8 + i) * SCREEN_W * 4),
           (void*)(textbuf + i * SCREEN_W), 3 * n * 8 * 4);
}

void print_time_toDisplay(int x, int y, std::string label, long int t,
                          long int t_max, unsigned int fcol,
                          unsigned int bcol) {
  std::stringstream ss;
  std::string s;
  //  if ((t <= t_max) && (t >= 0)) {
  if (t >= 0) {
    ss.str("");
    ss << std::fixed << std::setprecision(3) << (t / 1000.0) << " ms";
    s = label + ss.str();
    print16x16_toDisplay(x, y, s, fcol, bcol);
  }
}

void print_background_image_toDisplay() {
  unsigned int addr = dmp::modules::get_iomap_ddr() + dmp::modules::get_fbA();
  for (unsigned int i = 0; i < SCREEN_H; i++) {  // height
    memcpy((void*)(addr + i * SCREEN_W * 4),
           (void*)(background_image + i * SCREEN_W), SCREEN_W * 4);
  }
}

void print_image_toDisplay(int x, int y, unsigned int* img, int crop_left) {
  unsigned int addr = dmp::modules::get_iomap_ddr() + dmp::modules::get_fbA();

  /*
  for (int i = 0; i < IMAGE_W * IMAGE_H; i++) {
      unsigned int px = img[i];
      unsigned char r, g, b, a;
      r = px & 0xff;
      g = (px >> 8) & 0xff;
      b = (px >> 16) & 0xff;
      a = (px >> 24) & 0xff;
      imgTmp[i] = (r << 24) | (g << 16) | (b << 8) | a;
  }
  for (int i = 0; i < IMAGE_H; i++) {
      memcpy((void*)(addr + x * 4 + (y + i) * SCREEN_W * 4), (void*)(imgTmp + i
  * IMAGE_W), (IMAGE_W)*4);
  }
  */

  for (unsigned int i = 0; i < IMAGE_H; i++) {
    memcpy((void*)(addr + x * 4 + (y + i) * SCREEN_W * 4),
           (void*)(img + i * IMAGE_W + crop_left), (IMAGE_W - crop_left) * 4);
  }
}

void draw_box(int x, int y, int w, int h, unsigned int fcol,
              unsigned int* img) {
  // Top
  for (int xx = x; xx < x + w; xx++) {
    img[IMAGE_W * y + xx] = fcol;
  }
  // Bottom
  for (int xx = x; xx < x + w; xx++) {
    img[IMAGE_W * (y + h - 1) + xx] = fcol;
  }
  // Left
  for (int yy = y; yy < y + h; yy++) {
    img[IMAGE_W * yy + x] = fcol;
  }
  // Right
  for (int yy = y; yy < y + h; yy++) {
    img[IMAGE_W * yy + (x + w - 1)] = fcol;
  }
}

int string2bitmap_bbox(std::string s, unsigned int* b, unsigned int fcol,
                       unsigned int bcol, int x, int y, unsigned int* img) {
  int n = 0;
  while (s[n]) {
    char c = s[n];
    unsigned int* a = b;
    for (int i = 0; i < 8; i++) {
      char bits = c < 0xA0 ? font8x8_basic[short(c)][i]
                           : font8x8_ext_latin[short(c - 0xA0)][i];
      for (int j = 0; j < 8; j++) {
        //*a = (bits & 0x1) ? fcol : ((bcol & 0x1) ? (img[IMAGE_W * (y + i) +
        //((x + 8 * n) + j)]) : bcol);
        *a = (bits & 0x1) ? bcol : fcol;
        a++;
        bits = bits >> 1;
      }
      a += IMAGE_W - 8;
    }
    b += 8;
    n++;
  }
  return n;
}

void draw_box_text(int x, int y, std::string s, unsigned int fcol,
                   unsigned int* img) {
  int n = string2bitmap_bbox(s, textbuf8, fcol, 0, x, y, img);

  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8 * n; j++)
      img[IMAGE_W * (y + i) + (x + j)] = textbuf8[i * IMAGE_W + j];
}

//-----------------------------------------------------------------
void draw_progress_bar(unsigned int addr, int x, int y, int w, int h, int fcol,
                       int bcol, int steps, int prog) {
  int gap = 1;
  float x_step = (1.0 * w) / (1.0 * steps);
  for (int i = 0; i < steps; i++) {
    int x_0 = ceil(i * x_step);
    int x_1 = ceil((i + 1) * x_step);
    for (int x = x_0; x < x_1; x++) {
      if (i < prog) {
        if (x < x_1 - 1 - gap)
          barbuf[x] = fcol;
        else
          barbuf[x] = bcol;
      } else {
        barbuf[x] = bcol;
      }
    }
  }

  for (int i = 0; i < h; i++)
    memcpy((void*)(addr + ((y + i) * SCREEN_W + x) * 4), (void*)(barbuf),
           w * 4);
}

//-----------------------------------------------------------------

void print_xy(int x, int y, std::string s, unsigned int fcol,
              unsigned int bcol) {
  unsigned int textbuf[SCREEN_W * 8];

  int n = string2bitmap_xy(s, textbuf, 0x00ff0000, 0x1, x, y);

  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8 * n; j++)
      background_image[SCREEN_W * (y + i) + (x + j)] =
          textbuf[i * SCREEN_W + j];
  // memcpy((void*)(fbA+iomap_ddr + x*8*4 + (y*8+i)*SCREEN_W*4), (void*)(textbuf
  // + i*8*80), n*8*4);
}

int string2bitmap16x24(std::string s, unsigned int* b, unsigned int fcol,
                       unsigned int bcol, int x, int y) {
  int n = 0;
  while (s[n]) {
    unsigned short c = (unsigned short)(s[n]) - 0x20;
    unsigned int* a = b;
    for (int i = 0; i < 24; i++) {
      unsigned short bits = Arial_round_16x24[24 * 2 * c + 2 * i] << 8;
      bits = bits | Arial_round_16x24[24 * 2 * c + 2 * i + 1];
      for (int j = 0; j < 16; j++) {
        *a =
            (bits & 0x8000)
                ? fcol
                : ((bcol & 0x1) ? (background_image[SCREEN_W * (3 * 8 * y + i) +
                                                    (2 * 8 * (x + n) + j)])
                                : bcol);
        a++;
        bits = bits << 1;
      }
      a += SCREEN_W - 16;
    }
    b += 16;
    n++;
  }
  return n;
}

int string2bitmap24x48(std::string s, unsigned int* b, unsigned int fcol,
                       unsigned int bcol, int x, int y) {
  int n = 0;
  while (s[n]) {
    unsigned short c = (unsigned short)(s[n]) - 0x20;
    unsigned int* a = b;
    for (int i = 0; i < 48; i++) {
      unsigned long bits = GroteskBold24x48[48 * 3 * c + 3 * i] << 16;
      bits = bits | (GroteskBold24x48[48 * 3 * c + 3 * i + 1] << 8);
      bits = bits | GroteskBold24x48[48 * 3 * c + 3 * i + 2];
      for (int j = 0; j < 24; j++) {
        *a = (bits & 0x800000)
                 ? fcol
                 : ((bcol & 0x1) ? (background_image[SCREEN_W * (8 * y + i) +
                                                     (8 * (x + 3 * n) + j)])
                                 : bcol);
        a++;
        bits = bits << 1;
      }
      a += SCREEN_W - 24;
    }
    b += 24;
    n++;
  }
  return n;
}

void capture_screen(std::string filename) {
  FILE* file = fopen(filename.c_str(), "wb");
  void* addr = (void*)(dmp::modules::get_iomap_ddr() + dmp::modules::get_fbA());
  fwrite(addr, 1, SCREEN_W * SCREEN_H * 4, file);
  fclose(file);
}

};  // end of namespace util
};  // end of namespace dmp
