/*
*------------------------------------------------------------
* Copyright(c) 2017 by Digital Media Professionals Inc.
* All rights reserved.
*------------------------------------------------------------
* This source code was generated using DMP-DV700 tools
* Digital Media Professionals Inc.
*------------------------------------------------------------
*/

#include "SegNetBasic_gen.h"



CSegNetBasic::CSegNetBasic()
{

}

CSegNetBasic::~CSegNetBasic()
{

}

unsigned int CSegNetBasic::get_total_layer_count()
{
    return num_layers;
}

unsigned int CSegNetBasic::get_output_layer_count()
{
    return num_output_layers;
}

unsigned int CSegNetBasic::get_convolution_layer_count()
{
    return num_conv_layers;
}

unsigned int CSegNetBasic::get_innerproduct_layer_count()
{
    return num_fc_layers;
}

int CSegNetBasic::initialize()
{
    num_layers = 16;
    num_output_layers = 1;
    num_conv_layers = 15;
    num_fc_layers = 0;
    weight_size = 1210528;
    buffer_size = 31641600;
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

    //Add 2 memory size requests. One for weights, the other for io buffers
    memory_size_request[0] = weight_size;
    memory_size_request[1] = buffer_size;

    return 0;
}

//Layer_0: Convolution Layer
//  ->: conv2d_1
//  ->: batch_normalization_1
//  ->: batch_normalization_1
//  ->: activation_1
void CSegNetBasic::Layer_0()
{
    struct top_conv_conf& _conf = get_conv_layer(0);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 320; // Input Width
    _conf.hw.input.h = 240; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 3; // Input Channels
    _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
    _conf.hw.input.tiles = 3; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 320; // Output Width
    _conf.sw.output.h = 240; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 64; // Output Channels
    _conf.hw.output.output_base_addr = 0x00070800; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode =0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: conv2d_1
    //->: batch_normalization_1
    //->: batch_normalization_1
    //->: activation_1
    _conf.sw.run[0].in_w = 320; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 240; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 3; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 320; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 240; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 64; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 3; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x00000000; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 1; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 9344; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[0].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[0].pool_stride =0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
    _conf.hw.run[0].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU
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
    layer.addr_offset_output = 0x00070800;
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
void CSegNetBasic::Layer_1()
{
    struct top_conv_conf& _conf = get_conv_layer(1);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 320; // Input Width
    _conf.hw.input.h = 240; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 64; // Input Channels
    _conf.hw.input.input_base_addr = 0x00070800; // Input byte address
    _conf.hw.input.tiles = 2; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 160; // Output Width
    _conf.sw.output.h = 120; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 64; // Output Channels
    _conf.hw.output.output_base_addr = 0x009D0800; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode =0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: max_pooling2d_1
    _conf.sw.run[0].in_w = 320; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 240; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 64; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 160; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 120; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 64; // Output Channels
    _conf.hw.run[0].conv_enable = 0; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 1; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x00002480; // Filter Weight and Bias byte address
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
    _conf.hw.run[0].actfunc = 0; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU
    _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
    _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
    _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
    _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

    struct fpga_layer& layer = layers[1];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x00070800;
    layer.addr_offset_output = 0x009D0800;
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
//  ->: batch_normalization_2
//  ->: batch_normalization_2
//  ->: activation_2
void CSegNetBasic::Layer_2()
{
    struct top_conv_conf& _conf = get_conv_layer(2);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 160; // Input Width
    _conf.hw.input.h = 120; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 64; // Input Channels
    _conf.hw.input.input_base_addr = 0x009D0800; // Input byte address
    _conf.hw.input.tiles = 5; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 160; // Output Width
    _conf.sw.output.h = 120; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 80; // Output Channels
    _conf.hw.output.output_base_addr = 0x00000000; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode =0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: conv2d_2
    //->: batch_normalization_2
    //->: batch_normalization_2
    //->: activation_2
    _conf.sw.run[0].in_w = 160; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 120; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 64; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 160; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 120; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 80; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 3; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x00002480; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 1; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 92320; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[0].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[0].pool_stride =0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
    _conf.hw.run[0].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU
    _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
    _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
    _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
    _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

    struct fpga_layer& layer = layers[2];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x009D0800;
    layer.addr_offset_output = 0x00000000;
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
void CSegNetBasic::Layer_3()
{
    struct top_conv_conf& _conf = get_conv_layer(3);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 160; // Input Width
    _conf.hw.input.h = 120; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 80; // Input Channels
    _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 80; // Output Width
    _conf.sw.output.h = 60; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 80; // Output Channels
    _conf.hw.output.output_base_addr = 0x002EE000; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode =0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: max_pooling2d_2
    _conf.sw.run[0].in_w = 160; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 120; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 80; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 80; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 60; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 80; // Output Channels
    _conf.hw.run[0].conv_enable = 0; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 1; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x00018D20; // Filter Weight and Bias byte address
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
    _conf.hw.run[0].actfunc = 0; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU
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
    layer.addr_offset_output = 0x002EE000;
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
//  ->: batch_normalization_3
//  ->: batch_normalization_3
//  ->: activation_3
void CSegNetBasic::Layer_4()
{
    struct top_conv_conf& _conf = get_conv_layer(4);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 80; // Input Width
    _conf.hw.input.h = 60; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 80; // Input Channels
    _conf.hw.input.input_base_addr = 0x002EE000; // Input byte address
    _conf.hw.input.tiles = 2; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 80; // Output Width
    _conf.sw.output.h = 60; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 96; // Output Channels
    _conf.hw.output.output_base_addr = 0x00000000; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode =0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: conv2d_3
    //->: batch_normalization_3
    //->: batch_normalization_3
    //->: activation_3
    _conf.sw.run[0].in_w = 80; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 60; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 80; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 80; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 60; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 96; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 3; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x00018D20; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 1; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 138432; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[0].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[0].pool_stride =0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
    _conf.hw.run[0].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU
    _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
    _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
    _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
    _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

    struct fpga_layer& layer = layers[4];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x002EE000;
    layer.addr_offset_output = 0x00000000;
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
void CSegNetBasic::Layer_5()
{
    struct top_conv_conf& _conf = get_conv_layer(5);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 80; // Input Width
    _conf.hw.input.h = 60; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 96; // Input Channels
    _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 40; // Output Width
    _conf.sw.output.h = 30; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 96; // Output Channels
    _conf.hw.output.output_base_addr = 0x000E1000; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode =0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: max_pooling2d_3
    _conf.sw.run[0].in_w = 80; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 60; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 96; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 40; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 30; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 96; // Output Channels
    _conf.hw.run[0].conv_enable = 0; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 1; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x0003A9E0; // Filter Weight and Bias byte address
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
    _conf.hw.run[0].actfunc = 0; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU
    _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
    _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
    _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
    _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

    struct fpga_layer& layer = layers[5];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x00000000;
    layer.addr_offset_output = 0x000E1000;
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
//  ->: batch_normalization_4
//  ->: batch_normalization_4
//  ->: activation_4
void CSegNetBasic::Layer_6()
{
    struct top_conv_conf& _conf = get_conv_layer(6);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 40; // Input Width
    _conf.hw.input.h = 30; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 96; // Input Channels
    _conf.hw.input.input_base_addr = 0x000E1000; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 40; // Output Width
    _conf.sw.output.h = 30; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 128; // Output Channels
    _conf.hw.output.output_base_addr = 0x00000000; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode =0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: conv2d_4
    //->: batch_normalization_4
    //->: batch_normalization_4
    //->: activation_4
    _conf.sw.run[0].in_w = 40; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 30; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 96; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 40; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 30; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 128; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 3; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x0003A9E0; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 1; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 221440; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[0].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[0].pool_stride =0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
    _conf.hw.run[0].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU
    _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
    _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
    _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
    _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

    struct fpga_layer& layer = layers[6];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x000E1000;
    layer.addr_offset_output = 0x00000000;
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
//  ->: conv2d_5
//  ->: batch_normalization_5
//  ->: batch_normalization_5
void CSegNetBasic::Layer_7()
{
    struct top_conv_conf& _conf = get_conv_layer(7);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 40; // Input Width
    _conf.hw.input.h = 30; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 128; // Input Channels
    _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 40; // Output Width
    _conf.sw.output.h = 30; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 128; // Output Channels
    _conf.hw.output.output_base_addr = 0x0004B000; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode =0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: conv2d_5
    //->: batch_normalization_5
    //->: batch_normalization_5
    _conf.sw.run[0].in_w = 40; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 30; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 128; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 40; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 30; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 128; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 3; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x00070AE0; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 1; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 295168; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[0].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[0].pool_stride =0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
    _conf.hw.run[0].actfunc = 0; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU
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
    layer.addr_offset_output = 0x0004B000;
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
//  ->: up_sampling2d_1
void CSegNetBasic::Layer_8()
{
    struct top_conv_conf& _conf = get_conv_layer(8);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 40; // Input Width
    _conf.hw.input.h = 30; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 128; // Input Channels
    _conf.hw.input.input_base_addr = 0x0004B000; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 80; // Output Width
    _conf.sw.output.h = 60; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 128; // Output Channels
    _conf.hw.output.output_base_addr = 0x00096000; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode =0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: up_sampling2d_1
    _conf.sw.run[0].in_w = 40; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 30; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 128; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 80; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 60; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 128; // Output Channels
    _conf.hw.run[0].conv_enable = 0; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 1; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x000B8BE0; // Filter Weight and Bias byte address
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
    _conf.hw.run[0].actfunc = 0; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU
    _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
    _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
    _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
    _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

    struct fpga_layer& layer = layers[8];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x0004B000;
    layer.addr_offset_output = 0x00096000;
    layer.output_size = 1228800;
    layer.input_dim[0] = 40;
    layer.input_dim[1] = 30;
    layer.input_dim[2] = 128;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 80;
    layer.output_dim[1] = 60;
    layer.output_dim[2] = 128;
    layer.output_dim_size = 3;
    layer.is_output = false;
    layer.is_f32_output = false;
    layer.is_input_hw_layout = true;
}//end of  Layer_8

//Layer_9: Convolution Layer
//  ->: conv2d_6
//  ->: batch_normalization_6
//  ->: batch_normalization_6
void CSegNetBasic::Layer_9()
{
    struct top_conv_conf& _conf = get_conv_layer(9);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 80; // Input Width
    _conf.hw.input.h = 60; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 128; // Input Channels
    _conf.hw.input.input_base_addr = 0x00096000; // Input byte address
    _conf.hw.input.tiles = 3; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 80; // Output Width
    _conf.sw.output.h = 60; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 96; // Output Channels
    _conf.hw.output.output_base_addr = 0x001C2000; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode =0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: conv2d_6
    //->: batch_normalization_6
    //->: batch_normalization_6
    _conf.sw.run[0].in_w = 80; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 60; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 128; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 80; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 60; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 96; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 3; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x000B8BE0; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 1; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 221376; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[0].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[0].pool_stride =0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
    _conf.hw.run[0].actfunc = 0; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU
    _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
    _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
    _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
    _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

    struct fpga_layer& layer = layers[9];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x00096000;
    layer.addr_offset_output = 0x001C2000;
    layer.output_size = 921600;
    layer.input_dim[0] = 80;
    layer.input_dim[1] = 60;
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
//  ->: up_sampling2d_2
void CSegNetBasic::Layer_10()
{
    struct top_conv_conf& _conf = get_conv_layer(10);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 80; // Input Width
    _conf.hw.input.h = 60; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 96; // Input Channels
    _conf.hw.input.input_base_addr = 0x001C2000; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 160; // Output Width
    _conf.sw.output.h = 120; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 96; // Output Channels
    _conf.hw.output.output_base_addr = 0x002A3000; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode =0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: up_sampling2d_2
    _conf.sw.run[0].in_w = 80; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 60; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 96; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 160; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 120; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 96; // Output Channels
    _conf.hw.run[0].conv_enable = 0; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 1; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x000EECA0; // Filter Weight and Bias byte address
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
    _conf.hw.run[0].actfunc = 0; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU
    _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
    _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
    _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
    _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

    struct fpga_layer& layer = layers[10];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x001C2000;
    layer.addr_offset_output = 0x002A3000;
    layer.output_size = 3686400;
    layer.input_dim[0] = 80;
    layer.input_dim[1] = 60;
    layer.input_dim[2] = 96;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 160;
    layer.output_dim[1] = 120;
    layer.output_dim[2] = 96;
    layer.output_dim_size = 3;
    layer.is_output = false;
    layer.is_f32_output = false;
    layer.is_input_hw_layout = true;
}//end of  Layer_10

//Layer_11: Convolution Layer
//  ->: conv2d_7
//  ->: batch_normalization_7
//  ->: batch_normalization_7
void CSegNetBasic::Layer_11()
{
    struct top_conv_conf& _conf = get_conv_layer(11);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 160; // Input Width
    _conf.hw.input.h = 120; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 96; // Input Channels
    _conf.hw.input.input_base_addr = 0x002A3000; // Input byte address
    _conf.hw.input.tiles = 7; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 160; // Output Width
    _conf.sw.output.h = 120; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 80; // Output Channels
    _conf.hw.output.output_base_addr = 0x00627000; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode =0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: conv2d_7
    //->: batch_normalization_7
    //->: batch_normalization_7
    _conf.sw.run[0].in_w = 160; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 120; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 96; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 160; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 120; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 80; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 3; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x000EECA0; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 1; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 138400; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[0].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[0].pool_stride =0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
    _conf.hw.run[0].actfunc = 0; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU
    _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
    _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
    _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
    _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

    struct fpga_layer& layer = layers[11];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x002A3000;
    layer.addr_offset_output = 0x00627000;
    layer.output_size = 3072000;
    layer.input_dim[0] = 160;
    layer.input_dim[1] = 120;
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
//  ->: up_sampling2d_3
void CSegNetBasic::Layer_12()
{
    struct top_conv_conf& _conf = get_conv_layer(12);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 160; // Input Width
    _conf.hw.input.h = 120; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 80; // Input Channels
    _conf.hw.input.input_base_addr = 0x00627000; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 320; // Output Width
    _conf.sw.output.h = 240; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 80; // Output Channels
    _conf.hw.output.output_base_addr = 0x00915000; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode =0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: up_sampling2d_3
    _conf.sw.run[0].in_w = 160; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 120; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 80; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 320; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 240; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 80; // Output Channels
    _conf.hw.run[0].conv_enable = 0; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 1; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x00110940; // Filter Weight and Bias byte address
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
    _conf.hw.run[0].actfunc = 0; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU
    _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
    _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
    _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
    _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

    struct fpga_layer& layer = layers[12];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x00627000;
    layer.addr_offset_output = 0x00915000;
    layer.output_size = 12288000;
    layer.input_dim[0] = 160;
    layer.input_dim[1] = 120;
    layer.input_dim[2] = 80;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 320;
    layer.output_dim[1] = 240;
    layer.output_dim[2] = 80;
    layer.output_dim_size = 3;
    layer.is_output = false;
    layer.is_f32_output = false;
    layer.is_input_hw_layout = true;
}//end of  Layer_12

//Layer_13: Convolution Layer
//  ->: conv2d_8
//  ->: batch_normalization_8
//  ->: batch_normalization_8
void CSegNetBasic::Layer_13()
{
    struct top_conv_conf& _conf = get_conv_layer(13);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 320; // Input Width
    _conf.hw.input.h = 240; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 80; // Input Channels
    _conf.hw.input.input_base_addr = 0x00915000; // Input byte address
    _conf.hw.input.tiles = 25; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 320; // Output Width
    _conf.sw.output.h = 240; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 64; // Output Channels
    _conf.hw.output.output_base_addr = 0x014CD000; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode =0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: conv2d_8
    //->: batch_normalization_8
    //->: batch_normalization_8
    _conf.sw.run[0].in_w = 320; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 240; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 80; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 320; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 240; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 64; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 3; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x00110940; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 1; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 92288; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[0].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[0].pool_stride =0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
    _conf.hw.run[0].actfunc = 0; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU
    _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
    _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
    _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
    _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

    struct fpga_layer& layer = layers[13];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x00915000;
    layer.addr_offset_output = 0x014CD000;
    layer.output_size = 9830400;
    layer.input_dim[0] = 320;
    layer.input_dim[1] = 240;
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
//  ->: conv2d_9
void CSegNetBasic::Layer_14()
{
    struct top_conv_conf& _conf = get_conv_layer(14);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 320; // Input Width
    _conf.hw.input.h = 240; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 64; // Input Channels
    _conf.hw.input.input_base_addr = 0x014CD000; // Input byte address
    _conf.hw.input.tiles = 18; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 320; // Output Width
    _conf.sw.output.h = 240; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 12; // Output Channels
    _conf.hw.output.output_base_addr = 0x00000000; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode =0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: conv2d_9
    _conf.sw.run[0].in_w = 320; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 240; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 64; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 320; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 240; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 12; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 1; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x001271C0; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 1; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 1760; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[0].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[0].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[0].pool_stride =0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
    _conf.hw.run[0].actfunc = 0; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU
    _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
    _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
    _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
    _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

    struct fpga_layer& layer = layers[14];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x014CD000;
    layer.addr_offset_output = 0x00000000;
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
}//end of  Layer_14

//Layer_15: Flatten Layer
//	->: reshape_1_flatten
void CSegNetBasic::Layer_15()
{
    struct fpga_layer& layer = layers[15];
    layer.type = LT_FLATTEN;
    layer.hw_conf = (void*)0;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x00000000;
    layer.addr_offset_output = 0x001C2000;
    layer.output_size = 1843200;
    layer.input_dim[0] = 320;
    layer.input_dim[1] = 240;
    layer.input_dim[2] = 12;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 76800;
    layer.output_dim[1] = 12;
    layer.output_dim_size = 2;
    layer.is_output = true;
    layer.is_f32_output = false;
    layer.is_input_hw_layout = true;
    output_layers[0] = &layer;
}//end of  Layer_15

