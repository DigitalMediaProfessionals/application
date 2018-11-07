/*
 *  Copyright 2018 Digital Media Professionals Inc.

 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at

 *      http://www.apache.org/licenses/LICENSE-2.0

 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.

 *  This source code was generated using DMP-DV700 tools.
 */

#include "YOLOv3Pywrap_gen.h"


CYOLOv3Pywrap::CYOLOv3Pywrap() {
  // Empty by design
}

CYOLOv3Pywrap::~CYOLOv3Pywrap() {
  // Empty by design
}

bool CYOLOv3Pywrap::Initialize() {
  if (!ReserveMemory(17822496, 6782976)) {
    return false;
  }

  set_num_layers(22);
  set_num_output_layers(1);

  Layer_0();
  Layer_1();
  Layer_2();
  Layer_3();
  Layer_4();
  Layer_5();
  Layer_6();
  Layer_7();
  Layer_8();
  Layer_9();
  Layer_10();
  Layer_11();
  Layer_12();
  Layer_13();
  Layer_14();
  Layer_15();
  Layer_16();
  Layer_17();
  Layer_18();
  Layer_19();
  Layer_20();
  Layer_21();

  return true;
}

//Layer_0: Convolution Layer
//  ->: conv2d_1
//  ->: batch_normalization_1
//  ->: batch_normalization_1
//  ->: leaky_re_lu_1
void CYOLOv3Pywrap::Layer_0() {
  get_layer(0).name = "conv2d_1, batch_normalization_1, batch_normalization_1, leaky_re_lu_1";
  dmp_dv_cmdraw_conv_v0& conf = get_layer(0).conv_conf;
  conf.header.size = sizeof(conf);
  conf.header.device_type = DMP_DV_DEV_CONV;
  conf.header.version = 0;
  // Topo: 00000000000000000000000000000001
  conf.topo = 0x1;  // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  // Input Configuration:
  conf.w = 512;  // Input Width
  conf.h = 288;  // Input Height
  conf.z = 1;  // Input Depth
  conf.c = 3;  // Input Channels
  conf.input_buf.mem = io_mem_;
  conf.input_buf.offs = 0;

  // Output Configuration:
  conf.output_buf.mem = io_mem_;
  conf.output_buf.offs = 884736;

  conf.eltwise_buf.mem = NULL;
  conf.eltwise_buf.offs = 0;  // Input byte address for elementwise add (0 = UBUF Input Buffer)
  conf.output_mode = 0;  // 0 = concat, 1 = eltwise add

  // Runs Configuration:
  // ->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv2d_1
  //->: batch_normalization_1
  //->: batch_normalization_1
  //->: leaky_re_lu_1
  conf.run[0].m = 16;  // Output Channels
  conf.run[0].conv_enable = 1;  // 1 = Enabled, 0 = Disabled
  conf.run[0].p = 0x3;  // Filter Width and Height
  conf.run[0].pz = 1;  // Filter Depth
  conf.run[0].weight_buf.mem = weights_mem_;
  conf.run[0].weight_buf.offs = 0;
  conf.run[0].weight_fmt = 1;  // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  conf.run[0].conv_pad = 0x1010101;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].conv_stride = 0x101;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].conv_dilation = 0x0;  // bits [7:0] = X dilation, bits [15:8] = Y dilation
  conf.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  conf.run[0].pool_size = 0x0;  // bits [7:0] = width, bits [15:8] = height
  conf.run[0].pool_stride = 0x101;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].pool_pad = 0x0;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].pool_avg_param = 0x0;  // Usually set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  conf.run[0].actfunc = 2;  // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  conf.run[0].actfunc_param = 0x2E66;  // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  conf.run[0].rectifi_en = 0;  // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  conf.run[0].lrn = 0x0;  // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2

  fpga_layer& layer = get_layer(0);
  layer.type = LT_CONV;
  layer.input_offs = 0;
  layer.output_offs = 884736;
  layer.output_size = 4718592;
  layer.input_dim[0] = 512;
  layer.input_dim[1] = 288;
  layer.input_dim[2] = 3;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 512;
  layer.output_dim[1] = 288;
  layer.output_dim[2] = 16;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = false;
}//end of  Layer_0

//Layer_1: Convolution Layer
//  ->: max_pooling2d_1
void CYOLOv3Pywrap::Layer_1() {
  get_layer(1).name = "max_pooling2d_1";
  dmp_dv_cmdraw_conv_v0& conf = get_layer(1).conv_conf;
  conf.header.size = sizeof(conf);
  conf.header.device_type = DMP_DV_DEV_CONV;
  conf.header.version = 0;
  // Topo: 00000000000000000000000000000001
  conf.topo = 0x1;  // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  // Input Configuration:
  conf.w = 512;  // Input Width
  conf.h = 288;  // Input Height
  conf.z = 1;  // Input Depth
  conf.c = 16;  // Input Channels
  conf.input_buf.mem = io_mem_;
  conf.input_buf.offs = 884736;

  // Output Configuration:
  conf.output_buf.mem = io_mem_;
  conf.output_buf.offs = 5603328;

  conf.eltwise_buf.mem = NULL;
  conf.eltwise_buf.offs = 0;  // Input byte address for elementwise add (0 = UBUF Input Buffer)
  conf.output_mode = 0;  // 0 = concat, 1 = eltwise add

  // Runs Configuration:
  // ->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: max_pooling2d_1
  conf.run[0].m = 16;  // Output Channels
  conf.run[0].conv_enable = 0;  // 1 = Enabled, 0 = Disabled
  conf.run[0].p = 0x1;  // Filter Width and Height
  conf.run[0].pz = 1;  // Filter Depth
  conf.run[0].weight_buf.mem = weights_mem_;
  conf.run[0].weight_buf.offs = 2336;
  conf.run[0].weight_fmt = 0;  // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  conf.run[0].conv_pad = 0x0;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].conv_stride = 0x101;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].conv_dilation = 0x0;  // bits [7:0] = X dilation, bits [15:8] = Y dilation
  conf.run[0].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  conf.run[0].pool_size = 0x202;  // bits [7:0] = width, bits [15:8] = height
  conf.run[0].pool_stride = 0x202;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].pool_pad = 0x0;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].pool_avg_param = 0x0;  // Usually set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  conf.run[0].actfunc = 0;  // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  conf.run[0].actfunc_param = 0x0;  // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  conf.run[0].rectifi_en = 0;  // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  conf.run[0].lrn = 0x0;  // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2

  fpga_layer& layer = get_layer(1);
  layer.type = LT_CONV;
  layer.input_offs = 884736;
  layer.output_offs = 5603328;
  layer.output_size = 1179648;
  layer.input_dim[0] = 512;
  layer.input_dim[1] = 288;
  layer.input_dim[2] = 16;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 256;
  layer.output_dim[1] = 144;
  layer.output_dim[2] = 16;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_1

