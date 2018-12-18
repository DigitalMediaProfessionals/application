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

#include <vector>
#include "util_draw.h"

using namespace dmp;
using namespace util;

#define IMAGE_W 320
#define IMAGE_H 240
#define CLASS_NUM 12

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

void convertimage(uint16_t *imgProc, COverlayRGB &overlay) {
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

void visualize(void *netoutCPU, COverlayRGB &overlay) {
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

void visualize(std::vector<float> &netout, COverlayRGB &overlay) {
  visualize(reinterpret_cast<void*>(netout.data()), overlay);
}
