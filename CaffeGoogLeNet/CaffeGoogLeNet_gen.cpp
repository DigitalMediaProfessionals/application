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

#include "CaffeGoogLeNet_gen.h"


CCaffeGoogLeNet::CCaffeGoogLeNet() {
  // Empty by design
}


CCaffeGoogLeNet::~CCaffeGoogLeNet() {
  // Empty by design
}


bool CCaffeGoogLeNet::Initialize() {
  if (!ReserveMemory(7629744, 2809856)) {
    return false;
  }

  set_num_layers(18);
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

  if (!GenerateCommandLists()) {
    return false;
  }

  return true;
}


//Layer_0: Convolution Layer
//  ->: conv1/7x7_s2
//  ->: conv1/relu_7x7
//  ->: pool1/3x3_s2
void CCaffeGoogLeNet::Layer_0() {
  dmp_dv_cmdraw_conv_v0& conf = get_layer(0).conv_conf;
  // Topo: 00000000000000000000000000000001
  conf.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  // Input Configuration:
  conf.w = 224;  // Input Width
  conf.h = 224;  // Input Height
  conf.z = 1;    // Input Depth
  conf.c = 3;    // Input Channels
  conf.input_buf.mem = io_mem_;
  conf.input_buf.offs = 0; // Input byte address

  conf.output_buf.mem = io_mem_;
  conf.output_buf.offs = 0x00049800; // Output byte address

  conf.eltwise_buf.mem = NULL;
  conf.eltwise_buf.offs = 0;
  conf.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv1/7x7_s2
  //->: conv1/relu_7x7
  //->: pool1/3x3_s2
  _conf.sw.run[0].in_w = 224; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 224; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 3; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 56; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 56; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 64; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 7; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x00000000; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 14464; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[0].conv_pad = 0x3030303; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].conv_stride = 0x202; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[0].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[0].pool_size = 0x303; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[0].pool_stride = 0x202; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].pool_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[0].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

  struct fpga_layer& layer = layers_[0];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00000000;
  layer.addr_offset_output = 0x00049800;
  layer.output_size = 401408;
  layer.input_dim[0] = 224;
  layer.input_dim[1] = 224;
  layer.input_dim[2] = 3;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 56;
  layer.output_dim[1] = 56;
  layer.output_dim[2] = 64;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = false;
}//end of  Layer_0

