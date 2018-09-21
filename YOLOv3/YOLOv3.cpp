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
CYOLOv3 network;

using namespace dmp;
using namespace util;

#define FILENAME_WEIGHTS "YOLOv3_weights.bin"

using namespace std;

#define SCREEN_W (dmp::util::get_screen_width())
#define SCREEN_H (dmp::util::get_screen_height())

#define IMAGE_W 512
#define IMAGE_H 288

#define TEXT_XOFS (((SCREEN_W - IMAGE_W) / 2) / 24 + 4)  // 8x8 characters
#define TEXT_YOFS ((512 + 48) / 8 + 2 + 3 + 2)           // 8x8 characters

uint32_t imgView[IMAGE_W * IMAGE_H];
__fp16 imgProc[IMAGE_W * IMAGE_H * 3];

uint32_t fc = 0;

// 2ND THREAD FOR HW CONTROL

volatile uint64_t sync_cnn_in = 0;
volatile uint64_t sync_cnn_out = 0;

volatile int conv_time_tot = 0;
volatile int fc_time_tot = 0;

volatile bool g_should_stop = false;

const int NUM_CLASS = 80;
const int NUM_BOX = 3;
const int NUM_TENSOR = NUM_CLASS + 5;
// const float ANCHOR[] = { 116, 90, 156, 198, 373, 326,
//                         30, 61, 62, 45, 59, 119,
//                         10, 13, 16, 30, 33, 23 };
const float ANCHOR[] = {81, 82, 135, 169, 344, 319, 23, 27, 37, 58, 81, 82};
// const float DIM[] = { 10, 10, 20, 20, 40, 40 };
const float DIM[] = {16, 9, 32, 18};
const float NETDIM[] = {512, 288};
const float SIG_THRES = -1.3863f;
// const float SIG_THRES = 0.0f;
const float THRESHOLD = 0.2f;
const float NMS = 0.45f;

static inline float sigmoid(float x) { return 0.5f + 0.5f * std::tanh(0.5f * x); }

static inline float overlap(float x1, float w1, float x2, float w2) {
  float left = max(x1, x2);
  float right = min(x1 + w1, x2 + w2);
  return max(right - left, 0.0f);
}

static float box_iou(const float *a, const float *b) {
  float ow = overlap(a[0], a[2], b[0], b[2]);
  float oh = overlap(a[1], a[3], b[1], b[3]);
  float box_int = ow * oh;
  float box_uni = a[2] * a[3] + b[2] * b[3] - box_int;
  return box_int / box_uni;
}

static void decode_yolo_box(
    float *box, const float *anchor, const float *dim, int x, int y) {
  box[2] = exp(box[2]) * anchor[0] / NETDIM[0];
  box[3] = exp(box[3]) * anchor[1] / NETDIM[1];
  box[0] = (x + box[0]) / dim[0] - box[2] / 2.0f;
  box[1] = (y + box[1]) / dim[1] - box[3] / 2.0f;
}

static void get_bboxes(const vector<float> &tensor, vector<float> &boxes) {
  int box_num = 0;
  const float *t = &tensor[0];
  float *box;

  boxes.clear();
  for (int i = 0; i < 2; i++) {
    for (int y = 0; y < DIM[i * 2 + 1]; y++) {
      for (int x = 0; x < DIM[i * 2]; x++) {
        for (int n = 0; n < NUM_BOX; n++) {
          if (t[4] < SIG_THRES) {
            t += NUM_TENSOR;
            continue;
          }

          boxes.resize(boxes.size() + NUM_TENSOR);
          box = &boxes[box_num * NUM_TENSOR];

          memcpy(box, t, sizeof(float) * NUM_TENSOR);
          ++box_num;
          t += NUM_TENSOR;

          box[0] = sigmoid(box[0]);
          box[1] = sigmoid(box[1]);
          box[4] = sigmoid(box[4]);
          for (int j = 5; j < NUM_TENSOR; j++) {
            box[j] = box[4] * sigmoid(box[j]);
            if (box[j] < THRESHOLD) box[j] = 0.0f;
          }

          decode_yolo_box(box, ANCHOR + (i * NUM_BOX + n) * 2, DIM + i * 2, x,
                          y);
        }
      }
    }
  }

  for (int i = 0; i < NUM_CLASS; i++) {
    float lastprob = 1.0f;
    do {
      float *mbox = nullptr;
      float mprob = 0.0f;
      for (int j = 0; j < box_num; j++) {
        box = &boxes[j * NUM_TENSOR];
        if (box[5 + i] > mprob && box[5 + i] < lastprob) {
          mbox = box;
          mprob = box[5 + i];
        }
      }
      lastprob = mprob;
      if (mbox) {
        for (int j = 0; j < box_num; j++) {
          box = &boxes[j * NUM_TENSOR];
          if (box[5 + i] == 0.0f or mbox == box) continue;
          if (box_iou(mbox, box) > NMS) box[5 + i] = 0.0f;
        }
      }
    } while (lastprob > 0.0f);
  }
}

