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

#include "DeconvNetBasic_gen.h"


CDeconvNetBasic::CDeconvNetBasic() {
  // Empty by design
}

CDeconvNetBasic::~CDeconvNetBasic() {
  // Empty by design
}

bool CDeconvNetBasic::Initialize() {
  if (!ReserveMemory(1596608, 23347200)) {
    return false;
  }

  set_num_layers(17);
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

  return true;
}

//Layer_0: Convolution Layer
//  ->: conv2d_1
//  ->: batch_normalization_1
//  ->: batch_normalization_1
//  ->: re_lu_1
void CDeconvNetBasic::Layer_0() {
  dmp_dv_cmdraw_conv_v0& conf = get_layer(0).conv_conf;
  conf.header.size = sizeof(conf);
  conf.header.device_type = DMP_DV_DEV_CONV;
  conf.header.version = 0;
  // Topo: 00000000000000000000000000000001
  conf.topo = 0x1;  // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  // Input Configuration:
  conf.w = 320;  // Input Width
  conf.h = 240;  // Input Height
  conf.z = 1;  // Input Depth
  conf.c = 3;  // Input Channels
  conf.input_buf.mem = io_mem_;
  conf.input_buf.offs = 0;

  // Output Configuration:
  conf.output_buf.mem = io_mem_;
  conf.output_buf.offs = 7756800;

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
  //->: re_lu_1
  conf.run[0].m = 64;  // Output Channels
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
  conf.run[0].actfunc_param = 0x0;  // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  conf.run[0].rectifi_en = 0;  // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  conf.run[0].lrn = 0x0;  // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2

  fpga_layer& layer = get_layer(0);
  layer.name = "conv2d_1";
  layer.type = LT_CONV;
  layer.input_offs = 0;
  layer.output_offs = 7756800;
  layer.output_size = 9830400;
  layer.input_dim[0] = 320;
  layer.input_dim[1] = 240;
  layer.input_dim[2] = 3;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 320;
  layer.output_dim[1] = 240;
  layer.output_dim[2] = 64;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = false;
}//end of  Layer_0

