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

#include "KerasMobileNet_gen.h"

CKerasMobileNet::CKerasMobileNet() {}

CKerasMobileNet::~CKerasMobileNet() {}

unsigned int CKerasMobileNet::get_total_layer_count() {
  return num_layers;
}

unsigned int CKerasMobileNet::get_output_layer_count() {
  return num_output_layers;
}

unsigned int CKerasMobileNet::get_convolution_layer_count() {
  return num_conv_layers;
}

unsigned int CKerasMobileNet::get_innerproduct_layer_count() {
  return num_fc_layers;
}

int CKerasMobileNet::initialize() {
  num_layers = 30;
  num_output_layers = 1;
  num_conv_layers = 29;
  num_fc_layers = 0;
  weight_size = 5083984;
  buffer_size = 3512320;
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
  Layer_21();
  Layer_22();
  Layer_23();
  Layer_24();
  Layer_25();
  Layer_26();
  Layer_27();
  Layer_28();
  Layer_29();

  //Add 2 memory size requests. One for weights, the other for io buffers
  memory_size_request[0] = weight_size;
  memory_size_request[1] = buffer_size;

  return 0;
}

//Layer_0: Convolution Layer
//  ->: conv1
//  ->: conv1_bn
//  ->: conv1_bn
//  ->: conv1_relu
void CKerasMobileNet::Layer_0() {
  struct top_conv_conf& _conf = get_conv_layer(0);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 224; // Input Width
  _conf.hw.input.h = 224; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 3; // Input Channels
  _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 112; // Output Width
  _conf.sw.output.h = 112; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 32; // Output Channels
  _conf.hw.output.output_base_addr = 0x00049800; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv1
  //->: conv1_bn
  //->: conv1_bn
  //->: conv1_relu
  _conf.sw.run[0].in_w = 224; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 224; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 3; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 112; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 112; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 32; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 3; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x00000000; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 2880; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[0].conv_pad = 0x1000100; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].conv_stride = 0x202; // bits [7:0] = X stride, bits [15:8] = Y stride
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

  struct fpga_layer& layer = layers[0];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00000000;
  layer.addr_offset_output = 0x00049800;
  layer.output_size = 802816;
  layer.input_dim[0] = 224;
  layer.input_dim[1] = 224;
  layer.input_dim[2] = 3;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 112;
  layer.output_dim[1] = 112;
  layer.output_dim[2] = 32;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = false;
}//end of  Layer_0

