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

#include <stdio.h>
#include <math.h>

#include <linux/fb.h>
#include <linux/videodev2.h>
#include <linux/kd.h>

using namespace dmp;
using namespace util;

namespace dmp {
namespace util {

static uint32_t* background_image = NULL;
static uint32_t* textbuf8 = NULL;   //[SCREEN_W*8];
static uint32_t* textbuf16 = NULL;  //[SCREEN_W*16];
static uint32_t* barbuf = NULL;

static uint32_t* imgTmp;

static uint32_t IMAGE_W = 0;
static uint32_t IMAGE_H = 0;

static int g_fb_file = -1;
static struct fb_fix_screeninfo g_fb_fix_info;
static struct fb_var_screeninfo g_fb_var_info;
static uint32_t g_fb_pixfmt = 0;
static uint8_t *g_fb_mem = NULL;
static uint8_t *g_frame_ptr = NULL;
static int g_console = -1;

#define SCREEN_W (g_fb_var_info.xres)
#define SCREEN_H (g_fb_var_info.yres)

#define ERR(...) fprintf(stderr, __VA_ARGS__); fflush(stderr)

static void update_frame_ptr() {
  g_frame_ptr = g_fb_mem + (g_fb_var_info.yoffset * g_fb_var_info.xres + g_fb_var_info.xoffset) * (g_fb_var_info.bits_per_pixel >> 3);
}

static bool set_pan(uint32_t pan_x, uint32_t pan_y) {
  struct fb_var_screeninfo var_info;
  memset(&var_info, 0, sizeof var_info);
  var_info.xoffset = pan_x;
  var_info.yoffset = pan_y;

  int res = ioctl(g_fb_file, FBIOPAN_DISPLAY, &var_info);
  if (res < 0) {
    ERR("ioctl(FBIOPAN_DISPLAY) failed for /dev/fb0\n");
    return false;
  }

  g_fb_var_info.xoffset = var_info.xoffset;
  g_fb_var_info.yoffset = var_info.yoffset;

  update_frame_ptr();

  return true;
}

static inline uint8_t* get_frame_ptr() {
  return g_frame_ptr;
}

uint32_t get_screen_width() {
  return g_fb_var_info.xres;
}

uint32_t get_screen_height() {
  return g_fb_var_info.yres;
}

static void release_fb() {
  if (g_console != -1) {
    ioctl(g_console, KDSETMODE, KD_TEXT);
    close(g_console);
    g_console = -1;
  }
  if (g_fb_mem) {
    munmap(g_fb_mem, g_fb_fix_info.smem_len);
    g_fb_mem = NULL;
  }
  if (g_fb_file != -1) {
    close(g_fb_file);
    g_fb_file = -1;
  }
}

bool init_fb() {
  if (g_fb_file != -1) {
    ERR("Framebuffer is already opened\n");
    return false;
  }
  g_fb_file = open("/dev/fb0", O_RDWR | O_CLOEXEC);
  if (g_fb_file == -1) {
    ERR("open() failed for /dev/fb0\n");
    return false;
  }

  int res = ioctl(g_fb_file, FBIOGET_FSCREENINFO, &g_fb_fix_info);
  if (res < 0) {
    ERR("ioctl(FBIOGET_FSCREENINFO) failed for /dev/fb0\n");
    release_fb();
    return false;
  }
  res = ioctl(g_fb_file, FBIOGET_VSCREENINFO, &g_fb_var_info);
  if (res < 0) {
    ERR("ioctl(FBIOGET_FSCREENINFO) failed for /dev/fb0\n");
    release_fb();
    return false;
  }
  if ((!g_fb_var_info.xres) || (!g_fb_var_info.yres)) {
    ERR("Could not determine framebuffer dimensions: xres=%u yres=%u\n",
        g_fb_var_info.xres, g_fb_var_info.yres);
    release_fb();
    return false;
  }

  switch (g_fb_var_info.bits_per_pixel) {
    case 16:
      g_fb_pixfmt = V4L2_PIX_FMT_RGB565;
      break;
    case 24:
      if (g_fb_var_info.red.offset == 0) {
        g_fb_pixfmt = V4L2_PIX_FMT_RGB24;
      }
      else {
        g_fb_pixfmt = V4L2_PIX_FMT_BGR24;
      }
      break;
     case 32:
      if (g_fb_var_info.red.offset == 0) {
        g_fb_pixfmt = V4L2_PIX_FMT_RGB32;
      }
      else {
        g_fb_pixfmt = V4L2_PIX_FMT_BGR32;
      }
      break;
      default: {
        g_fb_pixfmt = 0;
      }
  }
  if (g_fb_pixfmt != V4L2_PIX_FMT_BGR24) {
    ERR("Unsupported pixel format: bpp=%d red.offset=%d\n",
        g_fb_var_info.bits_per_pixel, g_fb_var_info.red.offset);
    release_fb();
    return false;
  }

  if (g_fb_fix_info.smem_len < g_fb_var_info.xres * g_fb_var_info.yres * (g_fb_var_info.bits_per_pixel >> 2)) {
    ERR("Framebuffer doesn't support double buffering\n");
    release_fb();
    return false;
  }

  if (g_fb_fix_info.line_length != g_fb_var_info.xres * (g_fb_var_info.bits_per_pixel >> 3)) {
    ERR("Support for framebuffer with bigger than visible width %d line length %d is not implemented\n",
        g_fb_var_info.xres * (g_fb_var_info.bits_per_pixel >> 3), g_fb_fix_info.line_length);
    release_fb();
    return false;
  }

  g_fb_mem = (uint8_t*)mmap(
      NULL, g_fb_fix_info.smem_len, PROT_READ | PROT_WRITE,
      MAP_SHARED, g_fb_file, 0);
  if (!g_fb_mem) {
    ERR("mmap() failed for /dev/fb0\n");
    release_fb();
    return false;
  }

  // Set graphics mode on the console
  static const char *console_fnmes[2] = {"/dev/tty", "/dev/tty0"};
  for (int i = 0; i < 2; ++i) {
    g_console = open(console_fnmes[i], O_RDWR | O_CLOEXEC);
    if (g_console != -1) {
      if (ioctl(g_console, KDSETMODE, KD_GRAPHICS)) {
        close(g_console);
        g_console = -1;
      }
      else {
        break;
      }
    }
  }

  set_pan(g_fb_var_info.xoffset, 0);

  return true;
}

void shutdown() {
  deleteBackgroundImage();
  release_fb();
}

bool swap_buffer() {
  int res = ioctl(g_fb_file, FBIOBLANK, FB_BLANK_UNBLANK);
  if (res < 0) {
    ERR("ioctl(FB_BLANK_UNBLANK) failed for /dev/fb0\n");
    return false;
  }

  unsigned int screen = 0;
  res = ioctl(g_fb_file, FBIO_WAITFORVSYNC, &screen);
  if (res < 0) {
    ERR("ioctl(FBIO_WAITFORVSYNC) failed for /dev/fb0\n");
    return false;
  }

  return set_pan(g_fb_var_info.xoffset, g_fb_var_info.yoffset ? 0 : g_fb_var_info.yres);
}

/// @brief Resets button state.
void reset_button_state() {
  // TODO: implement.
}

uint32_t get_button_state() {
  // TODO: implement.
  return 0;
}

std::string centered(const std::string& original, int targetSize) {
  std::string res;
  int padding = targetSize - original.size();
  if ((padding >> 1) <= 0) {
    res = original;
  }
  else {
    res = std::string(padding >> 1, ' ') + original + std::string(padding >> 1, ' ');
  }
  for (; (int)res.size() < targetSize; res += ' ') {
    // Empty by design
  }
  if ((int)res.size() != targetSize) {
    fflush(stdout);
    fprintf(stderr, "Detected broken implementation of centered(): res.size=%d while targetSize=%d\n",
            (int)res.size(), targetSize);
    fflush(stderr);
    _exit(-1);
  }
  return res;
}

void print_result(const std::vector<std::string>& catstr_vec,
                  int x, int y, const std::vector<std::pair<float, int> >& f, uint32_t wcol,
                  uint32_t fcol, uint32_t bcol) {
  std::vector<std::pair<std::string, float> > result;
  result.push_back(std::make_pair(catstr_vec[f[0].second], f[0].first));
  result.push_back(std::make_pair(catstr_vec[f[1].second], f[1].first));
  result.push_back(std::make_pair(catstr_vec[f[2].second], f[2].first));
  result.push_back(std::make_pair(catstr_vec[f[3].second], f[3].first));
  result.push_back(std::make_pair(catstr_vec[f[4].second], f[4].first));

  std::stringstream ss;
  std::string s;
  for (uint32_t i = 0; i < result.size(); i++) {
    std::pair<std::string, float> p = result[i];
    ss.str("");
    ss << std::fixed << std::setprecision(3) << p.second << "  " << p.first;
    s = ss.str();
    if (s.size() > 45) s = s.substr(0, 45 - 3) + "...";
    s.resize(45, ' ');
    if (i == 0)
      dmp::util::print16x16_toDisplay(x, y + i, s, wcol, bcol);
    else
      dmp::util::print16x16_toDisplay(x, y + 2 * i + 1, s, fcol, bcol);
    if (i == 0) {
      std::string all_words = p.first;
      std::string word = all_words.substr(0, all_words.find(","));
      if (word.size() > 32) word = word.substr(0, 32 - 3) + "...";
      word = centered(word, 32);
      // print16x24(16, 18, word,  0xf17f1f00, 0x00000001);
      // print16x24(((1280/2)/(2*8)-16), 18, word,  0xf17f1f00, 0x00000001);
      dmp::util::print24x48_toDisplay(((1280 / 2) / 8 - 3 * 16), 54, word,
                                      0xf17f1f00, 0x00000001);
    }
  }
}

std::vector<std::pair<float, int> > catrank(float* softmax, int count) {
  std::vector<std::pair<float, int> > v;
  for (int i = 0; i < count; i++) {
    std::pair<float, int> p;
    p.first = softmax[i];
    p.second = i;
    v.push_back(p);
  }
  std::sort(v.begin(), v.end());
  std::reverse(v.begin(), v.end());

  std::vector<std::pair<float, int> > r(v.begin(), v.begin() + 5);
  return r;
}

void set_inputImageSize(unsigned w, uint32_t h) {
  IMAGE_W = w;
  IMAGE_H = h;
}

void createBackgroundImage(int screen_w, int screen_h) {
  background_image = new uint32_t[screen_w * screen_h];
  SCREEN_W = screen_w;
  SCREEN_H = screen_h;

  textbuf8 = new uint32_t[SCREEN_W * 8];
  textbuf16 = new uint32_t[SCREEN_W * 16];
  barbuf = new uint32_t[SCREEN_W];

  imgTmp = new uint32_t[IMAGE_W * IMAGE_H];
}

bool load_background_image(std::string filename) {
  char px[3];

  std::ifstream dfs(filename.c_str());  //"fpgatitle_yolo.ppm");
  if (!dfs.is_open()) {
    std::cout << "Failed to open backgound image file." << std::endl;
    return false;
  } else {
    for (uint32_t i = 0; i < 54 - 15; i++) dfs.read((char*)px, 1);
    for (uint32_t j = 0; j < SCREEN_H; j++) {
      for (uint32_t i = 0; i < SCREEN_W; i++) {
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
  if (background_image) {
    delete background_image;
    background_image = NULL;
  }
  if (textbuf8) {
    delete textbuf8;
    textbuf8 = NULL;
  }
  if (textbuf16) {
    delete textbuf16;
    textbuf16 = NULL;
  }
  if (barbuf) {
    delete barbuf;
    barbuf = NULL;
  }
  if (imgTmp) {
    delete imgTmp;
    imgTmp = NULL;
  }
}

int string2bitmap(std::string s, uint32_t* b, uint32_t fcol,
                  uint32_t bcol, int x, int y) {
  int n = 0;
  while (s[n]) {
    char c = s[n];
    uint32_t* a = b;
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

int string2bitmap_xy(std::string s, uint32_t* b, uint32_t fcol,
                     uint32_t bcol, int x, int y) {
  int n = 0;
  while (s[n]) {
    char c = s[n];
    uint32_t* a = b;
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

int string2bitmap16x16(std::string s, uint32_t* b, uint32_t fcol,
                       uint32_t bcol, int x, int y) {
  int n = 0;
  while (s[n]) {
    uint16_t c = (uint16_t)(s[n]) - 0x20;
    uint32_t* a = b;
    for (int i = 0; i < 16; i++) {
      uint16_t bits = font16x16[16 * 2 * c + 2 * i] << 8;
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

void print16x16_toDisplay(int x, int y, std::string s, uint32_t fcol,
                          uint32_t bcol) {
  /*uint32_t addr = dmp::modules::get_iomap_ddr() + dmp::modules::get_fbA();
  int n = string2bitmap16x16(s, textbuf16, fcol, bcol, x, y);
  for (int i = 0; i < 16; i++)
    memcpy((void*)(addr + x * 8 * 4 + (y * 8 + i) * SCREEN_W * 4),
           (void*)(textbuf16 + i * SCREEN_W), 2 * n * 8 * 4);*/
  fprintf(stdout, "%s\n", s.c_str());
  fflush(stdout);
}

void print16x24_toDisplay(int x, int y, std::string s, uint32_t fcol,
                          uint32_t bcol) {
  /*uint32_t addr = dmp::modules::get_iomap_ddr() + dmp::modules::get_fbA();
  uint32_t textbuf[SCREEN_W * 24];

  int n = string2bitmap16x24(s, textbuf, fcol, bcol, x, y);

  for (int i = 0; i < 24; i++)
    memcpy((void*)(addr + 2 * x * 8 * 4 + (3 * y * 8 + i) * SCREEN_W * 4),
           (void*)(textbuf + i * SCREEN_W), 2 * n * 8 * 4);*/
}

void print8x8_toDisplay(int x, int y, std::string s, uint32_t fcol,
                        uint32_t bcol) {
  /*uint32_t addr = dmp::modules::get_iomap_ddr() + dmp::modules::get_fbA();
  int n = string2bitmap(s, textbuf8, fcol, bcol, x, y);
  for (int i = 0; i < 8; i++)
    memcpy((void*)(addr + x * 8 * 4 + (y * 8 + i) * SCREEN_W * 4),
           (void*)(textbuf8 + i * 8 * (SCREEN_W / 8)), n * 8 * 4);*/
}

void print24x48_toDisplay(int x, int y, std::string s, uint32_t fcol,
                          uint32_t bcol) {
  /*uint32_t addr = dmp::modules::get_iomap_ddr() + dmp::modules::get_fbA();
  uint32_t textbuf[SCREEN_W * 48];

  int n = string2bitmap24x48(s, textbuf, fcol, bcol, x, y);

  for (int i = 0; i < 48; i++)
    memcpy((void*)(addr + x * 8 * 4 + (y * 8 + i) * SCREEN_W * 4),
           (void*)(textbuf + i * SCREEN_W), 3 * n * 8 * 4);*/
  fprintf(stdout, "%s\n", s.c_str());
  fflush(stdout);
}

void print_time_toDisplay(int x, int y, std::string label, long int t,
                          long int t_max, uint32_t fcol,
                          uint32_t bcol) {
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
  uint8_t *frame = get_frame_ptr();
  const uint32_t n = SCREEN_H * SCREEN_W;
  for (uint32_t i = 0, j = 0; i < n; ++i, j += 3) {
    const uint32_t rgba = background_image[i];
    frame[j] = (rgba >> 8) & 0xFF;
    frame[j + 1] = (rgba >> 16) & 0xFF;
    frame[j + 2] = (rgba >> 24) & 0xFF;
  }
}

void print_image_toDisplay(int x, int y, uint32_t* img, int crop_left) {
  //uint32_t addr = dmp::modules::get_iomap_ddr() + dmp::modules::get_fbA();

  /*
  for (int i = 0; i < IMAGE_W * IMAGE_H; i++) {
      uint32_t px = img[i];
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

  //for (uint32_t i = 0; i < IMAGE_H; i++) {
  //  memcpy((void*)(addr + x * 4 + (y + i) * SCREEN_W * 4),
  //         (void*)(img + i * IMAGE_W + crop_left), (IMAGE_W - crop_left) * 4);
  //}
}

void draw_box(int x, int y, int w, int h, uint32_t fcol,
              uint32_t* img) {
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

int string2bitmap_bbox(std::string s, uint32_t* b, uint32_t fcol,
                       uint32_t bcol, int x, int y, uint32_t* img) {
  int n = 0;
  while (s[n]) {
    char c = s[n];
    uint32_t* a = b;
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

void draw_box_text(int x, int y, std::string s, uint32_t fcol,
                   uint32_t* img) {
  int n = string2bitmap_bbox(s, textbuf8, fcol, 0, x, y, img);

  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8 * n; j++)
      img[IMAGE_W * (y + i) + (x + j)] = textbuf8[i * IMAGE_W + j];
}

//-----------------------------------------------------------------
void draw_progress_bar(uint32_t addr, int x, int y, int w, int h, int fcol,
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

void print_xy(int x, int y, std::string s, uint32_t fcol,
              uint32_t bcol) {
  uint32_t textbuf[SCREEN_W * 8];

  int n = string2bitmap_xy(s, textbuf, 0x00ff0000, 0x1, x, y);

  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8 * n; j++)
      background_image[SCREEN_W * (y + i) + (x + j)] =
          textbuf[i * SCREEN_W + j];
  // memcpy((void*)(fbA+iomap_ddr + x*8*4 + (y*8+i)*SCREEN_W*4), (void*)(textbuf
  // + i*8*80), n*8*4);
}

int string2bitmap16x24(std::string s, uint32_t* b, uint32_t fcol,
                       uint32_t bcol, int x, int y) {
  int n = 0;
  while (s[n]) {
    uint16_t c = (uint16_t)(s[n]) - 0x20;
    uint32_t* a = b;
    for (int i = 0; i < 24; i++) {
      uint16_t bits = Arial_round_16x24[24 * 2 * c + 2 * i] << 8;
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

int string2bitmap24x48(std::string s, uint32_t* b, uint32_t fcol,
                       uint32_t bcol, int x, int y) {
  int n = 0;
  while (s[n]) {
    uint16_t c = (uint16_t)(s[n]) - 0x20;
    uint32_t* a = b;
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
  //void* addr = (void*)(dmp::modules::get_iomap_ddr() + dmp::modules::get_fbA());
  //fwrite(addr, 1, SCREEN_W * SCREEN_H * 4, file);
  fclose(file);
}

};  // end of namespace util
};  // end of namespace dmp
