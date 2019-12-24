#!/usr/bin/env python3
"""
    Copyright 2019 Digital Media Professionals Inc.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
"""

import os
import sys
import math
import tensorflow as tf
import tensorflow.keras.backend as K
import numpy as np
import cv2
import argparse
from pathlib import Path


if __name__ != '__main__':
    raise ImportError('Do not import this file')

# YOLOv3 parameters
N_CLS = 80
N_BOX = 3
LEN_BBOX = N_CLS + 5  # length of one bounding box including objectiveness and class probabilities
ANCHOR = [81, 82, 135, 169, 344, 319, 23, 27, 37, 58, 81, 82]
INPUT_W = 576  # input image width
INPUT_H = 288  # input image height
DIM = [INPUT_W // 32, INPUT_H // 32, INPUT_W // 16, INPUT_H // 16]

# index of output from YOLOv3
YOLO_OUT_OBJNESS = 4
YOLO_OUT_X = 0
YOLO_OUT_Y = 1
YOLO_OUT_W = 2
YOLO_OUT_H = 3
YOLO_OUT_CLS = 5


CLS_NAME = [
    "person",
    "bicycle",
    "car",
    "motorbike",
    "aeroplane",
    "bus",
    "train",
    "truck",
    "boat",
    "traffic light",
    "fire hydrant",
    "stop sign",
    "parking meter",
    "bench",
    "bird",
    "cat",
    "dog",
    "horse",
    "sheep",
    "cow",
    "elephant",
    "bear",
    "zebra",
    "giraffe",
    "backpack",
    "umbrella",
    "handbag",
    "tie",
    "suitcase",
    "frisbee",
    "skis",
    "snowboard",
    "sports ball",
    "kite",
    "baseball bat",
    "baseball glove",
    "skateboard",
    "surfboard",
    "tennis racket",
    "bottle",
    "wine glass",
    "cup",
    "fork",
    "knife",
    "spoon",
    "bowl",
    "banana",
    "apple",
    "sandwich",
    "orange",
    "broccoli",
    "carrot",
    "hot dog",
    "pizza",
    "donut",
    "cake",
    "chair",
    "sofa",
    "pottedplant",
    "bed",
    "diningtable",
    "toilet",
    "tvmonitor",
    "laptop",
    "mouse",
    "remote",
    "keyboard",
    "cell phone",
    "microwave",
    "oven",
    "toaster",
    "sink",
    "refrigerator",
    "book",
    "clock",
    "vase",
    "scissors",
    "teddy bear",
    "hair drier",
    "toothbrush",
]


CLS_COLOR = [
    (0x00, 0xFF, 0x3F), (0x00, 0x3F, 0xFF), (0xFF, 0x26, 0x00), (0xF2, 0x00, 0xFF), (0xFF, 0x4C, 0x00),
    (0xA5, 0xFF, 0x00), (0xFF, 0x72, 0x00), (0xFF, 0x85, 0x00), (0xFF, 0x99, 0x00), (0xFF, 0xAC, 0x00),
    (0xFF, 0xBF, 0x00), (0xFF, 0xD2, 0x00), (0xFF, 0xE5, 0x00), (0xFF, 0xF8, 0x00), (0xF2, 0xFF, 0x00),
    (0xDF, 0xFF, 0x00), (0xCB, 0xFF, 0x00), (0xB8, 0xFF, 0x00), (0xFF, 0x5F, 0x00), (0x92, 0xFF, 0x00),
    (0x7F, 0xFF, 0x00), (0x6C, 0xFF, 0x00), (0x59, 0xFF, 0x00), (0x46, 0xFF, 0x00), (0x33, 0xFF, 0x00),
    (0x1F, 0xFF, 0x00), (0x0C, 0xFF, 0x00), (0x00, 0xFF, 0x06), (0x00, 0xFF, 0x19), (0x00, 0xFF, 0x2C),
    (0xFF, 0x00, 0x00), (0x00, 0xFF, 0x52), (0x00, 0xFF, 0x66), (0x00, 0xFF, 0x79), (0x00, 0xFF, 0x8C),
    (0x00, 0xFF, 0x9F), (0x00, 0xFF, 0xB2), (0x00, 0xFF, 0xC5), (0x00, 0xFF, 0xD8), (0x00, 0xFF, 0xEB),
    (0x00, 0xFF, 0xFF), (0x00, 0xEB, 0xFF), (0x00, 0xD8, 0xFF), (0x00, 0xC5, 0xFF), (0x00, 0xB2, 0xFF),
    (0x00, 0x9F, 0xFF), (0x00, 0x8C, 0xFF), (0x00, 0x79, 0xFF), (0x00, 0x66, 0xFF), (0x00, 0x52, 0xFF),
    (0xFF, 0x13, 0x00), (0x00, 0x2C, 0xFF), (0x00, 0x19, 0xFF), (0x00, 0x06, 0xFF), (0x0C, 0x00, 0xFF),
    (0x1F, 0x00, 0xFF), (0x32, 0x00, 0xFF), (0x46, 0x00, 0xFF), (0x59, 0x00, 0xFF), (0x6C, 0x00, 0xFF),
    (0x7F, 0x00, 0xFF), (0x92, 0x00, 0xFF), (0xA5, 0x00, 0xFF), (0xB8, 0x00, 0xFF), (0xCC, 0x00, 0xFF),
    (0xDF, 0x00, 0xFF), (0xFF, 0x39, 0x00), (0xFF, 0x00, 0xF8), (0xFF, 0x00, 0xE5), (0xFF, 0x00, 0xD2),
    (0xFF, 0x00, 0xBF), (0xFF, 0x00, 0xAC), (0xFF, 0x00, 0x98), (0xFF, 0x00, 0x85), (0xFF, 0x00, 0x72),
    (0xFF, 0x00, 0x5F), (0xFF, 0x00, 0x4C), (0xFF, 0x00, 0x39), (0xFF, 0x00, 0x26), (0xFF, 0x00, 0x13),
]


def get_bboxes(yolo_out, cls_thres=0.2, objness_thres=0.2, nms_thres=0.45):
    """

    :param yolo_out: raw output from YOLOv3 network
    :return: ndarray representing acceppted bounding boxes in shape of [-1, LEN_BBOX]
    """
    def sigmoid(x):
        return 0.5 + 0.5 * math.tanh(0.5 * x)

    def class_calc(x, thres, objness):
        x *= 0.5
        np.tanh(x, out=x)
        x *= 0.5
        x += 0.5
        x *= objness
        x[x < thres] = 0

    def decode_yolo_box(box, anchor, dim, grid_x, grid_y):
        box[YOLO_OUT_W] = math.exp(box[YOLO_OUT_W]) * (anchor[0] / INPUT_W)
        box[YOLO_OUT_H] = math.exp(box[YOLO_OUT_H]) * (anchor[1] / INPUT_H)
        box[YOLO_OUT_X] = (grid_x + box[YOLO_OUT_X]) / dim[0] - box[YOLO_OUT_W] / 2
        box[YOLO_OUT_Y] = (grid_y + box[YOLO_OUT_Y]) / dim[1] - box[YOLO_OUT_H] / 2

    ret = np.empty((0, LEN_BBOX))
    bbox_idx = 0
    inv_objness_thres = math.log(objness_thres / (1.0 - objness_thres))
    inv_objness_thres = np.float32(inv_objness_thres)
    for i in (0, 1):
        for y in range(0, DIM[i * 2 + 1]):
            for x in range(0, DIM[i * 2]):
                for n in range(0, N_BOX):
                    out = yolo_out[bbox_idx:bbox_idx + LEN_BBOX]
                    bbox_idx = bbox_idx + LEN_BBOX
                    if out[YOLO_OUT_OBJNESS] >= inv_objness_thres:
                        out[YOLO_OUT_OBJNESS] = sigmoid(out[YOLO_OUT_OBJNESS])
                        out[YOLO_OUT_X] = sigmoid(out[YOLO_OUT_X])
                        out[YOLO_OUT_Y] = sigmoid(out[YOLO_OUT_Y])
                        class_calc(out[YOLO_OUT_CLS:], cls_thres, out[YOLO_OUT_OBJNESS])

                        decode_yolo_box(out, ANCHOR[(i * N_BOX + n) * 2:], DIM[i * 2:], x, y)
                        ret = np.concatenate([ret, [out]], axis=0)

    # handle overlapping bboxes
    x1 = ret[:,YOLO_OUT_X]
    y1 = ret[:,YOLO_OUT_Y]
    w1 = ret[:,YOLO_OUT_W]
    h1 = ret[:,YOLO_OUT_H]
    x2 = x1 + w1
    y2 = y1 + h1
    area = w1 * h1
    for ci in range(YOLO_OUT_CLS, LEN_BBOX):
        idxs = np.argsort(ret[:,ci])
        while len(idxs) > 0:
            last = len(idxs) - 1
            i = idxs[last]
            if ret[i, ci] <= 0.0:
                break

            #find minimum and maximum x y coordinates
            xx1 = np.maximum(x1[i], x1[idxs[:last]])
            yy1 = np.maximum(y1[i], y1[idxs[:last]])
            xx2 = np.minimum(x2[i], x2[idxs[:last]])
            yy2 = np.minimum(y2[i], y2[idxs[:last]])

            # compute the width and height of the bounding box
            w2 = np.maximum(0, xx2 - xx1)
            h2 = np.maximum(0, yy2 - yy1)
            area2 = w2 * h2

            # compute the ratio of overlap
            overlap = area2 / (area[idxs[:last]] + area[i] - area2)

            over_idx = np.where(overlap > nms_thres)
            ret[idxs[over_idx],ci] = 0.0
            idxs = np.delete(idxs[:last], over_idx)

    return [o for o in ret if (o[YOLO_OUT_CLS:] != 0).any()]


def draw_bboxes(img, hw, bboxes_rect, bboxes_cls, thickness=2):
    """
    :param img: OpenCV compatible image
    :param hw: (height, width) of image
    :param bboxes_rect: list of (x, y, width, height) of each bounding box.
        Each element have to be not an absolute value but a ratio within the image.
    :param bboxes_cls: list of ndarray representing class probabilities of each bounding box
    :param cls_colors: list of color in form of (r, g, b)
    :param thickness: thichness of line of a bounding box
    :return: img with bounding box
    """

    height = hw[0]
    width = hw[1]
    for rect, cls in zip(bboxes_rect, bboxes_cls):
        # identify object type
        obj_type = cls.argmax()
        color = CLS_COLOR[obj_type]

        # calculate and adjust x, y, w, h in pixel
        def minmax(x, min, max):
            return min if x < min else \
                max if max < x else x
        x = int(width * rect[0])
        y = int(height * rect[1])
        w = int(width * rect[2])
        h = int(height * rect[3])
        x0 = minmax(x, 0, width - 1)
        y0 = minmax(y, 0, height - 1)
        x1 = minmax(x + w, 0, width - 1)
        y1 = minmax(y + h, 0, height - 1)

        # draw bbox on the image
        img = cv2.rectangle(img, (x0, y0), (x1, y1), color, thickness)
        name = CLS_NAME[obj_type]
        txt_x0 = x0
        txt_y0 = max(y0 - 6, 0)
        txt_x1 = min(txt_x0 + len(name) * 5, img.shape[1] - 1)
        txt_y1 = min(txt_y0 + 6, img.shape[0] - 1)
        img = cv2.rectangle(img, (txt_x0, txt_y0), (txt_x1, txt_y1), color, -1)
        img = cv2.putText(img, name, (txt_x0, txt_y1), cv2.FONT_HERSHEY_SIMPLEX, 0.3, (255, 255, 255))

    return img


# parse cmdline args
parser = argparse.ArgumentParser()
parser.add_argument('-v', '--verbose', help="enable verbose mode", action="store_true")
parser.add_argument('--image-dir', help="path to directory containing images to be procedured", default="../bin/images_yolo/")
parser.add_argument('--model-path', help="path to the YOLOv3-tiny KERAS model", default="../model/yolov3-tiny.h5")
CONFIG = parser.parse_args()

# get image names
p = Path(CONFIG.image_dir)
img_paths = []
for ext in ["jpg", "jpeg", "JPG", ".JPEG"]:
    img_paths.extend(list(p.glob('**/*.' + ext)))
if not img_paths:
    raise FileNotFoundError("No jpeg file are found in " + CONFIG.image_dir)
img_paths = sorted(img_paths)

# Set learning phase flag to 0 to reduce generated graph passes.
K.set_learning_phase(0)

# initialize output
output_dir = "./output/"
os.makedirs(output_dir, exist_ok=True)

# load YOLOv3-tiny model
model = tf.keras.models.load_model(CONFIG.model_path)

# main inference loop
for img_path in img_paths:
    # load image
    if CONFIG.verbose:
        print("process {}".format(img_path))
    img = cv2.imread(str(img_path))
    rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    rgb = cv2.resize(rgb, (INPUT_W, INPUT_H))
    rgb = (rgb / 256).astype(np.float16, copy=False)

    # inference
    rgb = np.expand_dims(rgb, 0)
    outs = model.predict(rgb)
    outs.shape = (-1)

    # manipulate outs
    bboxes = get_bboxes(outs)
    img = draw_bboxes(img, img.shape[0:2],
                      [b[:YOLO_OUT_OBJNESS] for b in bboxes],
                      [b[YOLO_OUT_CLS:] for b in bboxes])

    # output
    cv2.imwrite(output_dir + str(img_path.name), img)