//Layer_1: Convolution Layer
//  ->: conv_dw_1
//  ->: conv_dw_1_bn
//  ->: conv_dw_1_bn
//  ->: conv_dw_1_relu
void CKerasMobileNet::Layer_1() {
  struct top_conv_conf& _conf = get_conv_layer(1);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 112; // Input Width
  _conf.hw.input.h = 112; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 32; // Input Channels
  _conf.hw.input.input_base_addr = 0x00049800; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 112; // Output Width
  _conf.sw.output.h = 112; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 32; // Output Channels
  _conf.hw.output.output_base_addr = 0x0010D800; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv_dw_1
  //->: conv_dw_1_bn
  //->: conv_dw_1_bn
  //->: conv_dw_1_relu
  _conf.sw.run[0].in_w = 112; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 112; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 32; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 112; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 112; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 32; // Output Channels
  _conf.hw.run[0].conv_enable = 3; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 3; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x00000B40; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 2880; // Actual size in bytes of LUT, weights and bias (in bytes)
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

  struct fpga_layer& layer = layers[1];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00049800;
  layer.addr_offset_output = 0x0010D800;
  layer.output_size = 802816;
  layer.input_dim[0] = 112;
  layer.input_dim[1] = 112;
  layer.input_dim[2] = 32;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 112;
  layer.output_dim[1] = 112;
  layer.output_dim[2] = 32;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_1

//Layer_2: Convolution Layer
//  ->: conv_pw_1
//  ->: conv_pw_1_bn
//  ->: conv_pw_1_bn
//  ->: conv_pw_1_relu
void CKerasMobileNet::Layer_2() {
  struct top_conv_conf& _conf = get_conv_layer(2);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 112; // Input Width
  _conf.hw.input.h = 112; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 32; // Input Channels
  _conf.hw.input.input_base_addr = 0x0010D800; // Input byte address
  _conf.hw.input.tiles = 2; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 112; // Output Width
  _conf.sw.output.h = 112; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 64; // Output Channels
  _conf.hw.output.output_base_addr = 0x001D1800; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv_pw_1
  //->: conv_pw_1_bn
  //->: conv_pw_1_bn
  //->: conv_pw_1_relu
  _conf.sw.run[0].in_w = 112; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 112; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 32; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 112; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 112; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 64; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x00001680; // Filter Weight and Bias byte address
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
  layer.addr_offset_input = 0x0010D800;
  layer.addr_offset_output = 0x001D1800;
  layer.output_size = 1605632;
  layer.input_dim[0] = 112;
  layer.input_dim[1] = 112;
  layer.input_dim[2] = 32;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 112;
  layer.output_dim[1] = 112;
  layer.output_dim[2] = 64;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_2

//Layer_3: Convolution Layer
//  ->: conv_dw_2
//  ->: conv_dw_2_bn
//  ->: conv_dw_2_bn
//  ->: conv_dw_2_relu
void CKerasMobileNet::Layer_3() {
  struct top_conv_conf& _conf = get_conv_layer(3);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 112; // Input Width
  _conf.hw.input.h = 112; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 64; // Input Channels
  _conf.hw.input.input_base_addr = 0x001D1800; // Input byte address
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
  //->: conv_dw_2
  //->: conv_dw_2_bn
  //->: conv_dw_2_bn
  //->: conv_dw_2_relu
  _conf.sw.run[0].in_w = 112; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 112; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 64; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 56; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 56; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 64; // Output Channels
  _conf.hw.run[0].conv_enable = 3; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 3; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x00002B00; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 5248; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[0].conv_pad = 0x1000100; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].conv_stride = 0x202; // bits [7:0] = X stride, bits [15:8] = Y stride
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
  layer.addr_offset_input = 0x001D1800;
  layer.addr_offset_output = 0x00000000;
  layer.output_size = 401408;
  layer.input_dim[0] = 112;
  layer.input_dim[1] = 112;
  layer.input_dim[2] = 64;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 56;
  layer.output_dim[1] = 56;
  layer.output_dim[2] = 64;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_3

//Layer_4: Convolution Layer
//  ->: conv_pw_2
//  ->: conv_pw_2_bn
//  ->: conv_pw_2_bn
//  ->: conv_pw_2_relu
void CKerasMobileNet::Layer_4() {
  struct top_conv_conf& _conf = get_conv_layer(4);
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
  _conf.sw.output.m = 128; // Output Channels
  _conf.hw.output.output_base_addr = 0x00062000; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv_pw_2
  //->: conv_pw_2_bn
  //->: conv_pw_2_bn
  //->: conv_pw_2_relu
  _conf.sw.run[0].in_w = 56; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 56; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 64; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 56; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 56; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 128; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x00003F80; // Filter Weight and Bias byte address
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

  struct fpga_layer& layer = layers[4];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00000000;
  layer.addr_offset_output = 0x00062000;
  layer.output_size = 802816;
  layer.input_dim[0] = 56;
  layer.input_dim[1] = 56;
  layer.input_dim[2] = 64;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 56;
  layer.output_dim[1] = 56;
  layer.output_dim[2] = 128;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_4

//Layer_5: Convolution Layer
//  ->: conv_dw_3
//  ->: conv_dw_3_bn
//  ->: conv_dw_3_bn
//  ->: conv_dw_3_relu
void CKerasMobileNet::Layer_5() {
  struct top_conv_conf& _conf = get_conv_layer(5);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 56; // Input Width
  _conf.hw.input.h = 56; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 128; // Input Channels
  _conf.hw.input.input_base_addr = 0x00062000; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 56; // Output Width
  _conf.sw.output.h = 56; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 128; // Output Channels
  _conf.hw.output.output_base_addr = 0x00126000; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv_dw_3
  //->: conv_dw_3_bn
  //->: conv_dw_3_bn
  //->: conv_dw_3_relu
  _conf.sw.run[0].in_w = 56; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 56; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 128; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 56; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 56; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 128; // Output Channels
  _conf.hw.run[0].conv_enable = 3; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 3; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x00006680; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 9984; // Actual size in bytes of LUT, weights and bias (in bytes)
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

  struct fpga_layer& layer = layers[5];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00062000;
  layer.addr_offset_output = 0x00126000;
  layer.output_size = 802816;
  layer.input_dim[0] = 56;
  layer.input_dim[1] = 56;
  layer.input_dim[2] = 128;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 56;
  layer.output_dim[1] = 56;
  layer.output_dim[2] = 128;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_5

//Layer_6: Convolution Layer
//  ->: conv_pw_3
//  ->: conv_pw_3_bn
//  ->: conv_pw_3_bn
//  ->: conv_pw_3_relu
void CKerasMobileNet::Layer_6() {
  struct top_conv_conf& _conf = get_conv_layer(6);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 56; // Input Width
  _conf.hw.input.h = 56; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 128; // Input Channels
  _conf.hw.input.input_base_addr = 0x00126000; // Input byte address
  _conf.hw.input.tiles = 2; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 56; // Output Width
  _conf.sw.output.h = 56; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 128; // Output Channels
  _conf.hw.output.output_base_addr = 0x00000000; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv_pw_3
  //->: conv_pw_3_bn
  //->: conv_pw_3_bn
  //->: conv_pw_3_relu
  _conf.sw.run[0].in_w = 56; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 56; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 128; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 56; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 56; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 128; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x00008D80; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 19200; // Actual size in bytes of LUT, weights and bias (in bytes)
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

  struct fpga_layer& layer = layers[6];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00126000;
  layer.addr_offset_output = 0x00000000;
  layer.output_size = 802816;
  layer.input_dim[0] = 56;
  layer.input_dim[1] = 56;
  layer.input_dim[2] = 128;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 56;
  layer.output_dim[1] = 56;
  layer.output_dim[2] = 128;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_6

//Layer_7: Convolution Layer
//  ->: conv_dw_4
//  ->: conv_dw_4_bn
//  ->: conv_dw_4_bn
//  ->: conv_dw_4_relu
void CKerasMobileNet::Layer_7() {
  struct top_conv_conf& _conf = get_conv_layer(7);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 56; // Input Width
  _conf.hw.input.h = 56; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 128; // Input Channels
  _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 28; // Output Width
  _conf.sw.output.h = 28; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 128; // Output Channels
  _conf.hw.output.output_base_addr = 0x000C4000; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv_dw_4
  //->: conv_dw_4_bn
  //->: conv_dw_4_bn
  //->: conv_dw_4_relu
  _conf.sw.run[0].in_w = 56; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 56; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 128; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 28; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 28; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 128; // Output Channels
  _conf.hw.run[0].conv_enable = 3; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 3; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x0000D880; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 9984; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[0].conv_pad = 0x1000100; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].conv_stride = 0x202; // bits [7:0] = X stride, bits [15:8] = Y stride
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
  layer.addr_offset_output = 0x000C4000;
  layer.output_size = 200704;
  layer.input_dim[0] = 56;
  layer.input_dim[1] = 56;
  layer.input_dim[2] = 128;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 28;
  layer.output_dim[1] = 28;
  layer.output_dim[2] = 128;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_7

//Layer_8: Convolution Layer
//  ->: conv_pw_4
//  ->: conv_pw_4_bn
//  ->: conv_pw_4_bn
//  ->: conv_pw_4_relu
void CKerasMobileNet::Layer_8() {
  struct top_conv_conf& _conf = get_conv_layer(8);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 28; // Input Width
  _conf.hw.input.h = 28; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 128; // Input Channels
  _conf.hw.input.input_base_addr = 0x000C4000; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 28; // Output Width
  _conf.sw.output.h = 28; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 256; // Output Channels
  _conf.hw.output.output_base_addr = 0x00000000; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv_pw_4
  //->: conv_pw_4_bn
  //->: conv_pw_4_bn
  //->: conv_pw_4_relu
  _conf.sw.run[0].in_w = 28; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 28; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 128; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 28; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 28; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 256; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x0000FF80; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 37888; // Actual size in bytes of LUT, weights and bias (in bytes)
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

  struct fpga_layer& layer = layers[8];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x000C4000;
  layer.addr_offset_output = 0x00000000;
  layer.output_size = 401408;
  layer.input_dim[0] = 28;
  layer.input_dim[1] = 28;
  layer.input_dim[2] = 128;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 28;
  layer.output_dim[1] = 28;
  layer.output_dim[2] = 256;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_8

//Layer_9: Convolution Layer
//  ->: conv_dw_5
//  ->: conv_dw_5_bn
//  ->: conv_dw_5_bn
//  ->: conv_dw_5_relu
void CKerasMobileNet::Layer_9() {
  struct top_conv_conf& _conf = get_conv_layer(9);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 28; // Input Width
  _conf.hw.input.h = 28; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 256; // Input Channels
  _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 28; // Output Width
  _conf.sw.output.h = 28; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 256; // Output Channels
  _conf.hw.output.output_base_addr = 0x00062000; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv_dw_5
  //->: conv_dw_5_bn
  //->: conv_dw_5_bn
  //->: conv_dw_5_relu
  _conf.sw.run[0].in_w = 28; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 28; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 256; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 28; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 28; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 256; // Output Channels
  _conf.hw.run[0].conv_enable = 3; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 3; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x00019380; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 19456; // Actual size in bytes of LUT, weights and bias (in bytes)
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

  struct fpga_layer& layer = layers[9];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00000000;
  layer.addr_offset_output = 0x00062000;
  layer.output_size = 401408;
  layer.input_dim[0] = 28;
  layer.input_dim[1] = 28;
  layer.input_dim[2] = 256;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 28;
  layer.output_dim[1] = 28;
  layer.output_dim[2] = 256;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_9

//Layer_10: Convolution Layer
//  ->: conv_pw_5
//  ->: conv_pw_5_bn
//  ->: conv_pw_5_bn
//  ->: conv_pw_5_relu
void CKerasMobileNet::Layer_10() {
  struct top_conv_conf& _conf = get_conv_layer(10);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 28; // Input Width
  _conf.hw.input.h = 28; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 256; // Input Channels
  _conf.hw.input.input_base_addr = 0x00062000; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 28; // Output Width
  _conf.sw.output.h = 28; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 256; // Output Channels
  _conf.hw.output.output_base_addr = 0x00000000; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv_pw_5
  //->: conv_pw_5_bn
  //->: conv_pw_5_bn
  //->: conv_pw_5_relu
  _conf.sw.run[0].in_w = 28; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 28; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 256; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 28; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 28; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 256; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x0001DF80; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 74752; // Actual size in bytes of LUT, weights and bias (in bytes)
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

  struct fpga_layer& layer = layers[10];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00062000;
  layer.addr_offset_output = 0x00000000;
  layer.output_size = 401408;
  layer.input_dim[0] = 28;
  layer.input_dim[1] = 28;
  layer.input_dim[2] = 256;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 28;
  layer.output_dim[1] = 28;
  layer.output_dim[2] = 256;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_10

//Layer_11: Convolution Layer
//  ->: conv_dw_6
//  ->: conv_dw_6_bn
//  ->: conv_dw_6_bn
//  ->: conv_dw_6_relu
void CKerasMobileNet::Layer_11() {
  struct top_conv_conf& _conf = get_conv_layer(11);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 28; // Input Width
  _conf.hw.input.h = 28; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 256; // Input Channels
  _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 14; // Output Width
  _conf.sw.output.h = 14; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 256; // Output Channels
  _conf.hw.output.output_base_addr = 0x00062000; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv_dw_6
  //->: conv_dw_6_bn
  //->: conv_dw_6_bn
  //->: conv_dw_6_relu
  _conf.sw.run[0].in_w = 28; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 28; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 256; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 256; // Output Channels
  _conf.hw.run[0].conv_enable = 3; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 3; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x00030380; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 19456; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[0].conv_pad = 0x1000100; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].conv_stride = 0x202; // bits [7:0] = X stride, bits [15:8] = Y stride
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
  layer.addr_offset_input = 0x00000000;
  layer.addr_offset_output = 0x00062000;
  layer.output_size = 100352;
  layer.input_dim[0] = 28;
  layer.input_dim[1] = 28;
  layer.input_dim[2] = 256;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 14;
  layer.output_dim[1] = 14;
  layer.output_dim[2] = 256;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_11

//Layer_12: Convolution Layer
//  ->: conv_pw_6
//  ->: conv_pw_6_bn
//  ->: conv_pw_6_bn
//  ->: conv_pw_6_relu
void CKerasMobileNet::Layer_12() {
  struct top_conv_conf& _conf = get_conv_layer(12);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 14; // Input Width
  _conf.hw.input.h = 14; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 256; // Input Channels
  _conf.hw.input.input_base_addr = 0x00062000; // Input byte address
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
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv_pw_6
  //->: conv_pw_6_bn
  //->: conv_pw_6_bn
  //->: conv_pw_6_relu
  _conf.sw.run[0].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 256; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 512; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x00034F80; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 148992; // Actual size in bytes of LUT, weights and bias (in bytes)
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

  struct fpga_layer& layer = layers[12];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00062000;
  layer.addr_offset_output = 0x00000000;
  layer.output_size = 200704;
  layer.input_dim[0] = 14;
  layer.input_dim[1] = 14;
  layer.input_dim[2] = 256;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 14;
  layer.output_dim[1] = 14;
  layer.output_dim[2] = 512;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_12

//Layer_13: Convolution Layer
//  ->: conv_dw_7
//  ->: conv_dw_7_bn
//  ->: conv_dw_7_bn
//  ->: conv_dw_7_relu
void CKerasMobileNet::Layer_13() {
  struct top_conv_conf& _conf = get_conv_layer(13);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

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
  _conf.sw.output.m = 512; // Output Channels
  _conf.hw.output.output_base_addr = 0x00031000; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv_dw_7
  //->: conv_dw_7_bn
  //->: conv_dw_7_bn
  //->: conv_dw_7_relu
  _conf.sw.run[0].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 512; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 512; // Output Channels
  _conf.hw.run[0].conv_enable = 3; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 3; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x00059580; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 38400; // Actual size in bytes of LUT, weights and bias (in bytes)
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

  struct fpga_layer& layer = layers[13];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00000000;
  layer.addr_offset_output = 0x00031000;
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
}//end of  Layer_13

//Layer_14: Convolution Layer
//  ->: conv_pw_7
//  ->: conv_pw_7_bn
//  ->: conv_pw_7_bn
//  ->: conv_pw_7_relu
void CKerasMobileNet::Layer_14() {
  struct top_conv_conf& _conf = get_conv_layer(14);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 14; // Input Width
  _conf.hw.input.h = 14; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 512; // Input Channels
  _conf.hw.input.input_base_addr = 0x00031000; // Input byte address
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
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv_pw_7
  //->: conv_pw_7_bn
  //->: conv_pw_7_bn
  //->: conv_pw_7_relu
  _conf.sw.run[0].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 512; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 512; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x00062B80; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 296448; // Actual size in bytes of LUT, weights and bias (in bytes)
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

  struct fpga_layer& layer = layers[14];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00031000;
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
}//end of  Layer_14

//Layer_15: Convolution Layer
//  ->: conv_dw_8
//  ->: conv_dw_8_bn
//  ->: conv_dw_8_bn
//  ->: conv_dw_8_relu
void CKerasMobileNet::Layer_15() {
  struct top_conv_conf& _conf = get_conv_layer(15);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

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
  _conf.sw.output.m = 512; // Output Channels
  _conf.hw.output.output_base_addr = 0x00031000; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv_dw_8
  //->: conv_dw_8_bn
  //->: conv_dw_8_bn
  //->: conv_dw_8_relu
  _conf.sw.run[0].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 512; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 512; // Output Channels
  _conf.hw.run[0].conv_enable = 3; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 3; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x000AB180; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 38400; // Actual size in bytes of LUT, weights and bias (in bytes)
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

  struct fpga_layer& layer = layers[15];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00000000;
  layer.addr_offset_output = 0x00031000;
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
}//end of  Layer_15

//Layer_16: Convolution Layer
//  ->: conv_pw_8
//  ->: conv_pw_8_bn
//  ->: conv_pw_8_bn
//  ->: conv_pw_8_relu
void CKerasMobileNet::Layer_16() {
  struct top_conv_conf& _conf = get_conv_layer(16);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 14; // Input Width
  _conf.hw.input.h = 14; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 512; // Input Channels
  _conf.hw.input.input_base_addr = 0x00031000; // Input byte address
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
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv_pw_8
  //->: conv_pw_8_bn
  //->: conv_pw_8_bn
  //->: conv_pw_8_relu
  _conf.sw.run[0].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 512; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 512; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x000B4780; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 296448; // Actual size in bytes of LUT, weights and bias (in bytes)
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

  struct fpga_layer& layer = layers[16];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00031000;
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
}//end of  Layer_16

//Layer_17: Convolution Layer
//  ->: conv_dw_9
//  ->: conv_dw_9_bn
//  ->: conv_dw_9_bn
//  ->: conv_dw_9_relu
void CKerasMobileNet::Layer_17() {
  struct top_conv_conf& _conf = get_conv_layer(17);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

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
  _conf.sw.output.m = 512; // Output Channels
  _conf.hw.output.output_base_addr = 0x00031000; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv_dw_9
  //->: conv_dw_9_bn
  //->: conv_dw_9_bn
  //->: conv_dw_9_relu
  _conf.sw.run[0].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 512; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 512; // Output Channels
  _conf.hw.run[0].conv_enable = 3; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 3; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x000FCD80; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 38400; // Actual size in bytes of LUT, weights and bias (in bytes)
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
  layer.addr_offset_output = 0x00031000;
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
}//end of  Layer_17

//Layer_18: Convolution Layer
//  ->: conv_pw_9
//  ->: conv_pw_9_bn
//  ->: conv_pw_9_bn
//  ->: conv_pw_9_relu
void CKerasMobileNet::Layer_18() {
  struct top_conv_conf& _conf = get_conv_layer(18);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 14; // Input Width
  _conf.hw.input.h = 14; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 512; // Input Channels
  _conf.hw.input.input_base_addr = 0x00031000; // Input byte address
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
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv_pw_9
  //->: conv_pw_9_bn
  //->: conv_pw_9_bn
  //->: conv_pw_9_relu
  _conf.sw.run[0].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 512; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 512; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x00106380; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 296448; // Actual size in bytes of LUT, weights and bias (in bytes)
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

  struct fpga_layer& layer = layers[18];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00031000;
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
}//end of  Layer_18

//Layer_19: Convolution Layer
//  ->: conv_dw_10
//  ->: conv_dw_10_bn
//  ->: conv_dw_10_bn
//  ->: conv_dw_10_relu
void CKerasMobileNet::Layer_19() {
  struct top_conv_conf& _conf = get_conv_layer(19);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

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
  _conf.sw.output.m = 512; // Output Channels
  _conf.hw.output.output_base_addr = 0x00031000; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv_dw_10
  //->: conv_dw_10_bn
  //->: conv_dw_10_bn
  //->: conv_dw_10_relu
  _conf.sw.run[0].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 512; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 512; // Output Channels
  _conf.hw.run[0].conv_enable = 3; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 3; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x0014E980; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 38400; // Actual size in bytes of LUT, weights and bias (in bytes)
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

  struct fpga_layer& layer = layers[19];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00000000;
  layer.addr_offset_output = 0x00031000;
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
}//end of  Layer_19

//Layer_20: Convolution Layer
//  ->: conv_pw_10
//  ->: conv_pw_10_bn
//  ->: conv_pw_10_bn
//  ->: conv_pw_10_relu
void CKerasMobileNet::Layer_20() {
  struct top_conv_conf& _conf = get_conv_layer(20);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 14; // Input Width
  _conf.hw.input.h = 14; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 512; // Input Channels
  _conf.hw.input.input_base_addr = 0x00031000; // Input byte address
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
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv_pw_10
  //->: conv_pw_10_bn
  //->: conv_pw_10_bn
  //->: conv_pw_10_relu
  _conf.sw.run[0].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 512; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 512; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x00157F80; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 296448; // Actual size in bytes of LUT, weights and bias (in bytes)
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

  struct fpga_layer& layer = layers[20];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00031000;
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
}//end of  Layer_20

//Layer_21: Convolution Layer
//  ->: conv_dw_11
//  ->: conv_dw_11_bn
//  ->: conv_dw_11_bn
//  ->: conv_dw_11_relu
void CKerasMobileNet::Layer_21() {
  struct top_conv_conf& _conf = get_conv_layer(21);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

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
  _conf.sw.output.m = 512; // Output Channels
  _conf.hw.output.output_base_addr = 0x00031000; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv_dw_11
  //->: conv_dw_11_bn
  //->: conv_dw_11_bn
  //->: conv_dw_11_relu
  _conf.sw.run[0].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 512; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 512; // Output Channels
  _conf.hw.run[0].conv_enable = 3; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 3; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x001A0580; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 38400; // Actual size in bytes of LUT, weights and bias (in bytes)
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

  struct fpga_layer& layer = layers[21];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00000000;
  layer.addr_offset_output = 0x00031000;
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
}//end of  Layer_21

//Layer_22: Convolution Layer
//  ->: conv_pw_11
//  ->: conv_pw_11_bn
//  ->: conv_pw_11_bn
//  ->: conv_pw_11_relu
void CKerasMobileNet::Layer_22() {
  struct top_conv_conf& _conf = get_conv_layer(22);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 14; // Input Width
  _conf.hw.input.h = 14; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 512; // Input Channels
  _conf.hw.input.input_base_addr = 0x00031000; // Input byte address
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
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv_pw_11
  //->: conv_pw_11_bn
  //->: conv_pw_11_bn
  //->: conv_pw_11_relu
  _conf.sw.run[0].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 512; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 512; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x001A9B80; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 296448; // Actual size in bytes of LUT, weights and bias (in bytes)
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

  struct fpga_layer& layer = layers[22];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00031000;
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
}//end of  Layer_22

//Layer_23: Convolution Layer
//  ->: conv_dw_12
//  ->: conv_dw_12_bn
//  ->: conv_dw_12_bn
//  ->: conv_dw_12_relu
void CKerasMobileNet::Layer_23() {
  struct top_conv_conf& _conf = get_conv_layer(23);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 14; // Input Width
  _conf.hw.input.h = 14; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 512; // Input Channels
  _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 7; // Output Width
  _conf.sw.output.h = 7; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 512; // Output Channels
  _conf.hw.output.output_base_addr = 0x00031000; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv_dw_12
  //->: conv_dw_12_bn
  //->: conv_dw_12_bn
  //->: conv_dw_12_relu
  _conf.sw.run[0].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 512; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 7; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 7; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 512; // Output Channels
  _conf.hw.run[0].conv_enable = 3; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 3; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x001F2180; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 38400; // Actual size in bytes of LUT, weights and bias (in bytes)
  _conf.hw.run[0].conv_pad = 0x1000100; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
  _conf.hw.run[0].conv_stride = 0x202; // bits [7:0] = X stride, bits [15:8] = Y stride
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

  struct fpga_layer& layer = layers[23];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00000000;
  layer.addr_offset_output = 0x00031000;
  layer.output_size = 50176;
  layer.input_dim[0] = 14;
  layer.input_dim[1] = 14;
  layer.input_dim[2] = 512;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 7;
  layer.output_dim[1] = 7;
  layer.output_dim[2] = 512;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_23

//Layer_24: Convolution Layer
//  ->: conv_pw_12
//  ->: conv_pw_12_bn
//  ->: conv_pw_12_bn
//  ->: conv_pw_12_relu
void CKerasMobileNet::Layer_24() {
  struct top_conv_conf& _conf = get_conv_layer(24);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 7; // Input Width
  _conf.hw.input.h = 7; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 512; // Input Channels
  _conf.hw.input.input_base_addr = 0x00031000; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 7; // Output Width
  _conf.sw.output.h = 7; // Output Height
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
  //->: conv_pw_12
  //->: conv_pw_12_bn
  //->: conv_pw_12_bn
  //->: conv_pw_12_relu
  _conf.sw.run[0].in_w = 7; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 7; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 512; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 7; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 7; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 1024; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x001FB780; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 592384; // Actual size in bytes of LUT, weights and bias (in bytes)
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

  struct fpga_layer& layer = layers[24];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00031000;
  layer.addr_offset_output = 0x00000000;
  layer.output_size = 100352;
  layer.input_dim[0] = 7;
  layer.input_dim[1] = 7;
  layer.input_dim[2] = 512;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 7;
  layer.output_dim[1] = 7;
  layer.output_dim[2] = 1024;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_24

//Layer_25: Convolution Layer
//  ->: conv_dw_13
//  ->: conv_dw_13_bn
//  ->: conv_dw_13_bn
//  ->: conv_dw_13_relu
void CKerasMobileNet::Layer_25() {
  struct top_conv_conf& _conf = get_conv_layer(25);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 7; // Input Width
  _conf.hw.input.h = 7; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 1024; // Input Channels
  _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 7; // Output Width
  _conf.sw.output.h = 7; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 1024; // Output Channels
  _conf.hw.output.output_base_addr = 0x00018800; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: conv_dw_13
  //->: conv_dw_13_bn
  //->: conv_dw_13_bn
  //->: conv_dw_13_relu
  _conf.sw.run[0].in_w = 7; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 7; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 1024; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 7; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 7; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 1024; // Output Channels
  _conf.hw.run[0].conv_enable = 3; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 3; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x0028C180; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 76288; // Actual size in bytes of LUT, weights and bias (in bytes)
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

  struct fpga_layer& layer = layers[25];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00000000;
  layer.addr_offset_output = 0x00018800;
  layer.output_size = 100352;
  layer.input_dim[0] = 7;
  layer.input_dim[1] = 7;
  layer.input_dim[2] = 1024;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 7;
  layer.output_dim[1] = 7;
  layer.output_dim[2] = 1024;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_25

//Layer_26: Convolution Layer
//  ->: conv_pw_13
//  ->: conv_pw_13_bn
//  ->: conv_pw_13_bn
//  ->: conv_pw_13_relu
void CKerasMobileNet::Layer_26() {
  struct top_conv_conf& _conf = get_conv_layer(26);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 7; // Input Width
  _conf.hw.input.h = 7; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 1024; // Input Channels
  _conf.hw.input.input_base_addr = 0x00018800; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 7; // Output Width
  _conf.sw.output.h = 7; // Output Height
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
  //->: conv_pw_13
  //->: conv_pw_13_bn
  //->: conv_pw_13_bn
  //->: conv_pw_13_relu
  _conf.sw.run[0].in_w = 7; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 7; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 1024; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 7; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 7; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 1024; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x0029EB80; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 1182208; // Actual size in bytes of LUT, weights and bias (in bytes)
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

  struct fpga_layer& layer = layers[26];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00018800;
  layer.addr_offset_output = 0x00000000;
  layer.output_size = 100352;
  layer.input_dim[0] = 7;
  layer.input_dim[1] = 7;
  layer.input_dim[2] = 1024;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 7;
  layer.output_dim[1] = 7;
  layer.output_dim[2] = 1024;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_26

//Layer_27: Convolution Layer
//  ->: global_average_pooling2d_1
void CKerasMobileNet::Layer_27() {
  struct top_conv_conf& _conf = get_conv_layer(27);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 7; // Input Width
  _conf.hw.input.h = 7; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 1024; // Input Channels
  _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 1; // Output Width
  _conf.sw.output.h = 1; // Output Height
  _conf.sw.output.z = 1; // Output Depth
  _conf.sw.output.m = 1024; // Output Channels
  _conf.hw.output.output_base_addr = 0x00018800; // Output byte address
  _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
  _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

  //Runs Configuration:
  //->1 run(s)
  //--------------------------------------------------
  //RUN : 0
  //--------------------------------------------------
  //->: global_average_pooling2d_1
  _conf.sw.run[0].in_w = 7; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 7; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 1024; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 1; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 1; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 1024; // Output Channels
  _conf.hw.run[0].conv_enable = 0; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x003BF580; // Filter Weight and Bias byte address
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

  struct fpga_layer& layer = layers[27];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00000000;
  layer.addr_offset_output = 0x00018800;
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
}//end of  Layer_27

//Layer_28: Convolution Layer
//  ->: conv_preds
void CKerasMobileNet::Layer_28() {
  struct top_conv_conf& _conf = get_conv_layer(28);
  //Topo: 00000000000000000000000000000001
  _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

  //Input Configuration:
  _conf.hw.input.w = 1; // Input Width
  _conf.hw.input.h = 1; // Input Height
  _conf.hw.input.z = 1; // Input Depth
  _conf.hw.input.c = 1024; // Input Channels
  _conf.hw.input.input_base_addr = 0x00018800; // Input byte address
  _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

  //Output Configuration:
  _conf.sw.output.w = 1; // Output Width
  _conf.sw.output.h = 1; // Output Height
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
  //->: conv_preds
  _conf.sw.run[0].in_w = 1; // Optional: Input width (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_h = 1; // Optional: Input height (not used by HW - discovered on the fly)
  _conf.sw.run[0].in_c = 1024; // Optional: Input Channels (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_w = 1; // Optional: Output width (not used by HW - discovered on the fly)
  _conf.sw.run[0].out_h = 1; // Optional: Output height (not used by HW - discovered on the fly)
  _conf.hw.run[0].m = 1000; // Output Channels
  _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
  _conf.hw.run[0].p = 1; // Filter Width and Height
  _conf.hw.run[0].pz = 1; // Filter Depth
  _conf.hw.run[0].weight_base_addr = 0x003BF580; // Filter Weight and Bias byte address
  _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
  _conf.sw.run[0].weight_size = 1154512; // Actual size in bytes of LUT, weights and bias (in bytes)
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
  _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
  _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

  struct fpga_layer& layer = layers[28];
  layer.type = LT_CONV;
  layer.hw_conf = (void*)&_conf;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00018800;
  layer.addr_offset_output = 0x00000000;
  layer.output_size = 2000;
  layer.input_dim[0] = 1;
  layer.input_dim[1] = 1;
  layer.input_dim[2] = 1024;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 1;
  layer.output_dim[1] = 1;
  layer.output_dim[2] = 1000;
  layer.output_dim_size = 3;
  layer.is_output = false;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
}//end of  Layer_28

//Layer_29: SoftMax Layer
//	->: act_softmax
void CKerasMobileNet::Layer_29() {
  struct fpga_layer& layer = layers[29];
  layer.type = LT_SOFTMAX;
  layer.hw_conf = (void*)0;
  layer.addr_cpu_input = 0x0;
  layer.addr_cpu_output = 0x0;
  layer.addr_offset_input = 0x00000000;
  layer.addr_offset_output = 0x000007D0;
  layer.output_size = 2000;
  layer.input_dim[0] = 1;
  layer.input_dim[1] = 1;
  layer.input_dim[2] = 1000;
  layer.input_dim_size = 3;
  layer.output_dim[0] = 1000;
  layer.output_dim_size = 1;
  layer.is_output = true;
  layer.is_f32_output = false;
  layer.is_input_hw_layout = true;
  layer.softmax_axis = 2;
  output_layers[0] = &layer;
}//end of  Layer_29

