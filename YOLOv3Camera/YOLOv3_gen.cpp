/*
*------------------------------------------------------------
* Copyright(c) 2017 by Digital Media Professionals Inc.
* All rights reserved.
*------------------------------------------------------------
* This source code was generated using DMP-DV700 tools
* Digital Media Professionals Inc.
*------------------------------------------------------------
*/

#include "YOLOv3_gen.h"



CYOLOv3::CYOLOv3()
{

}

CYOLOv3::~CYOLOv3()
{

}

unsigned int CYOLOv3::get_total_layer_count()
{
    return num_layers;
}

unsigned int CYOLOv3::get_output_layer_count()
{
    return num_output_layers;
}

unsigned int CYOLOv3::get_convolution_layer_count()
{
    return num_conv_layers;
}

unsigned int CYOLOv3::get_innerproduct_layer_count()
{
    return num_fc_layers;
}

int CYOLOv3::initialize()
{
    num_layers = 21;
    num_output_layers = 1;
    num_conv_layers = 17;
    num_fc_layers = 0;
    weight_size = 17822496;
    buffer_size = 3768320;
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
//  ->: conv2d_1
//  ->: batch_normalization_1
//  ->: batch_normalization_1
//  ->: leaky_re_lu_1
void CYOLOv3::Layer_0()
{
    struct top_conv_conf& _conf = get_conv_layer(0);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 320; // Input Width
    _conf.hw.input.h = 256; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 3; // Input Channels
    _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
    _conf.hw.input.tiles = 3; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 320; // Output Width
    _conf.sw.output.h = 256; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 16; // Output Channels
    _conf.hw.output.output_base_addr = 0x00078000; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: conv2d_1
    //->: batch_normalization_1
    //->: batch_normalization_1
    //->: leaky_re_lu_1
    _conf.sw.run[0].in_w = 320; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 256; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 3; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 320; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 256; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 16; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 3; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x00000000; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 1; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 2336; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[0].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[0].pool_stride =0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
    _conf.hw.run[0].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
    _conf.hw.run[0].actfunc_param = 0x2E66; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
    _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
    _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
    _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

    struct fpga_layer& layer = layers[0];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x00000000;
    layer.addr_offset_output = 0x00078000;
    layer.output_size = 2621440;
    layer.input_dim[0] = 320;
    layer.input_dim[1] = 256;
    layer.input_dim[2] = 3;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 320;
    layer.output_dim[1] = 256;
    layer.output_dim[2] = 16;
    layer.output_dim_size = 3;
    layer.is_output = false;
    layer.is_f32_output = false;
    layer.is_input_hw_layout = false;
}//end of  Layer_0

//Layer_1: Convolution Layer
//  ->: max_pooling2d_1
void CYOLOv3::Layer_1()
{
    struct top_conv_conf& _conf = get_conv_layer(1);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 320; // Input Width
    _conf.hw.input.h = 256; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 16; // Input Channels
    _conf.hw.input.input_base_addr = 0x00078000; // Input byte address
    _conf.hw.input.tiles = 2; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 160; // Output Width
    _conf.sw.output.h = 128; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 16; // Output Channels
    _conf.hw.output.output_base_addr = 0x002F8000; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: max_pooling2d_1
    _conf.sw.run[0].in_w = 320; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 256; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 16; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 160; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 128; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 16; // Output Channels
    _conf.hw.run[0].conv_enable = 0; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 1; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x00000920; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 0; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 0; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[0].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[0].pool_size = 0x202; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[0].pool_stride =0x202; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
    _conf.hw.run[0].actfunc = 0; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
    _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
    _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
    _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
    _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

    struct fpga_layer& layer = layers[1];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x00078000;
    layer.addr_offset_output = 0x002F8000;
    layer.output_size = 655360;
    layer.input_dim[0] = 320;
    layer.input_dim[1] = 256;
    layer.input_dim[2] = 16;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 160;
    layer.output_dim[1] = 128;
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
void CYOLOv3::Layer_2()
{
    struct top_conv_conf& _conf = get_conv_layer(2);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 160; // Input Width
    _conf.hw.input.h = 128; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 16; // Input Channels
    _conf.hw.input.input_base_addr = 0x002F8000; // Input byte address
    _conf.hw.input.tiles = 2; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 160; // Output Width
    _conf.sw.output.h = 128; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 32; // Output Channels
    _conf.hw.output.output_base_addr = 0x00000000; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: conv2d_2
    //->: batch_normalization_2
    //->: batch_normalization_2
    //->: leaky_re_lu_2
    _conf.sw.run[0].in_w = 160; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 128; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 16; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 160; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 128; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 32; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 3; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x00000920; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 1; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 9280; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[0].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[0].pool_stride =0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
    _conf.hw.run[0].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
    _conf.hw.run[0].actfunc_param = 0x2E66; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
    _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
    _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
    _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

    struct fpga_layer& layer = layers[2];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x002F8000;
    layer.addr_offset_output = 0x00000000;
    layer.output_size = 1310720;
    layer.input_dim[0] = 160;
    layer.input_dim[1] = 128;
    layer.input_dim[2] = 16;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 160;
    layer.output_dim[1] = 128;
    layer.output_dim[2] = 32;
    layer.output_dim_size = 3;
    layer.is_output = false;
    layer.is_f32_output = false;
    layer.is_input_hw_layout = true;
}//end of  Layer_2

//Layer_3: Convolution Layer
//  ->: max_pooling2d_2
void CYOLOv3::Layer_3()
{
    struct top_conv_conf& _conf = get_conv_layer(3);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 160; // Input Width
    _conf.hw.input.h = 128; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 32; // Input Channels
    _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 80; // Output Width
    _conf.sw.output.h = 64; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 32; // Output Channels
    _conf.hw.output.output_base_addr = 0x00140000; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: max_pooling2d_2
    _conf.sw.run[0].in_w = 160; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 128; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 32; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 80; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 64; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 32; // Output Channels
    _conf.hw.run[0].conv_enable = 0; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 1; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x00002D60; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 0; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 0; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[0].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[0].pool_size = 0x202; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[0].pool_stride =0x202; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
    _conf.hw.run[0].actfunc = 0; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
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
    layer.addr_offset_output = 0x00140000;
    layer.output_size = 327680;
    layer.input_dim[0] = 160;
    layer.input_dim[1] = 128;
    layer.input_dim[2] = 32;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 80;
    layer.output_dim[1] = 64;
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
//  ->: max_pooling2d_3
void CYOLOv3::Layer_4()
{
    struct top_conv_conf& _conf = get_conv_layer(4);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 80; // Input Width
    _conf.hw.input.h = 64; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 32; // Input Channels
    _conf.hw.input.input_base_addr = 0x00140000; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 40; // Output Width
    _conf.sw.output.h = 32; // Output Height
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
    //->: conv2d_3
    //->: batch_normalization_3
    //->: batch_normalization_3
    //->: leaky_re_lu_3
    //->: max_pooling2d_3
    _conf.sw.run[0].in_w = 80; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 64; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 32; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 40; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 32; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 64; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 3; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x00002D60; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 1; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 36992; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[0].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[0].pool_size = 0x202; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[0].pool_stride =0x202; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
    _conf.hw.run[0].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
    _conf.hw.run[0].actfunc_param = 0x2E66; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
    _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
    _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
    _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

    struct fpga_layer& layer = layers[4];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x00140000;
    layer.addr_offset_output = 0x00000000;
    layer.output_size = 163840;
    layer.input_dim[0] = 80;
    layer.input_dim[1] = 64;
    layer.input_dim[2] = 32;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 40;
    layer.output_dim[1] = 32;
    layer.output_dim[2] = 64;
    layer.output_dim_size = 3;
    layer.is_output = false;
    layer.is_f32_output = false;
    layer.is_input_hw_layout = true;
}//end of  Layer_4

//Layer_5: Convolution Layer
//  ->: conv2d_4
//  ->: batch_normalization_4
//  ->: batch_normalization_4
//  ->: leaky_re_lu_4
//  ->: max_pooling2d_4
void CYOLOv3::Layer_5()
{
    struct top_conv_conf& _conf = get_conv_layer(5);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 40; // Input Width
    _conf.hw.input.h = 32; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 64; // Input Channels
    _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 20; // Output Width
    _conf.sw.output.h = 16; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 128; // Output Channels
    _conf.hw.output.output_base_addr = 0x00028000; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: conv2d_4
    //->: batch_normalization_4
    //->: batch_normalization_4
    //->: leaky_re_lu_4
    //->: max_pooling2d_4
    _conf.sw.run[0].in_w = 40; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 32; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 64; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 20; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 16; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 128; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 3; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x0000BDE0; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 1; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 147712; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[0].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[0].pool_size = 0x202; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[0].pool_stride =0x202; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
    _conf.hw.run[0].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
    _conf.hw.run[0].actfunc_param = 0x2E66; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
    _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
    _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
    _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

    struct fpga_layer& layer = layers[5];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x00000000;
    layer.addr_offset_output = 0x00028000;
    layer.output_size = 81920;
    layer.input_dim[0] = 40;
    layer.input_dim[1] = 32;
    layer.input_dim[2] = 64;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 20;
    layer.output_dim[1] = 16;
    layer.output_dim[2] = 128;
    layer.output_dim_size = 3;
    layer.is_output = false;
    layer.is_f32_output = false;
    layer.is_input_hw_layout = true;
}//end of  Layer_5

//Layer_6: Convolution Layer
//  ->: conv2d_5
//  ->: batch_normalization_5
//  ->: batch_normalization_5
//  ->: leaky_re_lu_5
void CYOLOv3::Layer_6()
{
    struct top_conv_conf& _conf = get_conv_layer(6);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 20; // Input Width
    _conf.hw.input.h = 16; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 128; // Input Channels
    _conf.hw.input.input_base_addr = 0x00028000; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 20; // Output Width
    _conf.sw.output.h = 16; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 256; // Output Channels
    _conf.hw.output.output_base_addr = 0x00050000; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: conv2d_5
    //->: batch_normalization_5
    //->: batch_normalization_5
    //->: leaky_re_lu_5
    _conf.sw.run[0].in_w = 20; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 16; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 128; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 20; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 16; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 256; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 3; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x0002FEE0; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 1; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 590336; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[0].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[0].pool_stride =0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
    _conf.hw.run[0].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
    _conf.hw.run[0].actfunc_param = 0x2E66; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
    _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
    _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
    _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

    struct fpga_layer& layer = layers[6];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x00028000;
    layer.addr_offset_output = 0x00050000;
    layer.output_size = 163840;
    layer.input_dim[0] = 20;
    layer.input_dim[1] = 16;
    layer.input_dim[2] = 128;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 20;
    layer.output_dim[1] = 16;
    layer.output_dim[2] = 256;
    layer.output_dim_size = 3;
    layer.is_output = false;
    layer.is_f32_output = false;
    layer.is_input_hw_layout = true;
}//end of  Layer_6

//Layer_7: Convolution Layer
//  ->: max_pooling2d_5
void CYOLOv3::Layer_7()
{
    struct top_conv_conf& _conf = get_conv_layer(7);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 20; // Input Width
    _conf.hw.input.h = 16; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 256; // Input Channels
    _conf.hw.input.input_base_addr = 0x00050000; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 10; // Output Width
    _conf.sw.output.h = 8; // Output Height
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
    //->: max_pooling2d_5
    _conf.sw.run[0].in_w = 20; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 16; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 256; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 10; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 8; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 256; // Output Channels
    _conf.hw.run[0].conv_enable = 0; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 1; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x000C00E0; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 0; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 0; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[0].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[0].pool_size = 0x202; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[0].pool_stride =0x202; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
    _conf.hw.run[0].actfunc = 0; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
    _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
    _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
    _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
    _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

    struct fpga_layer& layer = layers[7];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x00050000;
    layer.addr_offset_output = 0x00000000;
    layer.output_size = 40960;
    layer.input_dim[0] = 20;
    layer.input_dim[1] = 16;
    layer.input_dim[2] = 256;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 10;
    layer.output_dim[1] = 8;
    layer.output_dim[2] = 256;
    layer.output_dim_size = 3;
    layer.is_output = false;
    layer.is_f32_output = false;
    layer.is_input_hw_layout = true;
}//end of  Layer_7

//Layer_8: Convolution Layer
//  ->: conv2d_6
//  ->: batch_normalization_6
//  ->: batch_normalization_6
//  ->: leaky_re_lu_6
//  ->: max_pooling2d_6
void CYOLOv3::Layer_8()
{
    struct top_conv_conf& _conf = get_conv_layer(8);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 10; // Input Width
    _conf.hw.input.h = 8; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 256; // Input Channels
    _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 10; // Output Width
    _conf.sw.output.h = 8; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 512; // Output Channels
    _conf.hw.output.output_base_addr = 0x0000A000; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: conv2d_6
    //->: batch_normalization_6
    //->: batch_normalization_6
    //->: leaky_re_lu_6
    //->: max_pooling2d_6
    _conf.sw.run[0].in_w = 10; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 8; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 256; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 10; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 8; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 512; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 3; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x000C00E0; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 1; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 2360320; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[0].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[0].pool_size = 0x202; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[0].pool_stride =0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].pool_pad = 0x1000100; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
    _conf.hw.run[0].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
    _conf.hw.run[0].actfunc_param = 0x2E66; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
    _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
    _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
    _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

    struct fpga_layer& layer = layers[8];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x00000000;
    layer.addr_offset_output = 0x0000A000;
    layer.output_size = 81920;
    layer.input_dim[0] = 10;
    layer.input_dim[1] = 8;
    layer.input_dim[2] = 256;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 10;
    layer.output_dim[1] = 8;
    layer.output_dim[2] = 512;
    layer.output_dim_size = 3;
    layer.is_output = false;
    layer.is_f32_output = false;
    layer.is_input_hw_layout = true;
}//end of  Layer_8

//Layer_9: Convolution Layer
//  ->: conv2d_7
//  ->: batch_normalization_7
//  ->: batch_normalization_7
//  ->: leaky_re_lu_7
void CYOLOv3::Layer_9()
{
    struct top_conv_conf& _conf = get_conv_layer(9);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 10; // Input Width
    _conf.hw.input.h = 8; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 512; // Input Channels
    _conf.hw.input.input_base_addr = 0x0000A000; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 10; // Output Width
    _conf.sw.output.h = 8; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 1024; // Output Channels
    _conf.hw.output.output_base_addr = 0x00078000; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: conv2d_7
    //->: batch_normalization_7
    //->: batch_normalization_7
    //->: leaky_re_lu_7
    _conf.sw.run[0].in_w = 10; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 8; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 512; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 10; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 8; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 1024; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 3; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x003004E0; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 1; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 9439232; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[0].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[0].pool_stride =0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
    _conf.hw.run[0].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
    _conf.hw.run[0].actfunc_param = 0x2E66; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
    _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
    _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
    _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

    struct fpga_layer& layer = layers[9];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x0000A000;
    layer.addr_offset_output = 0x00078000;
    layer.output_size = 163840;
    layer.input_dim[0] = 10;
    layer.input_dim[1] = 8;
    layer.input_dim[2] = 512;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 10;
    layer.output_dim[1] = 8;
    layer.output_dim[2] = 1024;
    layer.output_dim_size = 3;
    layer.is_output = false;
    layer.is_f32_output = false;
    layer.is_input_hw_layout = true;
}//end of  Layer_9

//Layer_10: Convolution Layer
//  ->: conv2d_8
//  ->: batch_normalization_8
//  ->: batch_normalization_8
//  ->: leaky_re_lu_8
void CYOLOv3::Layer_10()
{
    struct top_conv_conf& _conf = get_conv_layer(10);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 10; // Input Width
    _conf.hw.input.h = 8; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 1024; // Input Channels
    _conf.hw.input.input_base_addr = 0x00078000; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 10; // Output Width
    _conf.sw.output.h = 8; // Output Height
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
    //->: conv2d_8
    //->: batch_normalization_8
    //->: batch_normalization_8
    //->: leaky_re_lu_8
    _conf.sw.run[0].in_w = 10; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 8; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 1024; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 10; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 8; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 256; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 1; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x00C00CE0; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 1; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 590336; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[0].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[0].pool_stride =0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
    _conf.hw.run[0].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
    _conf.hw.run[0].actfunc_param = 0x2E66; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
    _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
    _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
    _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

    struct fpga_layer& layer = layers[10];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x00078000;
    layer.addr_offset_output = 0x00000000;
    layer.output_size = 40960;
    layer.input_dim[0] = 10;
    layer.input_dim[1] = 8;
    layer.input_dim[2] = 1024;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 10;
    layer.output_dim[1] = 8;
    layer.output_dim[2] = 256;
    layer.output_dim_size = 3;
    layer.is_output = false;
    layer.is_f32_output = false;
    layer.is_input_hw_layout = true;
}//end of  Layer_10

//Layer_11: Convolution Layer
//  ->: conv2d_9
//  ->: batch_normalization_9
//  ->: batch_normalization_9
//  ->: leaky_re_lu_9
void CYOLOv3::Layer_11()
{
    struct top_conv_conf& _conf = get_conv_layer(11);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 10; // Input Width
    _conf.hw.input.h = 8; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 256; // Input Channels
    _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 10; // Output Width
    _conf.sw.output.h = 8; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 512; // Output Channels
    _conf.hw.output.output_base_addr = 0x0000A000; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: conv2d_9
    //->: batch_normalization_9
    //->: batch_normalization_9
    //->: leaky_re_lu_9
    _conf.sw.run[0].in_w = 10; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 8; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 256; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 10; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 8; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 512; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 3; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x00C90EE0; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 1; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 2360320; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[0].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[0].pool_stride =0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
    _conf.hw.run[0].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
    _conf.hw.run[0].actfunc_param = 0x2E66; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
    _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
    _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
    _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

    struct fpga_layer& layer = layers[11];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x00000000;
    layer.addr_offset_output = 0x0000A000;
    layer.output_size = 81920;
    layer.input_dim[0] = 10;
    layer.input_dim[1] = 8;
    layer.input_dim[2] = 256;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 10;
    layer.output_dim[1] = 8;
    layer.output_dim[2] = 512;
    layer.output_dim_size = 3;
    layer.is_output = false;
    layer.is_f32_output = false;
    layer.is_input_hw_layout = true;
}//end of  Layer_11

//Layer_12: Convolution Layer
//  ->: conv2d_10
void CYOLOv3::Layer_12()
{
    struct top_conv_conf& _conf = get_conv_layer(12);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 10; // Input Width
    _conf.hw.input.h = 8; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 512; // Input Channels
    _conf.hw.input.input_base_addr = 0x0000A000; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 10; // Output Width
    _conf.sw.output.h = 8; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 255; // Output Channels
    _conf.hw.output.output_base_addr = 0x0001E000; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: conv2d_10
    _conf.sw.run[0].in_w = 10; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 8; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 512; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 10; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 8; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 255; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 1; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x00ED12E0; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 1; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 294272; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[0].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[0].pool_stride =0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
    _conf.hw.run[0].actfunc = 0; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
    _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
    _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
    _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
    _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

    struct fpga_layer& layer = layers[12];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x0000A000;
    layer.addr_offset_output = 0x0001E000;
    layer.output_size = 40800;
    layer.input_dim[0] = 10;
    layer.input_dim[1] = 8;
    layer.input_dim[2] = 512;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 10;
    layer.output_dim[1] = 8;
    layer.output_dim[2] = 255;
    layer.output_dim_size = 3;
    layer.is_output = false;
    layer.is_f32_output = false;
    layer.is_input_hw_layout = true;
}//end of  Layer_12

//Layer_13: Flatten Layer
//	->: flatten_1
void CYOLOv3::Layer_13()
{
    struct fpga_layer& layer = layers[13];
    layer.type = LT_FLATTEN;
    layer.hw_conf = (void*)0;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x0001E000;
    layer.addr_offset_output = 0x00078000;
    layer.output_size = 40800;
    layer.input_dim[0] = 10;
    layer.input_dim[1] = 8;
    layer.input_dim[2] = 255;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 20400;
    layer.output_dim_size = 1;
    layer.is_output = false;
    layer.is_f32_output = false;
    layer.is_input_hw_layout = true;
}//end of  Layer_13

//Layer_14: Convolution Layer
//  ->: conv2d_11
//  ->: batch_normalization_10
//  ->: batch_normalization_10
//  ->: leaky_re_lu_10
void CYOLOv3::Layer_14()
{
    struct top_conv_conf& _conf = get_conv_layer(13);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 10; // Input Width
    _conf.hw.input.h = 8; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 256; // Input Channels
    _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 10; // Output Width
    _conf.sw.output.h = 8; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 128; // Output Channels
    _conf.hw.output.output_base_addr = 0x0000A000; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: conv2d_11
    //->: batch_normalization_10
    //->: batch_normalization_10
    //->: leaky_re_lu_10
    _conf.sw.run[0].in_w = 10; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 8; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 256; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 10; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 8; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 128; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 1; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x00F19060; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 1; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 73984; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[0].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[0].pool_stride =0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
    _conf.hw.run[0].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
    _conf.hw.run[0].actfunc_param = 0x2E66; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
    _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
    _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
    _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

    struct fpga_layer& layer = layers[14];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x00000000;
    layer.addr_offset_output = 0x0000A000;
    layer.output_size = 20480;
    layer.input_dim[0] = 10;
    layer.input_dim[1] = 8;
    layer.input_dim[2] = 256;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 10;
    layer.output_dim[1] = 8;
    layer.output_dim[2] = 128;
    layer.output_dim_size = 3;
    layer.is_output = false;
    layer.is_f32_output = false;
    layer.is_input_hw_layout = true;
}//end of  Layer_14

//Layer_15: Convolution Layer
//  ->: up_sampling2d_1
void CYOLOv3::Layer_15()
{
    struct top_conv_conf& _conf = get_conv_layer(14);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 10; // Input Width
    _conf.hw.input.h = 8; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 128; // Input Channels
    _conf.hw.input.input_base_addr = 0x0000A000; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 20; // Output Width
    _conf.sw.output.h = 16; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 128; // Output Channels
    _conf.hw.output.output_base_addr = 0x0003C000; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: up_sampling2d_1
    _conf.sw.run[0].in_w = 10; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 8; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 128; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 20; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 16; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 128; // Output Channels
    _conf.hw.run[0].conv_enable = 0; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 1; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x00F2B160; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 0; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 0; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[0].pool_enable = 4;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[0].pool_size = 0x202; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[0].pool_stride =0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
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
    layer.addr_offset_input = 0x0000A000;
    layer.addr_offset_output = 0x0003C000;
    layer.output_size = 81920;
    layer.input_dim[0] = 10;
    layer.input_dim[1] = 8;
    layer.input_dim[2] = 128;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 20;
    layer.output_dim[1] = 16;
    layer.output_dim[2] = 128;
    layer.output_dim_size = 3;
    layer.is_output = false;
    layer.is_f32_output = false;
    layer.is_input_hw_layout = true;
}//end of  Layer_15

//Layer_16: Concatenate Layer
//	->: concatenate_1
void CYOLOv3::Layer_16()
{
    struct fpga_layer& layer = layers[16];
    layer.type = LT_CONCAT;
    layer.hw_conf = (void*)0;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x00050000;
    layer.addr_offset_output = 0x0003C000;
    layer.output_size = 245760;
    layer.input_dim[0] = 20;
    layer.input_dim[1] = 16;
    layer.input_dim[2] = 384;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 20;
    layer.output_dim[1] = 16;
    layer.output_dim[2] = 384;
    layer.output_dim_size = 3;
    layer.is_output = false;
    layer.is_f32_output = false;
    layer.is_input_hw_layout = true;
}//end of  Layer_16

//Layer_17: Convolution Layer
//  ->: conv2d_12
//  ->: batch_normalization_11
//  ->: batch_normalization_11
//  ->: leaky_re_lu_11
void CYOLOv3::Layer_17()
{
    struct top_conv_conf& _conf = get_conv_layer(15);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 20; // Input Width
    _conf.hw.input.h = 16; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 384; // Input Channels
    _conf.hw.input.input_base_addr = 0x0003C000; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 20; // Output Width
    _conf.sw.output.h = 16; // Output Height
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
    //->: conv2d_12
    //->: batch_normalization_11
    //->: batch_normalization_11
    //->: leaky_re_lu_11
    _conf.sw.run[0].in_w = 20; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 16; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 384; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 20; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 16; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 256; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 3; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x00F2B160; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 1; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 1769984; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[0].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[0].pool_stride =0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
    _conf.hw.run[0].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU, 3 = Sigmoid, 4 = PReLU, 5 = ELU, 6 = ReLU6
    _conf.hw.run[0].actfunc_param = 0x2E66; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
    _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
    _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
    _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

    struct fpga_layer& layer = layers[17];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x0003C000;
    layer.addr_offset_output = 0x00000000;
    layer.output_size = 163840;
    layer.input_dim[0] = 20;
    layer.input_dim[1] = 16;
    layer.input_dim[2] = 384;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 20;
    layer.output_dim[1] = 16;
    layer.output_dim[2] = 256;
    layer.output_dim_size = 3;
    layer.is_output = false;
    layer.is_f32_output = false;
    layer.is_input_hw_layout = false;
}//end of  Layer_17

//Layer_18: Convolution Layer
//  ->: conv2d_13
void CYOLOv3::Layer_18()
{
    struct top_conv_conf& _conf = get_conv_layer(16);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 20; // Input Width
    _conf.hw.input.h = 16; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 256; // Input Channels
    _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 20; // Output Width
    _conf.sw.output.h = 16; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 255; // Output Channels
    _conf.hw.output.output_base_addr = 0x00028000; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode = 0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: conv2d_13
    _conf.sw.run[0].in_w = 20; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 16; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 256; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 20; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 16; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 255; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 1; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x010DB360; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 1; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 147392; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[0].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[0].pool_stride =0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
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
    layer.addr_offset_input = 0x00000000;
    layer.addr_offset_output = 0x00028000;
    layer.output_size = 163200;
    layer.input_dim[0] = 20;
    layer.input_dim[1] = 16;
    layer.input_dim[2] = 256;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 20;
    layer.output_dim[1] = 16;
    layer.output_dim[2] = 255;
    layer.output_dim_size = 3;
    layer.is_output = false;
    layer.is_f32_output = false;
    layer.is_input_hw_layout = true;
}//end of  Layer_18

//Layer_19: Flatten Layer
//	->: flatten_2
void CYOLOv3::Layer_19()
{
    struct fpga_layer& layer = layers[19];
    layer.type = LT_FLATTEN;
    layer.hw_conf = (void*)0;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x00028000;
    layer.addr_offset_output = 0x00081F60;
    layer.output_size = 163200;
    layer.input_dim[0] = 20;
    layer.input_dim[1] = 16;
    layer.input_dim[2] = 255;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 81600;
    layer.output_dim_size = 1;
    layer.is_output = false;
    layer.is_f32_output = false;
    layer.is_input_hw_layout = true;
}//end of  Layer_19

//Layer_20: Concatenate Layer
//	->: concatenate_2
void CYOLOv3::Layer_20()
{
    struct fpga_layer& layer = layers[20];
    layer.type = LT_CONCAT;
    layer.hw_conf = (void*)0;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x00078000;
    layer.addr_offset_output = 0x00078000;
    layer.output_size = 204000;
    layer.input_dim[0] = 102000;
    layer.input_dim_size = 1;
    layer.output_dim[0] = 102000;
    layer.output_dim_size = 1;
    layer.is_output = true;
    layer.is_f32_output = false;
    layer.is_input_hw_layout = false;
    output_layers[0] = &layer;
}//end of  Layer_20

