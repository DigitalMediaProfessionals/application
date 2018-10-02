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

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/input.h>
#include <sys/inotify.h>
#include "util_draw.h"

using namespace std;

struct mouse_pos{
	int x; // pixel
	int y; // pixel
	int w;
};

struct mouse_infor{
	struct mouse_pos cur;
	struct mouse_pos l_press, l_release; //position that left button press and release
	struct mouse_pos m_press, m_release; //position that wheel press and release
	struct mouse_pos r_press, r_release; //position that right button press and release
	bool l_pressed, m_pressed, r_pressed; // true = pressed and false = released
};

struct box{
	int x1;
	int y1;
	int x2;
	int y2;
};

void mouse_config(unsigned int m_refresh_rate, unsigned int m_resolution);

void screen_config(unsigned int screen_width, unsigned int screen_height, unsigned int screen_resolution);

void mouse_init(mouse_infor &mouse_infor, unsigned int mousex, unsigned int mousey);

void set_mouse_event( char *me);

int mouse_open();

int mouse_close();

int mouse_read(mouse_infor &m_infor);

int mouse2pointer(signed int virtual_count);

/*int mouseCursor2bitmap(unsigned int* b, unsigned int fcol,unsigned int bcol, int x, int y);

void printCursor_toDisplay(int x, int y, unsigned int fcol, unsigned int bcol);

void set_color2background_image(unsigned int fcol);

void create_button(box &button, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);

void draw_button2background_image( box button, unsigned int fcol);

bool button_is_pressed( mouse_infor m, box bt);*/













