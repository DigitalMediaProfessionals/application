/*
*------------------------------------------------------------
* Copyright(c) 2017 by Digital Media Professionals Inc.
* All rights reserved.
*------------------------------------------------------------
* This source code was generated using DMP-DV700 tools
* Digital Media Professionals Inc.
*------------------------------------------------------------
*/

#ifndef __DRAW_UTIL
#define __DRAW_UTIL

#include <stdlib.h>
#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>


namespace dmp {
namespace util {



	/*! Set size for displaying images during processing. Typically, this is the size of the network input. Allocate corresponding memory buffer.
	*/
    void set_inputImageSize(unsigned w, unsigned int h);
	/*! Set the size of the background image. Typically, 1280x720. Allocate corresponding memory buffer.
	*/
    void createBackgroundImage(int screen_w, int screen_h);

	/*! Delete (free memory) the memory allocated during createBackgroundImage call
	*/
   void deleteBackgroundImage();


	/*! Given a filename, load a an image to the memory allocatted by  createBackgroundImage. The image must be ppm format.
		<B>NOTE:</B> This function will change in future (different image format, merge with createBackgroundImage etc..)
	*/
    bool load_background_image(std::string filename);


	/*! Actual display of the background image.
	*/
      void print_background_image_toDisplay();

	/*! Actual display of the image. The img is copied to the memory allocated by set_inputImageSize and then displayed.
	*/
    void print_image_toDisplay(int x, int y, unsigned int* img, int crop_left = 0);

	/*! Utility function for drawing a box to img.
	* @param[in] x Lower left corner X coordinate
	* @param[in] y Lower left corner Y coordinate
	* @param[in] w width of the box
	* @param[in] h height of the box
	* @param[in] fcol RGB color of the box
	* @param[in,out] img pointer to a 32 bit image, of size defined by set_inputImageSize
	*/
    void draw_box(int x, int y, int w, int h, unsigned int fcol, unsigned int* img);

    /*! Utility function for converting a string to a bitmap. Font size is fixed as 8x8. Should not be called directly from application.
	* @param[in] s string to be converted
	* @param[in] bcol RGB color of the background. If first bif (bcol&0x1) is true, the actual background image color is used (alpha blending)
	* @param[in] fcol RGB color of the text
	* @param[in] x coordinate referring to the background image. Used if (bcol&0x1) is true
	* @param[in] y coordinate referring to the background image. Used if (bcol&0x1) is true
	* @param[in,out] b allocated memory (8xSCREEN_WIDTH), allocated during initialization
	*/
    int string2bitmap(std::string s, unsigned int* b, unsigned int fcol, unsigned int bcol, int x, int y);

    /*! Utility function for converting a string to a bitmap. Font size is fixed as 8x8. Should not be called directly from application. Difference with string2bitmap is not clear as of today and shall be fixed
	* @param[in] s string to be converted
	* @param[in] bcol RGB color of the background. If first bif (bcol&0x1) is true, the actual background image color is used (alpha blending)
	* @param[in] fcol RGB color of the text
	* @param[in] x coordinate referring to the background image. Used if (bcol&0x1) is true
	* @param[in] y coordinate referring to the background image. Used if (bcol&0x1) is true
	* @param[in,out] b allocated memory (8xSCREEN_WIDTH), allocated during initialization
	*/
	int string2bitmap_xy(std::string s, unsigned int* b, unsigned int fcol, unsigned int bcol, int x, int y);

  /*! Utility function for converting  a string to a bitmap. Font size is fixed as 8x8. Should not be called directly from application. Difference with string2bitmap is not clear as of today and shall be fixed
	* @param[in] s string to be converted
	* @param[in] bcol RGB color of the background. If first bif (bcol&0x1) is true, the actual background image color is used (alpha blending)
	* @param[in] fcol RGB color of the text
	* @param[in] x coordinate referring to the background image. Used if (bcol&0x1) is true
	* @param[in] y coordinate referring to the background image. Used if (bcol&0x1) is true
	* @param[in] img pointer to a 32 bit image, of size defined by set_inputImageSize
	* @param[in,out] b allocated memory (8xSCREEN_WIDTH), allocated during initialization
	*/
    int string2bitmap_bbox(std::string s, unsigned int* b, unsigned int fcol, unsigned int bcol, int x, int y, unsigned int* img);


      /*! Utility function for a string to a bitmap. Font size is fixed as 8x8.
	* @param[in] s string to be converted
	* @param[in] fcol RGB color of the text
	* @param[in] x coordinate
	* @param[in] y coordinate
	* @param[in,out] img pointer to a 32 bit image, of size defined by set_inputImageSize
	*/
	void draw_box_text(int x, int y, std::string s, unsigned int fcol, unsigned int* img);

    /*! Utility function for drawing a progress bar. Not complete yet / under development

	*/
	void draw_progress_bar(int x, int y, int w, int h, int fcol, int bcol, int steps, int prog);

