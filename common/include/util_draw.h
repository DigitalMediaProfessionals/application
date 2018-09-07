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

#ifndef __DRAW_UTIL
#define __DRAW_UTIL

#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include <string>

#include <cstring>
#include <math.h>
#include "agg_rasterizer_scanline_aa.h"
#include "agg_conv_transform.h"
#include "agg_span_image_filter_rgb.h"
#include "agg_span_image_filter_rgba.h"
#include "agg_pixfmt_rgba.h"
#include "agg_renderer_scanline.h"
#include "agg_scanline_p.h"
#include "agg_scanline_u.h"
#include "agg_rounded_rect.h"
#include "util/agg_color_conv_rgb8.h"
#include "util/agg_color_conv.h"
#include "agg_basics.h"
#include "agg_rendering_buffer.h"
#include "agg_pixfmt_rgb.h"
#include "agg_conv_stroke.h"
#include "agg_gsv_text.h"
#include "agg_embedded_raster_fonts.h"
#include "agg_glyph_raster_bin.h"
#include "agg_renderer_raster_text.h"

using namespace std;

namespace dmp {
namespace util {

typedef agg::rendering_buffer rbuf_type;

class COverlayRGB
{
	private:
    // raw buffer holds overlay
		uint8_t                      *buff_rgb_ = NULL;
    // width of overlay
		uint32_t                     overlay_rgb_width_;
    // height of overlay
		uint32_t                     overlay_rgb_height_;
    // width of screen
		uint32_t                     screen_width_;
    // height of screen
		uint32_t                     screen_height_;
    // bytes of a pixel
		uint32_t                     pixel_size_;
    // render buffer holds overlay
		rbuf_type                         render_buf_overlay_rgb_;

    public:
		/*! Utility constructor to create a overlay with rgb24 color format 
    * then using alloc_mem_overlay() to allocate memory for overlay
		* @param[in] screen_width Width of the screen
		* @param[in] screen_height Height of the screen
		*/
    COverlayRGB(uint32_t screen_width, uint32_t screen_height);

		/*! Utility function to allocate memory for overlay
		* @param[in] overlay_width Width of the overlay
		* @param[in] overlay_height Height of the overlay
		*/
    void alloc_mem_overlay(uint32_t overlay_width, uint32_t overlay_height);

		/*! Utility function to get the width of overlay
		* @return width of overlay
		*/
    uint32_t get_overlay_width(void)
    {
      return overlay_rgb_width_;
    }

		/*! Utility function to get the height of overlay
		* @return height of overlay
		*/
    uint32_t get_overlay_height(void)
		{
			return overlay_rgb_height_;
		}

		/*! Utility function to get overlay buffer reference
		 * which is used to fill data to overlay buffer
		* @return reference to overlay buffer
		*/
    uint8_t* get_overlay_buf_ref(void);

		/*! Utility function to convert from pixel in integer format to overlay rgba32 pixel format
		 * and both must have same (width x height)
		* @param[in] imgview Pointer to buffer of type integer
		* @param[in] size_of_imgview Size of the buffer
		* @return operation is successful or not
		*/
    bool convert_to_overlay_pixel_format(uint32_t *imgview, uint32_t size_of_imgview);

		/*! Utility function to get rendering buffer reference
		 * which is used to fill data to overlay buffer
		* @return reference to rendering buffer
		*/
    rbuf_type& get_ren_buf_ref(void);

		/*! Utility function to get reference to a row of overlay
		 * which is used to fill data to overlay buffer
		* @param[in] row Row need to get reference
		* @return reference to a row of overlay
		*/
    uint8_t* get_overlay_row_ptr_ref(uint32_t row);


		/*! Utility function to set pixel at a specific position with rgba value
		* @param[in] xpos x position
		* @param[in] ypos y position
		* @param[in] red  red value
		* @param[in] green green value
		* @param[in] blue blue value
		* @return operation is successful or not
		*/
    bool set_pixel(uint32_t xpos, uint32_t ypos,
								uint8_t red, uint8_t green, uint8_t blue);

		/*! Utility function to copy an area of another overlay - destination overlay fits in copied area
		* @param[in] source overlay to be copied
		* @param[in] xpos x position that start copying
		* @param[in] ypos  y position that start copying
		* @return operation is successful or not
		*/
    bool copy_overlay(COverlayRGB &src_overlay, uint32_t xpos, uint32_t ypos);

