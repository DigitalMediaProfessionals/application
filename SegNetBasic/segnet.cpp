
#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sys/time.h>
#include <limits>


#include "util_input.h"
#include "util_draw.h"
#include "SegNetBasic_gen.h"
CSegNetBasic  network;

#define FILENAME_WEIGHTS "SegNetBasic_weights.bin"

using namespace std;

#define SCREEN_W 1280
#define SCREEN_H 720

#define IMAGE_W 320
#define IMAGE_H 240
#define IMAGE_NUM 367
#define CLASS_NUM 12

#define TEXT_XOFS (((SCREEN_W - IMAGE_W) / 2) / 24 + 4) // 8x8 characters
#define TEXT_YOFS ((512 + 48) / 8 + 2 + 3 + 2) // 8x8 characters

unsigned int imgView[IMAGE_W * IMAGE_H];
unsigned short imgProc[IMAGE_W * IMAGE_H * 3];

unsigned int fc = 0;

// 2ND THREAD FOR HW CONTROL

volatile uint64_t sync_cnn_in = 0;
volatile uint64_t sync_cnn_out = 0;

volatile int conv_time_tot = 0;
volatile int ip_time_tot = 0;

#if 0
const unsigned int class_color[] = {
	0x80FFFF00,		//Sky
	0x80808000,		//Bulding
	0xC0C08000,		//Pole
	0x80408000,		//Road
	0x4030C000,		//Pavement
	0x00C00000,		//Tree
	0xC0808000,		//Sign_symbol
	0x40408000,		//Fence
	0xC0008000,		//Car
	0x40400000,		//Pedestrian
	0x0080C000,		//Bicyclist
	0x00000000,		//Unlabelled
};
#else
const unsigned int class_color[] = {
	0x40808000,		//Sky
	0x40404000,		//Bulding
	0x60604000,		//Pole
	0x40204000,		//Road
	0x40204000,		//Pavement
	0x00600000,		//Tree
	0x60404000,		//Sign_symbol
	0x20204000,		//Fence
	0x60004000,		//Car
	0x00406000,		//Pedestrian
	0x00406000,		//Bicyclist
	0x00000000,		//Unlabelled
};
#endif

void convertimage(unsigned short *imgProc, unsigned int *imgView)
{
	unsigned char c[3];
	unsigned short t;
	for (int y = 0; y < IMAGE_H; y++)
	{
		for (int x = 0; x < IMAGE_W; x++)
		{
			for (int i = 0; i < 3; i++)
			{
				t = imgProc[(x * IMAGE_H + y) * 3 + i];
				c[i] = ((t & 0x3FF) + 0x400) >> (26 - ((t & 0xFC00) >> 10));
			}
			imgView[y * IMAGE_W + x] = (c[2] << 25) | (c[1] << 17) | (c[0] << 9);
		}
	}
}

void visualize(void *netoutCPU, unsigned int *imgView)
{
	short *networkOutput = reinterpret_cast<short*>(netoutCPU);
	for (int y = 0; y < IMAGE_H; y++)
	{
		for (int x = 0; x < IMAGE_W; x++)
		{
			int maxIndex = 0;
			short maxVal = networkOutput[(y * IMAGE_W + x) * CLASS_NUM];
			for (int i = 1; i < CLASS_NUM; i++)
			{
				if (networkOutput[(y * IMAGE_W + x) * CLASS_NUM + i] > maxVal)
				{
					maxVal = networkOutput[(y * IMAGE_W + x) * CLASS_NUM + i];
					maxIndex = i;
				}
			}
			imgView[y * IMAGE_W + x] = (imgView[y * IMAGE_W + x] >> 1) + class_color[maxIndex];
		}
	}
}

void* hwacc_thread_func(void* targ)
{

    while (true) {

        while (sync_cnn_in == sync_cnn_out) {
            usleep(1000); // sleep 1 ms
        }

        network.run_network();

        conv_time_tot = network.get_convolution_performance(); // time_diff(&t1, &t2);
        ip_time_tot = network.get_innerproduct_performance();

        sync_cnn_out++;
    }

    return NULL; // will never reach here but this removes compiler warning...
}

