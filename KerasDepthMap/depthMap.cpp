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
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

#include "imagenet_1000_categories.h"

#include "util_draw.h"
#include "util_input.h"

#include "KerasDepthMap_gen.h"

using namespace std;
using namespace dmp;
using namespace util;

#define FILENAME_WEIGHTS "KerasDepthMap_weights.bin"

#define SCREEN_W (dmp::util::get_screen_width())
#define SCREEN_H (dmp::util::get_screen_height())

#define IMAGE_W 1242
#define IMAGE_H 375

#define IMAGE_RZ_W 512
#define IMAGE_RZ_H 128

void frame2rawUInt(COverlayRGB& intput_frm, uint32_t *imgview);
void opencv2dmp(cv::Mat& input_frm, COverlayRGB& output_frm, bool isColor = true);

CKerasDepthMap network;

// Frame counter
uint32_t fc = 0;

uint32_t imgView[IMAGE_RZ_W * IMAGE_RZ_H];
__fp16 imgProc[IMAGE_RZ_W * IMAGE_RZ_H * 3];

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

  const std::string input_image_path = "./images_depthmap/";
  const std::vector<std::string> input_image_suffix = {".png", ".PNG"};

  vector<string> image_names =
      dmp::util::get_input_image_names(input_image_path, input_image_suffix);
  int num_images = image_names.size();
  if (num_images == 0) {
    cout << "No input images." << endl;
    return 1;
  }

  std::vector<float> networkOutput;

  COverlayRGB bg_overlay(SCREEN_W, SCREEN_H);
  bg_overlay.alloc_mem_overlay(SCREEN_W, SCREEN_H);
  bg_overlay.load_ppm_img("fpgatitle_mobileNet");
  COverlayRGB overlay_input(SCREEN_W, SCREEN_H);
  overlay_input.alloc_mem_overlay(IMAGE_RZ_W, IMAGE_RZ_H);
  COverlayRGB overlay_input_debug(SCREEN_W, SCREEN_H);
  overlay_input_debug.alloc_mem_overlay(IMAGE_RZ_W, IMAGE_RZ_H);

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

  network.WantLayerOutputs();

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
        // network.get_final_output(networkOutput);
        // network.get_layer(0).output
        __fp16 outp = 0;
        for (int i=0; i<32; i++){
          outp = network.get_layer(32).output[i*IMAGE_RZ_H];
          printf("%0.3f ",outp);
        }

        printf("\nNetwork output length: %ld\n", network.get_layer(32).output.size());

        int x = (SCREEN_W - IMAGE_W) / 2;
        int y = (293 - 128) + 20;
        overlay_input_debug.print_to_display(x, y);

        x = (SCREEN_W / 5);
        y = (293 - 128) + IMAGE_W + 80;

        dmp::util::swap_buffer();
        fc++;

        int key = getchar();
        if(key == 27)
          break;
      }

      if (!pause) {
        // Read input image from jpg file
        cv::Mat colorMat = cv::imread(input_image_path + image_names[image_nr], CV_LOAD_IMAGE_COLOR);
        cv::Mat resizedMat;
        // Resize image into 512x128 before feeding through network 
        cv::resize( colorMat , resizedMat , cv::Size( IMAGE_RZ_W, IMAGE_RZ_H ), 0, 0, CV_INTER_LINEAR);
        printf("Resized image %dx%d into %dx%d\n", colorMat.cols, colorMat.rows, IMAGE_RZ_W, IMAGE_RZ_H);
        opencv2dmp( resizedMat, overlay_input );
        frame2rawUInt( overlay_input, imgView );
        overlay_input_debug.convert_to_overlay_pixel_format(imgView, IMAGE_RZ_W*IMAGE_RZ_H);
        dmp::util::preproc_image(imgView, imgProc, IMAGE_RZ_W, IMAGE_RZ_H, 0, 0, 0, 0.003921569, true);
        // __fp16 outp = 0;
        // for (int i=0; i<32; i++){
        //   outp = imgProc[i];
        //   printf("%0.3f ",outp);
        // }

        // int improc_size = sizeof(imgProc)/sizeof(__fp16);
        // printf("\nimgProc length: %d\n", improc_size);

        if (image_nr == num_images - 1) {
          image_nr = 0;
        } else {
          image_nr++;
        }
      }

      memcpy(ddr_buf_a_cpu, (void*)imgProc, IMAGE_RZ_W * IMAGE_RZ_H * 3 * 2);

      if (exit_code == -1) {  // do not start new HW ACC runs if about to exit...
        sync_cnn_in++;
      }
    }

  }

  g_should_stop = true;
  pthread_join(hwacc_thread, NULL);

  dmp::util::shutdown();

  return exit_code;
}

/**
 * @brief Convert opencv image format to dmp board frame format
 * 
 * @param input_frm      opencv image format
 * @param output_frm dmp board image format
 * @param isColor        input_fram is color or grayscale
 */
void opencv2dmp(cv::Mat& input_frm, COverlayRGB& output_frm, bool isColor)
{
  if( input_frm.cols != IMAGE_RZ_W && input_frm.rows != IMAGE_RZ_H ){
      output_frm.alloc_mem_overlay(input_frm.cols, input_frm.rows);
      printf("image height %d ", output_frm.get_overlay_height());
      printf("image width %d\n", output_frm.get_overlay_width());
  }
  // int i = 0;
  for (unsigned int h=0;h<output_frm.get_overlay_height();h++) {
    for(unsigned int w=0;w<output_frm.get_overlay_width();w++) {
      if(isColor){
        cv::Vec3b intensity = input_frm.at<cv::Vec3b>(h, w);
        uchar blue = intensity.val[0];
        uchar green = intensity.val[1];
        uchar red = intensity.val[2];
        output_frm.set_pixel(w,h, red, green, blue);
        // if(++i<32)
        //   printf("%d %d %d\n", red, green, blue);
      }else{
        uchar intensity = input_frm.at<uchar>(h, w);
        output_frm.set_pixel(w,h, intensity, intensity, intensity);
      }
    }
  }
}

/**
 * @brief get raw data from dmp board image fromat
 * 
 * @param input_frm   dmp board image format
 * @param imgview     unsigned int raw data pointer
 */
void frame2rawUInt(COverlayRGB& intput_frm, unsigned int *imgview)
{
  unsigned char *p = intput_frm.get_overlay_buf_ref();
  unsigned int size_of_imgview = intput_frm.get_overlay_width()*intput_frm.get_overlay_height();
  for(unsigned int i = 0; i < size_of_imgview*3; i += 3)
  {
    unsigned int imgview_tmp  = ((unsigned int)p[i]<<24)&0xff000000;
                 imgview_tmp  |= ((unsigned int)p[i+1]<<16)&0x00ff0000;
                 imgview_tmp  |= ((unsigned int)p[i+2]<<8)&0x0000ff00; 
    imgview[i/3]              = imgview_tmp;
  }
}