//Layer_2: Convolution Layer
//  ->: conv2d_2
//  ->: batch_normalization_2
//  ->: batch_normalization_2
//  ->: leaky_re_lu_2
void CYOLOv3Pywrap::Layer_2() {
  get_layer(2).name = "conv2d_2, batch_normalization_2, batch_normalization_2, leaky_re_lu_2";
  dmp_dv_cmdraw_conv_v0& conf = get_layer(2).conv_conf;
  conf.header.size = sizeof(conf);
  conf.header.device_type = DMP_DV_DEV_CONV;
  conf.header.version = 0;
  // Topo: 00000000000000000000000000000001
  conf.topo = 0x1;  // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  // Input Configuration:
  conf.w = 256;  // Input Width
  conf.h = 144;  // Input Height
  conf.z = 1;  // Input Depth
  conf.c = 16;  // Input Channels
  conf.input_buf.mem = io_mem_;
  conf.input_buf.offs = 5603328;

  // Output Configuration:
  conf.output_buf.mem = io_mem_;
  conf.output_buf.offs = 0;

  conf.eltwise_buf.mem = NULL;
  conf.eltwise_buf.offs = 0;  // Input byte address for elementwise add (0 = UBUF Input Buffer)
  conf.output_mode = 0;  // 0 = concat, 1 = eltwise add

  // Runs Configuration:
  // ->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv2d_2
  //->: batch_normalization_2
  //->: batch_normalization_2
  //->: leaky_re_lu_2
  conf.run[0].m = 32;  // Output Channels
  conf.run[0].conv_enable = 1;  // 1 = Enabled, 0 = Disabled
  conf.run[0].p = 0x3;  // Filter Width and Height
  conf.run[0].pz = 1;  // Filter Depth
  conf.run[0].weight_buf.mem = weights_mem_;
  conf.run[0].weight_buf.offs = 2336;
  conf.run[0].weight_fmt = 1;  // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  conf.run[0].conv_pad = 0x1010101;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].conv_stride = 0x101;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].conv_dilation = 0x0;  // bits [7:0] = X dilation, bits [15:8] = Y dilation
  conf.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  conf.run[0].pool_size = 0x0;  // bits [7:0] = width, bits [15:8] = height
  conf.run[0].pool_stride = 0x101;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].pool_pad = 0x0;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].pool_avg_param = 0x0;  // Usually set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  conf.run[0].actfunc = 2;  // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  conf.run[0].actfunc_param = 0x2E66;  // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  conf.run[0].rectifi_en = 0;  // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  conf.run[0].lrn = 0x0;  // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2

  fpga_layer& layer = get_layer(2);
  layer.type = LT_CONV;
  layer.input_offs = 5603328;
  layer.output_offs = 0;
  layer.output_size = 2359296;
  layer.input_dim[0] = 256;
  layer.input_dim[1] = 144;
  layer.input_dim[2] = 16;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 256;
  layer.output_dim[1] = 144;
  layer.output_dim[2] = 32;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_2

//Layer_3: Convolution Layer
//  ->: max_pooling2d_2
void CYOLOv3Pywrap::Layer_3() {
  get_layer(3).name = "max_pooling2d_2";
  dmp_dv_cmdraw_conv_v0& conf = get_layer(3).conv_conf;
  conf.header.size = sizeof(conf);
  conf.header.device_type = DMP_DV_DEV_CONV;
  conf.header.version = 0;
  // Topo: 00000000000000000000000000000001
  conf.topo = 0x1;  // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  // Input Configuration:
  conf.w = 256;  // Input Width
  conf.h = 144;  // Input Height
  conf.z = 1;  // Input Depth
  conf.c = 32;  // Input Channels
  conf.input_buf.mem = io_mem_;
  conf.input_buf.offs = 0;

  // Output Configuration:
  conf.output_buf.mem = io_mem_;
  conf.output_buf.offs = 2359296;

  conf.eltwise_buf.mem = NULL;
  conf.eltwise_buf.offs = 0;  // Input byte address for elementwise add (0 = UBUF Input Buffer)
  conf.output_mode = 0;  // 0 = concat, 1 = eltwise add

  // Runs Configuration:
  // ->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: max_pooling2d_2
  conf.run[0].m = 32;  // Output Channels
  conf.run[0].conv_enable = 0;  // 1 = Enabled, 0 = Disabled
  conf.run[0].p = 0x1;  // Filter Width and Height
  conf.run[0].pz = 1;  // Filter Depth
  conf.run[0].weight_buf.mem = weights_mem_;
  conf.run[0].weight_buf.offs = 11616;
  conf.run[0].weight_fmt = 0;  // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  conf.run[0].conv_pad = 0x0;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].conv_stride = 0x101;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].conv_dilation = 0x0;  // bits [7:0] = X dilation, bits [15:8] = Y dilation
  conf.run[0].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  conf.run[0].pool_size = 0x202;  // bits [7:0] = width, bits [15:8] = height
  conf.run[0].pool_stride = 0x202;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].pool_pad = 0x0;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].pool_avg_param = 0x0;  // Usually set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  conf.run[0].actfunc = 0;  // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  conf.run[0].actfunc_param = 0x0;  // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  conf.run[0].rectifi_en = 0;  // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  conf.run[0].lrn = 0x0;  // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2

  fpga_layer& layer = get_layer(3);
  layer.type = LT_CONV;
  layer.input_offs = 0;
  layer.output_offs = 2359296;
  layer.output_size = 589824;
  layer.input_dim[0] = 256;
  layer.input_dim[1] = 144;
  layer.input_dim[2] = 32;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 128;
  layer.output_dim[1] = 72;
  layer.output_dim[2] = 32;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_3

