#pragma once

int v4l2_cam_init(int width, int height, int fps);

int v4l2_cam_start(void);

int v4l2_cam_get(unsigned int * __restrict vImg, int capture_w, int capture_h, int crop_xoffs, int crop_yoffs, int crop_w, int crop_h);

int v4l2_cam_stop(void);

int v4l2_cam_deinit(void);