const char *class_name[] = {
    "person",        "bicycle",       "car",           "motorbike",
    "aeroplane",     "bus",           "train",         "truck",
    "boat",          "traffic light", "fire hydrant",  "stop sign",
    "parking meter", "bench",         "bird",          "cat",
    "dog",           "horse",         "sheep",         "cow",
    "elephant",      "bear",          "zebra",         "giraffe",
    "backpack",      "umbrella",      "handbag",       "tie",
    "suitcase",      "frisbee",       "skis",          "snowboard",
    "sports ball",   "kite",          "baseball bat",  "baseball glove",
    "skateboard",    "surfboard",     "tennis racket", "bottle",
    "wine glass",    "cup",           "fork",          "knife",
    "spoon",         "bowl",          "banana",        "apple",
    "sandwich",      "orange",        "broccoli",      "carrot",
    "hot dog",       "pizza",         "donut",         "cake",
    "chair",         "sofa",          "pottedplant",   "bed",
    "diningtable",   "toilet",        "tvmonitor",     "laptop",
    "mouse",         "remote",        "keyboard",      "cell phone",
    "microwave",     "oven",          "toaster",       "sink",
    "refrigerator",  "book",          "clock",         "vase",
    "scissors",      "teddy bear",    "hair drier",    "toothbrush",
};

const uint32_t class_color[] = {
    0x00FF3F, 0x003FFF, 0xFF2600, 0xF200FF, 0xFF4C00, 0xA5FF00,
    0xFF7200, 0xFF8500, 0xFF9900, 0xFFAC00, 0xFFBF00, 0xFFD200,
    0xFFE500, 0xFFF800, 0xF2FF00, 0xDFFF00, 0xCBFF00, 0xB8FF00,
    0xFF5F00, 0x92FF00, 0x7FFF00, 0x6CFF00, 0x59FF00, 0x46FF00,
    0x33FF00, 0x1FFF00, 0x0CFF00, 0x00FF06, 0x00FF19, 0x00FF2C,
    0xFF0000, 0x00FF52, 0x00FF66, 0x00FF79, 0x00FF8C, 0x00FF9F,
    0x00FFB2, 0x00FFC5, 0x00FFD8, 0x00FFEB, 0x00FFFF, 0x00EBFF,
    0x00D8FF, 0x00C5FF, 0x00B2FF, 0x009FFF, 0x008CFF, 0x0079FF,
    0x0066FF, 0x0052FF, 0xFF1300, 0x002CFF, 0x0019FF, 0x0006FF,
    0x0C00FF, 0x1F00FF, 0x3200FF, 0x4600FF, 0x5900FF, 0x6C00FF,
    0x7F00FF, 0x9200FF, 0xA500FF, 0xB800FF, 0xCC00FF, 0xDF00FF,
    0xFF3900, 0xFF00F8, 0xFF00E5, 0xFF00D2, 0xFF00BF, 0xFF00AC,
    0xFF0098, 0xFF0085, 0xFF0072, 0xFF005F, 0xFF004C, 0xFF0039,
    0xFF0026, 0xFF0013,
};