//Layer_4: Convolution Layer
//  ->: conv2d_3
//  ->: batch_normalization_3
//  ->: batch_normalization_3
//  ->: leaky_re_lu_3
void CYOLOv3Pywrap::Layer_4() {
  get_layer(4).name = "conv2d_3, batch_normalization_3, batch_normalization_3, leaky_re_lu_3";
  dmp_dv_cmdraw_conv_v0& conf = get_layer(4).conv_conf;
  conf.header.size = sizeof(conf);
  conf.header.device_type = DMP_DV_DEV_CONV;
  conf.header.version = 0;
  // Topo: 00000000000000000000000000000001
  conf.topo = 0x1;  // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  // Input Configuration:
  conf.w = 128;  // Input Width
  conf.h = 72;  // Input Height
  conf.z = 1;  // Input Depth
  conf.c = 32;  // Input Channels
  conf.input_buf.mem = io_mem_;
  conf.input_buf.offs = 2359296;

  // Output Configuration:
  conf.output_buf.mem = io_mem_;
  conf.output_buf.offs = 0;

  conf.eltwise_buf.mem = NULL;
  conf.eltwise_buf.offs = 0;  // Input byte address for elementwise add (0 = UBUF Input Buffer)
  conf.output_mode = 0;  // 0 = concat, 1 = eltwise add

  // Runs Configuration:
  // ->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv2d_3
  //->: batch_normalization_3
  //->: batch_normalization_3
  //->: leaky_re_lu_3
  conf.run[0].m = 64;  // Output Channels
  conf.run[0].conv_enable = 1;  // 1 = Enabled, 0 = Disabled
  conf.run[0].p = 0x3;  // Filter Width and Height
  conf.run[0].pz = 1;  // Filter Depth
  conf.run[0].weight_buf.mem = weights_mem_;
  conf.run[0].weight_buf.offs = 11616;
  conf.run[0].weight_fmt = 1;  // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  conf.run[0].conv_pad = 0x1010101;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].conv_stride = 0x101;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].conv_dilation = 0x0;  // bits [7:0] = X dilation, bits [15:8] = Y dilation
  conf.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  conf.run[0].pool_size = 0x0;  // bits [7:0] = width, bits [15:8] = height
  conf.run[0].pool_stride = 0x101;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].pool_pad = 0x0;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].pool_avg_param = 0x0;  // Usually set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  conf.run[0].actfunc = 2;  // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  conf.run[0].actfunc_param = 0x2E66;  // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  conf.run[0].rectifi_en = 0;  // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  conf.run[0].lrn = 0x0;  // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2

  fpga_layer& layer = get_layer(4);
  layer.type = LT_CONV;
  layer.input_offs = 2359296;
  layer.output_offs = 0;
  layer.output_size = 1179648;
  layer.input_dim[0] = 128;
  layer.input_dim[1] = 72;
  layer.input_dim[2] = 32;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 128;
  layer.output_dim[1] = 72;
  layer.output_dim[2] = 64;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_4

//Layer_5: Convolution Layer
//  ->: max_pooling2d_3
void CYOLOv3Pywrap::Layer_5() {
  get_layer(5).name = "max_pooling2d_3";
  dmp_dv_cmdraw_conv_v0& conf = get_layer(5).conv_conf;
  conf.header.size = sizeof(conf);
  conf.header.device_type = DMP_DV_DEV_CONV;
  conf.header.version = 0;
  // Topo: 00000000000000000000000000000001
  conf.topo = 0x1;  // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  // Input Configuration:
  conf.w = 128;  // Input Width
  conf.h = 72;  // Input Height
  conf.z = 1;  // Input Depth
  conf.c = 64;  // Input Channels
  conf.input_buf.mem = io_mem_;
  conf.input_buf.offs = 0;

  // Output Configuration:
  conf.output_buf.mem = io_mem_;
  conf.output_buf.offs = 1179648;

  conf.eltwise_buf.mem = NULL;
  conf.eltwise_buf.offs = 0;  // Input byte address for elementwise add (0 = UBUF Input Buffer)
  conf.output_mode = 0;  // 0 = concat, 1 = eltwise add

  // Runs Configuration:
  // ->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: max_pooling2d_3
  conf.run[0].m = 64;  // Output Channels
  conf.run[0].conv_enable = 0;  // 1 = Enabled, 0 = Disabled
  conf.run[0].p = 0x1;  // Filter Width and Height
  conf.run[0].pz = 1;  // Filter Depth
  conf.run[0].weight_buf.mem = weights_mem_;
  conf.run[0].weight_buf.offs = 48608;
  conf.run[0].weight_fmt = 0;  // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  conf.run[0].conv_pad = 0x0;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].conv_stride = 0x101;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].conv_dilation = 0x0;  // bits [7:0] = X dilation, bits [15:8] = Y dilation
  conf.run[0].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  conf.run[0].pool_size = 0x202;  // bits [7:0] = width, bits [15:8] = height
  conf.run[0].pool_stride = 0x202;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].pool_pad = 0x0;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].pool_avg_param = 0x0;  // Usually set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  conf.run[0].actfunc = 0;  // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  conf.run[0].actfunc_param = 0x0;  // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  conf.run[0].rectifi_en = 0;  // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  conf.run[0].lrn = 0x0;  // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2

  fpga_layer& layer = get_layer(5);
  layer.type = LT_CONV;
  layer.input_offs = 0;
  layer.output_offs = 1179648;
  layer.output_size = 294912;
  layer.input_dim[0] = 128;
  layer.input_dim[1] = 72;
  layer.input_dim[2] = 64;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 64;
  layer.output_dim[1] = 36;
  layer.output_dim[2] = 64;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_5

//Layer_6: Convolution Layer
//  ->: conv2d_4
//  ->: batch_normalization_4
//  ->: batch_normalization_4
//  ->: leaky_re_lu_4
//  ->: max_pooling2d_4
void CYOLOv3Pywrap::Layer_6() {
  get_layer(6).name = "conv2d_4, batch_normalization_4, batch_normalization_4, leaky_re_lu_4, max_pooling2d_4";
  dmp_dv_cmdraw_conv_v0& conf = get_layer(6).conv_conf;
  conf.header.size = sizeof(conf);
  conf.header.device_type = DMP_DV_DEV_CONV;
  conf.header.version = 0;
  // Topo: 00000000000000000000000000000001
  conf.topo = 0x1;  // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  // Input Configuration:
  conf.w = 64;  // Input Width
  conf.h = 36;  // Input Height
  conf.z = 1;  // Input Depth
  conf.c = 64;  // Input Channels
  conf.input_buf.mem = io_mem_;
  conf.input_buf.offs = 1179648;

  // Output Configuration:
  conf.output_buf.mem = io_mem_;
  conf.output_buf.offs = 0;

  conf.eltwise_buf.mem = NULL;
  conf.eltwise_buf.offs = 0;  // Input byte address for elementwise add (0 = UBUF Input Buffer)
  conf.output_mode = 0;  // 0 = concat, 1 = eltwise add

  // Runs Configuration:
  // ->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv2d_4
  //->: batch_normalization_4
  //->: batch_normalization_4
  //->: leaky_re_lu_4
  //->: max_pooling2d_4
  conf.run[0].m = 128;  // Output Channels
  conf.run[0].conv_enable = 1;  // 1 = Enabled, 0 = Disabled
  conf.run[0].p = 0x3;  // Filter Width and Height
  conf.run[0].pz = 1;  // Filter Depth
  conf.run[0].weight_buf.mem = weights_mem_;
  conf.run[0].weight_buf.offs = 48608;
  conf.run[0].weight_fmt = 1;  // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  conf.run[0].conv_pad = 0x1010101;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].conv_stride = 0x101;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].conv_dilation = 0x0;  // bits [7:0] = X dilation, bits [15:8] = Y dilation
  conf.run[0].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  conf.run[0].pool_size = 0x202;  // bits [7:0] = width, bits [15:8] = height
  conf.run[0].pool_stride = 0x202;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].pool_pad = 0x0;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].pool_avg_param = 0x0;  // Usually set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  conf.run[0].actfunc = 2;  // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  conf.run[0].actfunc_param = 0x2E66;  // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  conf.run[0].rectifi_en = 0;  // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  conf.run[0].lrn = 0x0;  // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2

  fpga_layer& layer = get_layer(6);
  layer.type = LT_CONV;
  layer.input_offs = 1179648;
  layer.output_offs = 0;
  layer.output_size = 147456;
  layer.input_dim[0] = 64;
  layer.input_dim[1] = 36;
  layer.input_dim[2] = 64;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 32;
  layer.output_dim[1] = 18;
  layer.output_dim[2] = 128;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_6

