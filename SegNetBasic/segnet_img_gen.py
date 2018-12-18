#!/usr/bin/env python3
"""
    MIT License

    Copyright (c) [2016] [Yad Faeq]

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
"""

import cv2
import numpy as np

import argparse
from pathlib import Path


def normalized(rgb):
    # return rgb/255.0
    norm = np.zeros((rgb.shape[0], rgb.shape[1], 3), np.float32)

    b = rgb[:, :, 0]
    g = rgb[:, :, 1]
    r = rgb[:, :, 2]

    norm[:, :, 0] = cv2.equalizeHist(b)
    norm[:, :, 1] = cv2.equalizeHist(g)
    norm[:, :, 2] = cv2.equalizeHist(r)

    return norm


def load_data(img_dir):
    p = Path(img_dir).expanduser()
    img_ext_list = ["jpg", "jpeg", "JPG", "JPEG"]
    img_paths = []
    for ext in img_ext_list:
        img_paths.extend(p.glob("*." + ext))

    data = []
    for img_path in sorted(img_paths):
        tmp = cv2.imread(str(img_path))
        tmp = cv2.transpose(tmp)
        tmp = normalized(tmp)
        tmp = np.ascontiguousarray(tmp)
        data.append(tmp)
    return np.array(data, dtype=np.float16)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Program to generate preprocesed image data")
    parser.add_argument("--img-dir", help="image directory", default="~/dv-sdk/application/bin/images_yolo/from_walkway2/")
    parser.add_argument("-o", help="output file", default="segnet_image.bin")
    CONFIG = parser.parse_args()

    data = np.ascontiguousarray(load_data(CONFIG.img_dir))
    # data = load_data(CONFIG.img_dir)
    with open(CONFIG.o, "wb") as f:
        f.write(data.data)
    print("Number of Images : {}".format(data.shape[0]))