int main(int argc, char** argv)
{
    const char input_image_file[] = "segnet_image.bin";
	FILE *fimg = fopen(input_image_file, "r");

    vector<float> networkOutput;

    int my_number = 0;
    bool has_democonf = false;
    if (argc >= 2) {
        my_number = atoi(argv[1]);
        has_democonf = true;
    }
    vector<pair<int, string> > democonf;
    int democonf_sel = 0; // currencly selected element index (0 .. num-1)
    int democonf_num = 0; // number of elements in democonf
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
            if (c_int == my_number)
                democonf_sel = count;
            count++;
        }
        democonf_num = count;
    }

    dmp::util::set_inputImageSize(IMAGE_W, IMAGE_H);
    dmp::util::createBackgroundImage(SCREEN_W, SCREEN_H);

    if (!dmp::util::load_background_image("fpgatitle_yolo.ppm"))
        return 1;

    dmp::modules::initialize();

    string conv_freq, fc_freq;
    unsigned int conv_freq_int, fc_freq_int;
    dmp::modules::get_info(dmp::modules::FREQ_CONV, &conv_freq_int);
    dmp::modules::get_info(dmp::modules::FREQ_FC, &fc_freq_int);
    conv_freq = to_string(conv_freq_int);
    fc_freq = to_string(fc_freq_int);

    network.verbose(true);
    network.initialize();
    network.reserve_memory();
    network.load_weights(FILENAME_WEIGHTS);

    void *ddr_buf_a_cpu = network.get_network_input_addr_cpu();
	void *ddr_buf_b_cpu = network.get_layer(15).addr_cpu_output;

    dmp::modules::reset_button_state();

    int exit_code = -1;

    int image_nr = 0;

    bool pause = false;

    pthread_t hwacc_thread;
    pthread_create(&hwacc_thread, NULL, hwacc_thread_func, NULL);

    while (exit_code == -1) {

        // Static Images
        if (fc < 2) {
            dmp::util::print_background_image_toDisplay();
            dmp::modules::swap_buffer();
            fc++; // Frame Counter
            continue;
        }

        // HW processing times
        if (conv_time_tot != 0) {
            dmp::util::print_time_toDisplay(TEXT_XOFS, TEXT_YOFS + 4, "Convolution (" + conv_freq + " MHz HW ACC)     : ", conv_time_tot, 9999, 0xff00ff00, 0x00000001);
        }

        if (sync_cnn_out == sync_cnn_in) {
            if (sync_cnn_out != 0) {
				//network.get_final_output(networkOutput);
				convertimage(imgProc, imgView);
                dmp::util::print_image_toDisplay((SCREEN_W / 2 - IMAGE_W) , (293 - 128) + 20, imgView);
				visualize(ddr_buf_b_cpu, imgView);
                dmp::util::print_image_toDisplay(SCREEN_W / 2, (293 - 128) + 20, imgView);
                dmp::modules::swap_buffer();
                fc++;

                unsigned int button = dmp::modules::get_button_state();
                if (button & 4) { // exit demo with exit code of selected next demo
                    if (has_democonf) {
                        int sel_num = democonf[democonf_sel].first;
                        if (sel_num != my_number)
                            exit_code = sel_num;
                    }
                    else {
                        exit_code = my_number;
                    }
                }
                //exit_code = my_number;
                if (button & 2) { // cycle through demo configuratom list
                    if (has_democonf) {
                        democonf_display = true;
                        if (democonf_sel == democonf_num - 1)
                            democonf_sel = 0;
                        else
                            democonf_sel++;
                    }
                }
                if (button & 1)
                    pause = !pause;
            }

            if (!pause) {
				fseek(fimg, IMAGE_W * IMAGE_H * 6 * image_nr, SEEK_SET);
				fread(imgProc, 2, IMAGE_W * IMAGE_H * 3, fimg);
                if (image_nr == IMAGE_NUM - 1) {
                    image_nr = 0;
                }
                else {
                    image_nr++;
                }
            }

			//Copy image to FPGA memory
            memcpy(ddr_buf_a_cpu, (void*)imgProc, IMAGE_W * IMAGE_H * 3 * 2);

            if (exit_code == -1) // do not start new HW ACC runs if about to exit...
                sync_cnn_in++;
        }

        if (democonf_display) {
            string s = democonf[democonf_sel].second;
            s.resize(democonf_string_max, ' ');
            dmp::util::print8x8_toDisplay((SCREEN_W / 8 - democonf_string_max) / 2, SCREEN_H / 8 - 1, s, 0x00ff0000, 0x00000001);
        }
    }

    dmp::modules::shutdown();

    return exit_code;
}