		/*! Utility function to draw box with text, color is argb format
		* @param[in] x0pos top-left x position of box in overlay
		* @param[in] y0pos top-left y position of box in overlay
		* @param[in] x1pos bottom-right x position of box in overlay
		* @param[in] y1pos bottom-right y position of box in overlay
		* @param[in] color color of box
		* @param[in] text text content
		*/
    void set_box_with_text(uint32_t x0pos, uint32_t y0pos, uint32_t x1pos,
        													uint32_t y1pos, uint32_t color, string text);

		/*! Utility function to draw text, color is argb format.
		 * This function depends on calculate_boundary_text()
		* @param[in] x0pos top-left x position of text in overlay
		* @param[in] y0pos top-left y position of text in overlay
		* @param[in] text text content
		* @param[in] text_size size of text
		* @param[in] color color of text
		*/
    void set_text(uint32_t xpos, uint32_t ypos, string text, uint32_t text_size, uint32_t color);

		/*! Utility function to draw box without text, color is argb format
		* @param[in] x0pos top-left x position of box in overlay
		* @param[in] y0pos top-left y position of box in overlay
		* @param[in] x1pos bottom-right x position of box in overlay
		* @param[in] y1pos bottom-right y position of box in overlay
		* @param[in] color color of box
		*/
    void set_box(uint32_t x0pos, uint32_t y0pos,
        						uint32_t x1pos, uint32_t y1pos, uint32_t color);

		/*! Utility function to blend 2 overlays with same size
		* @param[in] overlay overlay to blend
		* @param[in] alpha alpha value
		*/
    void blend_from(COverlayRGB &overlay, double alpha=0.5);

		/*! Utility function to load ppm file and file name without extension
		* @param[in] filename_wo_ext file name without extension
		* @return operation is successful or not
		*/
    bool load_ppm_img(string filename_wo_ext);

		/*! Utility function to save as ppm format and file name without extension
		* @param[in] filename_wo_ext file name without extension
		* @return operation is successful or not
		*/
    bool save_as_ppm_img(string filename_wo_ext);

		/*! Utility function for drawing a progress bar
		* @param[in] x x-position of progress bar in overlay
		* @param[in] y y-position of progress bar in overlay
		* @param[in] w width of progress bar in overlay
		* @param[in] h height of progress bar in overlay
		* @param[in] color color of progress bar
		* @param[in] prog_0_to_100 progress from 0 to 100
		*/
		void draw_progress_bar(uint32_t x, uint32_t y, uint32_t w, uint32_t h,
						uint32_t color, uint8_t prog_0_to_100) ;

		/*! Utility function to print overlay to display
		* @param[in] xpos top-left x position of overlay in display
		* @param[in] ypos top-left y position of overlay in display
		*/
    void print_to_display(uint32_t xpos, uint32_t ypos);

		/*! Utility function to delete a overlay
		*/
    void delete_overlay_rgb();

        /*! destructor to delete a overlay
		*/
    virtual ~COverlayRGB();

		/*! Utility function to convert time to text
		* @param[in] label label of time
		* @param[in] time value to convert
		*/
		static string convert_time_to_text(string label, long int time);

		/*! Utility function to cLCULte boundary of text
		* @param[in] text text content
		* @param[in] text_size size of text
		* @param[out] width width of boundary
		* @param[out] height height of boundary
		*/
		static void calculate_boundary_text(string text, uint32_t text_size,
											uint32_t &width, uint32_t &height);