//Layer_7: Convolution Layer
//  ->: conv2d_5
//  ->: batch_normalization_5
//  ->: batch_normalization_5
//  ->: leaky_re_lu_5
void CYOLOv3Pywrap::Layer_7() {
  get_layer(7).name = "conv2d_5, batch_normalization_5, batch_normalization_5, leaky_re_lu_5";
  dmp_dv_cmdraw_conv_v0& conf = get_layer(7).conv_conf;
  conf.header.size = sizeof(conf);
  conf.header.device_type = DMP_DV_DEV_CONV;
  conf.header.version = 0;
  // Topo: 00000000000000000000000000000001
  conf.topo = 0x1;  // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  // Input Configuration:
  conf.w = 32;  // Input Width
  conf.h = 18;  // Input Height
  conf.z = 1;  // Input Depth
  conf.c = 128;  // Input Channels
  conf.input_buf.mem = io_mem_;
  conf.input_buf.offs = 0;

  // Output Configuration:
  conf.output_buf.mem = io_mem_;
  conf.output_buf.offs = 294912;

  conf.eltwise_buf.mem = NULL;
  conf.eltwise_buf.offs = 0;  // Input byte address for elementwise add (0 = UBUF Input Buffer)
  conf.output_mode = 0;  // 0 = concat, 1 = eltwise add

  // Runs Configuration:
  // ->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv2d_5
  //->: batch_normalization_5
  //->: batch_normalization_5
  //->: leaky_re_lu_5
  conf.run[0].m = 256;  // Output Channels
  conf.run[0].conv_enable = 1;  // 1 = Enabled, 0 = Disabled
  conf.run[0].p = 0x3;  // Filter Width and Height
  conf.run[0].pz = 1;  // Filter Depth
  conf.run[0].weight_buf.mem = weights_mem_;
  conf.run[0].weight_buf.offs = 196320;
  conf.run[0].weight_fmt = 1;  // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  conf.run[0].conv_pad = 0x1010101;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].conv_stride = 0x101;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].conv_dilation = 0x0;  // bits [7:0] = X dilation, bits [15:8] = Y dilation
  conf.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  conf.run[0].pool_size = 0x0;  // bits [7:0] = width, bits [15:8] = height
  conf.run[0].pool_stride = 0x101;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].pool_pad = 0x0;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].pool_avg_param = 0x0;  // Usually set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  conf.run[0].actfunc = 2;  // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  conf.run[0].actfunc_param = 0x2E66;  // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  conf.run[0].rectifi_en = 0;  // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  conf.run[0].lrn = 0x0;  // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2

  fpga_layer& layer = get_layer(7);
  layer.type = LT_CONV;
  layer.input_offs = 0;
  layer.output_offs = 294912;
  layer.output_size = 294912;
  layer.input_dim[0] = 32;
  layer.input_dim[1] = 18;
  layer.input_dim[2] = 128;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 32;
  layer.output_dim[1] = 18;
  layer.output_dim[2] = 256;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_7

//Layer_8: Convolution Layer
//  ->: max_pooling2d_5
void CYOLOv3Pywrap::Layer_8() {
  get_layer(8).name = "max_pooling2d_5";
  dmp_dv_cmdraw_conv_v0& conf = get_layer(8).conv_conf;
  conf.header.size = sizeof(conf);
  conf.header.device_type = DMP_DV_DEV_CONV;
  conf.header.version = 0;
  // Topo: 00000000000000000000000000000001
  conf.topo = 0x1;  // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  // Input Configuration:
  conf.w = 32;  // Input Width
  conf.h = 18;  // Input Height
  conf.z = 1;  // Input Depth
  conf.c = 256;  // Input Channels
  conf.input_buf.mem = io_mem_;
  conf.input_buf.offs = 294912;

  // Output Configuration:
  conf.output_buf.mem = io_mem_;
  conf.output_buf.offs = 0;

  conf.eltwise_buf.mem = NULL;
  conf.eltwise_buf.offs = 0;  // Input byte address for elementwise add (0 = UBUF Input Buffer)
  conf.output_mode = 0;  // 0 = concat, 1 = eltwise add

  // Runs Configuration:
  // ->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: max_pooling2d_5
  conf.run[0].m = 256;  // Output Channels
  conf.run[0].conv_enable = 0;  // 1 = Enabled, 0 = Disabled
  conf.run[0].p = 0x1;  // Filter Width and Height
  conf.run[0].pz = 1;  // Filter Depth
  conf.run[0].weight_buf.mem = weights_mem_;
  conf.run[0].weight_buf.offs = 786656;
  conf.run[0].weight_fmt = 0;  // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  conf.run[0].conv_pad = 0x0;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].conv_stride = 0x101;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].conv_dilation = 0x0;  // bits [7:0] = X dilation, bits [15:8] = Y dilation
  conf.run[0].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  conf.run[0].pool_size = 0x202;  // bits [7:0] = width, bits [15:8] = height
  conf.run[0].pool_stride = 0x202;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].pool_pad = 0x0;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].pool_avg_param = 0x0;  // Usually set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  conf.run[0].actfunc = 0;  // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  conf.run[0].actfunc_param = 0x0;  // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  conf.run[0].rectifi_en = 0;  // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  conf.run[0].lrn = 0x0;  // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2

  fpga_layer& layer = get_layer(8);
  layer.type = LT_CONV;
  layer.input_offs = 294912;
  layer.output_offs = 0;
  layer.output_size = 73728;
  layer.input_dim[0] = 32;
  layer.input_dim[1] = 18;
  layer.input_dim[2] = 256;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 16;
  layer.output_dim[1] = 9;
  layer.output_dim[2] = 256;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_8