//Layer_1: Convolution Layer
//  ->: pool1/norm1
void CCaffeGoogLeNet::Layer_1() {
  struct top_conv_conf& _conf = get_conv_layer(1);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 56; // Input Width
  _conf.hw.input.h = 56; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 64; // Input Channels
  _conf.hw.input.input_base_addr = 0x00049800; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 56; // Output Width
  _conf.sw.output.h = 56; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 64; // Output Channels
  _conf.hw.output.output_base_addr = 0x000AB800; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: pool1/norm1
  _conf.sw.run[0].in_w = 56; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 56; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 64; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 56; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 56; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 64; // Output Channels
  _conf.hw.run[0].conv_enable = 0; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x00003880; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 0; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 0; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[0].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[0].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[0].actfunc = 0; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[0].lrn= 0x403; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

  struct fpga_layer& layer = layers[1];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00049800;
  layer.addr_offset_output = 0x000AB800;
  layer.output_size = 401408;
  layer.input_dim[0] = 56;
  layer.input_dim[1] = 56;
  layer.input_dim[2] = 64;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 56;
  layer.output_dim[1] = 56;
  layer.output_dim[2] = 64;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_1

//Layer_2: Convolution Layer
//  ->: conv2/3x3_reduce
//  ->: conv2/relu_3x3_reduce
void CCaffeGoogLeNet::Layer_2() {
  struct top_conv_conf& _conf = get_conv_layer(2);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 56; // Input Width
  _conf.hw.input.h = 56; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 64; // Input Channels
  _conf.hw.input.input_base_addr = 0x000AB800; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 56; // Output Width
  _conf.sw.output.h = 56; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 64; // Output Channels
  _conf.hw.output.output_base_addr = 0x00000000; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv2/3x3_reduce
  //->: conv2/relu_3x3_reduce
  _conf.sw.run[0].in_w = 56; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 56; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 64; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 56; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 56; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 64; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x00003880; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 5248; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[0].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[0].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[0].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

  struct fpga_layer& layer = layers[2];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x000AB800;
  layer.addr_offset_output = 0x00000000;
  layer.output_size = 401408;
  layer.input_dim[0] = 56;
  layer.input_dim[1] = 56;
  layer.input_dim[2] = 64;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 56;
  layer.output_dim[1] = 56;
  layer.output_dim[2] = 64;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_2

//Layer_3: Convolution Layer
//  ->: conv2/3x3
//  ->: conv2/relu_3x3
void CCaffeGoogLeNet::Layer_3() {
  struct top_conv_conf& _conf = get_conv_layer(3);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 56; // Input Width
  _conf.hw.input.h = 56; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 64; // Input Channels
  _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 56; // Output Width
  _conf.sw.output.h = 56; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 192; // Output Channels
  _conf.hw.output.output_base_addr = 0x00062000; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv2/3x3
  //->: conv2/relu_3x3
  _conf.sw.run[0].in_w = 56; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 56; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 64; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 56; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 56; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 192; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 3; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x00004D00; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 111488; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[0].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[0].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[0].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[0].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

  struct fpga_layer& layer = layers[3];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00000000;
  layer.addr_offset_output = 0x00062000;
  layer.output_size = 1204224;
  layer.input_dim[0] = 56;
  layer.input_dim[1] = 56;
  layer.input_dim[2] = 64;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 56;
  layer.output_dim[1] = 56;
  layer.output_dim[2] = 192;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_3

//Layer_4: Convolution Layer
//  ->: conv2/norm2
void CCaffeGoogLeNet::Layer_4() {
  struct top_conv_conf& _conf = get_conv_layer(4);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 56; // Input Width
  _conf.hw.input.h = 56; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 192; // Input Channels
  _conf.hw.input.input_base_addr = 0x00062000; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 56; // Output Width
  _conf.sw.output.h = 56; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 192; // Output Channels
  _conf.hw.output.output_base_addr = 0x00188000; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv2/norm2
  _conf.sw.run[0].in_w = 56; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 56; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 192; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 56; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 56; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 192; // Output Channels
  _conf.hw.run[0].conv_enable = 0; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x00020080; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 0; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 0; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[0].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[0].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[0].actfunc = 0; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[0].lrn= 0x403; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

  struct fpga_layer& layer = layers[4];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00062000;
  layer.addr_offset_output = 0x00188000;
  layer.output_size = 1204224;
  layer.input_dim[0] = 56;
  layer.input_dim[1] = 56;
  layer.input_dim[2] = 192;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 56;
  layer.output_dim[1] = 56;
  layer.output_dim[2] = 192;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_4

//Layer_5: Convolution Layer
//  ->: pool2/3x3_s2
void CCaffeGoogLeNet::Layer_5() {
  struct top_conv_conf& _conf = get_conv_layer(5);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 56; // Input Width
  _conf.hw.input.h = 56; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 192; // Input Channels
  _conf.hw.input.input_base_addr = 0x00188000; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 28; // Output Width
  _conf.sw.output.h = 28; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 192; // Output Channels
  _conf.hw.output.output_base_addr = 0x00000000; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: pool2/3x3_s2
  _conf.sw.run[0].in_w = 56; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 56; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 192; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 28; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 28; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 192; // Output Channels
  _conf.hw.run[0].conv_enable = 0; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x00020080; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 0; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 0; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[0].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[0].pool_size = 0x303; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[0].pool_stride = 0x202; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].pool_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[0].actfunc = 0; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

  struct fpga_layer& layer = layers[5];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00188000;
  layer.addr_offset_output = 0x00000000;
  layer.output_size = 301056;
  layer.input_dim[0] = 56;
  layer.input_dim[1] = 56;
  layer.input_dim[2] = 192;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 28;
  layer.output_dim[1] = 28;
  layer.output_dim[2] = 192;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_5

//Layer_6: Convolution Layer
//  ->: inception_3a/1x1
//  ->: inception_3a/relu_1x1
//  ->: inception_3a/3x3_reduce
//  ->: inception_3a/relu_3x3_reduce
//  ->: inception_3a/3x3
//  ->: inception_3a/relu_3x3
//  ->: inception_3a/5x5_reduce
//  ->: inception_3a/relu_5x5_reduce
//  ->: inception_3a/5x5
//  ->: inception_3a/relu_5x5
//  ->: inception_3a/pool
//  ->: inception_3a/pool_proj
//  ->: inception_3a/relu_pool_proj
void CCaffeGoogLeNet::Layer_6() {
  struct top_conv_conf& _conf = get_conv_layer(6);
  //Topo: 00000000000000000000000001010101
  _conf.hw.header.topo = 0x55; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 28; // Input Width
  _conf.hw.input.h = 28; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 192; // Input Channels
  _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 28; // Output Width
  _conf.sw.output.h = 28; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 256; // Output Channels
  _conf.hw.output.output_base_addr = 0x00049800; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->7 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: inception_3a/1x1
  //->: inception_3a/relu_1x1
  _conf.sw.run[0].in_w = 28; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 28; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 192; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 28; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 28; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 64; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x00020080; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 14464; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[0].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[0].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[0].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 1
  //--------------------------------------------------
  //->: inception_3a/3x3_reduce
  //->: inception_3a/relu_3x3_reduce
  _conf.sw.run[1].in_w = 28; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[1].in_h = 28; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[1].in_c = 192; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[1].out_w = 28; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[1].out_h = 28; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[1].m = 96; // Output Channels
  _conf.hw.run[1].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[1].p = 1; // Filter Width and Height
  _conf.hw.run[1].pz = 1; // Filter Depth
  _conf.hw.run[1].weight_base_addr = 0x00023900; // Filter Weight and Bias byte address
  _conf.hw.run[1].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[1].weight_size = 21440; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[1].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[1].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[1].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[1].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[1].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[1].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[1].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[1].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[1].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[1].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[1].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[1].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[1].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 2
  //--------------------------------------------------
  //->: inception_3a/3x3
  //->: inception_3a/relu_3x3
  _conf.sw.run[2].in_w = 28; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[2].in_h = 28; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[2].in_c = 96; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[2].out_w = 28; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[2].out_h = 28; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[2].m = 128; // Output Channels
  _conf.hw.run[2].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[2].p = 3; // Filter Width and Height
  _conf.hw.run[2].pz = 1; // Filter Depth
  _conf.hw.run[2].weight_base_addr = 0x00028CC0; // Filter Weight and Bias byte address
  _conf.hw.run[2].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[2].weight_size = 111360; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[2].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[2].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[2].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[2].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[2].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[2].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[2].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[2].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[2].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[2].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[2].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[2].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[2].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 3
  //--------------------------------------------------
  //->: inception_3a/5x5_reduce
  //->: inception_3a/relu_5x5_reduce
  _conf.sw.run[3].in_w = 28; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[3].in_h = 28; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[3].in_c = 192; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[3].out_w = 28; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[3].out_h = 28; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[3].m = 16; // Output Channels
  _conf.hw.run[3].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[3].p = 1; // Filter Width and Height
  _conf.hw.run[3].pz = 1; // Filter Depth
  _conf.hw.run[3].weight_base_addr = 0x00043FC0; // Filter Weight and Bias byte address
  _conf.hw.run[3].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[3].weight_size = 4000; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[3].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[3].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[3].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[3].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[3].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[3].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[3].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[3].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[3].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[3].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[3].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[3].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[3].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 4
  //--------------------------------------------------
  //->: inception_3a/5x5
  //->: inception_3a/relu_5x5
  _conf.sw.run[4].in_w = 28; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[4].in_h = 28; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[4].in_c = 16; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[4].out_w = 28; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[4].out_h = 28; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[4].m = 32; // Output Channels
  _conf.hw.run[4].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[4].p = 5; // Filter Width and Height
  _conf.hw.run[4].pz = 1; // Filter Depth
  _conf.hw.run[4].weight_base_addr = 0x00044F60; // Filter Weight and Bias byte address
  _conf.hw.run[4].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[4].weight_size = 19008; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[4].conv_pad = 0x2020202; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[4].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[4].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[4].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[4].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[4].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[4].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[4].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[4].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[4].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[4].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[4].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[4].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 5
  //--------------------------------------------------
  //->: inception_3a/pool
  _conf.sw.run[5].in_w = 28; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[5].in_h = 28; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[5].in_c = 192; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[5].out_w = 28; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[5].out_h = 28; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[5].m = 192; // Output Channels
  _conf.hw.run[5].conv_enable = 0; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[5].p = 1; // Filter Width and Height
  _conf.hw.run[5].pz = 1; // Filter Depth
  _conf.hw.run[5].weight_base_addr = 0x000499A0; // Filter Weight and Bias byte address
  _conf.hw.run[5].weight_fmt = 0; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[5].weight_size = 0; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[5].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[5].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[5].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[5].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[5].pool_size = 0x303; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[5].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[5].pool_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[5].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[5].actfunc = 0; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[5].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[5].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[5].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[5].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 6
  //--------------------------------------------------
  //->: inception_3a/pool_proj
  //->: inception_3a/relu_pool_proj
  _conf.sw.run[6].in_w = 28; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[6].in_h = 28; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[6].in_c = 192; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[6].out_w = 28; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[6].out_h = 28; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[6].m = 32; // Output Channels
  _conf.hw.run[6].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[6].p = 1; // Filter Width and Height
  _conf.hw.run[6].pz = 1; // Filter Depth
  _conf.hw.run[6].weight_base_addr = 0x000499A0; // Filter Weight and Bias byte address
  _conf.hw.run[6].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[6].weight_size = 7488; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[6].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[6].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[6].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[6].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[6].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[6].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[6].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[6].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[6].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[6].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[6].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[6].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[6].ALIGN_0 = 0;//Some comments needed here

  struct fpga_layer& layer = layers[6];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00000000;
  layer.addr_offset_output = 0x00049800;
  layer.output_size = 401408;
  layer.input_dim[0] = 28;
  layer.input_dim[1] = 28;
  layer.input_dim[2] = 192;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 28;
  layer.output_dim[1] = 28;
  layer.output_dim[2] = 256;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_6

//Layer_7: Convolution Layer
//  ->: inception_3b/1x1
//  ->: inception_3b/relu_1x1
//  ->: pool3/3x3_s2
//  ->: inception_3b/3x3_reduce
//  ->: inception_3b/relu_3x3_reduce
//  ->: inception_3b/3x3
//  ->: inception_3b/relu_3x3
//  ->: pool3/3x3_s2
//  ->: inception_3b/5x5_reduce
//  ->: inception_3b/relu_5x5_reduce
//  ->: inception_3b/5x5
//  ->: inception_3b/relu_5x5
//  ->: pool3/3x3_s2
//  ->: inception_3b/pool
//  ->: inception_3b/pool_proj
//  ->: inception_3b/relu_pool_proj
//  ->: pool3/3x3_s2
void CCaffeGoogLeNet::Layer_7() {
  struct top_conv_conf& _conf = get_conv_layer(7);
  //Topo: 00000000000000000000000001010101
  _conf.hw.header.topo = 0x55; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 28; // Input Width
  _conf.hw.input.h = 28; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 256; // Input Channels
  _conf.hw.input.input_base_addr = 0x00049800; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 14; // Output Width
  _conf.sw.output.h = 14; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 480; // Output Channels
  _conf.hw.output.output_base_addr = 0x00000000; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->7 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: inception_3b/1x1
  //->: inception_3b/relu_1x1
  //->: pool3/3x3_s2
  _conf.sw.run[0].in_w = 28; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 28; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 256; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 128; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x0004B6E0; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 37632; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[0].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[0].pool_size = 0x303; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[0].pool_stride = 0x202; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].pool_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[0].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 1
  //--------------------------------------------------
  //->: inception_3b/3x3_reduce
  //->: inception_3b/relu_3x3_reduce
  _conf.sw.run[1].in_w = 28; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[1].in_h = 28; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[1].in_c = 256; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[1].out_w = 28; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[1].out_h = 28; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[1].m = 128; // Output Channels
  _conf.hw.run[1].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[1].p = 1; // Filter Width and Height
  _conf.hw.run[1].pz = 1; // Filter Depth
  _conf.hw.run[1].weight_base_addr = 0x000549E0; // Filter Weight and Bias byte address
  _conf.hw.run[1].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[1].weight_size = 37632; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[1].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[1].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[1].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[1].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[1].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[1].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[1].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[1].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[1].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[1].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[1].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[1].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[1].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 2
  //--------------------------------------------------
  //->: inception_3b/3x3
  //->: inception_3b/relu_3x3
  //->: pool3/3x3_s2
  _conf.sw.run[2].in_w = 28; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[2].in_h = 28; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[2].in_c = 128; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[2].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[2].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[2].m = 192; // Output Channels
  _conf.hw.run[2].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[2].p = 3; // Filter Width and Height
  _conf.hw.run[2].pz = 1; // Filter Depth
  _conf.hw.run[2].weight_base_addr = 0x0005DCE0; // Filter Weight and Bias byte address
  _conf.hw.run[2].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[2].weight_size = 222080; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[2].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[2].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[2].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[2].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[2].pool_size = 0x303; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[2].pool_stride = 0x202; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[2].pool_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[2].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[2].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[2].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[2].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[2].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[2].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 3
  //--------------------------------------------------
  //->: inception_3b/5x5_reduce
  //->: inception_3b/relu_5x5_reduce
  _conf.sw.run[3].in_w = 28; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[3].in_h = 28; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[3].in_c = 256; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[3].out_w = 28; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[3].out_h = 28; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[3].m = 32; // Output Channels
  _conf.hw.run[3].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[3].p = 1; // Filter Width and Height
  _conf.hw.run[3].pz = 1; // Filter Depth
  _conf.hw.run[3].weight_base_addr = 0x00094060; // Filter Weight and Bias byte address
  _conf.hw.run[3].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[3].weight_size = 9792; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[3].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[3].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[3].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[3].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[3].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[3].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[3].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[3].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[3].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[3].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[3].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[3].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[3].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 4
  //--------------------------------------------------
  //->: inception_3b/5x5
  //->: inception_3b/relu_5x5
  //->: pool3/3x3_s2
  _conf.sw.run[4].in_w = 28; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[4].in_h = 28; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[4].in_c = 32; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[4].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[4].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[4].m = 96; // Output Channels
  _conf.hw.run[4].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[4].p = 5; // Filter Width and Height
  _conf.hw.run[4].pz = 1; // Filter Depth
  _conf.hw.run[4].weight_base_addr = 0x000966A0; // Filter Weight and Bias byte address
  _conf.hw.run[4].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[4].weight_size = 111296; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[4].conv_pad = 0x2020202; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[4].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[4].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[4].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[4].pool_size = 0x303; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[4].pool_stride = 0x202; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[4].pool_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[4].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[4].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[4].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[4].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[4].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[4].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 5
  //--------------------------------------------------
  //->: inception_3b/pool
  _conf.sw.run[5].in_w = 28; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[5].in_h = 28; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[5].in_c = 256; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[5].out_w = 28; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[5].out_h = 28; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[5].m = 256; // Output Channels
  _conf.hw.run[5].conv_enable = 0; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[5].p = 1; // Filter Width and Height
  _conf.hw.run[5].pz = 1; // Filter Depth
  _conf.hw.run[5].weight_base_addr = 0x000B1960; // Filter Weight and Bias byte address
  _conf.hw.run[5].weight_fmt = 0; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[5].weight_size = 0; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[5].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[5].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[5].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[5].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[5].pool_size = 0x303; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[5].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[5].pool_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[5].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[5].actfunc = 0; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[5].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[5].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[5].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[5].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 6
  //--------------------------------------------------
  //->: inception_3b/pool_proj
  //->: inception_3b/relu_pool_proj
  //->: pool3/3x3_s2
  _conf.sw.run[6].in_w = 28; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[6].in_h = 28; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[6].in_c = 256; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[6].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[6].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[6].m = 64; // Output Channels
  _conf.hw.run[6].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[6].p = 1; // Filter Width and Height
  _conf.hw.run[6].pz = 1; // Filter Depth
  _conf.hw.run[6].weight_base_addr = 0x000B1960; // Filter Weight and Bias byte address
  _conf.hw.run[6].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[6].weight_size = 19072; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[6].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[6].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[6].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[6].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[6].pool_size = 0x303; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[6].pool_stride = 0x202; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[6].pool_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[6].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[6].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[6].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[6].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[6].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[6].ALIGN_0 = 0;//Some comments needed here

  struct fpga_layer& layer = layers[7];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00049800;
  layer.addr_offset_output = 0x00000000;
  layer.output_size = 188160;
  layer.input_dim[0] = 28;
  layer.input_dim[1] = 28;
  layer.input_dim[2] = 256;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 14;
  layer.output_dim[1] = 14;
  layer.output_dim[2] = 480;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_7

//Layer_8: Convolution Layer
//  ->: inception_4a/1x1
//  ->: inception_4a/relu_1x1
//  ->: inception_4a/3x3_reduce
//  ->: inception_4a/relu_3x3_reduce
//  ->: inception_4a/3x3
//  ->: inception_4a/relu_3x3
//  ->: inception_4a/5x5_reduce
//  ->: inception_4a/relu_5x5_reduce
//  ->: inception_4a/5x5
//  ->: inception_4a/relu_5x5
//  ->: inception_4a/pool
//  ->: inception_4a/pool_proj
//  ->: inception_4a/relu_pool_proj
void CCaffeGoogLeNet::Layer_8() {
  struct top_conv_conf& _conf = get_conv_layer(8);
  //Topo: 00000000000000000000000001010101
  _conf.hw.header.topo = 0x55; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 14; // Input Width
  _conf.hw.input.h = 14; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 480; // Input Channels
  _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 14; // Output Width
  _conf.sw.output.h = 14; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 512; // Output Channels
  _conf.hw.output.output_base_addr = 0x0002DF00; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->7 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: inception_4a/1x1
  //->: inception_4a/relu_1x1
  _conf.sw.run[0].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 480; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 192; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x000B63E0; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 111488; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[0].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[0].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[0].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 1
  //--------------------------------------------------
  //->: inception_4a/3x3_reduce
  //->: inception_4a/relu_3x3_reduce
  _conf.sw.run[1].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[1].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[1].in_c = 480; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[1].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[1].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[1].m = 96; // Output Channels
  _conf.hw.run[1].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[1].p = 1; // Filter Width and Height
  _conf.hw.run[1].pz = 1; // Filter Depth
  _conf.hw.run[1].weight_base_addr = 0x000D1760; // Filter Weight and Bias byte address
  _conf.hw.run[1].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[1].weight_size = 56000; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[1].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[1].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[1].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[1].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[1].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[1].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[1].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[1].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[1].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[1].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[1].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[1].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[1].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 2
  //--------------------------------------------------
  //->: inception_4a/3x3
  //->: inception_4a/relu_3x3
  _conf.sw.run[2].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[2].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[2].in_c = 96; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[2].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[2].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[2].m = 208; // Output Channels
  _conf.hw.run[2].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[2].p = 3; // Filter Width and Height
  _conf.hw.run[2].pz = 1; // Filter Depth
  _conf.hw.run[2].weight_base_addr = 0x000DF220; // Filter Weight and Bias byte address
  _conf.hw.run[2].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[2].weight_size = 180640; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[2].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[2].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[2].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[2].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[2].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[2].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[2].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[2].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[2].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[2].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[2].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[2].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[2].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 3
  //--------------------------------------------------
  //->: inception_4a/5x5_reduce
  //->: inception_4a/relu_5x5_reduce
  _conf.sw.run[3].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[3].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[3].in_c = 480; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[3].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[3].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[3].m = 16; // Output Channels
  _conf.hw.run[3].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[3].p = 1; // Filter Width and Height
  _conf.hw.run[3].pz = 1; // Filter Depth
  _conf.hw.run[3].weight_base_addr = 0x0010B3C0; // Filter Weight and Bias byte address
  _conf.hw.run[3].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[3].weight_size = 9760; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[3].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[3].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[3].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[3].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[3].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[3].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[3].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[3].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[3].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[3].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[3].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[3].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[3].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 4
  //--------------------------------------------------
  //->: inception_4a/5x5
  //->: inception_4a/relu_5x5
  _conf.sw.run[4].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[4].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[4].in_c = 16; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[4].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[4].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[4].m = 48; // Output Channels
  _conf.hw.run[4].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[4].p = 5; // Filter Width and Height
  _conf.hw.run[4].pz = 1; // Filter Depth
  _conf.hw.run[4].weight_base_addr = 0x0010D9E0; // Filter Weight and Bias byte address
  _conf.hw.run[4].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[4].weight_size = 28256; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[4].conv_pad = 0x2020202; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[4].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[4].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[4].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[4].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[4].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[4].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[4].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[4].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[4].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[4].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[4].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[4].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 5
  //--------------------------------------------------
  //->: inception_4a/pool
  _conf.sw.run[5].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[5].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[5].in_c = 480; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[5].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[5].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[5].m = 480; // Output Channels
  _conf.hw.run[5].conv_enable = 0; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[5].p = 1; // Filter Width and Height
  _conf.hw.run[5].pz = 1; // Filter Depth
  _conf.hw.run[5].weight_base_addr = 0x00114840; // Filter Weight and Bias byte address
  _conf.hw.run[5].weight_fmt = 0; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[5].weight_size = 0; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[5].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[5].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[5].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[5].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[5].pool_size = 0x303; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[5].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[5].pool_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[5].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[5].actfunc = 0; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[5].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[5].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[5].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[5].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 6
  //--------------------------------------------------
  //->: inception_4a/pool_proj
  //->: inception_4a/relu_pool_proj
  _conf.sw.run[6].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[6].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[6].in_c = 480; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[6].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[6].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[6].m = 64; // Output Channels
  _conf.hw.run[6].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[6].p = 1; // Filter Width and Height
  _conf.hw.run[6].pz = 1; // Filter Depth
  _conf.hw.run[6].weight_base_addr = 0x00114840; // Filter Weight and Bias byte address
  _conf.hw.run[6].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[6].weight_size = 37504; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[6].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[6].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[6].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[6].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[6].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[6].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[6].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[6].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[6].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[6].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[6].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[6].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[6].ALIGN_0 = 0;//Some comments needed here

  struct fpga_layer& layer = layers[8];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00000000;
  layer.addr_offset_output = 0x0002DF00;
  layer.output_size = 200704;
  layer.input_dim[0] = 14;
  layer.input_dim[1] = 14;
  layer.input_dim[2] = 480;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 14;
  layer.output_dim[1] = 14;
  layer.output_dim[2] = 512;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_8

//Layer_9: Convolution Layer
//  ->: inception_4b/1x1
//  ->: inception_4b/relu_1x1
//  ->: inception_4b/3x3_reduce
//  ->: inception_4b/relu_3x3_reduce
//  ->: inception_4b/3x3
//  ->: inception_4b/relu_3x3
//  ->: inception_4b/5x5_reduce
//  ->: inception_4b/relu_5x5_reduce
//  ->: inception_4b/5x5
//  ->: inception_4b/relu_5x5
//  ->: inception_4b/pool
//  ->: inception_4b/pool_proj
//  ->: inception_4b/relu_pool_proj
void CCaffeGoogLeNet::Layer_9() {
  struct top_conv_conf& _conf = get_conv_layer(9);
  //Topo: 00000000000000000000000001010101
  _conf.hw.header.topo = 0x55; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 14; // Input Width
  _conf.hw.input.h = 14; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 512; // Input Channels
  _conf.hw.input.input_base_addr = 0x0002DF00; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 14; // Output Width
  _conf.sw.output.h = 14; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 512; // Output Channels
  _conf.hw.output.output_base_addr = 0x0005EF00; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->7 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: inception_4b/1x1
  //->: inception_4b/relu_1x1
  _conf.sw.run[0].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 512; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 160; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x0011DAC0; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 92992; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[0].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[0].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[0].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 1
  //--------------------------------------------------
  //->: inception_4b/3x3_reduce
  //->: inception_4b/relu_3x3_reduce
  _conf.sw.run[1].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[1].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[1].in_c = 512; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[1].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[1].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[1].m = 112; // Output Channels
  _conf.hw.run[1].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[1].p = 1; // Filter Width and Height
  _conf.hw.run[1].pz = 1; // Filter Depth
  _conf.hw.run[1].weight_base_addr = 0x00134600; // Filter Weight and Bias byte address
  _conf.hw.run[1].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[1].weight_size = 65248; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[1].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[1].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[1].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[1].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[1].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[1].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[1].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[1].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[1].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[1].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[1].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[1].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[1].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 2
  //--------------------------------------------------
  //->: inception_4b/3x3
  //->: inception_4b/relu_3x3
  _conf.sw.run[2].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[2].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[2].in_c = 112; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[2].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[2].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[2].m = 224; // Output Channels
  _conf.hw.run[2].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[2].p = 3; // Filter Width and Height
  _conf.hw.run[2].pz = 1; // Filter Depth
  _conf.hw.run[2].weight_base_addr = 0x001444E0; // Filter Weight and Bias byte address
  _conf.hw.run[2].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[2].weight_size = 226752; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[2].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[2].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[2].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[2].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[2].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[2].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[2].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[2].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[2].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[2].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[2].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[2].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[2].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 3
  //--------------------------------------------------
  //->: inception_4b/5x5_reduce
  //->: inception_4b/relu_5x5_reduce
  _conf.sw.run[3].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[3].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[3].in_c = 512; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[3].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[3].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[3].m = 24; // Output Channels
  _conf.hw.run[3].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[3].p = 1; // Filter Width and Height
  _conf.hw.run[3].pz = 1; // Filter Depth
  _conf.hw.run[3].weight_base_addr = 0x0017BAA0; // Filter Weight and Bias byte address
  _conf.hw.run[3].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[3].weight_size = 14384; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[3].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[3].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[3].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[3].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[3].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[3].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[3].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[3].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[3].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[3].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[3].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[3].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[3].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 4
  //--------------------------------------------------
  //->: inception_4b/5x5
  //->: inception_4b/relu_5x5
  _conf.sw.run[4].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[4].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[4].in_c = 24; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[4].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[4].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[4].m = 64; // Output Channels
  _conf.hw.run[4].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[4].p = 5; // Filter Width and Height
  _conf.hw.run[4].pz = 1; // Filter Depth
  _conf.hw.run[4].weight_base_addr = 0x0017F2D0; // Filter Weight and Bias byte address
  _conf.hw.run[4].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[4].weight_size = 55936; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[4].conv_pad = 0x2020202; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[4].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[4].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[4].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[4].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[4].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[4].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[4].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[4].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[4].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[4].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[4].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[4].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 5
  //--------------------------------------------------
  //->: inception_4b/pool
  _conf.sw.run[5].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[5].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[5].in_c = 512; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[5].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[5].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[5].m = 512; // Output Channels
  _conf.hw.run[5].conv_enable = 0; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[5].p = 1; // Filter Width and Height
  _conf.hw.run[5].pz = 1; // Filter Depth
  _conf.hw.run[5].weight_base_addr = 0x0018CD50; // Filter Weight and Bias byte address
  _conf.hw.run[5].weight_fmt = 0; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[5].weight_size = 0; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[5].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[5].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[5].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[5].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[5].pool_size = 0x303; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[5].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[5].pool_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[5].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[5].actfunc = 0; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[5].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[5].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[5].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[5].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 6
  //--------------------------------------------------
  //->: inception_4b/pool_proj
  //->: inception_4b/relu_pool_proj
  _conf.sw.run[6].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[6].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[6].in_c = 512; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[6].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[6].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[6].m = 64; // Output Channels
  _conf.hw.run[6].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[6].p = 1; // Filter Width and Height
  _conf.hw.run[6].pz = 1; // Filter Depth
  _conf.hw.run[6].weight_base_addr = 0x0018CD50; // Filter Weight and Bias byte address
  _conf.hw.run[6].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[6].weight_size = 37504; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[6].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[6].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[6].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[6].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[6].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[6].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[6].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[6].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[6].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[6].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[6].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[6].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[6].ALIGN_0 = 0;//Some comments needed here

  struct fpga_layer& layer = layers[9];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x0002DF00;
  layer.addr_offset_output = 0x0005EF00;
  layer.output_size = 200704;
  layer.input_dim[0] = 14;
  layer.input_dim[1] = 14;
  layer.input_dim[2] = 512;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 14;
  layer.output_dim[1] = 14;
  layer.output_dim[2] = 512;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_9

//Layer_10: Convolution Layer
//  ->: inception_4c/1x1
//  ->: inception_4c/relu_1x1
//  ->: inception_4c/3x3_reduce
//  ->: inception_4c/relu_3x3_reduce
//  ->: inception_4c/3x3
//  ->: inception_4c/relu_3x3
//  ->: inception_4c/5x5_reduce
//  ->: inception_4c/relu_5x5_reduce
//  ->: inception_4c/5x5
//  ->: inception_4c/relu_5x5
//  ->: inception_4c/pool
//  ->: inception_4c/pool_proj
//  ->: inception_4c/relu_pool_proj
void CCaffeGoogLeNet::Layer_10() {
  struct top_conv_conf& _conf = get_conv_layer(10);
  //Topo: 00000000000000000000000001010101
  _conf.hw.header.topo = 0x55; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 14; // Input Width
  _conf.hw.input.h = 14; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 512; // Input Channels
  _conf.hw.input.input_base_addr = 0x0005EF00; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 14; // Output Width
  _conf.sw.output.h = 14; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 512; // Output Channels
  _conf.hw.output.output_base_addr = 0x00000000; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->7 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: inception_4c/1x1
  //->: inception_4c/relu_1x1
  _conf.sw.run[0].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 512; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 128; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x00195FD0; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 74496; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[0].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[0].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[0].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 1
  //--------------------------------------------------
  //->: inception_4c/3x3_reduce
  //->: inception_4c/relu_3x3_reduce
  _conf.sw.run[1].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[1].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[1].in_c = 512; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[1].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[1].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[1].m = 128; // Output Channels
  _conf.hw.run[1].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[1].p = 1; // Filter Width and Height
  _conf.hw.run[1].pz = 1; // Filter Depth
  _conf.hw.run[1].weight_base_addr = 0x001A82D0; // Filter Weight and Bias byte address
  _conf.hw.run[1].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[1].weight_size = 74496; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[1].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[1].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[1].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[1].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[1].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[1].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[1].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[1].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[1].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[1].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[1].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[1].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[1].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 2
  //--------------------------------------------------
  //->: inception_4c/3x3
  //->: inception_4c/relu_3x3
  _conf.sw.run[2].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[2].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[2].in_c = 128; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[2].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[2].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[2].m = 256; // Output Channels
  _conf.hw.run[2].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[2].p = 3; // Filter Width and Height
  _conf.hw.run[2].pz = 1; // Filter Depth
  _conf.hw.run[2].weight_base_addr = 0x001BA5D0; // Filter Weight and Bias byte address
  _conf.hw.run[2].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[2].weight_size = 295936; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[2].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[2].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[2].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[2].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[2].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[2].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[2].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[2].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[2].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[2].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[2].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[2].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[2].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 3
  //--------------------------------------------------
  //->: inception_4c/5x5_reduce
  //->: inception_4c/relu_5x5_reduce
  _conf.sw.run[3].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[3].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[3].in_c = 512; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[3].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[3].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[3].m = 24; // Output Channels
  _conf.hw.run[3].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[3].p = 1; // Filter Width and Height
  _conf.hw.run[3].pz = 1; // Filter Depth
  _conf.hw.run[3].weight_base_addr = 0x002029D0; // Filter Weight and Bias byte address
  _conf.hw.run[3].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[3].weight_size = 14384; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[3].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[3].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[3].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[3].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[3].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[3].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[3].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[3].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[3].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[3].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[3].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[3].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[3].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 4
  //--------------------------------------------------
  //->: inception_4c/5x5
  //->: inception_4c/relu_5x5
  _conf.sw.run[4].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[4].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[4].in_c = 24; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[4].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[4].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[4].m = 64; // Output Channels
  _conf.hw.run[4].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[4].p = 5; // Filter Width and Height
  _conf.hw.run[4].pz = 1; // Filter Depth
  _conf.hw.run[4].weight_base_addr = 0x00206200; // Filter Weight and Bias byte address
  _conf.hw.run[4].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[4].weight_size = 55936; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[4].conv_pad = 0x2020202; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[4].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[4].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[4].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[4].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[4].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[4].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[4].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[4].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[4].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[4].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[4].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[4].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 5
  //--------------------------------------------------
  //->: inception_4c/pool
  _conf.sw.run[5].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[5].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[5].in_c = 512; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[5].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[5].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[5].m = 512; // Output Channels
  _conf.hw.run[5].conv_enable = 0; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[5].p = 1; // Filter Width and Height
  _conf.hw.run[5].pz = 1; // Filter Depth
  _conf.hw.run[5].weight_base_addr = 0x00213C80; // Filter Weight and Bias byte address
  _conf.hw.run[5].weight_fmt = 0; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[5].weight_size = 0; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[5].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[5].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[5].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[5].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[5].pool_size = 0x303; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[5].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[5].pool_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[5].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[5].actfunc = 0; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[5].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[5].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[5].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[5].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 6
  //--------------------------------------------------
  //->: inception_4c/pool_proj
  //->: inception_4c/relu_pool_proj
  _conf.sw.run[6].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[6].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[6].in_c = 512; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[6].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[6].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[6].m = 64; // Output Channels
  _conf.hw.run[6].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[6].p = 1; // Filter Width and Height
  _conf.hw.run[6].pz = 1; // Filter Depth
  _conf.hw.run[6].weight_base_addr = 0x00213C80; // Filter Weight and Bias byte address
  _conf.hw.run[6].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[6].weight_size = 37504; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[6].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[6].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[6].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[6].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[6].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[6].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[6].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[6].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[6].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[6].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[6].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[6].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[6].ALIGN_0 = 0;//Some comments needed here

  struct fpga_layer& layer = layers[10];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x0005EF00;
  layer.addr_offset_output = 0x00000000;
  layer.output_size = 200704;
  layer.input_dim[0] = 14;
  layer.input_dim[1] = 14;
  layer.input_dim[2] = 512;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 14;
  layer.output_dim[1] = 14;
  layer.output_dim[2] = 512;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_10

//Layer_11: Convolution Layer
//  ->: inception_4d/1x1
//  ->: inception_4d/relu_1x1
//  ->: inception_4d/3x3_reduce
//  ->: inception_4d/relu_3x3_reduce
//  ->: inception_4d/3x3
//  ->: inception_4d/relu_3x3
//  ->: inception_4d/5x5_reduce
//  ->: inception_4d/relu_5x5_reduce
//  ->: inception_4d/5x5
//  ->: inception_4d/relu_5x5
//  ->: inception_4d/pool
//  ->: inception_4d/pool_proj
//  ->: inception_4d/relu_pool_proj
void CCaffeGoogLeNet::Layer_11() {
  struct top_conv_conf& _conf = get_conv_layer(11);
  //Topo: 00000000000000000000000001010101
  _conf.hw.header.topo = 0x55; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 14; // Input Width
  _conf.hw.input.h = 14; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 512; // Input Channels
  _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 14; // Output Width
  _conf.sw.output.h = 14; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 528; // Output Channels
  _conf.hw.output.output_base_addr = 0x00031000; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->7 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: inception_4d/1x1
  //->: inception_4d/relu_1x1
  _conf.sw.run[0].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 512; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 112; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x0021CF00; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 65248; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[0].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[0].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[0].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 1
  //--------------------------------------------------
  //->: inception_4d/3x3_reduce
  //->: inception_4d/relu_3x3_reduce
  _conf.sw.run[1].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[1].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[1].in_c = 512; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[1].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[1].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[1].m = 144; // Output Channels
  _conf.hw.run[1].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[1].p = 1; // Filter Width and Height
  _conf.hw.run[1].pz = 1; // Filter Depth
  _conf.hw.run[1].weight_base_addr = 0x0022CDE0; // Filter Weight and Bias byte address
  _conf.hw.run[1].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[1].weight_size = 83744; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[1].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[1].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[1].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[1].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[1].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[1].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[1].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[1].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[1].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[1].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[1].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[1].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[1].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 2
  //--------------------------------------------------
  //->: inception_4d/3x3
  //->: inception_4d/relu_3x3
  _conf.sw.run[2].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[2].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[2].in_c = 144; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[2].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[2].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[2].m = 288; // Output Channels
  _conf.hw.run[2].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[2].p = 3; // Filter Width and Height
  _conf.hw.run[2].pz = 1; // Filter Depth
  _conf.hw.run[2].weight_base_addr = 0x00241500; // Filter Weight and Bias byte address
  _conf.hw.run[2].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[2].weight_size = 374336; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[2].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[2].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[2].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[2].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[2].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[2].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[2].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[2].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[2].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[2].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[2].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[2].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[2].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 3
  //--------------------------------------------------
  //->: inception_4d/5x5_reduce
  //->: inception_4d/relu_5x5_reduce
  _conf.sw.run[3].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[3].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[3].in_c = 512; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[3].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[3].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[3].m = 32; // Output Channels
  _conf.hw.run[3].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[3].p = 1; // Filter Width and Height
  _conf.hw.run[3].pz = 1; // Filter Depth
  _conf.hw.run[3].weight_base_addr = 0x0029CB40; // Filter Weight and Bias byte address
  _conf.hw.run[3].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[3].weight_size = 19008; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[3].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[3].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[3].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[3].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[3].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[3].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[3].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[3].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[3].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[3].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[3].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[3].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[3].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 4
  //--------------------------------------------------
  //->: inception_4d/5x5
  //->: inception_4d/relu_5x5
  _conf.sw.run[4].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[4].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[4].in_c = 32; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[4].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[4].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[4].m = 64; // Output Channels
  _conf.hw.run[4].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[4].p = 5; // Filter Width and Height
  _conf.hw.run[4].pz = 1; // Filter Depth
  _conf.hw.run[4].weight_base_addr = 0x002A1580; // Filter Weight and Bias byte address
  _conf.hw.run[4].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[4].weight_size = 74368; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[4].conv_pad = 0x2020202; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[4].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[4].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[4].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[4].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[4].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[4].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[4].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[4].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[4].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[4].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[4].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[4].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 5
  //--------------------------------------------------
  //->: inception_4d/pool
  _conf.sw.run[5].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[5].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[5].in_c = 512; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[5].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[5].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[5].m = 512; // Output Channels
  _conf.hw.run[5].conv_enable = 0; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[5].p = 1; // Filter Width and Height
  _conf.hw.run[5].pz = 1; // Filter Depth
  _conf.hw.run[5].weight_base_addr = 0x002B3800; // Filter Weight and Bias byte address
  _conf.hw.run[5].weight_fmt = 0; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[5].weight_size = 0; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[5].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[5].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[5].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[5].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[5].pool_size = 0x303; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[5].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[5].pool_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[5].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[5].actfunc = 0; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[5].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[5].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[5].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[5].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 6
  //--------------------------------------------------
  //->: inception_4d/pool_proj
  //->: inception_4d/relu_pool_proj
  _conf.sw.run[6].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[6].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[6].in_c = 512; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[6].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[6].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[6].m = 64; // Output Channels
  _conf.hw.run[6].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[6].p = 1; // Filter Width and Height
  _conf.hw.run[6].pz = 1; // Filter Depth
  _conf.hw.run[6].weight_base_addr = 0x002B3800; // Filter Weight and Bias byte address
  _conf.hw.run[6].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[6].weight_size = 37504; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[6].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[6].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[6].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[6].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[6].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[6].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[6].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[6].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[6].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[6].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[6].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[6].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[6].ALIGN_0 = 0;//Some comments needed here

  struct fpga_layer& layer = layers[11];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00000000;
  layer.addr_offset_output = 0x00031000;
  layer.output_size = 206976;
  layer.input_dim[0] = 14;
  layer.input_dim[1] = 14;
  layer.input_dim[2] = 512;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 14;
  layer.output_dim[1] = 14;
  layer.output_dim[2] = 528;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_11

//Layer_12: Convolution Layer
//  ->: inception_4e/1x1
//  ->: inception_4e/relu_1x1
//  ->: pool4/3x3_s2
//  ->: inception_4e/3x3_reduce
//  ->: inception_4e/relu_3x3_reduce
//  ->: inception_4e/3x3
//  ->: inception_4e/relu_3x3
//  ->: pool4/3x3_s2
//  ->: inception_4e/5x5_reduce
//  ->: inception_4e/relu_5x5_reduce
//  ->: inception_4e/5x5
//  ->: inception_4e/relu_5x5
//  ->: pool4/3x3_s2
//  ->: inception_4e/pool
//  ->: inception_4e/pool_proj
//  ->: inception_4e/relu_pool_proj
//  ->: pool4/3x3_s2
void CCaffeGoogLeNet::Layer_12() {
  struct top_conv_conf& _conf = get_conv_layer(12);
  //Topo: 00000000000000000000000001010101
  _conf.hw.header.topo = 0x55; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 14; // Input Width
  _conf.hw.input.h = 14; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 528; // Input Channels
  _conf.hw.input.input_base_addr = 0x00031000; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 7; // Output Width
  _conf.sw.output.h = 7; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 832; // Output Channels
  _conf.hw.output.output_base_addr = 0x00000000; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->7 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: inception_4e/1x1
  //->: inception_4e/relu_1x1
  //->: pool4/3x3_s2
  _conf.sw.run[0].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 528; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 7; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 7; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 256; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x002BCA80; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 166912; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[0].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[0].pool_size = 0x303; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[0].pool_stride = 0x202; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].pool_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[0].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 1
  //--------------------------------------------------
  //->: inception_4e/3x3_reduce
  //->: inception_4e/relu_3x3_reduce
  _conf.sw.run[1].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[1].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[1].in_c = 528; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[1].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[1].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[1].m = 160; // Output Channels
  _conf.hw.run[1].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[1].p = 1; // Filter Width and Height
  _conf.hw.run[1].pz = 1; // Filter Depth
  _conf.hw.run[1].weight_base_addr = 0x002E5680; // Filter Weight and Bias byte address
  _conf.hw.run[1].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[1].weight_size = 104512; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[1].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[1].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[1].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[1].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[1].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[1].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[1].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[1].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[1].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[1].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[1].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[1].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[1].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 2
  //--------------------------------------------------
  //->: inception_4e/3x3
  //->: inception_4e/relu_3x3
  //->: pool4/3x3_s2
  _conf.sw.run[2].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[2].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[2].in_c = 160; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[2].out_w = 7; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[2].out_h = 7; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[2].m = 320; // Output Channels
  _conf.hw.run[2].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[2].p = 3; // Filter Width and Height
  _conf.hw.run[2].pz = 1; // Filter Depth
  _conf.hw.run[2].weight_base_addr = 0x002FEEC0; // Filter Weight and Bias byte address
  _conf.hw.run[2].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[2].weight_size = 461952; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[2].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[2].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[2].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[2].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[2].pool_size = 0x303; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[2].pool_stride = 0x202; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[2].pool_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[2].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[2].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[2].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[2].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[2].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[2].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 3
  //--------------------------------------------------
  //->: inception_4e/5x5_reduce
  //->: inception_4e/relu_5x5_reduce
  _conf.sw.run[3].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[3].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[3].in_c = 528; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[3].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[3].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[3].m = 32; // Output Channels
  _conf.hw.run[3].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[3].p = 1; // Filter Width and Height
  _conf.hw.run[3].pz = 1; // Filter Depth
  _conf.hw.run[3].weight_base_addr = 0x0036FB40; // Filter Weight and Bias byte address
  _conf.hw.run[3].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[3].weight_size = 21312; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[3].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[3].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[3].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[3].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[3].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[3].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[3].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[3].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[3].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[3].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[3].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[3].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[3].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 4
  //--------------------------------------------------
  //->: inception_4e/5x5
  //->: inception_4e/relu_5x5
  //->: pool4/3x3_s2
  _conf.sw.run[4].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[4].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[4].in_c = 32; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[4].out_w = 7; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[4].out_h = 7; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[4].m = 128; // Output Channels
  _conf.hw.run[4].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[4].p = 5; // Filter Width and Height
  _conf.hw.run[4].pz = 1; // Filter Depth
  _conf.hw.run[4].weight_base_addr = 0x00374E80; // Filter Weight and Bias byte address
  _conf.hw.run[4].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[4].weight_size = 148224; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[4].conv_pad = 0x2020202; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[4].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[4].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[4].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[4].pool_size = 0x303; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[4].pool_stride = 0x202; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[4].pool_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[4].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[4].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[4].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[4].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[4].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[4].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 5
  //--------------------------------------------------
  //->: inception_4e/pool
  _conf.sw.run[5].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[5].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[5].in_c = 528; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[5].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[5].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[5].m = 528; // Output Channels
  _conf.hw.run[5].conv_enable = 0; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[5].p = 1; // Filter Width and Height
  _conf.hw.run[5].pz = 1; // Filter Depth
  _conf.hw.run[5].weight_base_addr = 0x00399180; // Filter Weight and Bias byte address
  _conf.hw.run[5].weight_fmt = 0; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[5].weight_size = 0; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[5].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[5].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[5].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[5].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[5].pool_size = 0x303; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[5].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[5].pool_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[5].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[5].actfunc = 0; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[5].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[5].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[5].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[5].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 6
  //--------------------------------------------------
  //->: inception_4e/pool_proj
  //->: inception_4e/relu_pool_proj
  //->: pool4/3x3_s2
  _conf.sw.run[6].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[6].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[6].in_c = 528; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[6].out_w = 7; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[6].out_h = 7; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[6].m = 128; // Output Channels
  _conf.hw.run[6].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[6].p = 1; // Filter Width and Height
  _conf.hw.run[6].pz = 1; // Filter Depth
  _conf.hw.run[6].weight_base_addr = 0x00399180; // Filter Weight and Bias byte address
  _conf.hw.run[6].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[6].weight_size = 83712; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[6].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[6].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[6].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[6].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[6].pool_size = 0x303; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[6].pool_stride = 0x202; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[6].pool_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[6].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[6].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[6].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[6].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[6].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[6].ALIGN_0 = 0;//Some comments needed here

  struct fpga_layer& layer = layers[12];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00031000;
  layer.addr_offset_output = 0x00000000;
  layer.output_size = 81536;
  layer.input_dim[0] = 14;
  layer.input_dim[1] = 14;
  layer.input_dim[2] = 528;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 7;
  layer.output_dim[1] = 7;
  layer.output_dim[2] = 832;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_12

//Layer_13: Convolution Layer
//  ->: inception_5a/1x1
//  ->: inception_5a/relu_1x1
//  ->: inception_5a/3x3_reduce
//  ->: inception_5a/relu_3x3_reduce
//  ->: inception_5a/3x3
//  ->: inception_5a/relu_3x3
//  ->: inception_5a/5x5_reduce
//  ->: inception_5a/relu_5x5_reduce
//  ->: inception_5a/5x5
//  ->: inception_5a/relu_5x5
//  ->: inception_5a/pool
//  ->: inception_5a/pool_proj
//  ->: inception_5a/relu_pool_proj
void CCaffeGoogLeNet::Layer_13() {
  struct top_conv_conf& _conf = get_conv_layer(13);
  //Topo: 00000000000000000000000001010101
  _conf.hw.header.topo = 0x55; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 7; // Input Width
  _conf.hw.input.h = 7; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 832; // Input Channels
  _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 7; // Output Width
  _conf.sw.output.h = 7; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 832; // Output Channels
  _conf.hw.output.output_base_addr = 0x00013E80; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->7 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: inception_5a/1x1
  //->: inception_5a/relu_1x1
  _conf.sw.run[0].in_w = 7; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 7; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 832; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 7; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 7; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 256; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x003AD880; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 240640; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[0].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[0].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[0].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 1
  //--------------------------------------------------
  //->: inception_5a/3x3_reduce
  //->: inception_5a/relu_3x3_reduce
  _conf.sw.run[1].in_w = 7; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[1].in_h = 7; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[1].in_c = 832; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[1].out_w = 7; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[1].out_h = 7; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[1].m = 160; // Output Channels
  _conf.hw.run[1].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[1].p = 1; // Filter Width and Height
  _conf.hw.run[1].pz = 1; // Filter Depth
  _conf.hw.run[1].weight_base_addr = 0x003E8480; // Filter Weight and Bias byte address
  _conf.hw.run[1].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[1].weight_size = 150592; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[1].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[1].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[1].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[1].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[1].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[1].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[1].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[1].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[1].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[1].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[1].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[1].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[1].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 2
  //--------------------------------------------------
  //->: inception_5a/3x3
  //->: inception_5a/relu_3x3
  _conf.sw.run[2].in_w = 7; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[2].in_h = 7; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[2].in_c = 160; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[2].out_w = 7; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[2].out_h = 7; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[2].m = 320; // Output Channels
  _conf.hw.run[2].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[2].p = 3; // Filter Width and Height
  _conf.hw.run[2].pz = 1; // Filter Depth
  _conf.hw.run[2].weight_base_addr = 0x0040D0C0; // Filter Weight and Bias byte address
  _conf.hw.run[2].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[2].weight_size = 461952; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[2].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[2].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[2].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[2].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[2].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[2].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[2].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[2].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[2].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[2].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[2].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[2].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[2].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 3
  //--------------------------------------------------
  //->: inception_5a/5x5_reduce
  //->: inception_5a/relu_5x5_reduce
  _conf.sw.run[3].in_w = 7; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[3].in_h = 7; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[3].in_c = 832; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[3].out_w = 7; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[3].out_h = 7; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[3].m = 32; // Output Channels
  _conf.hw.run[3].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[3].p = 1; // Filter Width and Height
  _conf.hw.run[3].pz = 1; // Filter Depth
  _conf.hw.run[3].weight_base_addr = 0x0047DD40; // Filter Weight and Bias byte address
  _conf.hw.run[3].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[3].weight_size = 30528; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[3].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[3].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[3].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[3].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[3].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[3].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[3].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[3].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[3].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[3].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[3].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[3].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[3].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 4
  //--------------------------------------------------
  //->: inception_5a/5x5
  //->: inception_5a/relu_5x5
  _conf.sw.run[4].in_w = 7; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[4].in_h = 7; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[4].in_c = 32; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[4].out_w = 7; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[4].out_h = 7; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[4].m = 128; // Output Channels
  _conf.hw.run[4].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[4].p = 5; // Filter Width and Height
  _conf.hw.run[4].pz = 1; // Filter Depth
  _conf.hw.run[4].weight_base_addr = 0x00485480; // Filter Weight and Bias byte address
  _conf.hw.run[4].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[4].weight_size = 148224; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[4].conv_pad = 0x2020202; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[4].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[4].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[4].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[4].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[4].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[4].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[4].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[4].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[4].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[4].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[4].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[4].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 5
  //--------------------------------------------------
  //->: inception_5a/pool
  _conf.sw.run[5].in_w = 7; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[5].in_h = 7; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[5].in_c = 832; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[5].out_w = 7; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[5].out_h = 7; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[5].m = 832; // Output Channels
  _conf.hw.run[5].conv_enable = 0; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[5].p = 1; // Filter Width and Height
  _conf.hw.run[5].pz = 1; // Filter Depth
  _conf.hw.run[5].weight_base_addr = 0x004A9780; // Filter Weight and Bias byte address
  _conf.hw.run[5].weight_fmt = 0; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[5].weight_size = 0; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[5].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[5].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[5].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[5].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[5].pool_size = 0x303; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[5].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[5].pool_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[5].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[5].actfunc = 0; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[5].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[5].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[5].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[5].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 6
  //--------------------------------------------------
  //->: inception_5a/pool_proj
  //->: inception_5a/relu_pool_proj
  _conf.sw.run[6].in_w = 7; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[6].in_h = 7; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[6].in_c = 832; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[6].out_w = 7; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[6].out_h = 7; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[6].m = 128; // Output Channels
  _conf.hw.run[6].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[6].p = 1; // Filter Width and Height
  _conf.hw.run[6].pz = 1; // Filter Depth
  _conf.hw.run[6].weight_base_addr = 0x004A9780; // Filter Weight and Bias byte address
  _conf.hw.run[6].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[6].weight_size = 120576; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[6].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[6].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[6].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[6].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[6].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[6].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[6].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[6].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[6].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[6].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[6].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[6].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[6].ALIGN_0 = 0;//Some comments needed here

  struct fpga_layer& layer = layers[13];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00000000;
  layer.addr_offset_output = 0x00013E80;
  layer.output_size = 81536;
  layer.input_dim[0] = 7;
  layer.input_dim[1] = 7;
  layer.input_dim[2] = 832;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 7;
  layer.output_dim[1] = 7;
  layer.output_dim[2] = 832;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_13

//Layer_14: Convolution Layer
//  ->: inception_5b/1x1
//  ->: inception_5b/relu_1x1
//  ->: inception_5b/3x3_reduce
//  ->: inception_5b/relu_3x3_reduce
//  ->: inception_5b/3x3
//  ->: inception_5b/relu_3x3
//  ->: inception_5b/5x5_reduce
//  ->: inception_5b/relu_5x5_reduce
//  ->: inception_5b/5x5
//  ->: inception_5b/relu_5x5
//  ->: inception_5b/pool
//  ->: inception_5b/pool_proj
//  ->: inception_5b/relu_pool_proj
void CCaffeGoogLeNet::Layer_14() {
  struct top_conv_conf& _conf = get_conv_layer(14);
  //Topo: 00000000000000000000000001010101
  _conf.hw.header.topo = 0x55; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 7; // Input Width
  _conf.hw.input.h = 7; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 832; // Input Channels
  _conf.hw.input.input_base_addr = 0x00013E80; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 7; // Output Width
  _conf.sw.output.h = 7; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 1024; // Output Channels
  _conf.hw.output.output_base_addr = 0x00027D00; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->7 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: inception_5b/1x1
  //->: inception_5b/relu_1x1
  _conf.sw.run[0].in_w = 7; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 7; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 832; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 7; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 7; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 384; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x004C6E80; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 360704; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[0].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[0].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[0].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 1
  //--------------------------------------------------
  //->: inception_5b/3x3_reduce
  //->: inception_5b/relu_3x3_reduce
  _conf.sw.run[1].in_w = 7; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[1].in_h = 7; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[1].in_c = 832; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[1].out_w = 7; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[1].out_h = 7; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[1].m = 192; // Output Channels
  _conf.hw.run[1].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[1].p = 1; // Filter Width and Height
  _conf.hw.run[1].pz = 1; // Filter Depth
  _conf.hw.run[1].weight_base_addr = 0x0051EF80; // Filter Weight and Bias byte address
  _conf.hw.run[1].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[1].weight_size = 180608; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[1].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[1].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[1].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[1].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[1].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[1].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[1].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[1].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[1].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[1].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[1].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[1].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[1].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 2
  //--------------------------------------------------
  //->: inception_5b/3x3
  //->: inception_5b/relu_3x3
  _conf.sw.run[2].in_w = 7; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[2].in_h = 7; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[2].in_c = 192; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[2].out_w = 7; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[2].out_h = 7; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[2].m = 384; // Output Channels
  _conf.hw.run[2].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[2].p = 3; // Filter Width and Height
  _conf.hw.run[2].pz = 1; // Filter Depth
  _conf.hw.run[2].weight_base_addr = 0x0054B100; // Filter Weight and Bias byte address
  _conf.hw.run[2].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[2].weight_size = 664832; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[2].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[2].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[2].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[2].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[2].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[2].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[2].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[2].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[2].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[2].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[2].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[2].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[2].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 3
  //--------------------------------------------------
  //->: inception_5b/5x5_reduce
  //->: inception_5b/relu_5x5_reduce
  _conf.sw.run[3].in_w = 7; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[3].in_h = 7; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[3].in_c = 832; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[3].out_w = 7; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[3].out_h = 7; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[3].m = 48; // Output Channels
  _conf.hw.run[3].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[3].p = 1; // Filter Width and Height
  _conf.hw.run[3].pz = 1; // Filter Depth
  _conf.hw.run[3].weight_base_addr = 0x005ED600; // Filter Weight and Bias byte address
  _conf.hw.run[3].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[3].weight_size = 45536; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[3].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[3].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[3].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[3].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[3].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[3].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[3].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[3].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[3].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[3].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[3].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[3].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[3].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 4
  //--------------------------------------------------
  //->: inception_5b/5x5
  //->: inception_5b/relu_5x5
  _conf.sw.run[4].in_w = 7; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[4].in_h = 7; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[4].in_c = 48; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[4].out_w = 7; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[4].out_h = 7; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[4].m = 128; // Output Channels
  _conf.hw.run[4].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[4].p = 5; // Filter Width and Height
  _conf.hw.run[4].pz = 1; // Filter Depth
  _conf.hw.run[4].weight_base_addr = 0x005F87E0; // Filter Weight and Bias byte address
  _conf.hw.run[4].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[4].weight_size = 221952; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[4].conv_pad = 0x2020202; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[4].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[4].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[4].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[4].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[4].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[4].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[4].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[4].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[4].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[4].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[4].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[4].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 5
  //--------------------------------------------------
  //->: inception_5b/pool
  _conf.sw.run[5].in_w = 7; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[5].in_h = 7; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[5].in_c = 832; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[5].out_w = 7; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[5].out_h = 7; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[5].m = 832; // Output Channels
  _conf.hw.run[5].conv_enable = 0; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[5].p = 1; // Filter Width and Height
  _conf.hw.run[5].pz = 1; // Filter Depth
  _conf.hw.run[5].weight_base_addr = 0x0062EAE0; // Filter Weight and Bias byte address
  _conf.hw.run[5].weight_fmt = 0; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[5].weight_size = 0; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[5].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[5].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[5].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[5].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[5].pool_size = 0x303; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[5].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[5].pool_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[5].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[5].actfunc = 0; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[5].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[5].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[5].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[5].ALIGN_0 = 0;//Some comments needed here
  //--------------------------------------------------
  //RUN : 6
  //--------------------------------------------------
  //->: inception_5b/pool_proj
  //->: inception_5b/relu_pool_proj
  _conf.sw.run[6].in_w = 7; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[6].in_h = 7; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[6].in_c = 832; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[6].out_w = 7; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[6].out_h = 7; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[6].m = 128; // Output Channels
  _conf.hw.run[6].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[6].p = 1; // Filter Width and Height
  _conf.hw.run[6].pz = 1; // Filter Depth
  _conf.hw.run[6].weight_base_addr = 0x0062EAE0; // Filter Weight and Bias byte address
  _conf.hw.run[6].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[6].weight_size = 120576; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[6].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[6].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[6].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[6].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[6].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[6].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[6].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[6].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[6].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[6].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[6].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[6].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[6].ALIGN_0 = 0;//Some comments needed here

  struct fpga_layer& layer = layers[14];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00013E80;
  layer.addr_offset_output = 0x00027D00;
  layer.output_size = 100352;
  layer.input_dim[0] = 7;
  layer.input_dim[1] = 7;
  layer.input_dim[2] = 832;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 7;
  layer.output_dim[1] = 7;
  layer.output_dim[2] = 1024;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_14

//Layer_15: Convolution Layer
//  ->: pool5/7x7_s1
void CCaffeGoogLeNet::Layer_15() {
  struct top_conv_conf& _conf = get_conv_layer(15);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 7; // Input Width
  _conf.hw.input.h = 7; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 1024; // Input Channels
  _conf.hw.input.input_base_addr = 0x00027D00; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 1; // Output Width
  _conf.sw.output.h = 1; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 1024; // Output Channels
  _conf.hw.output.output_base_addr = 0x00000000; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: pool5/7x7_s1
  _conf.sw.run[0].in_w = 7; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 7; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 1024; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 1; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 1; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 1024; // Output Channels
  _conf.hw.run[0].conv_enable = 0; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x0064C1E0; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 0; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 0; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[0].pool_enable = 2;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[0].pool_size = 0x707; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[0].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].pool_avg_param = 0x2539; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[0].actfunc = 0; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

  struct fpga_layer& layer = layers[15];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00027D00;
  layer.addr_offset_output = 0x00000000;
  layer.output_size = 2048;
  layer.input_dim[0] = 7;
  layer.input_dim[1] = 7;
  layer.input_dim[2] = 1024;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 1;
  layer.output_dim[1] = 1;
  layer.output_dim[2] = 1024;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_15

//Layer_16: Fully Connected Layer
//	->: loss3/classifier
void CCaffeGoogLeNet::Layer_16() {
  struct top_fc_conf& cf = get_ip_layer(0);
  cf.hw.input_size = 1024;
  cf.hw.output_size = 1000;
  cf.sw.total_size = 1026512; //from tool // Actual size in bytes of LUT, weights and bias (in bytes)
  cf.hw.stride = cf.hw.input_size;
  cf.hw.bias_size = 2 * cf.hw.output_size; // bias size (in bytes) = 2 times the output size
  cf.hw.param_base_addr = 0x0064C1E0; //base address
  cf.hw.weight_addr = 0x0064C3E0; //weight address = param_base_addr + 2*256 (lut size/float16/2bytes)
  cf.hw.bias_addr = 0x007463E0; //bias address =  weight_addr + stride*input size
  cf.hw.input_base_addr = 0x00000000;
  cf.hw.output_base_addr = 0x00000800;
  cf.hw.param_fmt = 1; // 0 = unquantized weight matrix, 1 = qunatized
  cf.hw.actfunc = 0x0; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  cf.hw.actfunc_param = 0x0; // Leaky ReLU parameter (in FP16 format), 0 = non-leaky

  struct fpga_layer& layer = layers[16];
  layer.type = LT_FC;
  layer.hw_conf = (void*)&cf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00000000;
  layer.addr_offset_output = 0x00000800;
  layer.output_size = 2000;
  layer.input_dim[0] = 1;
  layer.input_dim[1] = 1;
  layer.input_dim[2] = 1024;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 1000;
  layer.output_dim_size = 1;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_16

//Layer_17: SoftMax Layer
//	->: prob
void CCaffeGoogLeNet::Layer_17() {
  struct fpga_layer& layer = layers[17];
  layer.type = LT_SOFTMAX;
  layer.hw_conf = (void*)0;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00000800;
  layer.addr_offset_output = 0x00000FD0;
  layer.output_size = 4000;
  layer.input_dim[0] = 1000;
  layer.input_dim_size = 1;
  layer.output_dim[0] = 1000;
  layer.output_dim_size = 1;
  layer.is_output = true;
  layer.is_f32_output = true;
  layer.is_input_hw_layout = false;
  layer.softmax_axis = 0;
  output_layers[0] = &layer;
}//end of  Layer_17