static void draw_bboxes(const vector<float> &boxes, COverlayRGB &overlay) {
  int num = boxes.size() / NUM_TENSOR;
  const float *box;

  for (int i = 0; i < num; i++) {
    box = &boxes[i * NUM_TENSOR];
    bool has_obj = false;
    int obj_type = -1;
    string s;
    for (int j = 0; j < NUM_CLASS; j++)
      if (box[5 + j] > 0.0f) {
        has_obj = true;
        obj_type = j;
        if (s.size() > 0) s += ",";
        s += class_name[obj_type];
      }
    if (!has_obj) continue;
#if 0
    for (int j = 0; j < NUM_TENSOR; j += 5)
    {
      for (int k = 0; k < 5; k++)
        printf("%.2f  ", box[j + k]);
      printf("\n");
    }
    printf("\n");
#endif
    int x = IMAGE_W * box[0];
    int y = IMAGE_H * box[1];
    int w = IMAGE_W * box[2];
    int h = IMAGE_H * box[3];
    uint32_t color = class_color[obj_type];

    int x0 = (x > IMAGE_W - 1) ? (IMAGE_W - 1) : ((x < 0) ? 0 : x);
    int y0 = (y > IMAGE_H - 1) ? (IMAGE_H - 1) : ((y < 0) ? 0 : y);
    int x1 = x + w;
    x1 = (x1 > IMAGE_W - 1) ? (IMAGE_W - 1) : ((x1 < 0) ? 0 : x1);
    int y1 = y + h;
    y1 = (y1 > IMAGE_H - 1) ? (IMAGE_H - 1) : ((y1 < 0) ? 0 : y1);
    x = x0;
    y = y0;
    w = x1 - x0;
    h = y1 - y0;
    bool no_text =
        (x + 8 * s.length() >= IMAGE_W) || (y + 8 >= IMAGE_W) || (y - 9 < 0);

    overlay.set_box(x0, y0, x1, y1, color);
	  if (!no_text) overlay.set_box_with_text(x0, y0, x1, y1, color, s);
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
  string text = "CNN - Object Detection";
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

  text = "Bounding Box and Object Class detection";
  COverlayRGB::calculate_boundary_text_with_font(font_file, text, text_size, w, h);
  x = ((SCREEN_W - w) / 2);
  y = 65;
  bg_text.delete_overlay();
  bg_text.alloc_mem_overlay(w, h);
  bg_text.copy_overlay(bg_overlay, x, y);
  bg_text.set_text_with_font(font_file, text, 0, 3*h/4, text_size, 0x00ffffff);
  bg_text.print_to_display(x, y);

  text = "FPGA Demonstration";
  COverlayRGB::calculate_boundary_text_with_font(font_file, text, text_size, w, h);
  x = ((SCREEN_W - w) / 2);
  y = 105;
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

  const std::string input_image_path = "./images_yolo/";
  const std::vector<std::string> input_image_suffix = {".jpg", ".jpeg", ".JPG",
                                                       ".JPEG"};

  vector<string> image_names =
      dmp::util::get_input_image_names(input_image_path, input_image_suffix);
  int num_images = image_names.size();
  if (num_images == 0) {
    cout << "No input images." << endl;
    return 1;
  }

  std::vector<float> tensor;
  std::vector<float> boxes;

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
  COverlayRGB cam_overlay(SCREEN_W, SCREEN_H);
  cam_overlay.alloc_mem_overlay(IMAGE_W, IMAGE_H);

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
      string text = COverlayRGB::convert_time_to_text("Convolution (" + conv_freq + " MHz HW ACC)     : ", conv_time_tot);
      unsigned text_size = 14;

      unsigned w = 0;
      unsigned h = 0;
      COverlayRGB::calculate_boundary_text(text, text_size, w, h);

      int x = ((SCREEN_W - w) / 2);
      int y = ((293 - 138) + IMAGE_H + 80);

      COverlayRGB overlay_time(SCREEN_W, SCREEN_H);
      overlay_time.alloc_mem_overlay(w, h);
      overlay_time.copy_overlay(bg_overlay, x, y);
      overlay_time.set_text(0, 0, text, text_size, 0x00f4419d);
      overlay_time.print_to_display(x, y);
    }

    if (sync_cnn_out == sync_cnn_in) {
      if (sync_cnn_out != 0) {
        network.get_final_output(tensor);
        get_bboxes(tensor, boxes);
        draw_bboxes(boxes, cam_overlay);

        int x = ((SCREEN_W - IMAGE_W) / 2);
        int y = ((293 - 128) + 36);
        cam_overlay.print_to_display(x, y);

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
        cam_overlay.convert_to_overlay_pixel_format(imgView, IMAGE_W*IMAGE_H);
        dmp::util::preproc_image(imgView, imgProc, IMAGE_W, IMAGE_H, 0.0f, 0.0f,
                                 0.0f, 1.0f / 255.0f, true, false);
        /*
        FILE* fin;
        fin = fopen("binary_dump_nakano_images_view.bin", "r");
        fseek(fin, image_nr * (IMAGE_W * IMAGE_H * 4), SEEK_SET);
        fread(imgView, 1, (IMAGE_W * IMAGE_H * 4), fin);
        fclose(fin);
        fin = fopen("binary_dump_nakano_images_process.bin", "r");
        fseek(fin, image_nr * (IMAGE_W * IMAGE_H * 6), SEEK_SET);
        fread(imgProc, 1, (IMAGE_W * IMAGE_H * 6), fin);
        fclose(fin);
        if (image_nr == 0)
                dump_raw("input_2.raw", imgProc, IMAGE_W * IMAGE_H * 6);
        */
        if (image_nr == num_images - 1) {
          image_nr = 0;
        } else {
          image_nr++;
        }
      }

      // Copy image to FPGA memory
      memcpy(ddr_buf_a_cpu, (void *)imgProc, IMAGE_W * IMAGE_H * 3 * 2);

      if (exit_code == -1)  // do not start new HW ACC runs if about to exit...
        sync_cnn_in++;
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
