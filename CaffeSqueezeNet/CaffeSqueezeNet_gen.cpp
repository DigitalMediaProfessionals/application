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

#include "CaffeSqueezeNet_gen.h"

CCaffeSqueezeNet::CCaffeSqueezeNet() {}

CCaffeSqueezeNet::~CCaffeSqueezeNet() {}

unsigned int CCaffeSqueezeNet::get_total_layer_count() {
  return num_layers;
}

unsigned int CCaffeSqueezeNet::get_output_layer_count() {
  return num_output_layers;
}

unsigned int CCaffeSqueezeNet::get_convolution_layer_count() {
  return num_conv_layers;
}

unsigned int CCaffeSqueezeNet::get_innerproduct_layer_count() {
  return num_fc_layers;
}

int CCaffeSqueezeNet::initialize() {
  num_layers = 21;
  num_output_layers = 1;
  num_conv_layers = 20;
  num_fc_layers = 0;
  weight_size = 1380624;
  buffer_size = 1064800;
  layers.resize(num_layers);
  output_layers.resize(num_output_layers);
  conv_layers.resize(num_conv_layers);
  fc_layers.resize(num_fc_layers);
  memory_size_request.resize(2);

  //set_default_convolution_layers_parameters();
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

  //Add 2 memory size requests. One for weights, the other for io buffers
  memory_size_request[0] = weight_size;
  memory_size_request[1] = buffer_size;

  return 0;
}

//Layer_0: Convolution Layer
//  ->: conv1
//  ->: relu_conv1
//  ->: pool1
void CCaffeSqueezeNet::Layer_0() {
  struct top_conv_conf& _conf = get_conv_layer(0);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 227; // Input Width
  _conf.hw.input.h = 227; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 3; // Input Channels
  _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 55; // Output Width
  _conf.sw.output.h = 55; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 96; // Output Channels
  _conf.hw.output.output_base_addr = 0x0004B7C0; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv1
  //->: relu_conv1
  //->: pool1
  _conf.sw.run[0].in_w = 227; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 227; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 3; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 55; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 55; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 96; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 7; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x00000000; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 21440; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].conv_stride = 0x202; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[0].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[0].pool_size = 0x303; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[0].pool_stride = 0x202; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[0].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

  struct fpga_layer& layer = layers[0];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00000000;
  layer.addr_offset_output = 0x0004B7C0;
  layer.output_size = 580800;
  layer.input_dim[0] = 227;
  layer.input_dim[1] = 227;
  layer.input_dim[2] = 3;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 55;
  layer.output_dim[1] = 55;
  layer.output_dim[2] = 96;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = false;
}//end of  Layer_0