//Layer_9: Convolution Layer
//  ->: conv2d_6
//  ->: batch_normalization_6
//  ->: batch_normalization_6
//  ->: leaky_re_lu_6
//  ->: max_pooling2d_6
void CYOLOv3Pywrap::Layer_9() {
  get_layer(9).name = "conv2d_6, batch_normalization_6, batch_normalization_6, leaky_re_lu_6, max_pooling2d_6";
  dmp_dv_cmdraw_conv_v0& conf = get_layer(9).conv_conf;
  conf.header.size = sizeof(conf);
  conf.header.device_type = DMP_DV_DEV_CONV;
  conf.header.version = 0;
  // Topo: 00000000000000000000000000000001
  conf.topo = 0x1;  // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  // Input Configuration:
  conf.w = 16;  // Input Width
  conf.h = 9;  // Input Height
  conf.z = 1;  // Input Depth
  conf.c = 256;  // Input Channels
  conf.input_buf.mem = io_mem_;
  conf.input_buf.offs = 0;

  // Output Configuration:
  conf.output_buf.mem = io_mem_;
  conf.output_buf.offs = 589824;

  conf.eltwise_buf.mem = NULL;
  conf.eltwise_buf.offs = 0;  // Input byte address for elementwise add (0 = UBUF Input Buffer)
  conf.output_mode = 0;  // 0 = concat, 1 = eltwise add

  // Runs Configuration:
  // ->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv2d_6
  //->: batch_normalization_6
  //->: batch_normalization_6
  //->: leaky_re_lu_6
  //->: max_pooling2d_6
  conf.run[0].m = 512;  // Output Channels
  conf.run[0].conv_enable = 1;  // 1 = Enabled, 0 = Disabled
  conf.run[0].p = 0x3;  // Filter Width and Height
  conf.run[0].pz = 1;  // Filter Depth
  conf.run[0].weight_buf.mem = weights_mem_;
  conf.run[0].weight_buf.offs = 786656;
  conf.run[0].weight_fmt = 1;  // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  conf.run[0].conv_pad = 0x1010101;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].conv_stride = 0x101;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].conv_dilation = 0x0;  // bits [7:0] = X dilation, bits [15:8] = Y dilation
  conf.run[0].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  conf.run[0].pool_size = 0x202;  // bits [7:0] = width, bits [15:8] = height
  conf.run[0].pool_stride = 0x101;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].pool_pad = 0x1000100;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].pool_avg_param = 0x0;  // Usually set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  conf.run[0].actfunc = 2;  // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  conf.run[0].actfunc_param = 0x2E66;  // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  conf.run[0].rectifi_en = 0;  // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  conf.run[0].lrn = 0x0;  // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2

  fpga_layer& layer = get_layer(9);
  layer.type = LT_CONV;
  layer.input_offs = 0;
  layer.output_offs = 589824;
  layer.output_size = 147456;
  layer.input_dim[0] = 16;
  layer.input_dim[1] = 9;
  layer.input_dim[2] = 256;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 16;
  layer.output_dim[1] = 9;
  layer.output_dim[2] = 512;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_9

//Layer_10: Convolution Layer
//  ->: conv2d_7
//  ->: batch_normalization_7
//  ->: batch_normalization_7
//  ->: leaky_re_lu_7
void CYOLOv3Pywrap::Layer_10() {
  get_layer(10).name = "conv2d_7, batch_normalization_7, batch_normalization_7, leaky_re_lu_7";
  dmp_dv_cmdraw_conv_v0& conf = get_layer(10).conv_conf;
  conf.header.size = sizeof(conf);
  conf.header.device_type = DMP_DV_DEV_CONV;
  conf.header.version = 0;
  // Topo: 00000000000000000000000000000001
  conf.topo = 0x1;  // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  // Input Configuration:
  conf.w = 16;  // Input Width
  conf.h = 9;  // Input Height
  conf.z = 1;  // Input Depth
  conf.c = 512;  // Input Channels
  conf.input_buf.mem = io_mem_;
  conf.input_buf.offs = 589824;

  // Output Configuration:
  conf.output_buf.mem = io_mem_;
  conf.output_buf.offs = 737280;

  conf.eltwise_buf.mem = NULL;
  conf.eltwise_buf.offs = 0;  // Input byte address for elementwise add (0 = UBUF Input Buffer)
  conf.output_mode = 0;  // 0 = concat, 1 = eltwise add

  // Runs Configuration:
  // ->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv2d_7
  //->: batch_normalization_7
  //->: batch_normalization_7
  //->: leaky_re_lu_7
  conf.run[0].m = 1024;  // Output Channels
  conf.run[0].conv_enable = 1;  // 1 = Enabled, 0 = Disabled
  conf.run[0].p = 0x3;  // Filter Width and Height
  conf.run[0].pz = 1;  // Filter Depth
  conf.run[0].weight_buf.mem = weights_mem_;
  conf.run[0].weight_buf.offs = 3146976;
  conf.run[0].weight_fmt = 1;  // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  conf.run[0].conv_pad = 0x1010101;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].conv_stride = 0x101;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].conv_dilation = 0x0;  // bits [7:0] = X dilation, bits [15:8] = Y dilation
  conf.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  conf.run[0].pool_size = 0x0;  // bits [7:0] = width, bits [15:8] = height
  conf.run[0].pool_stride = 0x101;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].pool_pad = 0x0;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].pool_avg_param = 0x0;  // Usually set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  conf.run[0].actfunc = 2;  // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  conf.run[0].actfunc_param = 0x2E66;  // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  conf.run[0].rectifi_en = 0;  // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  conf.run[0].lrn = 0x0;  // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2

  fpga_layer& layer = get_layer(10);
  layer.type = LT_CONV;
  layer.input_offs = 589824;
  layer.output_offs = 737280;
  layer.output_size = 294912;
  layer.input_dim[0] = 16;
  layer.input_dim[1] = 9;
  layer.input_dim[2] = 512;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 16;
  layer.output_dim[1] = 9;
  layer.output_dim[2] = 1024;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_10

