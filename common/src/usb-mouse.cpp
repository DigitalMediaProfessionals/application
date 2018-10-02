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

#include <usb-mouse.h>

using namespace dmp;
using namespace util;

static unsigned int SCREEN_RESOLUTION = 96; //DPI
static unsigned int MOUSE_REFRESH_RATE = 125; // Hz
static unsigned int MOUSE_RESOLUTION = 400; //DPI
static unsigned int SCREEN_WIDTH = 1280; //Pixel
static unsigned int SCREEN_HEIGHT = 720; //Pixel

float SmoothMouseXCurve[] = {0.00, 0.43001, 1.25, 3.86001, 40};
float SmoothMouseYCurve[] = {0.00, 1.37, 5.30001, 24.30001, 568};
float residual = 0;

//unsigned int mouse_cursor[42] = { 0x10,0x00,0x18,0x00,0x1C,0x00,0x1E,0x00,0x1F,0x00,0x1F,0x80,0x1F,0xC0,0x1F,0xE0,0x1F,0xF0,0x1F,0xF8,0x1F,0xFC,0x1F,0xFE,0x1F,0xFF,0x1F,0xC0,0x1F,0xC0,0x1C,0xE0,0x18,0x60,0x18,0x60,0x00,0x30,0x00,0x30,0x00,0x30}; //13x21
//unsigned int mouse_cursor[32] = { 0x02,0x00,0x03,0x00,0x03,0x80,0x03,0xC0,0x03,0xE0,0x03,0xF0,0x03,0xF8,0x03,0xFC,0x03,0xFE,0x03,0xFF,0x03,0xE0,0x03,0xB0,0x03,0x30,0x02,0x10,0x00,0x18,0x00,0x18 }; //10x16
unsigned int mouse_cursor[11] = {0x40,0x60,0x70,0x78,0x7C,0x7E,0x7F,0x78,0x68,0x4C,0x04}; //7x11

unsigned int* textbuf11 = NULL;  //[SCREEN_W*11];
//static unsigned int background_color = 0xffffff00;

char default_event[] = "/dev/input/event0";
char default_ename[] = "Unknown";
static int fid = 0;
char *mouse_event = default_event;
char *name = default_ename;

// The events of external devices getting through USB gates are packed into "event" in "/dev/input" folder
// Go to the folder to check which event is the mouse and change the mouse event
void set_mouse_event( char *me){
  mouse_event = me;
}

// Update mouse infor if necessary
void mouse_config(unsigned int m_refresh_rate, unsigned int m_resolution) {
  MOUSE_REFRESH_RATE = m_refresh_rate;
  MOUSE_RESOLUTION = m_resolution;
}

// Update screen infor if necessary
void screen_config(unsigned int screen_width, unsigned int screen_height, unsigned int screen_resolution){
  SCREEN_WIDTH = screen_width;
  SCREEN_HEIGHT = screen_height;
  SCREEN_RESOLUTION = screen_resolution;
}

// Init function for mouse
void mouse_init(mouse_infor &mouse_infor, unsigned int mousex, unsigned int mousey){
  textbuf11 = new unsigned int[SCREEN_WIDTH * 11];
  mouse_infor.cur.x = mousex;
  mouse_infor.cur.y = mousey;
  mouse_infor.l_press.x = 0;
  mouse_infor.l_press.y = 0;
  mouse_infor.m_press.x = 0;
  mouse_infor.m_press.y = 0;
  mouse_infor.r_press.x = 0;
  mouse_infor.r_press.y = 0;
  mouse_infor.l_pressed = false;
  mouse_infor.m_pressed = false;
  mouse_infor.r_pressed = false;
}

// Open mouse event
// Return 0 -> success, 1 -> fail
int mouse_open(){
  // Check whether you have root access to open files in root folders
  if ((getuid ()) != 0){
    printf ("You are not root! Please run the application with sudo");
    return EXIT_FAILURE;
  }
  else {
    // Events from the mouse are packed into a file
    fid = open( mouse_event, O_NONBLOCK);// use O_RDONLY if you want a non-stop reading input event until something is read
    if (fid == 0){
      printf("Could not open %s!\n", mouse_event);
      return EXIT_FAILURE;
    }
    else if (fid == -1){
      printf ("%s is not a valid device!\n", mouse_event);
      return EXIT_FAILURE;
    }

    //Print Device Name
    ioctl (fid, EVIOCGNAME (sizeof (name)), name);
    printf ("%s (%s) is ready to work!\n", mouse_event, name);
  }
  return EXIT_SUCCESS;
}

// Close mouse
// Return 0 --> Success; 1 --> Fail
int mouse_close(){
  if( close(fid) == EXIT_SUCCESS){
    return EXIT_SUCCESS;
  }
  else{
    return EXIT_FAILURE;
  }
}

// Read events that come up in the input file
int mouse_read(mouse_infor &m_infor){ //// Event type from <linux/input.h>
  unsigned int nbytes;
  input_event event;
  nbytes = read(fid, &event, sizeof(event));
  if (nbytes >= sizeof(event)) {
    switch (event.type){
      case EV_KEY:
        switch (event.code){
        case BTN_LEFT:
          m_infor.l_press.x = m_infor.cur.x;
          m_infor.l_press.y = m_infor.cur.y;
          m_infor.l_press.w = m_infor.cur.w;
          if (event.value == 1) {m_infor.l_pressed = true;}
          else{ m_infor.l_pressed = false;}
          break;
        case BTN_RIGHT:
          m_infor.r_press.x = m_infor.cur.x;
          m_infor.r_press.y = m_infor.cur.y;
          m_infor.r_press.w = m_infor.cur.w;
          if (event.value == 1) {m_infor.r_pressed = true;}
          else{ m_infor.r_pressed = false;}
          break;
        case BTN_MIDDLE:
          m_infor.m_press.x = m_infor.cur.x;
          m_infor.m_press.y = m_infor.cur.y;
          m_infor.m_press.w = m_infor.cur.w;
          if (event.value == 1) {m_infor.m_pressed = true;}
          else{ m_infor.m_pressed = false;}
          break;
        }
        break;
      case EV_REL:
        switch (event.code){
        case REL_X:
          m_infor.cur.x += event.value;
          //m_infor.cur.x += mouse2pointer(event.value);
          m_infor.cur.x = m_infor.cur.x < 0 ? 0 : m_infor.cur.x;
          m_infor.cur.x = m_infor.cur.x > static_cast<int>( SCREEN_WIDTH - 1) ? SCREEN_WIDTH - 1: m_infor.cur.x;
          break;
        case REL_Y:
          m_infor.cur.y += event.value;
          //m_infor.cur.y += mouse2pointer(event.value);
          m_infor.cur.y = m_infor.cur.y < 0? 0: m_infor.cur.y;
          m_infor.cur.y = m_infor.cur.y > static_cast<int>( SCREEN_HEIGHT - 1) ? SCREEN_HEIGHT - 1: m_infor.cur.y;
          break;
        case REL_WHEEL:
          m_infor.cur.w += event.value;
          break;
        }
    }
  }
  return nbytes;
}