//Layer_1: Convolution Layer
//  ->: fire2/squeeze1x1
//  ->: fire2/relu_squeeze1x1
void CCaffeSqueezeNet::Layer_1() {
  struct top_conv_conf& _conf = get_conv_layer(1);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 55; // Input Width
  _conf.hw.input.h = 55; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 96; // Input Channels
  _conf.hw.input.input_base_addr = 0x0004B7C0; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 55; // Output Width
  _conf.sw.output.h = 55; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 16; // Output Channels
  _conf.hw.output.output_base_addr = 0x00000000; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: fire2/squeeze1x1
  //->: fire2/relu_squeeze1x1
  _conf.sw.run[0].in_w = 55; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 55; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 96; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 55; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 55; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 16; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x000053C0; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 2848; // Actual size in bytes of LUT, weights and bias (in bytes)
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

  struct fpga_layer& layer = layers[1];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x0004B7C0;
  layer.addr_offset_output = 0x00000000;
  layer.output_size = 96800;
  layer.input_dim[0] = 55;
  layer.input_dim[1] = 55;
  layer.input_dim[2] = 96;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 55;
  layer.output_dim[1] = 55;
  layer.output_dim[2] = 16;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_1

//Layer_2: Convolution Layer
//  ->: fire2/expand1x1
//  ->: fire2/relu_expand1x1
//  ->: fire2/expand3x3
//  ->: fire2/relu_expand3x3
void CCaffeSqueezeNet::Layer_2() {
  struct top_conv_conf& _conf = get_conv_layer(2);
  //Topo: 00000000000000000000000000000011
  _conf.hw.header.topo = 0x3; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 55; // Input Width
  _conf.hw.input.h = 55; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 16; // Input Channels
  _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 55; // Output Width
  _conf.sw.output.h = 55; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 128; // Output Channels
  _conf.hw.output.output_base_addr = 0x00017A20; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->2 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: fire2/expand1x1
  //->: fire2/relu_expand1x1
  _conf.sw.run[0].in_w = 55; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 55; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 16; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 55; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 55; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 64; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x00005EE0; // Filter Weight and Bias byte address
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
  //--------------------------------------------------
  //RUN : 1
  //--------------------------------------------------
  //->: fire2/expand3x3
  //->: fire2/relu_expand3x3
  _conf.sw.run[1].in_w = 55; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[1].in_h = 55; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[1].in_c = 16; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[1].out_w = 55; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[1].out_h = 55; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[1].m = 64; // Output Channels
  _conf.hw.run[1].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[1].p = 3; // Filter Width and Height
  _conf.hw.run[1].pz = 1; // Filter Depth
  _conf.hw.run[1].weight_base_addr = 0x00007360; // Filter Weight and Bias byte address
  _conf.hw.run[1].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[1].weight_size = 9856; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[1].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
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

  struct fpga_layer& layer = layers[2];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00000000;
  layer.addr_offset_output = 0x00017A20;
  layer.output_size = 774400;
  layer.input_dim[0] = 55;
  layer.input_dim[1] = 55;
  layer.input_dim[2] = 16;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 55;
  layer.output_dim[1] = 55;
  layer.output_dim[2] = 128;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_2

//Layer_3: Convolution Layer
//  ->: fire3/squeeze1x1
//  ->: fire3/relu_squeeze1x1
void CCaffeSqueezeNet::Layer_3() {
  struct top_conv_conf& _conf = get_conv_layer(3);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 55; // Input Width
  _conf.hw.input.h = 55; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 128; // Input Channels
  _conf.hw.input.input_base_addr = 0x00017A20; // Input byte address
  _conf.hw.input.tiles = 2; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 55; // Output Width
  _conf.sw.output.h = 55; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 16; // Output Channels
  _conf.hw.output.output_base_addr = 0x00000000; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: fire3/squeeze1x1
  //->: fire3/relu_squeeze1x1
  _conf.sw.run[0].in_w = 55; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 55; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 128; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 55; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 55; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 16; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x000099E0; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 2848; // Actual size in bytes of LUT, weights and bias (in bytes)
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

  struct fpga_layer& layer = layers[3];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00017A20;
  layer.addr_offset_output = 0x00000000;
  layer.output_size = 96800;
  layer.input_dim[0] = 55;
  layer.input_dim[1] = 55;
  layer.input_dim[2] = 128;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 55;
  layer.output_dim[1] = 55;
  layer.output_dim[2] = 16;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_3

//Layer_4: Convolution Layer
//  ->: fire3/expand1x1
//  ->: fire3/relu_expand1x1
//  ->: fire3/expand3x3
//  ->: fire3/relu_expand3x3
void CCaffeSqueezeNet::Layer_4() {
  struct top_conv_conf& _conf = get_conv_layer(4);
  //Topo: 00000000000000000000000000000011
  _conf.hw.header.topo = 0x3; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 55; // Input Width
  _conf.hw.input.h = 55; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 16; // Input Channels
  _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 55; // Output Width
  _conf.sw.output.h = 55; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 128; // Output Channels
  _conf.hw.output.output_base_addr = 0x00017A20; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->2 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: fire3/expand1x1
  //->: fire3/relu_expand1x1
  _conf.sw.run[0].in_w = 55; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 55; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 16; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 55; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 55; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 64; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x0000A500; // Filter Weight and Bias byte address
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
  //--------------------------------------------------
  //RUN : 1
  //--------------------------------------------------
  //->: fire3/expand3x3
  //->: fire3/relu_expand3x3
  _conf.sw.run[1].in_w = 55; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[1].in_h = 55; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[1].in_c = 16; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[1].out_w = 55; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[1].out_h = 55; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[1].m = 64; // Output Channels
  _conf.hw.run[1].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[1].p = 3; // Filter Width and Height
  _conf.hw.run[1].pz = 1; // Filter Depth
  _conf.hw.run[1].weight_base_addr = 0x0000B980; // Filter Weight and Bias byte address
  _conf.hw.run[1].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[1].weight_size = 9856; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[1].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
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

  struct fpga_layer& layer = layers[4];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00000000;
  layer.addr_offset_output = 0x00017A20;
  layer.output_size = 774400;
  layer.input_dim[0] = 55;
  layer.input_dim[1] = 55;
  layer.input_dim[2] = 16;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 55;
  layer.output_dim[1] = 55;
  layer.output_dim[2] = 128;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_4

//Layer_5: Convolution Layer
//  ->: fire4/squeeze1x1
//  ->: fire4/relu_squeeze1x1
void CCaffeSqueezeNet::Layer_5() {
  struct top_conv_conf& _conf = get_conv_layer(5);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 55; // Input Width
  _conf.hw.input.h = 55; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 128; // Input Channels
  _conf.hw.input.input_base_addr = 0x00017A20; // Input byte address
  _conf.hw.input.tiles = 2; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 55; // Output Width
  _conf.sw.output.h = 55; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 32; // Output Channels
  _conf.hw.output.output_base_addr = 0x000D4B20; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: fire4/squeeze1x1
  //->: fire4/relu_squeeze1x1
  _conf.sw.run[0].in_w = 55; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 55; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 128; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 55; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 55; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 32; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x0000E000; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 5184; // Actual size in bytes of LUT, weights and bias (in bytes)
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

  struct fpga_layer& layer = layers[5];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00017A20;
  layer.addr_offset_output = 0x000D4B20;
  layer.output_size = 193600;
  layer.input_dim[0] = 55;
  layer.input_dim[1] = 55;
  layer.input_dim[2] = 128;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 55;
  layer.output_dim[1] = 55;
  layer.output_dim[2] = 32;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_5

//Layer_6: Convolution Layer
//  ->: fire4/expand1x1
//  ->: fire4/relu_expand1x1
//  ->: pool4
//  ->: fire4/expand3x3
//  ->: fire4/relu_expand3x3
//  ->: pool4
void CCaffeSqueezeNet::Layer_6() {
  struct top_conv_conf& _conf = get_conv_layer(6);
  //Topo: 00000000000000000000000000000011
  _conf.hw.header.topo = 0x3; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 55; // Input Width
  _conf.hw.input.h = 55; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 32; // Input Channels
  _conf.hw.input.input_base_addr = 0x000D4B20; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 27; // Output Width
  _conf.sw.output.h = 27; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 256; // Output Channels
  _conf.hw.output.output_base_addr = 0x00000000; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->2 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: fire4/expand1x1
  //->: fire4/relu_expand1x1
  //->: pool4
  _conf.sw.run[0].in_w = 55; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 55; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 32; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 27; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 27; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 128; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x0000F440; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 9984; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[0].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[0].pool_size = 0x303; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[0].pool_stride = 0x202; // bits [7:0] = X stride, bits [15:8] = Y stride
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
  //->: fire4/expand3x3
  //->: fire4/relu_expand3x3
  //->: pool4
  _conf.sw.run[1].in_w = 55; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[1].in_h = 55; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[1].in_c = 32; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[1].out_w = 27; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[1].out_h = 27; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[1].m = 128; // Output Channels
  _conf.hw.run[1].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[1].p = 3; // Filter Width and Height
  _conf.hw.run[1].pz = 1; // Filter Depth
  _conf.hw.run[1].weight_base_addr = 0x00011B40; // Filter Weight and Bias byte address
  _conf.hw.run[1].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[1].weight_size = 37632; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[1].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[1].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[1].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[1].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[1].pool_size = 0x303; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[1].pool_stride = 0x202; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[1].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[1].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[1].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[1].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[1].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[1].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[1].ALIGN_0 = 0;//Some comments needed here

  struct fpga_layer& layer = layers[6];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x000D4B20;
  layer.addr_offset_output = 0x00000000;
  layer.output_size = 373248;
  layer.input_dim[0] = 55;
  layer.input_dim[1] = 55;
  layer.input_dim[2] = 32;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 27;
  layer.output_dim[1] = 27;
  layer.output_dim[2] = 256;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_6

//Layer_7: Convolution Layer
//  ->: fire5/squeeze1x1
//  ->: fire5/relu_squeeze1x1
void CCaffeSqueezeNet::Layer_7() {
  struct top_conv_conf& _conf = get_conv_layer(7);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 27; // Input Width
  _conf.hw.input.h = 27; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 256; // Input Channels
  _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 27; // Output Width
  _conf.sw.output.h = 27; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 32; // Output Channels
  _conf.hw.output.output_base_addr = 0x0005B200; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: fire5/squeeze1x1
  //->: fire5/relu_squeeze1x1
  _conf.sw.run[0].in_w = 27; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 27; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 256; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 27; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 27; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 32; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x0001AE40; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 9792; // Actual size in bytes of LUT, weights and bias (in bytes)
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

  struct fpga_layer& layer = layers[7];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00000000;
  layer.addr_offset_output = 0x0005B200;
  layer.output_size = 46656;
  layer.input_dim[0] = 27;
  layer.input_dim[1] = 27;
  layer.input_dim[2] = 256;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 27;
  layer.output_dim[1] = 27;
  layer.output_dim[2] = 32;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_7

//Layer_8: Convolution Layer
//  ->: fire5/expand1x1
//  ->: fire5/relu_expand1x1
//  ->: fire5/expand3x3
//  ->: fire5/relu_expand3x3
void CCaffeSqueezeNet::Layer_8() {
  struct top_conv_conf& _conf = get_conv_layer(8);
  //Topo: 00000000000000000000000000000011
  _conf.hw.header.topo = 0x3; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 27; // Input Width
  _conf.hw.input.h = 27; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 32; // Input Channels
  _conf.hw.input.input_base_addr = 0x0005B200; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 27; // Output Width
  _conf.sw.output.h = 27; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 256; // Output Channels
  _conf.hw.output.output_base_addr = 0x00000000; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->2 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: fire5/expand1x1
  //->: fire5/relu_expand1x1
  _conf.sw.run[0].in_w = 27; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 27; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 32; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 27; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 27; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 128; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x0001D480; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 9984; // Actual size in bytes of LUT, weights and bias (in bytes)
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
  //->: fire5/expand3x3
  //->: fire5/relu_expand3x3
  _conf.sw.run[1].in_w = 27; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[1].in_h = 27; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[1].in_c = 32; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[1].out_w = 27; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[1].out_h = 27; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[1].m = 128; // Output Channels
  _conf.hw.run[1].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[1].p = 3; // Filter Width and Height
  _conf.hw.run[1].pz = 1; // Filter Depth
  _conf.hw.run[1].weight_base_addr = 0x0001FB80; // Filter Weight and Bias byte address
  _conf.hw.run[1].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[1].weight_size = 37632; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[1].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
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

  struct fpga_layer& layer = layers[8];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x0005B200;
  layer.addr_offset_output = 0x00000000;
  layer.output_size = 373248;
  layer.input_dim[0] = 27;
  layer.input_dim[1] = 27;
  layer.input_dim[2] = 32;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 27;
  layer.output_dim[1] = 27;
  layer.output_dim[2] = 256;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_8

//Layer_9: Convolution Layer
//  ->: fire6/squeeze1x1
//  ->: fire6/relu_squeeze1x1
void CCaffeSqueezeNet::Layer_9() {
  struct top_conv_conf& _conf = get_conv_layer(9);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 27; // Input Width
  _conf.hw.input.h = 27; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 256; // Input Channels
  _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 27; // Output Width
  _conf.sw.output.h = 27; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 48; // Output Channels
  _conf.hw.output.output_base_addr = 0x0005B200; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: fire6/squeeze1x1
  //->: fire6/relu_squeeze1x1
  _conf.sw.run[0].in_w = 27; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 27; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 256; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 27; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 27; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 48; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x00028E80; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 14432; // Actual size in bytes of LUT, weights and bias (in bytes)
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

  struct fpga_layer& layer = layers[9];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00000000;
  layer.addr_offset_output = 0x0005B200;
  layer.output_size = 69984;
  layer.input_dim[0] = 27;
  layer.input_dim[1] = 27;
  layer.input_dim[2] = 256;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 27;
  layer.output_dim[1] = 27;
  layer.output_dim[2] = 48;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_9

//Layer_10: Convolution Layer
//  ->: fire6/expand1x1
//  ->: fire6/relu_expand1x1
//  ->: fire6/expand3x3
//  ->: fire6/relu_expand3x3
void CCaffeSqueezeNet::Layer_10() {
  struct top_conv_conf& _conf = get_conv_layer(10);
  //Topo: 00000000000000000000000000000011
  _conf.hw.header.topo = 0x3; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 27; // Input Width
  _conf.hw.input.h = 27; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 48; // Input Channels
  _conf.hw.input.input_base_addr = 0x0005B200; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 27; // Output Width
  _conf.sw.output.h = 27; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 384; // Output Channels
  _conf.hw.output.output_base_addr = 0x0006C360; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->2 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: fire6/expand1x1
  //->: fire6/relu_expand1x1
  _conf.sw.run[0].in_w = 27; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 27; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 48; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 27; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 27; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 192; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x0002C6E0; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 14720; // Actual size in bytes of LUT, weights and bias (in bytes)
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
  //->: fire6/expand3x3
  //->: fire6/relu_expand3x3
  _conf.sw.run[1].in_w = 27; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[1].in_h = 27; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[1].in_c = 48; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[1].out_w = 27; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[1].out_h = 27; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[1].m = 192; // Output Channels
  _conf.hw.run[1].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[1].p = 3; // Filter Width and Height
  _conf.hw.run[1].pz = 1; // Filter Depth
  _conf.hw.run[1].weight_base_addr = 0x00030060; // Filter Weight and Bias byte address
  _conf.hw.run[1].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[1].weight_size = 83840; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[1].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
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

  struct fpga_layer& layer = layers[10];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x0005B200;
  layer.addr_offset_output = 0x0006C360;
  layer.output_size = 559872;
  layer.input_dim[0] = 27;
  layer.input_dim[1] = 27;
  layer.input_dim[2] = 48;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 27;
  layer.output_dim[1] = 27;
  layer.output_dim[2] = 384;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_10

//Layer_11: Convolution Layer
//  ->: fire7/squeeze1x1
//  ->: fire7/relu_squeeze1x1
void CCaffeSqueezeNet::Layer_11() {
  struct top_conv_conf& _conf = get_conv_layer(11);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 27; // Input Width
  _conf.hw.input.h = 27; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 384; // Input Channels
  _conf.hw.input.input_base_addr = 0x0006C360; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 27; // Output Width
  _conf.sw.output.h = 27; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 48; // Output Channels
  _conf.hw.output.output_base_addr = 0x00000000; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: fire7/squeeze1x1
  //->: fire7/relu_squeeze1x1
  _conf.sw.run[0].in_w = 27; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 27; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 384; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 27; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 27; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 48; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x000447E0; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 21344; // Actual size in bytes of LUT, weights and bias (in bytes)
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

  struct fpga_layer& layer = layers[11];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x0006C360;
  layer.addr_offset_output = 0x00000000;
  layer.output_size = 69984;
  layer.input_dim[0] = 27;
  layer.input_dim[1] = 27;
  layer.input_dim[2] = 384;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 27;
  layer.output_dim[1] = 27;
  layer.output_dim[2] = 48;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_11

//Layer_12: Convolution Layer
//  ->: fire7/expand1x1
//  ->: fire7/relu_expand1x1
//  ->: fire7/expand3x3
//  ->: fire7/relu_expand3x3
void CCaffeSqueezeNet::Layer_12() {
  struct top_conv_conf& _conf = get_conv_layer(12);
  //Topo: 00000000000000000000000000000011
  _conf.hw.header.topo = 0x3; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 27; // Input Width
  _conf.hw.input.h = 27; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 48; // Input Channels
  _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 27; // Output Width
  _conf.sw.output.h = 27; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 384; // Output Channels
  _conf.hw.output.output_base_addr = 0x00011160; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->2 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: fire7/expand1x1
  //->: fire7/relu_expand1x1
  _conf.sw.run[0].in_w = 27; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 27; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 48; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 27; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 27; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 192; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x00049B40; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 14720; // Actual size in bytes of LUT, weights and bias (in bytes)
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
  //->: fire7/expand3x3
  //->: fire7/relu_expand3x3
  _conf.sw.run[1].in_w = 27; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[1].in_h = 27; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[1].in_c = 48; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[1].out_w = 27; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[1].out_h = 27; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[1].m = 192; // Output Channels
  _conf.hw.run[1].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[1].p = 3; // Filter Width and Height
  _conf.hw.run[1].pz = 1; // Filter Depth
  _conf.hw.run[1].weight_base_addr = 0x0004D4C0; // Filter Weight and Bias byte address
  _conf.hw.run[1].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[1].weight_size = 83840; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[1].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
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

  struct fpga_layer& layer = layers[12];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00000000;
  layer.addr_offset_output = 0x00011160;
  layer.output_size = 559872;
  layer.input_dim[0] = 27;
  layer.input_dim[1] = 27;
  layer.input_dim[2] = 48;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 27;
  layer.output_dim[1] = 27;
  layer.output_dim[2] = 384;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_12

//Layer_13: Convolution Layer
//  ->: fire8/squeeze1x1
//  ->: fire8/relu_squeeze1x1
void CCaffeSqueezeNet::Layer_13() {
  struct top_conv_conf& _conf = get_conv_layer(13);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 27; // Input Width
  _conf.hw.input.h = 27; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 384; // Input Channels
  _conf.hw.input.input_base_addr = 0x00011160; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 27; // Output Width
  _conf.sw.output.h = 27; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 64; // Output Channels
  _conf.hw.output.output_base_addr = 0x00099C60; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: fire8/squeeze1x1
  //->: fire8/relu_squeeze1x1
  _conf.sw.run[0].in_w = 27; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 27; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 384; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 27; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 27; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 64; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x00061C40; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 28288; // Actual size in bytes of LUT, weights and bias (in bytes)
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

  struct fpga_layer& layer = layers[13];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00011160;
  layer.addr_offset_output = 0x00099C60;
  layer.output_size = 93312;
  layer.input_dim[0] = 27;
  layer.input_dim[1] = 27;
  layer.input_dim[2] = 384;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 27;
  layer.output_dim[1] = 27;
  layer.output_dim[2] = 64;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_13

//Layer_14: Convolution Layer
//  ->: fire8/expand1x1
//  ->: fire8/relu_expand1x1
//  ->: pool8
//  ->: fire8/expand3x3
//  ->: fire8/relu_expand3x3
//  ->: pool8
void CCaffeSqueezeNet::Layer_14() {
  struct top_conv_conf& _conf = get_conv_layer(14);
  //Topo: 00000000000000000000000000000011
  _conf.hw.header.topo = 0x3; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 27; // Input Width
  _conf.hw.input.h = 27; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 64; // Input Channels
  _conf.hw.input.input_base_addr = 0x00099C60; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 13; // Output Width
  _conf.sw.output.h = 13; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 512; // Output Channels
  _conf.hw.output.output_base_addr = 0x00000000; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->2 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: fire8/expand1x1
  //->: fire8/relu_expand1x1
  //->: pool8
  _conf.sw.run[0].in_w = 27; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 27; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 64; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 13; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 13; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 256; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x00068AC0; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 19456; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[0].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[0].pool_size = 0x303; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[0].pool_stride = 0x202; // bits [7:0] = X stride, bits [15:8] = Y stride
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
  //->: fire8/expand3x3
  //->: fire8/relu_expand3x3
  //->: pool8
  _conf.sw.run[1].in_w = 27; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[1].in_h = 27; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[1].in_c = 64; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[1].out_w = 13; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[1].out_h = 13; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[1].m = 256; // Output Channels
  _conf.hw.run[1].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[1].p = 3; // Filter Width and Height
  _conf.hw.run[1].pz = 1; // Filter Depth
  _conf.hw.run[1].weight_base_addr = 0x0006D6C0; // Filter Weight and Bias byte address
  _conf.hw.run[1].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[1].weight_size = 148480; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[1].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[1].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[1].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[1].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[1].pool_size = 0x303; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[1].pool_stride = 0x202; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[1].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[1].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[1].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[1].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[1].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[1].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[1].ALIGN_0 = 0;//Some comments needed here

  struct fpga_layer& layer = layers[14];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00099C60;
  layer.addr_offset_output = 0x00000000;
  layer.output_size = 173056;
  layer.input_dim[0] = 27;
  layer.input_dim[1] = 27;
  layer.input_dim[2] = 64;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 13;
  layer.output_dim[1] = 13;
  layer.output_dim[2] = 512;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_14

//Layer_15: Convolution Layer
//  ->: fire9/squeeze1x1
//  ->: fire9/relu_squeeze1x1
void CCaffeSqueezeNet::Layer_15() {
  struct top_conv_conf& _conf = get_conv_layer(15);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 13; // Input Width
  _conf.hw.input.h = 13; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 512; // Input Channels
  _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 13; // Output Width
  _conf.sw.output.h = 13; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 64; // Output Channels
  _conf.hw.output.output_base_addr = 0x0002A400; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: fire9/squeeze1x1
  //->: fire9/relu_squeeze1x1
  _conf.sw.run[0].in_w = 13; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 13; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 512; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 13; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 13; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 64; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x00091AC0; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 37504; // Actual size in bytes of LUT, weights and bias (in bytes)
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

  struct fpga_layer& layer = layers[15];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00000000;
  layer.addr_offset_output = 0x0002A400;
  layer.output_size = 21632;
  layer.input_dim[0] = 13;
  layer.input_dim[1] = 13;
  layer.input_dim[2] = 512;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 13;
  layer.output_dim[1] = 13;
  layer.output_dim[2] = 64;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_15

//Layer_16: Convolution Layer
//  ->: fire9/expand1x1
//  ->: fire9/relu_expand1x1
//  ->: fire9/expand3x3
//  ->: fire9/relu_expand3x3
void CCaffeSqueezeNet::Layer_16() {
  struct top_conv_conf& _conf = get_conv_layer(16);
  //Topo: 00000000000000000000000000000011
  _conf.hw.header.topo = 0x3; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 13; // Input Width
  _conf.hw.input.h = 13; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 64; // Input Channels
  _conf.hw.input.input_base_addr = 0x0002A400; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 13; // Output Width
  _conf.sw.output.h = 13; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 512; // Output Channels
  _conf.hw.output.output_base_addr = 0x00000000; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->2 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: fire9/expand1x1
  //->: fire9/relu_expand1x1
  _conf.sw.run[0].in_w = 13; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 13; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 64; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 13; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 13; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 256; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x0009AD40; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 19456; // Actual size in bytes of LUT, weights and bias (in bytes)
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
  //->: fire9/expand3x3
  //->: fire9/relu_expand3x3
  _conf.sw.run[1].in_w = 13; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[1].in_h = 13; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[1].in_c = 64; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[1].out_w = 13; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[1].out_h = 13; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[1].m = 256; // Output Channels
  _conf.hw.run[1].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[1].p = 3; // Filter Width and Height
  _conf.hw.run[1].pz = 1; // Filter Depth
  _conf.hw.run[1].weight_base_addr = 0x0009F940; // Filter Weight and Bias byte address
  _conf.hw.run[1].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[1].weight_size = 148480; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[1].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
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

  struct fpga_layer& layer = layers[16];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x0002A400;
  layer.addr_offset_output = 0x00000000;
  layer.output_size = 173056;
  layer.input_dim[0] = 13;
  layer.input_dim[1] = 13;
  layer.input_dim[2] = 64;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 13;
  layer.output_dim[1] = 13;
  layer.output_dim[2] = 512;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_16

//Layer_17: Convolution Layer
//  ->: conv10
//  ->: relu_conv10
void CCaffeSqueezeNet::Layer_17() {
  struct top_conv_conf& _conf = get_conv_layer(17);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 13; // Input Width
  _conf.hw.input.h = 13; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 512; // Input Channels
  _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 15; // Output Width
  _conf.sw.output.h = 15; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 1000; // Output Channels
  _conf.hw.output.output_base_addr = 0x0002A400; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv10
  //->: relu_conv10
  _conf.sw.run[0].in_w = 13; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 13; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 512; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 15; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 15; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 1000; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x000C3D40; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 578512; // Actual size in bytes of LUT, weights and bias (in bytes)
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

  struct fpga_layer& layer = layers[17];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00000000;
  layer.addr_offset_output = 0x0002A400;
  layer.output_size = 450000;
  layer.input_dim[0] = 13;
  layer.input_dim[1] = 13;
  layer.input_dim[2] = 512;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 15;
  layer.output_dim[1] = 15;
  layer.output_dim[2] = 1000;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_17

//Layer_18: Convolution Layer
//  ->: pool10_5
void CCaffeSqueezeNet::Layer_18() {
  struct top_conv_conf& _conf = get_conv_layer(18);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 15; // Input Width
  _conf.hw.input.h = 15; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 1000; // Input Channels
  _conf.hw.input.input_base_addr = 0x0002A400; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 3; // Output Width
  _conf.sw.output.h = 3; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 1000; // Output Channels
  _conf.hw.output.output_base_addr = 0x00000000; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: pool10_5
  _conf.sw.run[0].in_w = 15; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 15; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 1000; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 3; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 3; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 1000; // Output Channels
  _conf.hw.run[0].conv_enable = 0; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x00151110; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 0; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 0; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[0].pool_enable = 2;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[0].pool_size = 0x505; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[0].pool_stride = 0x505; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].pool_avg_param = 0x291F; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[0].actfunc = 0; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

  struct fpga_layer& layer = layers[18];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x0002A400;
  layer.addr_offset_output = 0x00000000;
  layer.output_size = 18000;
  layer.input_dim[0] = 15;
  layer.input_dim[1] = 15;
  layer.input_dim[2] = 1000;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 3;
  layer.output_dim[1] = 3;
  layer.output_dim[2] = 1000;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_18

//Layer_19: Convolution Layer
//  ->: pool10_3
void CCaffeSqueezeNet::Layer_19() {
  struct top_conv_conf& _conf = get_conv_layer(19);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 3; // Input Width
  _conf.hw.input.h = 3; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 1000; // Input Channels
  _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 1; // Output Width
  _conf.sw.output.h = 1; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 1000; // Output Channels
  _conf.hw.output.output_base_addr = 0x00004650; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: pool10_3
  _conf.sw.run[0].in_w = 3; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 3; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 1000; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 1; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 1; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 1000; // Output Channels
  _conf.hw.run[0].conv_enable = 0; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x00151110; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 0; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 0; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
  _conf.hw.run[0].pool_enable = 2;  // 0 = disabled, 1 = max pooling, 2 = average pooling
  _conf.hw.run[0].pool_size = 0x303; // bits [7:0] = width, bits [15:8] = height
  _conf.hw.run[0].pool_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
  _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].pool_avg_param = 0x2F1C; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
  _conf.hw.run[0].actfunc = 0; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
  _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
  _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
  _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

  struct fpga_layer& layer = layers[19];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00000000;
  layer.addr_offset_output = 0x00004650;
  layer.output_size = 2000;
  layer.input_dim[0] = 3;
  layer.input_dim[1] = 3;
  layer.input_dim[2] = 1000;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 1;
  layer.output_dim[1] = 1;
  layer.output_dim[2] = 1000;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_19

//Layer_20: SoftMax Layer
//	->: prob
void CCaffeSqueezeNet::Layer_20() {
  struct fpga_layer& layer = layers[20];
  layer.type = LT_SOFTMAX;
  layer.hw_conf = (void*)0;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00004650;
  layer.addr_offset_output = 0x00000000;
  layer.output_size = 4000;
  layer.input_dim[0] = 1;
  layer.input_dim[1] = 1;
  layer.input_dim[2] = 1000;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 1;
  layer.output_dim[1] = 1;
  layer.output_dim[2] = 1000;
  layer.output_dim_size = 3;
  layer.is_output = true;
  layer.is_f32_output = true;
  layer.is_input_hw_layout = true;
  layer.softmax_axis = 2;
  output_layers[0] = &layer;
}//end of  Layer_20

