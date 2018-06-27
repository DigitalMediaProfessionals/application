/*
*------------------------------------------------------------
* Copyright(c) 2017 by Digital Media Professionals Inc.
* All rights reserved.
*------------------------------------------------------------
* This source code was generated using DMP-DV700 tools
* Digital Media Professionals Inc.
*------------------------------------------------------------
*/

#include "KerasSqueezeNet_gen.h"



CKerasSqueezeNet::CKerasSqueezeNet()
{

}

CKerasSqueezeNet::~CKerasSqueezeNet()
{

}

unsigned int CKerasSqueezeNet::get_total_layer_count()
{
    return num_layers;
}

unsigned int CKerasSqueezeNet::get_output_layer_count()
{
    return num_output_layers;
}

unsigned int CKerasSqueezeNet::get_convolution_layer_count()
{
    return num_conv_layers;
}

unsigned int CKerasSqueezeNet::get_innerproduct_layer_count()
{
    return num_fc_layers;
}

int CKerasSqueezeNet::initialize()
{
    num_layers = 21;
    num_output_layers = 1;
    num_conv_layers = 20;
    num_fc_layers = 0;
    weight_size = 1363280;
    buffer_size = 903168;
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
void CKerasSqueezeNet::Layer_0()
{
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
    _conf.sw.output.w = 56; // Output Width
    _conf.sw.output.h = 56; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 64; // Output Channels
    _conf.hw.output.output_base_addr = 0x0004B7C0; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode =0; // 0 = concat, 1 = eltwise add

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
    _conf.sw.run[0].out_w = 56; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 56; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 64; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 3; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x00000000; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 5248; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].conv_stride = 0x202; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[0].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[0].pool_size = 0x303; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[0].pool_stride =0x202; // bits [7:0] = X stride, bits [15:8] = Y stride
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
    layer.addr_offset_output = 0x0004B7C0;
    layer.output_size = 401408;
    layer.input_dim[0] = 227;
    layer.input_dim[1] = 227;
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
//  ->: fire2/squeeze1x1
//  ->: fire2/relu_squeeze1x1
void CKerasSqueezeNet::Layer_1()
{
    struct top_conv_conf& _conf = get_conv_layer(1);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 56; // Input Width
    _conf.hw.input.h = 56; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 64; // Input Channels
    _conf.hw.input.input_base_addr = 0x0004B7C0; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 56; // Output Width
    _conf.sw.output.h = 56; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 16; // Output Channels
    _conf.hw.output.output_base_addr = 0x00000000; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode =0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: fire2/squeeze1x1
    //->: fire2/relu_squeeze1x1
    _conf.sw.run[0].in_w = 56; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 56; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 64; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 56; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 56; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 16; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 1; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x00001480; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 1696; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
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

    struct fpga_layer& layer = layers[1];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x0004B7C0;
    layer.addr_offset_output = 0x00000000;
    layer.output_size = 100352;
    layer.input_dim[0] = 56;
    layer.input_dim[1] = 56;
    layer.input_dim[2] = 64;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 56;
    layer.output_dim[1] = 56;
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
void CKerasSqueezeNet::Layer_2()
{
    struct top_conv_conf& _conf = get_conv_layer(2);
    //Topo: 00000000000000000000000000000011
    _conf.hw.header.topo = 0x3; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 56; // Input Width
    _conf.hw.input.h = 56; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 16; // Input Channels
    _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 56; // Output Width
    _conf.sw.output.h = 56; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 128; // Output Channels
    _conf.hw.output.output_base_addr = 0x00018800; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode =0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->2 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: fire2/expand1x1
    //->: fire2/relu_expand1x1
    _conf.sw.run[0].in_w = 56; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 56; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 16; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 56; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 56; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 64; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 1; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x00001B20; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 5248; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
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
    //--------------------------------------------------
    //RUN : 1
    //--------------------------------------------------
    //->: fire2/expand3x3
    //->: fire2/relu_expand3x3
    _conf.sw.run[1].in_w = 56; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[1].in_h = 56; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[1].in_c = 16; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[1].out_w = 56; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[1].out_h = 56; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[1].m = 64; // Output Channels
    _conf.hw.run[1].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[1].p = 3; // Filter Width and Height
    _conf.hw.run[1].pz = 1; // Filter Depth
    _conf.hw.run[1].weight_base_addr = 0x00002FA0; // Filter Weight and Bias byte address
    _conf.hw.run[1].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[1].weight_size = 9856; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[1].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[1].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[1].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[1].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[1].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[1].pool_stride =0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[1].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[1].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
    _conf.hw.run[1].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU
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
    layer.addr_offset_output = 0x00018800;
    layer.output_size = 802816;
    layer.input_dim[0] = 56;
    layer.input_dim[1] = 56;
    layer.input_dim[2] = 16;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 56;
    layer.output_dim[1] = 56;
    layer.output_dim[2] = 128;
    layer.output_dim_size = 3;
    layer.is_output = false;
    layer.is_f32_output = false;
    layer.is_input_hw_layout = true;
}//end of  Layer_2

//Layer_3: Convolution Layer
//  ->: fire3/squeeze1x1
//  ->: fire3/relu_squeeze1x1
void CKerasSqueezeNet::Layer_3()
{
    struct top_conv_conf& _conf = get_conv_layer(3);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 56; // Input Width
    _conf.hw.input.h = 56; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 128; // Input Channels
    _conf.hw.input.input_base_addr = 0x00018800; // Input byte address
    _conf.hw.input.tiles = 2; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 56; // Output Width
    _conf.sw.output.h = 56; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 16; // Output Channels
    _conf.hw.output.output_base_addr = 0x00000000; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode =0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: fire3/squeeze1x1
    //->: fire3/relu_squeeze1x1
    _conf.sw.run[0].in_w = 56; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 56; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 128; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 56; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 56; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 16; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 1; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x00005620; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 2848; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
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

    struct fpga_layer& layer = layers[3];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x00018800;
    layer.addr_offset_output = 0x00000000;
    layer.output_size = 100352;
    layer.input_dim[0] = 56;
    layer.input_dim[1] = 56;
    layer.input_dim[2] = 128;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 56;
    layer.output_dim[1] = 56;
    layer.output_dim[2] = 16;
    layer.output_dim_size = 3;
    layer.is_output = false;
    layer.is_f32_output = false;
    layer.is_input_hw_layout = true;
}//end of  Layer_3

//Layer_4: Convolution Layer
//  ->: fire3/expand1x1
//  ->: fire3/relu_expand1x1
//  ->: pool3
//  ->: fire3/expand3x3
//  ->: fire3/relu_expand3x3
//  ->: pool3
void CKerasSqueezeNet::Layer_4()
{
    struct top_conv_conf& _conf = get_conv_layer(4);
    //Topo: 00000000000000000000000000000011
    _conf.hw.header.topo = 0x3; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 56; // Input Width
    _conf.hw.input.h = 56; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 16; // Input Channels
    _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 28; // Output Width
    _conf.sw.output.h = 28; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 128; // Output Channels
    _conf.hw.output.output_base_addr = 0x00018800; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode =0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->2 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: fire3/expand1x1
    //->: fire3/relu_expand1x1
    //->: pool3
    _conf.sw.run[0].in_w = 56; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 56; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 16; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 28; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 28; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 64; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 1; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x00006140; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 5248; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[0].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[0].pool_size = 0x303; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[0].pool_stride =0x202; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].pool_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
    _conf.hw.run[0].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU
    _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
    _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
    _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
    _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here
    //--------------------------------------------------
    //RUN : 1
    //--------------------------------------------------
    //->: fire3/expand3x3
    //->: fire3/relu_expand3x3
    //->: pool3
    _conf.sw.run[1].in_w = 56; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[1].in_h = 56; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[1].in_c = 16; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[1].out_w = 28; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[1].out_h = 28; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[1].m = 64; // Output Channels
    _conf.hw.run[1].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[1].p = 3; // Filter Width and Height
    _conf.hw.run[1].pz = 1; // Filter Depth
    _conf.hw.run[1].weight_base_addr = 0x000075C0; // Filter Weight and Bias byte address
    _conf.hw.run[1].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[1].weight_size = 9856; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[1].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[1].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[1].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[1].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[1].pool_size = 0x303; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[1].pool_stride =0x202; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[1].pool_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[1].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
    _conf.hw.run[1].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU
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
    layer.addr_offset_output = 0x00018800;
    layer.output_size = 200704;
    layer.input_dim[0] = 56;
    layer.input_dim[1] = 56;
    layer.input_dim[2] = 16;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 28;
    layer.output_dim[1] = 28;
    layer.output_dim[2] = 128;
    layer.output_dim_size = 3;
    layer.is_output = false;
    layer.is_f32_output = false;
    layer.is_input_hw_layout = true;
}//end of  Layer_4

//Layer_5: Convolution Layer
//  ->: fire4/squeeze1x1
//  ->: fire4/relu_squeeze1x1
void CKerasSqueezeNet::Layer_5()
{
    struct top_conv_conf& _conf = get_conv_layer(5);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 28; // Input Width
    _conf.hw.input.h = 28; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 128; // Input Channels
    _conf.hw.input.input_base_addr = 0x00018800; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 28; // Output Width
    _conf.sw.output.h = 28; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 32; // Output Channels
    _conf.hw.output.output_base_addr = 0x00000000; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode =0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: fire4/squeeze1x1
    //->: fire4/relu_squeeze1x1
    _conf.sw.run[0].in_w = 28; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 28; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 128; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 28; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 28; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 32; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 1; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x00009C40; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 5184; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
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

    struct fpga_layer& layer = layers[5];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x00018800;
    layer.addr_offset_output = 0x00000000;
    layer.output_size = 50176;
    layer.input_dim[0] = 28;
    layer.input_dim[1] = 28;
    layer.input_dim[2] = 128;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 28;
    layer.output_dim[1] = 28;
    layer.output_dim[2] = 32;
    layer.output_dim_size = 3;
    layer.is_output = false;
    layer.is_f32_output = false;
    layer.is_input_hw_layout = true;
}//end of  Layer_5

//Layer_6: Convolution Layer
//  ->: fire4/expand1x1
//  ->: fire4/relu_expand1x1
//  ->: fire4/expand3x3
//  ->: fire4/relu_expand3x3
void CKerasSqueezeNet::Layer_6()
{
    struct top_conv_conf& _conf = get_conv_layer(6);
    //Topo: 00000000000000000000000000000011
    _conf.hw.header.topo = 0x3; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 28; // Input Width
    _conf.hw.input.h = 28; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 32; // Input Channels
    _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 28; // Output Width
    _conf.sw.output.h = 28; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 256; // Output Channels
    _conf.hw.output.output_base_addr = 0x0000C400; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode =0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->2 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: fire4/expand1x1
    //->: fire4/relu_expand1x1
    _conf.sw.run[0].in_w = 28; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 28; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 32; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 28; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 28; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 128; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 1; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x0000B080; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 9984; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
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
    //--------------------------------------------------
    //RUN : 1
    //--------------------------------------------------
    //->: fire4/expand3x3
    //->: fire4/relu_expand3x3
    _conf.sw.run[1].in_w = 28; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[1].in_h = 28; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[1].in_c = 32; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[1].out_w = 28; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[1].out_h = 28; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[1].m = 128; // Output Channels
    _conf.hw.run[1].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[1].p = 3; // Filter Width and Height
    _conf.hw.run[1].pz = 1; // Filter Depth
    _conf.hw.run[1].weight_base_addr = 0x0000D780; // Filter Weight and Bias byte address
    _conf.hw.run[1].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[1].weight_size = 37632; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[1].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[1].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[1].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[1].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[1].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[1].pool_stride =0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[1].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[1].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
    _conf.hw.run[1].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU
    _conf.hw.run[1].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
    _conf.hw.run[1].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
    _conf.hw.run[1].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
    _conf.hw.run[1].ALIGN_0 = 0;//Some comments needed here

    struct fpga_layer& layer = layers[6];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x00000000;
    layer.addr_offset_output = 0x0000C400;
    layer.output_size = 401408;
    layer.input_dim[0] = 28;
    layer.input_dim[1] = 28;
    layer.input_dim[2] = 32;
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
//  ->: fire5/squeeze1x1
//  ->: fire5/relu_squeeze1x1
void CKerasSqueezeNet::Layer_7()
{
    struct top_conv_conf& _conf = get_conv_layer(7);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 28; // Input Width
    _conf.hw.input.h = 28; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 256; // Input Channels
    _conf.hw.input.input_base_addr = 0x0000C400; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 28; // Output Width
    _conf.sw.output.h = 28; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 32; // Output Channels
    _conf.hw.output.output_base_addr = 0x00000000; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode =0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: fire5/squeeze1x1
    //->: fire5/relu_squeeze1x1
    _conf.sw.run[0].in_w = 28; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 28; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 256; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 28; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 28; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 32; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 1; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x00016A80; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 9792; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
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

    struct fpga_layer& layer = layers[7];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x0000C400;
    layer.addr_offset_output = 0x00000000;
    layer.output_size = 50176;
    layer.input_dim[0] = 28;
    layer.input_dim[1] = 28;
    layer.input_dim[2] = 256;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 28;
    layer.output_dim[1] = 28;
    layer.output_dim[2] = 32;
    layer.output_dim_size = 3;
    layer.is_output = false;
    layer.is_f32_output = false;
    layer.is_input_hw_layout = true;
}//end of  Layer_7

//Layer_8: Convolution Layer
//  ->: fire5/expand1x1
//  ->: fire5/relu_expand1x1
//  ->: pool5
//  ->: fire5/expand3x3
//  ->: fire5/relu_expand3x3
//  ->: pool5
void CKerasSqueezeNet::Layer_8()
{
    struct top_conv_conf& _conf = get_conv_layer(8);
    //Topo: 00000000000000000000000000000011
    _conf.hw.header.topo = 0x3; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 28; // Input Width
    _conf.hw.input.h = 28; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 32; // Input Channels
    _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 14; // Output Width
    _conf.sw.output.h = 14; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 256; // Output Channels
    _conf.hw.output.output_base_addr = 0x0000C400; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode =0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->2 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: fire5/expand1x1
    //->: fire5/relu_expand1x1
    //->: pool5
    _conf.sw.run[0].in_w = 28; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 28; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 32; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 128; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 1; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x000190C0; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 9984; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[0].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[0].pool_size = 0x303; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[0].pool_stride =0x202; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].pool_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
    _conf.hw.run[0].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU
    _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
    _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
    _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
    _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here
    //--------------------------------------------------
    //RUN : 1
    //--------------------------------------------------
    //->: fire5/expand3x3
    //->: fire5/relu_expand3x3
    //->: pool5
    _conf.sw.run[1].in_w = 28; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[1].in_h = 28; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[1].in_c = 32; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[1].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[1].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[1].m = 128; // Output Channels
    _conf.hw.run[1].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[1].p = 3; // Filter Width and Height
    _conf.hw.run[1].pz = 1; // Filter Depth
    _conf.hw.run[1].weight_base_addr = 0x0001B7C0; // Filter Weight and Bias byte address
    _conf.hw.run[1].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[1].weight_size = 37632; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[1].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[1].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[1].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[1].pool_enable = 1;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[1].pool_size = 0x303; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[1].pool_stride =0x202; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[1].pool_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[1].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
    _conf.hw.run[1].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU
    _conf.hw.run[1].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
    _conf.hw.run[1].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
    _conf.hw.run[1].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
    _conf.hw.run[1].ALIGN_0 = 0;//Some comments needed here

    struct fpga_layer& layer = layers[8];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x00000000;
    layer.addr_offset_output = 0x0000C400;
    layer.output_size = 100352;
    layer.input_dim[0] = 28;
    layer.input_dim[1] = 28;
    layer.input_dim[2] = 32;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 14;
    layer.output_dim[1] = 14;
    layer.output_dim[2] = 256;
    layer.output_dim_size = 3;
    layer.is_output = false;
    layer.is_f32_output = false;
    layer.is_input_hw_layout = true;
}//end of  Layer_8

//Layer_9: Convolution Layer
//  ->: fire6/squeeze1x1
//  ->: fire6/relu_squeeze1x1
void CKerasSqueezeNet::Layer_9()
{
    struct top_conv_conf& _conf = get_conv_layer(9);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 14; // Input Width
    _conf.hw.input.h = 14; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 256; // Input Channels
    _conf.hw.input.input_base_addr = 0x0000C400; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 14; // Output Width
    _conf.sw.output.h = 14; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 48; // Output Channels
    _conf.hw.output.output_base_addr = 0x00000000; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode =0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: fire6/squeeze1x1
    //->: fire6/relu_squeeze1x1
    _conf.sw.run[0].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 256; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 48; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 1; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x00024AC0; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 14432; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
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

    struct fpga_layer& layer = layers[9];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x0000C400;
    layer.addr_offset_output = 0x00000000;
    layer.output_size = 18816;
    layer.input_dim[0] = 14;
    layer.input_dim[1] = 14;
    layer.input_dim[2] = 256;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 14;
    layer.output_dim[1] = 14;
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
void CKerasSqueezeNet::Layer_10()
{
    struct top_conv_conf& _conf = get_conv_layer(10);
    //Topo: 00000000000000000000000000000011
    _conf.hw.header.topo = 0x3; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 14; // Input Width
    _conf.hw.input.h = 14; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 48; // Input Channels
    _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 14; // Output Width
    _conf.sw.output.h = 14; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 384; // Output Channels
    _conf.hw.output.output_base_addr = 0x00004980; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode =0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->2 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: fire6/expand1x1
    //->: fire6/relu_expand1x1
    _conf.sw.run[0].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 48; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 192; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 1; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x00028320; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 14720; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
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
    //--------------------------------------------------
    //RUN : 1
    //--------------------------------------------------
    //->: fire6/expand3x3
    //->: fire6/relu_expand3x3
    _conf.sw.run[1].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[1].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[1].in_c = 48; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[1].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[1].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[1].m = 192; // Output Channels
    _conf.hw.run[1].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[1].p = 3; // Filter Width and Height
    _conf.hw.run[1].pz = 1; // Filter Depth
    _conf.hw.run[1].weight_base_addr = 0x0002BCA0; // Filter Weight and Bias byte address
    _conf.hw.run[1].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[1].weight_size = 83840; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[1].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[1].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[1].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[1].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[1].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[1].pool_stride =0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[1].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[1].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
    _conf.hw.run[1].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU
    _conf.hw.run[1].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
    _conf.hw.run[1].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
    _conf.hw.run[1].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
    _conf.hw.run[1].ALIGN_0 = 0;//Some comments needed here

    struct fpga_layer& layer = layers[10];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x00000000;
    layer.addr_offset_output = 0x00004980;
    layer.output_size = 150528;
    layer.input_dim[0] = 14;
    layer.input_dim[1] = 14;
    layer.input_dim[2] = 48;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 14;
    layer.output_dim[1] = 14;
    layer.output_dim[2] = 384;
    layer.output_dim_size = 3;
    layer.is_output = false;
    layer.is_f32_output = false;
    layer.is_input_hw_layout = true;
}//end of  Layer_10

//Layer_11: Convolution Layer
//  ->: fire7/squeeze1x1
//  ->: fire7/relu_squeeze1x1
void CKerasSqueezeNet::Layer_11()
{
    struct top_conv_conf& _conf = get_conv_layer(11);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 14; // Input Width
    _conf.hw.input.h = 14; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 384; // Input Channels
    _conf.hw.input.input_base_addr = 0x00004980; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 14; // Output Width
    _conf.sw.output.h = 14; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 48; // Output Channels
    _conf.hw.output.output_base_addr = 0x00000000; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode =0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: fire7/squeeze1x1
    //->: fire7/relu_squeeze1x1
    _conf.sw.run[0].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 384; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 48; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 1; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x00040420; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 21344; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
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

    struct fpga_layer& layer = layers[11];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x00004980;
    layer.addr_offset_output = 0x00000000;
    layer.output_size = 18816;
    layer.input_dim[0] = 14;
    layer.input_dim[1] = 14;
    layer.input_dim[2] = 384;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 14;
    layer.output_dim[1] = 14;
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
void CKerasSqueezeNet::Layer_12()
{
    struct top_conv_conf& _conf = get_conv_layer(12);
    //Topo: 00000000000000000000000000000011
    _conf.hw.header.topo = 0x3; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 14; // Input Width
    _conf.hw.input.h = 14; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 48; // Input Channels
    _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 14; // Output Width
    _conf.sw.output.h = 14; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 384; // Output Channels
    _conf.hw.output.output_base_addr = 0x00004980; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode =0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->2 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: fire7/expand1x1
    //->: fire7/relu_expand1x1
    _conf.sw.run[0].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 48; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 192; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 1; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x00045780; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 14720; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
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
    //--------------------------------------------------
    //RUN : 1
    //--------------------------------------------------
    //->: fire7/expand3x3
    //->: fire7/relu_expand3x3
    _conf.sw.run[1].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[1].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[1].in_c = 48; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[1].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[1].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[1].m = 192; // Output Channels
    _conf.hw.run[1].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[1].p = 3; // Filter Width and Height
    _conf.hw.run[1].pz = 1; // Filter Depth
    _conf.hw.run[1].weight_base_addr = 0x00049100; // Filter Weight and Bias byte address
    _conf.hw.run[1].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[1].weight_size = 83840; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[1].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[1].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[1].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[1].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[1].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[1].pool_stride =0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[1].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[1].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
    _conf.hw.run[1].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU
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
    layer.addr_offset_output = 0x00004980;
    layer.output_size = 150528;
    layer.input_dim[0] = 14;
    layer.input_dim[1] = 14;
    layer.input_dim[2] = 48;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 14;
    layer.output_dim[1] = 14;
    layer.output_dim[2] = 384;
    layer.output_dim_size = 3;
    layer.is_output = false;
    layer.is_f32_output = false;
    layer.is_input_hw_layout = true;
}//end of  Layer_12

//Layer_13: Convolution Layer
//  ->: fire8/squeeze1x1
//  ->: fire8/relu_squeeze1x1
void CKerasSqueezeNet::Layer_13()
{
    struct top_conv_conf& _conf = get_conv_layer(13);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 14; // Input Width
    _conf.hw.input.h = 14; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 384; // Input Channels
    _conf.hw.input.input_base_addr = 0x00004980; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 14; // Output Width
    _conf.sw.output.h = 14; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 64; // Output Channels
    _conf.hw.output.output_base_addr = 0x00029580; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode =0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: fire8/squeeze1x1
    //->: fire8/relu_squeeze1x1
    _conf.sw.run[0].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 384; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 64; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 1; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x0005D880; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 28288; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
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

    struct fpga_layer& layer = layers[13];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x00004980;
    layer.addr_offset_output = 0x00029580;
    layer.output_size = 25088;
    layer.input_dim[0] = 14;
    layer.input_dim[1] = 14;
    layer.input_dim[2] = 384;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 14;
    layer.output_dim[1] = 14;
    layer.output_dim[2] = 64;
    layer.output_dim_size = 3;
    layer.is_output = false;
    layer.is_f32_output = false;
    layer.is_input_hw_layout = true;
}//end of  Layer_13

//Layer_14: Convolution Layer
//  ->: fire8/expand1x1
//  ->: fire8/relu_expand1x1
//  ->: fire8/expand3x3
//  ->: fire8/relu_expand3x3
void CKerasSqueezeNet::Layer_14()
{
    struct top_conv_conf& _conf = get_conv_layer(14);
    //Topo: 00000000000000000000000000000011
    _conf.hw.header.topo = 0x3; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 14; // Input Width
    _conf.hw.input.h = 14; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 64; // Input Channels
    _conf.hw.input.input_base_addr = 0x00029580; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 14; // Output Width
    _conf.sw.output.h = 14; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 512; // Output Channels
    _conf.hw.output.output_base_addr = 0x0002F780; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode =0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->2 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: fire8/expand1x1
    //->: fire8/relu_expand1x1
    _conf.sw.run[0].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 64; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 256; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 1; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x00064700; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 19456; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
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
    //--------------------------------------------------
    //RUN : 1
    //--------------------------------------------------
    //->: fire8/expand3x3
    //->: fire8/relu_expand3x3
    _conf.sw.run[1].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[1].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[1].in_c = 64; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[1].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[1].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[1].m = 256; // Output Channels
    _conf.hw.run[1].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[1].p = 3; // Filter Width and Height
    _conf.hw.run[1].pz = 1; // Filter Depth
    _conf.hw.run[1].weight_base_addr = 0x00069300; // Filter Weight and Bias byte address
    _conf.hw.run[1].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[1].weight_size = 148480; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[1].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[1].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[1].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[1].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[1].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[1].pool_stride =0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[1].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[1].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
    _conf.hw.run[1].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU
    _conf.hw.run[1].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
    _conf.hw.run[1].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
    _conf.hw.run[1].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
    _conf.hw.run[1].ALIGN_0 = 0;//Some comments needed here

    struct fpga_layer& layer = layers[14];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x00029580;
    layer.addr_offset_output = 0x0002F780;
    layer.output_size = 200704;
    layer.input_dim[0] = 14;
    layer.input_dim[1] = 14;
    layer.input_dim[2] = 64;
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
//  ->: fire9/squeeze1x1
//  ->: fire9/relu_squeeze1x1
void CKerasSqueezeNet::Layer_15()
{
    struct top_conv_conf& _conf = get_conv_layer(15);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 14; // Input Width
    _conf.hw.input.h = 14; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 512; // Input Channels
    _conf.hw.input.input_base_addr = 0x0002F780; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 14; // Output Width
    _conf.sw.output.h = 14; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 64; // Output Channels
    _conf.hw.output.output_base_addr = 0x00000000; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode =0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: fire9/squeeze1x1
    //->: fire9/relu_squeeze1x1
    _conf.sw.run[0].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 512; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 64; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 1; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x0008D700; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 37504; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
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

    struct fpga_layer& layer = layers[15];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x0002F780;
    layer.addr_offset_output = 0x00000000;
    layer.output_size = 25088;
    layer.input_dim[0] = 14;
    layer.input_dim[1] = 14;
    layer.input_dim[2] = 512;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 14;
    layer.output_dim[1] = 14;
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
void CKerasSqueezeNet::Layer_16()
{
    struct top_conv_conf& _conf = get_conv_layer(16);
    //Topo: 00000000000000000000000000000011
    _conf.hw.header.topo = 0x3; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 14; // Input Width
    _conf.hw.input.h = 14; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 64; // Input Channels
    _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 14; // Output Width
    _conf.sw.output.h = 14; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 512; // Output Channels
    _conf.hw.output.output_base_addr = 0x00006200; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode =0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->2 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: fire9/expand1x1
    //->: fire9/relu_expand1x1
    _conf.sw.run[0].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 64; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 256; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 1; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x00096980; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 19456; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
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
    //--------------------------------------------------
    //RUN : 1
    //--------------------------------------------------
    //->: fire9/expand3x3
    //->: fire9/relu_expand3x3
    _conf.sw.run[1].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[1].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[1].in_c = 64; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[1].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[1].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[1].m = 256; // Output Channels
    _conf.hw.run[1].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[1].p = 3; // Filter Width and Height
    _conf.hw.run[1].pz = 1; // Filter Depth
    _conf.hw.run[1].weight_base_addr = 0x0009B580; // Filter Weight and Bias byte address
    _conf.hw.run[1].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[1].weight_size = 148480; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[1].conv_pad = 0x1010101; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[1].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[1].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[1].pool_enable = 0;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[1].pool_size = 0x0; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[1].pool_stride =0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[1].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[1].pool_avg_param = 0x0; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
    _conf.hw.run[1].actfunc = 2; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU
    _conf.hw.run[1].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
    _conf.hw.run[1].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
    _conf.hw.run[1].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
    _conf.hw.run[1].ALIGN_0 = 0;//Some comments needed here

    struct fpga_layer& layer = layers[16];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x00000000;
    layer.addr_offset_output = 0x00006200;
    layer.output_size = 200704;
    layer.input_dim[0] = 14;
    layer.input_dim[1] = 14;
    layer.input_dim[2] = 64;
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
//  ->: conv10
//  ->: relu_conv10
void CKerasSqueezeNet::Layer_17()
{
    struct top_conv_conf& _conf = get_conv_layer(17);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 14; // Input Width
    _conf.hw.input.h = 14; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 512; // Input Channels
    _conf.hw.input.input_base_addr = 0x00006200; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 14; // Output Width
    _conf.sw.output.h = 14; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 1000; // Output Channels
    _conf.hw.output.output_base_addr = 0x00037200; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode =0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: conv10
    //->: relu_conv10
    _conf.sw.run[0].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 512; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 14; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 14; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 1000; // Output Channels
    _conf.hw.run[0].conv_enable = 1; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 1; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x000BF980; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 3; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 578512; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
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

    struct fpga_layer& layer = layers[17];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x00006200;
    layer.addr_offset_output = 0x00037200;
    layer.output_size = 392000;
    layer.input_dim[0] = 14;
    layer.input_dim[1] = 14;
    layer.input_dim[2] = 512;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 14;
    layer.output_dim[1] = 14;
    layer.output_dim[2] = 1000;
    layer.output_dim_size = 3;
    layer.is_output = false;
    layer.is_f32_output = false;
    layer.is_input_hw_layout = true;
}//end of  Layer_17

//Layer_18: Convolution Layer
//  ->: global_average_pooling2d_1_7
void CKerasSqueezeNet::Layer_18()
{
    struct top_conv_conf& _conf = get_conv_layer(18);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 14; // Input Width
    _conf.hw.input.h = 14; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 1000; // Input Channels
    _conf.hw.input.input_base_addr = 0x00037200; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 2; // Output Width
    _conf.sw.output.h = 2; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 1000; // Output Channels
    _conf.hw.output.output_base_addr = 0x00000000; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode =0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: global_average_pooling2d_1_7
    _conf.sw.run[0].in_w = 14; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 14; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 1000; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 2; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 2; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 1000; // Output Channels
    _conf.hw.run[0].conv_enable = 0; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 1; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x0014CD50; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 0; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 0; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[0].pool_enable = 2;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[0].pool_size = 0x707; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[0].pool_stride =0x707; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].pool_avg_param = 0x2539; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
    _conf.hw.run[0].actfunc = 0; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU
    _conf.hw.run[0].actfunc_param = 0x0; // Leaky ReLU parameter (NOTE: 0x2E66 is 0.1 in FP16)
    _conf.hw.run[0].rectifi_en = 0; // Rectification, i.e. max(0, x) (NOTE: Can be applied after non-ReLU activation function)
    _conf.hw.run[0].lrn= 0x0; // [0] : 1 = LRN enable, 0 = LRN disable, [1] : 1 = incl. power func, 0 = excl., [8:11] = x^2 scale factor log2
    _conf.hw.run[0].ALIGN_0 = 0;//Some comments needed here

    struct fpga_layer& layer = layers[18];
    layer.type = LT_CONV;
    layer.hw_conf = (void*)&_conf;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x00037200;
    layer.addr_offset_output = 0x00000000;
    layer.output_size = 8000;
    layer.input_dim[0] = 14;
    layer.input_dim[1] = 14;
    layer.input_dim[2] = 1000;
    layer.input_dim_size = 3;
    layer.output_dim[0] = 2;
    layer.output_dim[1] = 2;
    layer.output_dim[2] = 1000;
    layer.output_dim_size = 3;
    layer.is_output = false;
    layer.is_f32_output = false;
    layer.is_input_hw_layout = true;
}//end of  Layer_18

//Layer_19: Convolution Layer
//  ->: global_average_pooling2d_1_2
void CKerasSqueezeNet::Layer_19()
{
    struct top_conv_conf& _conf = get_conv_layer(19);
    //Topo: 00000000000000000000000000000001
    _conf.hw.header.topo = 0x1; // [31:0] Output Destination of each run, 0 = UBUF, 1 = EXTMEM

    //Input Configuration:
    _conf.hw.input.w = 2; // Input Width
    _conf.hw.input.h = 2; // Input Height
    _conf.hw.input.z = 1; // Input Depth
    _conf.hw.input.c = 1000; // Input Channels
    _conf.hw.input.input_base_addr = 0x00000000; // Input byte address
    _conf.hw.input.tiles = 1; // Number of horizontal tiles (supported with restrictions)

    //Output Configuration:
    _conf.sw.output.w = 1; // Output Width
    _conf.sw.output.h = 1; // Output Height
    _conf.sw.output.z = 1; // Output Depth
    _conf.sw.output.m = 1000; // Output Channels
    _conf.hw.output.output_base_addr = 0x00001F40; // Output byte address
    _conf.hw.output.eltwise_base_addr = 0xDEADBEEF; // Input byte address for elementwise add (0 = UBUF Input Buffer)
    _conf.hw.output.output_mode =0; // 0 = concat, 1 = eltwise add

    //Runs Configuration:
    //->1 run(s)
    //--------------------------------------------------
    //RUN : 0
    //--------------------------------------------------
    //->: global_average_pooling2d_1_2
    _conf.sw.run[0].in_w = 2; // Optional: Input width (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_h = 2; // Optional: Input height (not used by HW - discovered on the fly)
    _conf.sw.run[0].in_c = 1000; // Optional: Input Channels (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_w = 1; // Optional: Output width (not used by HW - discovered on the fly)
    _conf.sw.run[0].out_h = 1; // Optional: Output height (not used by HW - discovered on the fly)
    _conf.hw.run[0].m = 1000; // Output Channels
    _conf.hw.run[0].conv_enable = 0; // 1 = Enabled, 0 = Disabled
    _conf.hw.run[0].p = 1; // Filter Width and Height
    _conf.hw.run[0].pz = 1; // Filter Depth
    _conf.hw.run[0].weight_base_addr = 0x0014CD50; // Filter Weight and Bias byte address
    _conf.hw.run[0].weight_fmt = 0; // Weight format (0 = random access blocks, 1 = compact stream, 3 = 8-bit qunatized stream)
    _conf.sw.run[0].weight_size = 0; // Actual size in bytes of LUT, weights and bias (in bytes)
    _conf.hw.run[0].conv_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].conv_stride = 0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].conv_dilation = 0x0; // bits [7:0] = X dilation, bits [15:8] = Y dilation
    _conf.hw.run[0].pool_enable = 2;  // 0 = disabled, 1 = max pooling, 2 = average pooling
    _conf.hw.run[0].pool_size = 0x202; // bits [7:0] = width, bits [15:8] = height
    _conf.hw.run[0].pool_stride =0x101; // bits [7:0] = X stride, bits [15:8] = Y stride
    _conf.hw.run[0].pool_pad = 0x0; // bits [7:0] = left padding, bits [15:8] = right padding, bits [23:16] = top padding, bits [31:24] = bottom padding
    _conf.hw.run[0].pool_avg_param = 0x3400; // Must be set to 1/pool_size^2 in FP16 format when using average pooling (average pooling assumes square size)
    _conf.hw.run[0].actfunc = 0; // Activation Function: 0 = None, 1 = Tanh, 2 = Leaky ReLU
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
    layer.addr_offset_output = 0x00001F40;
    layer.output_size = 2000;
    layer.input_dim[0] = 2;
    layer.input_dim[1] = 2;
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
//	->: loss
void CKerasSqueezeNet::Layer_20()
{
    struct fpga_layer& layer = layers[20];
    layer.type = LT_SOFTMAX;
    layer.hw_conf = (void*)0;
    layer.addr_cpu_input = 0x0;
    layer.addr_cpu_output = 0x0;
    layer.addr_offset_input = 0x00001F40;
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