		/*! Utility function to capture the screen
		*/
		static void capture_screen(std::string filename,
						uint32_t screen_width, uint32_t screen_height);
};

/// @brief Initializes the framebuffer (/dev/fb0).
/// @details If the /dev/tty0 was in text mode, it will be switched to graphics mode
///          and switched back on shutdown(), SIGINT, SIGQUIT or SIGTERM.
bool init_fb();

/// @brief Releases allocated resources if any (closes framebuffer).
void shutdown();

/// @brief Swaps the framebuffer.
bool swap_buffer();

/// @brief Returns framebuffer width in pixels.
uint32_t get_screen_width();

/// @brief Returns framebuffer height in pixels.
uint32_t get_screen_height();

/// @brief Pads the string with spaces to make it centered.
std::string centered(const std::string& original, int targetSize);

void print_result(const std::vector<std::string>& catstr_vec,
                  int x, int y, const std::vector<std::pair<float, int> >& f, COverlayRGB &bg_overlay);

std::vector<std::pair<float, int> > catrank(float* softmax, int count=1000);

/*! Set size for displaying images during processing. Typically, this is the
 * size of the network input. Allocate corresponding memory buffer.
*/
void set_inputImageSize(unsigned w, unsigned int h);

/*! Allocate buffers for the background image.
*/
bool createBackgroundImage();

/*! Delete (free memory) the memory allocated during createBackgroundImage call
*/
void deleteBackgroundImage();

/*! Given a filename, load a an image to the memory allocatted by
   createBackgroundImage. The image must be ppm format.
        <B>NOTE:</B> This function will change in future (different image
   format, merge with createBackgroundImage etc..)
*/
bool load_background_image(std::string filename);

/*! Actual display of the background image.
*/
void print_background_image_toDisplay();

/*! Actual display of the image. The img is copied to the memory allocated by
 * set_inputImageSize and then displayed.
*/
void print_image_toDisplay(int x, int y, unsigned int* img, int crop_left = 0);

/*! Utility function for drawing a box to img.
* @param[in] x Lower left corner X coordinate
* @param[in] y Lower left corner Y coordinate
* @param[in] w width of the box
* @param[in] h height of the box
* @param[in] fcol RGB color of the box
* @param[in,out] img pointer to a 32 bit image, of size defined by
* set_inputImageSize
*/
void draw_box(int x, int y, int w, int h, unsigned int fcol, unsigned int* img);

/*! Utility function for converting a string to a bitmap. Font size is fixed as
 * 8x8. Should not be called directly from application.
    * @param[in] s string to be converted
    * @param[in] bcol RGB color of the background. If first bif (bcol&0x1) is
 * true, the actual background image color is used (alpha blending)
    * @param[in] fcol RGB color of the text
    * @param[in] x coordinate referring to the background image. Used if
 * (bcol&0x1) is true
    * @param[in] y coordinate referring to the background image. Used if
 * (bcol&0x1) is true
    * @param[in,out] b allocated memory (8xSCREEN_WIDTH), allocated during
 * initialization
    */
int string2bitmap(std::string s, unsigned int* b, unsigned int fcol,
                  unsigned int bcol, int x, int y);

/*! Utility function for converting a string to a bitmap. Font size is fixed as
 * 8x8. Should not be called directly from application. Difference with
 * string2bitmap is not clear as of today and shall be fixed
    * @param[in] s string to be converted
    * @param[in] bcol RGB color of the background. If first bif (bcol&0x1) is
 * true, the actual background image color is used (alpha blending)
    * @param[in] fcol RGB color of the text
    * @param[in] x coordinate referring to the background image. Used if
 * (bcol&0x1) is true
    * @param[in] y coordinate referring to the background image. Used if
 * (bcol&0x1) is true
    * @param[in,out] b allocated memory (8xSCREEN_WIDTH), allocated during
 * initialization
    */
int string2bitmap_xy(std::string s, unsigned int* b, unsigned int fcol,
                     unsigned int bcol, int x, int y);

/*! Utility function for converting  a string to a bitmap. Font size is fixed as
 * 8x8. Should not be called directly from application. Difference with
 * string2bitmap is not clear as of today and shall be fixed
      * @param[in] s string to be converted
      * @param[in] bcol RGB color of the background. If first bif (bcol&0x1) is
 * true, the actual background image color is used (alpha blending)
      * @param[in] fcol RGB color of the text
      * @param[in] x coordinate referring to the background image. Used if
 * (bcol&0x1) is true
      * @param[in] y coordinate referring to the background image. Used if
 * (bcol&0x1) is true
      * @param[in] img pointer to a 32 bit image, of size defined by
 * set_inputImageSize
      * @param[in,out] b allocated memory (8xSCREEN_WIDTH), allocated during
 * initialization
      */
int string2bitmap_bbox(std::string s, unsigned int* b, unsigned int fcol,
                       unsigned int bcol, int x, int y, unsigned int* img);

/*! Utility function for a string to a bitmap. Font size is fixed as 8x8.
  * @param[in] s string to be converted
  * @param[in] fcol RGB color of the text
  * @param[in] x coordinate
  * @param[in] y coordinate
  * @param[in,out] img pointer to a 32 bit image, of size defined by
 * set_inputImageSize
  */
void draw_box_text(int x, int y, std::string s, unsigned int fcol,
                   unsigned int* img);

/*! Utility function for drawing a progress bar. Not complete yet / under
   development

    */
void draw_progress_bar(int x, int y, int w, int h, int fcol, int bcol,
                       int steps, int prog);

/*! Utility function for writing a string to the background image. Font size is
* fixed as 8x8. Should not be called directly from application.
* @param[in] s string to be converted
* @param[in] fcol RGB color of the text
* @param[in] bcol RGB color of the text backgournd. If (bcol&0x1) is true, then
* the background color of the image is used (alpha blending
* @param[in] x coordinate
* @param[in] y coordinate
*/
void print_xy(int x, int y, std::string s, unsigned int fcol,
              unsigned int bcol);

/*! Utility function for converting  a string to a bitmap. Font size is fixed as
* 16x16. Should not be called directly from application.
*@param[in] s string to be converted
*@param[in] bcol RGB color of the background. If first bif (bcol&0x1) is true,
* the actual background image color is used (alpha blending)
*@param[in] fcol RGB color of the text
*@param[in] x coordinate referring to the background image. Used if (bcol&0x1)
* is true
*@param[in] y coordinate referring to the background image. Used if (bcol&0x1)
* is true
*@param[in,out] b allocated memory (16xSCREEN_WIDTH), allocated during
* initialization
*/
int string2bitmap16x16(std::string s, unsigned int* b, unsigned int fcol,
                       unsigned int bcol, int x, int y);

/*! Utility function for converting  a string to a bitmap. Font size is fixed as
* 16x24. Should not be called directly from application.
* @param[in] s string to be converted
* @param[in] bcol RGB color of the background. If first bif (bcol&0x1) is true,
* the actual background image color is used (alpha blending)
* @param[in] fcol RGB color of the text
* @param[in] x coordinate referring to the background image. Used if (bcol&0x1)
* is true
* @param[in] y coordinate referring to the background image. Used if (bcol&0x1)
* is true
* @param[in,out] b allocated memory (24xSCREEN_WIDTH), allocated during
* initialization
*/
int string2bitmap16x24(std::string s, unsigned int* b, unsigned int fcol,
                       unsigned int bcol, int x, int y);

/*! Utility function for converting  a string to a bitmap. Font size is fixed as
* 24x48. Should not be called directly from application.
* @param[in] s string to be converted
* @param[in] bcol RGB color of the background. If first bif (bcol&0x1) is true,
* the actual background image color is used (alpha blending)
* @param[in] fcol RGB color of the text
* @param[in] x coordinate referring to the background image. Used if (bcol&0x1)
* is true
* @param[in] y coordinate referring to the background image. Used if (bcol&0x1)
* is true
* @param[in,out] b allocated memory (48xSCREEN_WIDTH), allocated during
* initialization
*/
int string2bitmap24x48(std::string s, unsigned int* b, unsigned int fcol,
                       unsigned int bcol, int x, int y);

/*! Utility function for writing directly to display memory a string using a 8x8
 * font
    * @param[in] x coordinate.
    * @param[in] y coordinate.
    * @param[in] s string to be converted
    * @param[in] fcol RGB color of the text
    * @param[in] bcol RGB color of the background.
    */
void print8x8_toDisplay(int x, int y, std::string s, unsigned int fcol,
                        unsigned int bcol);

/*! Utility function for writing directly to display memory a string using a
 * 16x16 font
     * @param[in] x coordinate.
     * @param[in] y coordinate.
     * @param[in] s string to be converted
     * @param[in] fcol RGB color of the text
     * @param[in] bcol RGB color of the background.
     */
void print16x16_toDisplay(int x, int y, std::string s, unsigned int fcol,
                          unsigned int bcol);

/*! Utility function for writing directly to display memory a string using a
* 16x24 font
* @param[in] x coordinate.
* @param[in] y coordinate.
* @param[in] s string to be converted
* @param[in] fcol RGB color of the text
* @param[in] bcol RGB color of the background.
*/
void print16x24_toDisplay(int x, int y, std::string s, unsigned int fcol,
                          unsigned int bcol);

/*! Utility function for writing directly to display memory a string using a
* 24x48 font
* @param[in] x coordinate.
* @param[in] y coordinate.
* @param[in] s string to be converted
* @param[in] fcol RGB color of the text
* @param[in] bcol RGB color of the background.
*/
void print24x48_toDisplay(int x, int y, std::string s, unsigned int fcol,
                          unsigned int bcol);

/*! Utility function for writing label and  time to display memory using  a
 * 16x16 font. The time is converted to ms autoatically, with 3 digits
 * @param[in] x coordinate.
 * @param[in] y coordinate.
 * @param[in] label Text to be written.
 * @param[in] t time
 * @param[in] t_max unused
 * @param[in] fcol RGB color of the text.
 * @param[in] bcol RGB background color of the text.
 */
void print_time_toDisplay(int x, int y, std::string label, long int t,
                          long int t_max, unsigned int fcol, unsigned int bcol);

void capture_screen(std::string filename);

};  // end of namespace util
};  // end of namespace dmp

#endif  //__DRAW_UTIL