//Layer_11: Convolution Layer
//  ->: conv2d_8
//  ->: batch_normalization_8
//  ->: batch_normalization_8
//  ->: leaky_re_lu_8
void CYOLOv3Pywrap::Layer_11() {
  get_layer(11).name = "conv2d_8, batch_normalization_8, batch_normalization_8, leaky_re_lu_8";
  dmp_dv_cmdraw_conv_v0& conf = get_layer(11).conv_conf;
  conf.header.size = sizeof(conf);
  conf.header.device_type = DMP_DV_DEV_CONV;
  conf.header.version = 0;
  // Topo: 00000000000000000000000000000001
  conf.topo = 0x1;  // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  // Input Configuration:
  conf.w = 16;  // Input Width
  conf.h = 9;  // Input Height
  conf.z = 1;  // Input Depth
  conf.c = 1024;  // Input Channels
  conf.input_buf.mem = io_mem_;
  conf.input_buf.offs = 737280;

  // Output Configuration:
  conf.output_buf.mem = io_mem_;
  conf.output_buf.offs = 0;

  conf.eltwise_buf.mem = NULL;
  conf.eltwise_buf.offs = 0;  // Input byte address for elementwise add (0 = UBUF Input Buffer)
  conf.output_mode = 0;  // 0 = concat, 1 = eltwise add

  // Runs Configuration:
  // ->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv2d_8
  //->: batch_normalization_8
  //->: batch_normalization_8
  //->: leaky_re_lu_8
  conf.run[0].m = 256;  // Output Channels
  conf.run[0].conv_enable = 1;  // 1 = Enabled, 0 = Disabled
  conf.run[0].p = 0x1;  // Filter Width and Height
  conf.run[0].pz = 1;  // Filter Depth
  conf.run[0].weight_buf.mem = weights_mem_;
  conf.run[0].weight_buf.offs = 12586208;
  conf.run[0].weight_fmt = 1;  // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  conf.run[0].conv_pad = 0x0;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].conv_stride = 0x101;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].conv_dilation = 0x0;  // bits [7:0] = X dilation, bits [15:8] = Y dilation
  conf.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  conf.run[0].pool_size = 0x0;  // bits [7:0] = width, bits [15:8] = height
  conf.run[0].pool_stride = 0x101;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].pool_pad = 0x0;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].pool_avg_param = 0x0;  // Usually set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  conf.run[0].actfunc = 2;  // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  conf.run[0].actfunc_param = 0x2E66;  // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  conf.run[0].rectifi_en = 0;  // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  conf.run[0].lrn = 0x0;  // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2

  fpga_layer& layer = get_layer(11);
  layer.type = LT_CONV;
  layer.input_offs = 737280;
  layer.output_offs = 0;
  layer.output_size = 73728;
  layer.input_dim[0] = 16;
  layer.input_dim[1] = 9;
  layer.input_dim[2] = 1024;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 16;
  layer.output_dim[1] = 9;
  layer.output_dim[2] = 256;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_11

//Layer_12: Convolution Layer
//  ->: conv2d_9
//  ->: batch_normalization_9
//  ->: batch_normalization_9
//  ->: leaky_re_lu_9
void CYOLOv3Pywrap::Layer_12() {
  get_layer(12).name = "conv2d_9, batch_normalization_9, batch_normalization_9, leaky_re_lu_9";
  dmp_dv_cmdraw_conv_v0& conf = get_layer(12).conv_conf;
  conf.header.size = sizeof(conf);
  conf.header.device_type = DMP_DV_DEV_CONV;
  conf.header.version = 0;
  // Topo: 00000000000000000000000000000001
  conf.topo = 0x1;  // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  // Input Configuration:
  conf.w = 16;  // Input Width
  conf.h = 9;  // Input Height
  conf.z = 1;  // Input Depth
  conf.c = 256;  // Input Channels
  conf.input_buf.mem = io_mem_;
  conf.input_buf.offs = 0;

  // Output Configuration:
  conf.output_buf.mem = io_mem_;
  conf.output_buf.offs = 589824;

  conf.eltwise_buf.mem = NULL;
  conf.eltwise_buf.offs = 0;  // Input byte address for elementwise add (0 = UBUF Input Buffer)
  conf.output_mode = 0;  // 0 = concat, 1 = eltwise add

  // Runs Configuration:
  // ->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv2d_9
  //->: batch_normalization_9
  //->: batch_normalization_9
  //->: leaky_re_lu_9
  conf.run[0].m = 512;  // Output Channels
  conf.run[0].conv_enable = 1;  // 1 = Enabled, 0 = Disabled
  conf.run[0].p = 0x3;  // Filter Width and Height
  conf.run[0].pz = 1;  // Filter Depth
  conf.run[0].weight_buf.mem = weights_mem_;
  conf.run[0].weight_buf.offs = 13176544;
  conf.run[0].weight_fmt = 1;  // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  conf.run[0].conv_pad = 0x1010101;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].conv_stride = 0x101;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].conv_dilation = 0x0;  // bits [7:0] = X dilation, bits [15:8] = Y dilation
  conf.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  conf.run[0].pool_size = 0x0;  // bits [7:0] = width, bits [15:8] = height
  conf.run[0].pool_stride = 0x101;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].pool_pad = 0x0;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].pool_avg_param = 0x0;  // Usually set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  conf.run[0].actfunc = 2;  // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  conf.run[0].actfunc_param = 0x2E66;  // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  conf.run[0].rectifi_en = 0;  // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  conf.run[0].lrn = 0x0;  // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2

  fpga_layer& layer = get_layer(12);
  layer.type = LT_CONV;
  layer.input_offs = 0;
  layer.output_offs = 589824;
  layer.output_size = 147456;
  layer.input_dim[0] = 16;
  layer.input_dim[1] = 9;
  layer.input_dim[2] = 256;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 16;
  layer.output_dim[1] = 9;
  layer.output_dim[2] = 512;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_12

//Layer_13: Convolution Layer
//  ->: conv2d_10
void CYOLOv3Pywrap::Layer_13() {
  get_layer(13).name = "conv2d_10";
  dmp_dv_cmdraw_conv_v0& conf = get_layer(13).conv_conf;
  conf.header.size = sizeof(conf);
  conf.header.device_type = DMP_DV_DEV_CONV;
  conf.header.version = 0;
  // Topo: 00000000000000000000000000000001
  conf.topo = 0x1;  // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  // Input Configuration:
  conf.w = 16;  // Input Width
  conf.h = 9;  // Input Height
  conf.z = 1;  // Input Depth
  conf.c = 512;  // Input Channels
  conf.input_buf.mem = io_mem_;
  conf.input_buf.offs = 589824;

  // Output Configuration:
  conf.output_buf.mem = io_mem_;
  conf.output_buf.offs = 73728;

  conf.eltwise_buf.mem = NULL;
  conf.eltwise_buf.offs = 0;  // Input byte address for elementwise add (0 = UBUF Input Buffer)
  conf.output_mode = 0;  // 0 = concat, 1 = eltwise add

  // Runs Configuration:
  // ->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv2d_10
  conf.run[0].m = 255;  // Output Channels
  conf.run[0].conv_enable = 1;  // 1 = Enabled, 0 = Disabled
  conf.run[0].p = 0x1;  // Filter Width and Height
  conf.run[0].pz = 1;  // Filter Depth
  conf.run[0].weight_buf.mem = weights_mem_;
  conf.run[0].weight_buf.offs = 15536864;
  conf.run[0].weight_fmt = 1;  // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  conf.run[0].conv_pad = 0x0;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].conv_stride = 0x101;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].conv_dilation = 0x0;  // bits [7:0] = X dilation, bits [15:8] = Y dilation
  conf.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  conf.run[0].pool_size = 0x0;  // bits [7:0] = width, bits [15:8] = height
  conf.run[0].pool_stride = 0x101;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].pool_pad = 0x0;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].pool_avg_param = 0x0;  // Usually set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  conf.run[0].actfunc = 0;  // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  conf.run[0].actfunc_param = 0x0;  // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  conf.run[0].rectifi_en = 0;  // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  conf.run[0].lrn = 0x0;  // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2

  fpga_layer& layer = get_layer(13);
  layer.type = LT_CONV;
  layer.input_offs = 589824;
  layer.output_offs = 73728;
  layer.output_size = 73440;
  layer.input_dim[0] = 16;
  layer.input_dim[1] = 9;
  layer.input_dim[2] = 512;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 16;
  layer.output_dim[1] = 9;
  layer.output_dim[2] = 255;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_13