	  /*! Utility function for writing a string to the background image. Font size is fixed as 8x8. Should not be called directly from application.
	* @param[in] s string to be converted
	* @param[in] fcol RGB color of the text
	* @param[in] bcol RGB color of the text backgournd. If (bcol&0x1) is true, then the background color of the image is used (alpha blending
	* @param[in] x coordinate
	* @param[in] y coordinate
	*/
    void print_xy(int x, int y, std::string s, unsigned int fcol, unsigned int bcol);

	 /*! Utility function for converting  a string to a bitmap. Font size is fixed as 16x16. Should not be called directly from application.
	* @param[in] s string to be converted
	* @param[in] bcol RGB color of the background. If first bif (bcol&0x1) is true, the actual background image color is used (alpha blending)
	* @param[in] fcol RGB color of the text
	* @param[in] x coordinate referring to the background image. Used if (bcol&0x1) is true
	* @param[in] y coordinate referring to the background image. Used if (bcol&0x1) is true
	* @param[in,out] b allocated memory (16xSCREEN_WIDTH), allocated during initialization
	*/
	int string2bitmap16x16(std::string s, unsigned int* b, unsigned int fcol, unsigned int bcol, int x, int y);

	/*! Utility function for converting  a string to a bitmap. Font size is fixed as 16x24. Should not be called directly from application.
	* @param[in] s string to be converted
	* @param[in] bcol RGB color of the background. If first bif (bcol&0x1) is true, the actual background image color is used (alpha blending)
	* @param[in] fcol RGB color of the text
	* @param[in] x coordinate referring to the background image. Used if (bcol&0x1) is true
	* @param[in] y coordinate referring to the background image. Used if (bcol&0x1) is true
	* @param[in,out] b allocated memory (24xSCREEN_WIDTH), allocated during initialization
	*/
    int string2bitmap16x24(std::string s, unsigned int* b, unsigned int fcol, unsigned int bcol, int x, int y);

	/*! Utility function for converting  a string to a bitmap. Font size is fixed as 24x48. Should not be called directly from application.
	* @param[in] s string to be converted
	* @param[in] bcol RGB color of the background. If first bif (bcol&0x1) is true, the actual background image color is used (alpha blending)
	* @param[in] fcol RGB color of the text
	* @param[in] x coordinate referring to the background image. Used if (bcol&0x1) is true
	* @param[in] y coordinate referring to the background image. Used if (bcol&0x1) is true
	* @param[in,out] b allocated memory (48xSCREEN_WIDTH), allocated during initialization
	*/
    int string2bitmap24x48(std::string s, unsigned int* b, unsigned int fcol, unsigned int bcol, int x, int y);

    /*! Utility function for writing directly to display memory a string using a 8x8 font
	* @param[in] x coordinate.
	* @param[in] y coordinate.
	* @param[in] s string to be converted
	* @param[in] fcol RGB color of the text
	* @param[in] bcol RGB color of the background.
	*/
    void print8x8_toDisplay(int x, int y, std::string s, unsigned int fcol, unsigned int bcol);

   /*! Utility function for writing directly to display memory a string using a 16x16 font
	* @param[in] x coordinate.
	* @param[in] y coordinate.
	* @param[in] s string to be converted
	* @param[in] fcol RGB color of the text
	* @param[in] bcol RGB color of the background.
	*/
    void print16x16_toDisplay(int x, int y, std::string s, unsigned int fcol, unsigned int bcol);

	  /*! Utility function for writing directly to display memory a string using a 16x24 font
	* @param[in] x coordinate.
	* @param[in] y coordinate.
	* @param[in] s string to be converted
	* @param[in] fcol RGB color of the text
	* @param[in] bcol RGB color of the background.
	*/
   void print16x24_toDisplay(	int x, int y, std::string s, unsigned int fcol, unsigned int bcol);

	  /*! Utility function for writing directly to display memory a string using a 24x48 font
	* @param[in] x coordinate.
	* @param[in] y coordinate.
	* @param[in] s string to be converted
	* @param[in] fcol RGB color of the text
	* @param[in] bcol RGB color of the background.
	*/
   void print24x48_toDisplay(int x, int y, std::string s, unsigned int fcol, unsigned int bcol);


       /*! Utility function for writing label and  time to display memory using  a 16x16 font. The time is converted to ms autoatically, with 3 digits
	* @param[in] x coordinate.
	* @param[in] y coordinate.
	* @param[in] label Text to be written.
	* @param[in] t time
	* @param[in] t_max unused
	* @param[in] fcol RGB color of the text.
	* @param[in] bcol RGB background color of the text.
	*/
    void print_time_toDisplay(int x, int y, std::string label, long int t, long int t_max, unsigned int fcol, unsigned int bcol);

	void capture_screen(std::string filename);

}; //end of namespace util
}; //end of namespace dmp

#endif //__DRAW_UTIL