//Layer_1: Convolution Layer
//  ->: max_pooling2d_1
void CDeconvNetBasic::Layer_1() {
  dmp_dv_cmdraw_conv_v0& conf = get_layer(1).conv_conf;
  conf.header.size = sizeof(conf);
  conf.header.device_type = DMP_DV_DEV_CONV;
  conf.header.version = 0;
  // Topo: 00000000000000000000000000000001
  conf.topo = 0x1;  // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  // Input Configuration:
  conf.w = 320;  // Input Width
  conf.h = 240;  // Input Height
  conf.z = 1;  // Input Depth
  conf.c = 64;  // Input Channels
  conf.input_buf.mem = io_mem_;
  conf.input_buf.offs = 7756800;

  // Output Configuration:
  conf.output_buf.mem = io_mem_;
  conf.output_buf.offs = 5299200;

  conf.eltwise_buf.mem = NULL;
  conf.eltwise_buf.offs = 0;  // Input byte address for elementwise add (0 = UBUF Input Buffer)
  conf.output_mode = 0;  // 0 = concat, 1 = eltwise add

  // Runs Configuration:
  // ->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: max_pooling2d_1
  conf.run[0].m = 64;  // Output Channels
  conf.run[0].conv_enable = 0;  // 1 = Enabled, 0 = Disabled
  conf.run[0].p = 0x1;  // Filter Width and Height
  conf.run[0].pz = 1;  // Filter Depth
  conf.run[0].weight_buf.mem = weights_mem_;
  conf.run[0].weight_buf.offs = 9344;
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
  layer.name = "max_pooling2d_1";
  layer.type = LT_CONV;
  layer.input_offs = 7756800;
  layer.output_offs = 5299200;
  layer.output_size = 2457600;
  layer.input_dim[0] = 320;
  layer.input_dim[1] = 240;
  layer.input_dim[2] = 64;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 160;
  layer.output_dim[1] = 120;
  layer.output_dim[2] = 64;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_1

//Layer_2: Convolution Layer
//  ->: conv2d_2
//  ->: batch_normalization_4
//  ->: batch_normalization_4
//  ->: re_lu_4
void CDeconvNetBasic::Layer_2() {
  dmp_dv_cmdraw_conv_v0& conf = get_layer(2).conv_conf;
  conf.header.size = sizeof(conf);
  conf.header.device_type = DMP_DV_DEV_CONV;
  conf.header.version = 0;
  // Topo: 00000000000000000000000000000001
  conf.topo = 0x1;  // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  // Input Configuration:
  conf.w = 160;  // Input Width
  conf.h = 120;  // Input Height
  conf.z = 1;  // Input Depth
  conf.c = 64;  // Input Channels
  conf.input_buf.mem = io_mem_;
  conf.input_buf.offs = 5299200;

  // Output Configuration:
  conf.output_buf.mem = io_mem_;
  conf.output_buf.offs = 2227200;

  conf.eltwise_buf.mem = NULL;
  conf.eltwise_buf.offs = 0;  // Input byte address for elementwise add (0 = UBUF Input Buffer)
  conf.output_mode = 0;  // 0 = concat, 1 = eltwise add

  // Runs Configuration:
  // ->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv2d_2
  //->: batch_normalization_4
  //->: batch_normalization_4
  //->: re_lu_4
  conf.run[0].m = 80;  // Output Channels
  conf.run[0].conv_enable = 1;  // 1 = Enabled, 0 = Disabled
  conf.run[0].p = 0x3;  // Filter Width and Height
  conf.run[0].pz = 1;  // Filter Depth
  conf.run[0].weight_buf.mem = weights_mem_;
  conf.run[0].weight_buf.offs = 9344;
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
  conf.run[0].actfunc_param = 0x0;  // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  conf.run[0].rectifi_en = 0;  // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  conf.run[0].lrn = 0x0;  // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2

  fpga_layer& layer = get_layer(2);
  layer.name = "conv2d_2";
  layer.type = LT_CONV;
  layer.input_offs = 5299200;
  layer.output_offs = 2227200;
  layer.output_size = 3072000;
  layer.input_dim[0] = 160;
  layer.input_dim[1] = 120;
  layer.input_dim[2] = 64;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 160;
  layer.output_dim[1] = 120;
  layer.output_dim[2] = 80;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_2

//Layer_3: Convolution Layer
//  ->: max_pooling2d_2
void CDeconvNetBasic::Layer_3() {
  dmp_dv_cmdraw_conv_v0& conf = get_layer(3).conv_conf;
  conf.header.size = sizeof(conf);
  conf.header.device_type = DMP_DV_DEV_CONV;
  conf.header.version = 0;
  // Topo: 00000000000000000000000000000001
  conf.topo = 0x1;  // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  // Input Configuration:
  conf.w = 160;  // Input Width
  conf.h = 120;  // Input Height
  conf.z = 1;  // Input Depth
  conf.c = 80;  // Input Channels
  conf.input_buf.mem = io_mem_;
  conf.input_buf.offs = 2227200;

  // Output Configuration:
  conf.output_buf.mem = io_mem_;
  conf.output_buf.offs = 1459200;

  conf.eltwise_buf.mem = NULL;
  conf.eltwise_buf.offs = 0;  // Input byte address for elementwise add (0 = UBUF Input Buffer)
  conf.output_mode = 0;  // 0 = concat, 1 = eltwise add

  // Runs Configuration:
  // ->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: max_pooling2d_2
  conf.run[0].m = 80;  // Output Channels
  conf.run[0].conv_enable = 0;  // 1 = Enabled, 0 = Disabled
  conf.run[0].p = 0x1;  // Filter Width and Height
  conf.run[0].pz = 1;  // Filter Depth
  conf.run[0].weight_buf.mem = weights_mem_;
  conf.run[0].weight_buf.offs = 101664;
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
  layer.name = "max_pooling2d_2";
  layer.type = LT_CONV;
  layer.input_offs = 2227200;
  layer.output_offs = 1459200;
  layer.output_size = 768000;
  layer.input_dim[0] = 160;
  layer.input_dim[1] = 120;
  layer.input_dim[2] = 80;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 80;
  layer.output_dim[1] = 60;
  layer.output_dim[2] = 80;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_3

//Layer_4: Convolution Layer
//  ->: conv2d_3
//  ->: batch_normalization_7
//  ->: batch_normalization_7
//  ->: re_lu_7
void CDeconvNetBasic::Layer_4() {
  dmp_dv_cmdraw_conv_v0& conf = get_layer(4).conv_conf;
  conf.header.size = sizeof(conf);
  conf.header.device_type = DMP_DV_DEV_CONV;
  conf.header.version = 0;
  // Topo: 00000000000000000000000000000001
  conf.topo = 0x1;  // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  // Input Configuration:
  conf.w = 80;  // Input Width
  conf.h = 60;  // Input Height
  conf.z = 1;  // Input Depth
  conf.c = 80;  // Input Channels
  conf.input_buf.mem = io_mem_;
  conf.input_buf.offs = 1459200;

  // Output Configuration:
  conf.output_buf.mem = io_mem_;
  conf.output_buf.offs = 537600;

  conf.eltwise_buf.mem = NULL;
  conf.eltwise_buf.offs = 0;  // Input byte address for elementwise add (0 = UBUF Input Buffer)
  conf.output_mode = 0;  // 0 = concat, 1 = eltwise add

  // Runs Configuration:
  // ->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv2d_3
  //->: batch_normalization_7
  //->: batch_normalization_7
  //->: re_lu_7
  conf.run[0].m = 96;  // Output Channels
  conf.run[0].conv_enable = 1;  // 1 = Enabled, 0 = Disabled
  conf.run[0].p = 0x3;  // Filter Width and Height
  conf.run[0].pz = 1;  // Filter Depth
  conf.run[0].weight_buf.mem = weights_mem_;
  conf.run[0].weight_buf.offs = 101664;
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
  conf.run[0].actfunc_param = 0x0;  // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  conf.run[0].rectifi_en = 0;  // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  conf.run[0].lrn = 0x0;  // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2

  fpga_layer& layer = get_layer(4);
  layer.name = "conv2d_3";
  layer.type = LT_CONV;
  layer.input_offs = 1459200;
  layer.output_offs = 537600;
  layer.output_size = 921600;
  layer.input_dim[0] = 80;
  layer.input_dim[1] = 60;
  layer.input_dim[2] = 80;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 80;
  layer.output_dim[1] = 60;
  layer.output_dim[2] = 96;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_4

//Layer_5: Convolution Layer
//  ->: max_pooling2d_3
void CDeconvNetBasic::Layer_5() {
  dmp_dv_cmdraw_conv_v0& conf = get_layer(5).conv_conf;
  conf.header.size = sizeof(conf);
  conf.header.device_type = DMP_DV_DEV_CONV;
  conf.header.version = 0;
  // Topo: 00000000000000000000000000000001
  conf.topo = 0x1;  // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  // Input Configuration:
  conf.w = 80;  // Input Width
  conf.h = 60;  // Input Height
  conf.z = 1;  // Input Depth
  conf.c = 96;  // Input Channels
  conf.input_buf.mem = io_mem_;
  conf.input_buf.offs = 537600;

  // Output Configuration:
  conf.output_buf.mem = io_mem_;
  conf.output_buf.offs = 307200;

  conf.eltwise_buf.mem = NULL;
  conf.eltwise_buf.offs = 0;  // Input byte address for elementwise add (0 = UBUF Input Buffer)
  conf.output_mode = 0;  // 0 = concat, 1 = eltwise add

  // Runs Configuration:
  // ->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: max_pooling2d_3
  conf.run[0].m = 96;  // Output Channels
  conf.run[0].conv_enable = 0;  // 1 = Enabled, 0 = Disabled
  conf.run[0].p = 0x1;  // Filter Width and Height
  conf.run[0].pz = 1;  // Filter Depth
  conf.run[0].weight_buf.mem = weights_mem_;
  conf.run[0].weight_buf.offs = 240096;
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
  layer.name = "max_pooling2d_3";
  layer.type = LT_CONV;
  layer.input_offs = 537600;
  layer.output_offs = 307200;
  layer.output_size = 230400;
  layer.input_dim[0] = 80;
  layer.input_dim[1] = 60;
  layer.input_dim[2] = 96;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 40;
  layer.output_dim[1] = 30;
  layer.output_dim[2] = 96;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_5

//Layer_6: Convolution Layer
//  ->: conv2d_4
//  ->: batch_normalization_10
//  ->: batch_normalization_10
//  ->: re_lu_10
void CDeconvNetBasic::Layer_6() {
  dmp_dv_cmdraw_conv_v0& conf = get_layer(6).conv_conf;
  conf.header.size = sizeof(conf);
  conf.header.device_type = DMP_DV_DEV_CONV;
  conf.header.version = 0;
  // Topo: 00000000000000000000000000000001
  conf.topo = 0x1;  // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  // Input Configuration:
  conf.w = 40;  // Input Width
  conf.h = 30;  // Input Height
  conf.z = 1;  // Input Depth
  conf.c = 96;  // Input Channels
  conf.input_buf.mem = io_mem_;
  conf.input_buf.offs = 307200;

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
  //->: batch_normalization_10
  //->: batch_normalization_10
  //->: re_lu_10
  conf.run[0].m = 128;  // Output Channels
  conf.run[0].conv_enable = 1;  // 1 = Enabled, 0 = Disabled
  conf.run[0].p = 0x3;  // Filter Width and Height
  conf.run[0].pz = 1;  // Filter Depth
  conf.run[0].weight_buf.mem = weights_mem_;
  conf.run[0].weight_buf.offs = 240096;
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
  conf.run[0].actfunc_param = 0x0;  // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  conf.run[0].rectifi_en = 0;  // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  conf.run[0].lrn = 0x0;  // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2

  fpga_layer& layer = get_layer(6);
  layer.name = "conv2d_4";
  layer.type = LT_CONV;
  layer.input_offs = 307200;
  layer.output_offs = 0;
  layer.output_size = 307200;
  layer.input_dim[0] = 40;
  layer.input_dim[1] = 30;
  layer.input_dim[2] = 96;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 40;
  layer.output_dim[1] = 30;
  layer.output_dim[2] = 128;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_6

//Layer_7: Convolution Layer
//  ->: batch_normalization_11
//  ->: batch_normalization_11
//  ->: batch_normalization_11
//  ->: re_lu_11
void CDeconvNetBasic::Layer_7() {
  dmp_dv_cmdraw_conv_v0& conf = get_layer(7).conv_conf;
  conf.header.size = sizeof(conf);
  conf.header.device_type = DMP_DV_DEV_CONV;
  conf.header.version = 0;
  // Topo: 00000000000000000000000000000001
  conf.topo = 0x1;  // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  // Input Configuration:
  conf.w = 40;  // Input Width
  conf.h = 30;  // Input Height
  conf.z = 1;  // Input Depth
  conf.c = 128;  // Input Channels
  conf.input_buf.mem = io_mem_;
  conf.input_buf.offs = 0;

  // Output Configuration:
  conf.output_buf.mem = io_mem_;
  conf.output_buf.offs = 307200;

  conf.eltwise_buf.mem = NULL;
  conf.eltwise_buf.offs = 0;  // Input byte address for elementwise add (0 = UBUF Input Buffer)
  conf.output_mode = 0;  // 0 = concat, 1 = eltwise add

  // Runs Configuration:
  // ->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: batch_normalization_11
  //->: batch_normalization_11
  //->: batch_normalization_11
  //->: re_lu_11
  conf.run[0].m = 128;  // Output Channels
  conf.run[0].conv_enable = 3;  // 1 = Enabled, 0 = Disabled
  conf.run[0].p = 0x1;  // Filter Width and Height
  conf.run[0].pz = 1;  // Filter Depth
  conf.run[0].weight_buf.mem = weights_mem_;
  conf.run[0].weight_buf.offs = 461536;
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
  conf.run[0].actfunc_param = 0x0;  // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  conf.run[0].rectifi_en = 0;  // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  conf.run[0].lrn = 0x0;  // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2

  fpga_layer& layer = get_layer(7);
  layer.name = "batch_normalization_11";
  layer.type = LT_CONV;
  layer.input_offs = 0;
  layer.output_offs = 307200;
  layer.output_size = 307200;
  layer.input_dim[0] = 40;
  layer.input_dim[1] = 30;
  layer.input_dim[2] = 128;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 40;
  layer.output_dim[1] = 30;
  layer.output_dim[2] = 128;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_7

//Layer_8: Convolution Layer
//  ->: conv2d_transpose_8
//  ->: batch_normalization_12
//  ->: batch_normalization_12
//  ->: re_lu_12
void CDeconvNetBasic::Layer_8() {
  dmp_dv_cmdraw_conv_v0& conf = get_layer(8).conv_conf;
  conf.header.size = sizeof(conf);
  conf.header.device_type = DMP_DV_DEV_CONV;
  conf.header.version = 0;
  // Topo: 00000000000000000000000000000001
  conf.topo = 0x1;  // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  // Input Configuration:
  conf.w = 40;  // Input Width
  conf.h = 30;  // Input Height
  conf.z = 1;  // Input Depth
  conf.c = 128;  // Input Channels
  conf.input_buf.mem = io_mem_;
  conf.input_buf.offs = 307200;

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
  //->: conv2d_transpose_8
  //->: batch_normalization_12
  //->: batch_normalization_12
  //->: re_lu_12
  conf.run[0].m = 128;  // Output Channels
  conf.run[0].conv_enable = 5;  // 1 = Enabled, 0 = Disabled
  conf.run[0].p = 0x3;  // Filter Width and Height
  conf.run[0].pz = 1;  // Filter Depth
  conf.run[0].weight_buf.mem = weights_mem_;
  conf.run[0].weight_buf.offs = 480224;
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
  conf.run[0].actfunc_param = 0x0;  // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  conf.run[0].rectifi_en = 0;  // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  conf.run[0].lrn = 0x0;  // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2

  fpga_layer& layer = get_layer(8);
  layer.name = "conv2d_transpose_8";
  layer.type = LT_CONV;
  layer.input_offs = 307200;
  layer.output_offs = 0;
  layer.output_size = 307200;
  layer.input_dim[0] = 40;
  layer.input_dim[1] = 30;
  layer.input_dim[2] = 128;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 40;
  layer.output_dim[1] = 30;
  layer.output_dim[2] = 128;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_8

//Layer_9: Convolution Layer
//  ->: conv2d_transpose_5
//  ->: batch_normalization_8
//  ->: batch_normalization_8
//  ->: re_lu_8
void CDeconvNetBasic::Layer_9() {
  dmp_dv_cmdraw_conv_v0& conf = get_layer(9).conv_conf;
  conf.header.size = sizeof(conf);
  conf.header.device_type = DMP_DV_DEV_CONV;
  conf.header.version = 0;
  // Topo: 00000000000000000000000000000001
  conf.topo = 0x1;  // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  // Input Configuration:
  conf.w = 40;  // Input Width
  conf.h = 30;  // Input Height
  conf.z = 1;  // Input Depth
  conf.c = 128;  // Input Channels
  conf.input_buf.mem = io_mem_;
  conf.input_buf.offs = 0;

  // Output Configuration:
  conf.output_buf.mem = io_mem_;
  conf.output_buf.offs = 921600;

  conf.eltwise_buf.mem = NULL;
  conf.eltwise_buf.offs = 0;  // Input byte address for elementwise add (0 = UBUF Input Buffer)
  conf.output_mode = 0;  // 0 = concat, 1 = eltwise add

  // Runs Configuration:
  // ->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv2d_transpose_5
  //->: batch_normalization_8
  //->: batch_normalization_8
  //->: re_lu_8
  conf.run[0].m = 96;  // Output Channels
  conf.run[0].conv_enable = 5;  // 1 = Enabled, 0 = Disabled
  conf.run[0].p = 0x2;  // Filter Width and Height
  conf.run[0].pz = 1;  // Filter Depth
  conf.run[0].weight_buf.mem = weights_mem_;
  conf.run[0].weight_buf.offs = 775392;
  conf.run[0].weight_fmt = 1;  // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  conf.run[0].conv_pad = 0x1010101;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].conv_stride = 0x202;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].conv_dilation = 0x0;  // bits [7:0] = X dilation, bits [15:8] = Y dilation
  conf.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  conf.run[0].pool_size = 0x0;  // bits [7:0] = width, bits [15:8] = height
  conf.run[0].pool_stride = 0x101;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].pool_pad = 0x0;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].pool_avg_param = 0x0;  // Usually set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  conf.run[0].actfunc = 2;  // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  conf.run[0].actfunc_param = 0x0;  // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  conf.run[0].rectifi_en = 0;  // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  conf.run[0].lrn = 0x0;  // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2

  fpga_layer& layer = get_layer(9);
  layer.name = "conv2d_transpose_5";
  layer.type = LT_CONV;
  layer.input_offs = 0;
  layer.output_offs = 921600;
  layer.output_size = 921600;
  layer.input_dim[0] = 40;
  layer.input_dim[1] = 30;
  layer.input_dim[2] = 128;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 80;
  layer.output_dim[1] = 60;
  layer.output_dim[2] = 96;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_9

//Layer_10: Convolution Layer
//  ->: conv2d_transpose_6
//  ->: batch_normalization_9
//  ->: batch_normalization_9
//  ->: re_lu_9
void CDeconvNetBasic::Layer_10() {
  dmp_dv_cmdraw_conv_v0& conf = get_layer(10).conv_conf;
  conf.header.size = sizeof(conf);
  conf.header.device_type = DMP_DV_DEV_CONV;
  conf.header.version = 0;
  // Topo: 00000000000000000000000000000001
  conf.topo = 0x1;  // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  // Input Configuration:
  conf.w = 80;  // Input Width
  conf.h = 60;  // Input Height
  conf.z = 1;  // Input Depth
  conf.c = 96;  // Input Channels
  conf.input_buf.mem = io_mem_;
  conf.input_buf.offs = 921600;

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
  //->: conv2d_transpose_6
  //->: batch_normalization_9
  //->: batch_normalization_9
  //->: re_lu_9
  conf.run[0].m = 96;  // Output Channels
  conf.run[0].conv_enable = 5;  // 1 = Enabled, 0 = Disabled
  conf.run[0].p = 0x3;  // Filter Width and Height
  conf.run[0].pz = 1;  // Filter Depth
  conf.run[0].weight_buf.mem = weights_mem_;
  conf.run[0].weight_buf.offs = 996768;
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
  conf.run[0].actfunc_param = 0x0;  // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  conf.run[0].rectifi_en = 0;  // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  conf.run[0].lrn = 0x0;  // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2

  fpga_layer& layer = get_layer(10);
  layer.name = "conv2d_transpose_6";
  layer.type = LT_CONV;
  layer.input_offs = 921600;
  layer.output_offs = 0;
  layer.output_size = 921600;
  layer.input_dim[0] = 80;
  layer.input_dim[1] = 60;
  layer.input_dim[2] = 96;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 80;
  layer.output_dim[1] = 60;
  layer.output_dim[2] = 96;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_10

//Layer_11: Convolution Layer
//  ->: conv2d_transpose_3
//  ->: batch_normalization_5
//  ->: batch_normalization_5
//  ->: re_lu_5
void CDeconvNetBasic::Layer_11() {
  dmp_dv_cmdraw_conv_v0& conf = get_layer(11).conv_conf;
  conf.header.size = sizeof(conf);
  conf.header.device_type = DMP_DV_DEV_CONV;
  conf.header.version = 0;
  // Topo: 00000000000000000000000000000001
  conf.topo = 0x1;  // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  // Input Configuration:
  conf.w = 80;  // Input Width
  conf.h = 60;  // Input Height
  conf.z = 1;  // Input Depth
  conf.c = 96;  // Input Channels
  conf.input_buf.mem = io_mem_;
  conf.input_buf.offs = 0;

  // Output Configuration:
  conf.output_buf.mem = io_mem_;
  conf.output_buf.offs = 3072000;

  conf.eltwise_buf.mem = NULL;
  conf.eltwise_buf.offs = 0;  // Input byte address for elementwise add (0 = UBUF Input Buffer)
  conf.output_mode = 0;  // 0 = concat, 1 = eltwise add

  // Runs Configuration:
  // ->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv2d_transpose_3
  //->: batch_normalization_5
  //->: batch_normalization_5
  //->: re_lu_5
  conf.run[0].m = 80;  // Output Channels
  conf.run[0].conv_enable = 5;  // 1 = Enabled, 0 = Disabled
  conf.run[0].p = 0x2;  // Filter Width and Height
  conf.run[0].pz = 1;  // Filter Depth
  conf.run[0].weight_buf.mem = weights_mem_;
  conf.run[0].weight_buf.offs = 1162848;
  conf.run[0].weight_fmt = 1;  // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  conf.run[0].conv_pad = 0x1010101;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].conv_stride = 0x202;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].conv_dilation = 0x0;  // bits [7:0] = X dilation, bits [15:8] = Y dilation
  conf.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  conf.run[0].pool_size = 0x0;  // bits [7:0] = width, bits [15:8] = height
  conf.run[0].pool_stride = 0x101;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].pool_pad = 0x0;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].pool_avg_param = 0x0;  // Usually set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  conf.run[0].actfunc = 2;  // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  conf.run[0].actfunc_param = 0x0;  // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  conf.run[0].rectifi_en = 0;  // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  conf.run[0].lrn = 0x0;  // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2

  fpga_layer& layer = get_layer(11);
  layer.name = "conv2d_transpose_3";
  layer.type = LT_CONV;
  layer.input_offs = 0;
  layer.output_offs = 3072000;
  layer.output_size = 3072000;
  layer.input_dim[0] = 80;
  layer.input_dim[1] = 60;
  layer.input_dim[2] = 96;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 160;
  layer.output_dim[1] = 120;
  layer.output_dim[2] = 80;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_11

//Layer_12: Convolution Layer
//  ->: conv2d_transpose_4
//  ->: batch_normalization_6
//  ->: batch_normalization_6
//  ->: re_lu_6
void CDeconvNetBasic::Layer_12() {
  dmp_dv_cmdraw_conv_v0& conf = get_layer(12).conv_conf;
  conf.header.size = sizeof(conf);
  conf.header.device_type = DMP_DV_DEV_CONV;
  conf.header.version = 0;
  // Topo: 00000000000000000000000000000001
  conf.topo = 0x1;  // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  // Input Configuration:
  conf.w = 160;  // Input Width
  conf.h = 120;  // Input Height
  conf.z = 1;  // Input Depth
  conf.c = 80;  // Input Channels
  conf.input_buf.mem = io_mem_;
  conf.input_buf.offs = 3072000;

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
  //->: conv2d_transpose_4
  //->: batch_normalization_6
  //->: batch_normalization_6
  //->: re_lu_6
  conf.run[0].m = 80;  // Output Channels
  conf.run[0].conv_enable = 5;  // 1 = Enabled, 0 = Disabled
  conf.run[0].p = 0x3;  // Filter Width and Height
  conf.run[0].pz = 1;  // Filter Depth
  conf.run[0].weight_buf.mem = weights_mem_;
  conf.run[0].weight_buf.offs = 1301248;
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
  conf.run[0].actfunc_param = 0x0;  // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  conf.run[0].rectifi_en = 0;  // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  conf.run[0].lrn = 0x0;  // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2

  fpga_layer& layer = get_layer(12);
  layer.name = "conv2d_transpose_4";
  layer.type = LT_CONV;
  layer.input_offs = 3072000;
  layer.output_offs = 0;
  layer.output_size = 3072000;
  layer.input_dim[0] = 160;
  layer.input_dim[1] = 120;
  layer.input_dim[2] = 80;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 160;
  layer.output_dim[1] = 120;
  layer.output_dim[2] = 80;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_12

//Layer_13: Convolution Layer
//  ->: conv2d_transpose_1
//  ->: batch_normalization_2
//  ->: batch_normalization_2
//  ->: re_lu_2
void CDeconvNetBasic::Layer_13() {
  dmp_dv_cmdraw_conv_v0& conf = get_layer(13).conv_conf;
  conf.header.size = sizeof(conf);
  conf.header.device_type = DMP_DV_DEV_CONV;
  conf.header.version = 0;
  // Topo: 00000000000000000000000000000001
  conf.topo = 0x1;  // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  // Input Configuration:
  conf.w = 160;  // Input Width
  conf.h = 120;  // Input Height
  conf.z = 1;  // Input Depth
  conf.c = 80;  // Input Channels
  conf.input_buf.mem = io_mem_;
  conf.input_buf.offs = 0;

  // Output Configuration:
  conf.output_buf.mem = io_mem_;
  conf.output_buf.offs = 13516800;

  conf.eltwise_buf.mem = NULL;
  conf.eltwise_buf.offs = 0;  // Input byte address for elementwise add (0 = UBUF Input Buffer)
  conf.output_mode = 0;  // 0 = concat, 1 = eltwise add

  // Runs Configuration:
  // ->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv2d_transpose_1
  //->: batch_normalization_2
  //->: batch_normalization_2
  //->: re_lu_2
  conf.run[0].m = 64;  // Output Channels
  conf.run[0].conv_enable = 5;  // 1 = Enabled, 0 = Disabled
  conf.run[0].p = 0x2;  // Filter Width and Height
  conf.run[0].pz = 1;  // Filter Depth
  conf.run[0].weight_buf.mem = weights_mem_;
  conf.run[0].weight_buf.offs = 1416608;
  conf.run[0].weight_fmt = 1;  // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  conf.run[0].conv_pad = 0x1010101;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].conv_stride = 0x202;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].conv_dilation = 0x0;  // bits [7:0] = X dilation, bits [15:8] = Y dilation
  conf.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  conf.run[0].pool_size = 0x0;  // bits [7:0] = width, bits [15:8] = height
  conf.run[0].pool_stride = 0x101;  // bits [7:0] = X stride, bits [15:8] = Y stride
  conf.run[0].pool_pad = 0x0;  // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  conf.run[0].pool_avg_param = 0x0;  // Usually set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  conf.run[0].actfunc = 2;  // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  conf.run[0].actfunc_param = 0x0;  // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  conf.run[0].rectifi_en = 0;  // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  conf.run[0].lrn = 0x0;  // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2

  fpga_layer& layer = get_layer(13);
  layer.name = "conv2d_transpose_1";
  layer.type = LT_CONV;
  layer.input_offs = 0;
  layer.output_offs = 13516800;
  layer.output_size = 9830400;
  layer.input_dim[0] = 160;
  layer.input_dim[1] = 120;
  layer.input_dim[2] = 80;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 320;
  layer.output_dim[1] = 240;
  layer.output_dim[2] = 64;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_13

//Layer_14: Convolution Layer
//  ->: conv2d_transpose_2
//  ->: batch_normalization_3
//  ->: batch_normalization_3
//  ->: re_lu_3
void CDeconvNetBasic::Layer_14() {
  dmp_dv_cmdraw_conv_v0& conf = get_layer(14).conv_conf;
  conf.header.size = sizeof(conf);
  conf.header.device_type = DMP_DV_DEV_CONV;
  conf.header.version = 0;
  // Topo: 00000000000000000000000000000001
  conf.topo = 0x1;  // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  // Input Configuration:
  conf.w = 320;  // Input Width
  conf.h = 240;  // Input Height
  conf.z = 1;  // Input Depth
  conf.c = 64;  // Input Channels
  conf.input_buf.mem = io_mem_;
  conf.input_buf.offs = 13516800;

  // Output Configuration:
  conf.output_buf.mem = io_mem_;
  conf.output_buf.offs = 3686400;

  conf.eltwise_buf.mem = NULL;
  conf.eltwise_buf.offs = 0;  // Input byte address for elementwise add (0 = UBUF Input Buffer)
  conf.output_mode = 0;  // 0 = concat, 1 = eltwise add

  // Runs Configuration:
  // ->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv2d_transpose_2
  //->: batch_normalization_3
  //->: batch_normalization_3
  //->: re_lu_3
  conf.run[0].m = 64;  // Output Channels
  conf.run[0].conv_enable = 5;  // 1 = Enabled, 0 = Disabled
  conf.run[0].p = 0x3;  // Filter Width and Height
  conf.run[0].pz = 1;  // Filter Depth
  conf.run[0].weight_buf.mem = weights_mem_;
  conf.run[0].weight_buf.offs = 1508896;
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
  conf.run[0].actfunc_param = 0x0;  // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  conf.run[0].rectifi_en = 0;  // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  conf.run[0].lrn = 0x0;  // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2

  fpga_layer& layer = get_layer(14);
  layer.name = "conv2d_transpose_2";
  layer.type = LT_CONV;
  layer.input_offs = 13516800;
  layer.output_offs = 3686400;
  layer.output_size = 9830400;
  layer.input_dim[0] = 320;
  layer.input_dim[1] = 240;
  layer.input_dim[2] = 64;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 320;
  layer.output_dim[1] = 240;
  layer.output_dim[2] = 64;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_14

//Layer_15: Convolution Layer
//  ->: conv2d_5
//  ->: batch_normalization_13
//  ->: batch_normalization_13
//  ->: re_lu_13
void CDeconvNetBasic::Layer_15() {
  dmp_dv_cmdraw_conv_v0& conf = get_layer(15).conv_conf;
  conf.header.size = sizeof(conf);
  conf.header.device_type = DMP_DV_DEV_CONV;
  conf.header.version = 0;
  // Topo: 00000000000000000000000000000001
  conf.topo = 0x1;  // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  // Input Configuration:
  conf.w = 320;  // Input Width
  conf.h = 240;  // Input Height
  conf.z = 1;  // Input Depth
  conf.c = 64;  // Input Channels
  conf.input_buf.mem = io_mem_;
  conf.input_buf.offs = 3686400;

  // Output Configuration:
  conf.output_buf.mem = io_mem_;
  conf.output_buf.offs = 1843200;

  conf.eltwise_buf.mem = NULL;
  conf.eltwise_buf.offs = 0;  // Input byte address for elementwise add (0 = UBUF Input Buffer)
  conf.output_mode = 0;  // 0 = concat, 1 = eltwise add

  // Runs Configuration:
  // ->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv2d_5
  //->: batch_normalization_13
  //->: batch_normalization_13
  //->: re_lu_13
  conf.run[0].m = 12;  // Output Channels
  conf.run[0].conv_enable = 1;  // 1 = Enabled, 0 = Disabled
  conf.run[0].p = 0x3;  // Filter Width and Height
  conf.run[0].pz = 1;  // Filter Depth
  conf.run[0].weight_buf.mem = weights_mem_;
  conf.run[0].weight_buf.offs = 1582752;
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
  conf.run[0].actfunc_param = 0x0;  // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  conf.run[0].rectifi_en = 0;  // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  conf.run[0].lrn = 0x0;  // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2

  fpga_layer& layer = get_layer(15);
  layer.name = "conv2d_5";
  layer.type = LT_CONV;
  layer.input_offs = 3686400;
  layer.output_offs = 1843200;
  layer.output_size = 1843200;
  layer.input_dim[0] = 320;
  layer.input_dim[1] = 240;
  layer.input_dim[2] = 64;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 320;
  layer.output_dim[1] = 240;
  layer.output_dim[2] = 12;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_15

//Layer_16: Flatten Layer
//	->: dmp_conv_flat_0
void CDeconvNetBasic::Layer_16() {
  fpga_layer& layer = get_layer(16);
  layer.name = "dmp_conv_flat_0";
  layer.type = LT_FLATTEN;
  layer.input_offs = 1843200;
  layer.output_offs = 0;
  layer.output_size = 1843200;
  layer.input_dim[0] = 320;
  layer.input_dim[1] = 240;
  layer.input_dim[2] = 12;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 921600;
  layer.output_dim_size = 1;
  layer.is_output = true;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
  output_layers_[0] = &layer;
}//end of  Layer_16