//Layer_14: Flatten Layer
//	->: flatten_1
void CYOLOv3Pywrap::Layer_14() {
  fpga_layer& layer = get_layer(14);
  layer.type = LT_FLATTEN;
  layer.input_offs = 73728;
  layer.output_offs = 589824;
  layer.output_size = 73440;
  layer.input_dim[0] = 16;
  layer.input_dim[1] = 9;
  layer.input_dim[2] = 255;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 36720;
  layer.output_dim_size = 1;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_14

//Layer_15: Convolution Layer
//  ->: conv2d_11
//  ->: batch_normalization_10
//  ->: batch_normalization_10
//  ->: leaky_re_lu_10
void CYOLOv3Pywrap::Layer_15() {
  get_layer(15).name = "conv2d_11, batch_normalization_10, batch_normalization_10, leaky_re_lu_10";
  dmp_dv_cmdraw_conv_v0& conf = get_layer(15).conv_conf;
  conf.header.size = sizeof(conf);
  conf.header.device_type = DMP_DV_DEV_CONV;
  conf.header.version = 0;
  // Topo: 00000000000000000000000000000001
  conf.topo = 0x1;  // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  // Input Configuration:
  conf.w = 16;  // Input Width
  conf.h = 9;  // Input Height
  conf.z = 1;  // Input Depth
  conf.c = 256;  // Input Channels
  conf.input_buf.mem = io_mem_;
  conf.input_buf.offs = 0;

  // Output Configuration:
  conf.output_buf.mem = io_mem_;
  conf.output_buf.offs = 73728;

  conf.eltwise_buf.mem = NULL;
  conf.eltwise_buf.offs = 0;  // Input byte address for elementwise add (0 = UBUF Input Buffer)
  conf.output_mode = 0;  // 0 = concat, 1 = eltwise add

  // Runs Configuration:
  // ->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv2d_11
  //->: batch_normalization_10
  //->: batch_normalization_10
  //->: leaky_re_lu_10
  conf.run[0].m = 128;  // Output Channels
  conf.run[0].conv_enable = 1;  // 1 = Enabled, 0 = Disabled
  conf.run[0].p = 0x1;  // Filter Width and Height
  conf.run[0].pz = 1;  // Filter Depth
  conf.run[0].weight_buf.mem = weights_mem_;
  conf.run[0].weight_buf.offs = 15831136;
  conf.run[0].weight_fmt = 1;  // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  conf.run[0].conv_pad = 0x0;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].conv_stride = 0x101;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].conv_dilation = 0x0;  // bits [7:0] = X dilation, bits [15:8] = Y dilation
  conf.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  conf.run[0].pool_size = 0x0;  // bits [7:0] = width, bits [15:8] = height
  conf.run[0].pool_stride = 0x101;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].pool_pad = 0x0;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].pool_avg_param = 0x0;  // Usually set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  conf.run[0].actfunc = 2;  // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  conf.run[0].actfunc_param = 0x2E66;  // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  conf.run[0].rectifi_en = 0;  // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  conf.run[0].lrn = 0x0;  // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2

  fpga_layer& layer = get_layer(15);
  layer.type = LT_CONV;
  layer.input_offs = 0;
  layer.output_offs = 73728;
  layer.output_size = 36864;
  layer.input_dim[0] = 16;
  layer.input_dim[1] = 9;
  layer.input_dim[2] = 256;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 16;
  layer.output_dim[1] = 9;
  layer.output_dim[2] = 128;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_15

//Layer_16: Convolution Layer
//  ->: up_sampling2d_1
void CYOLOv3Pywrap::Layer_16() {
  get_layer(16).name = "up_sampling2d_1";
  dmp_dv_cmdraw_conv_v0& conf = get_layer(16).conv_conf;
  conf.header.size = sizeof(conf);
  conf.header.device_type = DMP_DV_DEV_CONV;
  conf.header.version = 0;
  // Topo: 00000000000000000000000000000001
  conf.topo = 0x1;  // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  // Input Configuration:
  conf.w = 16;  // Input Width
  conf.h = 9;  // Input Height
  conf.z = 1;  // Input Depth
  conf.c = 128;  // Input Channels
  conf.input_buf.mem = io_mem_;
  conf.input_buf.offs = 73728;

  // Output Configuration:
  conf.output_buf.mem = io_mem_;
  conf.output_buf.offs = 147456;

  conf.eltwise_buf.mem = NULL;
  conf.eltwise_buf.offs = 0;  // Input byte address for elementwise add (0 = UBUF Input Buffer)
  conf.output_mode = 0;  // 0 = concat, 1 = eltwise add

  // Runs Configuration:
  // ->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: up_sampling2d_1
  conf.run[0].m = 128;  // Output Channels
  conf.run[0].conv_enable = 0;  // 1 = Enabled, 0 = Disabled
  conf.run[0].p = 0x1;  // Filter Width and Height
  conf.run[0].pz = 1;  // Filter Depth
  conf.run[0].weight_buf.mem = weights_mem_;
  conf.run[0].weight_buf.offs = 15905120;
  conf.run[0].weight_fmt = 0;  // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  conf.run[0].conv_pad = 0x0;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].conv_stride = 0x101;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].conv_dilation = 0x0;  // bits [7:0] = X dilation, bits [15:8] = Y dilation
  conf.run[0].pool_enable = 4;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  conf.run[0].pool_size = 0x202;  // bits [7:0] = width, bits [15:8] = height
  conf.run[0].pool_stride = 0x101;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].pool_pad = 0x0;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].pool_avg_param = 0x0;  // Usually set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  conf.run[0].actfunc = 0;  // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  conf.run[0].actfunc_param = 0x0;  // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  conf.run[0].rectifi_en = 0;  // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  conf.run[0].lrn = 0x0;  // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2

  fpga_layer& layer = get_layer(16);
  layer.type = LT_CONV;
  layer.input_offs = 73728;
  layer.output_offs = 147456;
  layer.output_size = 147456;
  layer.input_dim[0] = 16;
  layer.input_dim[1] = 9;
  layer.input_dim[2] = 128;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 32;
  layer.output_dim[1] = 18;
  layer.output_dim[2] = 128;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_16

//Layer_17: Concatenate Layer
//	->: concatenate_1
void CYOLOv3Pywrap::Layer_17() {
  fpga_layer& layer = get_layer(17);
  layer.type = LT_CONCAT;
  layer.input_offs = 147456;
  layer.output_offs = 147456;
  layer.output_size = 442368;
  layer.input_dim[0] = 32;
  layer.input_dim[1] = 18;
  layer.input_dim[2] = 384;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 32;
  layer.output_dim[1] = 18;
  layer.output_dim[2] = 384;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_17

//Layer_18: Convolution Layer
//  ->: conv2d_12
//  ->: batch_normalization_11
//  ->: batch_normalization_11
//  ->: leaky_re_lu_11
void CYOLOv3Pywrap::Layer_18() {
  get_layer(18).name = "conv2d_12, batch_normalization_11, batch_normalization_11, leaky_re_lu_11";
  dmp_dv_cmdraw_conv_v0& conf = get_layer(18).conv_conf;
  conf.header.size = sizeof(conf);
  conf.header.device_type = DMP_DV_DEV_CONV;
  conf.header.version = 0;
  // Topo: 00000000000000000000000000000001
  conf.topo = 0x1;  // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  // Input Configuration:
  conf.w = 32;  // Input Width
  conf.h = 18;  // Input Height
  conf.z = 1;  // Input Depth
  conf.c = 384;  // Input Channels
  conf.input_buf.mem = io_mem_;
  conf.input_buf.offs = 147456;

  // Output Configuration:
  conf.output_buf.mem = io_mem_;
  conf.output_buf.offs = 957024;

  conf.eltwise_buf.mem = NULL;
  conf.eltwise_buf.offs = 0;  // Input byte address for elementwise add (0 = UBUF Input Buffer)
  conf.output_mode = 0;  // 0 = concat, 1 = eltwise add

  // Runs Configuration:
  // ->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv2d_12
  //->: batch_normalization_11
  //->: batch_normalization_11
  //->: leaky_re_lu_11
  conf.run[0].m = 256;  // Output Channels
  conf.run[0].conv_enable = 1;  // 1 = Enabled, 0 = Disabled
  conf.run[0].p = 0x3;  // Filter Width and Height
  conf.run[0].pz = 1;  // Filter Depth
  conf.run[0].weight_buf.mem = weights_mem_;
  conf.run[0].weight_buf.offs = 15905120;
  conf.run[0].weight_fmt = 1;  // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  conf.run[0].conv_pad = 0x1010101;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].conv_stride = 0x101;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].conv_dilation = 0x0;  // bits [7:0] = X dilation, bits [15:8] = Y dilation
  conf.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  conf.run[0].pool_size = 0x0;  // bits [7:0] = width, bits [15:8] = height
  conf.run[0].pool_stride = 0x101;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].pool_pad = 0x0;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].pool_avg_param = 0x0;  // Usually set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  conf.run[0].actfunc = 2;  // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  conf.run[0].actfunc_param = 0x2E66;  // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  conf.run[0].rectifi_en = 0;  // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  conf.run[0].lrn = 0x0;  // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2

  fpga_layer& layer = get_layer(18);
  layer.type = LT_CONV;
  layer.input_offs = 147456;
  layer.output_offs = 957024;
  layer.output_size = 294912;
  layer.input_dim[0] = 32;
  layer.input_dim[1] = 18;
  layer.input_dim[2] = 384;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 32;
  layer.output_dim[1] = 18;
  layer.output_dim[2] = 256;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = false;
}//end of  Layer_18

//Layer_19: Convolution Layer
//  ->: conv2d_13
void CYOLOv3Pywrap::Layer_19() {
  get_layer(19).name = "conv2d_13";
  dmp_dv_cmdraw_conv_v0& conf = get_layer(19).conv_conf;
  conf.header.size = sizeof(conf);
  conf.header.device_type = DMP_DV_DEV_CONV;
  conf.header.version = 0;
  // Topo: 00000000000000000000000000000001
  conf.topo = 0x1;  // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  // Input Configuration:
  conf.w = 32;  // Input Width
  conf.h = 18;  // Input Height
  conf.z = 1;  // Input Depth
  conf.c = 256;  // Input Channels
  conf.input_buf.mem = io_mem_;
  conf.input_buf.offs = 957024;

  // Output Configuration:
  conf.output_buf.mem = io_mem_;
  conf.output_buf.offs = 0;

  conf.eltwise_buf.mem = NULL;
  conf.eltwise_buf.offs = 0;  // Input byte address for elementwise add (0 = UBUF Input Buffer)
  conf.output_mode = 0;  // 0 = concat, 1 = eltwise add

  // Runs Configuration:
  // ->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv2d_13
  conf.run[0].m = 255;  // Output Channels
  conf.run[0].conv_enable = 1;  // 1 = Enabled, 0 = Disabled
  conf.run[0].p = 0x1;  // Filter Width and Height
  conf.run[0].pz = 1;  // Filter Depth
  conf.run[0].weight_buf.mem = weights_mem_;
  conf.run[0].weight_buf.offs = 17675104;
  conf.run[0].weight_fmt = 1;  // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  conf.run[0].conv_pad = 0x0;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].conv_stride = 0x101;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].conv_dilation = 0x0;  // bits [7:0] = X dilation, bits [15:8] = Y dilation
  conf.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  conf.run[0].pool_size = 0x0;  // bits [7:0] = width, bits [15:8] = height
  conf.run[0].pool_stride = 0x101;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].pool_pad = 0x0;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].pool_avg_param = 0x0;  // Usually set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  conf.run[0].actfunc = 0;  // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  conf.run[0].actfunc_param = 0x0;  // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  conf.run[0].rectifi_en = 0;  // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  conf.run[0].lrn = 0x0;  // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2

  fpga_layer& layer = get_layer(19);
  layer.type = LT_CONV;
  layer.input_offs = 957024;
  layer.output_offs = 0;
  layer.output_size = 293760;
  layer.input_dim[0] = 32;
  layer.input_dim[1] = 18;
  layer.input_dim[2] = 256;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 32;
  layer.output_dim[1] = 18;
  layer.output_dim[2] = 255;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_19

//Layer_20: Flatten Layer
//	->: flatten_2
void CYOLOv3Pywrap::Layer_20() {
  fpga_layer& layer = get_layer(20);
  layer.type = LT_FLATTEN;
  layer.input_offs = 0;
  layer.output_offs = 663264;
  layer.output_size = 293760;
  layer.input_dim[0] = 32;
  layer.input_dim[1] = 18;
  layer.input_dim[2] = 255;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 146880;
  layer.output_dim_size = 1;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_20

//Layer_21: Concatenate Layer
//	->: concatenate_2
void CYOLOv3Pywrap::Layer_21() {
  fpga_layer& layer = get_layer(21);
  layer.type = LT_CONCAT;
  layer.input_offs = 589824;
  layer.output_offs = 589824;
  layer.output_size = 367200;
  layer.input_dim[0] = 183600;
  layer.input_dim_size = 1;
  layer.output_dim[0] = 183600;
  layer.output_dim_size = 1;
  layer.is_output = true;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = false;
  output_layers_[0] = &layer;
}//end of  Layer_21

