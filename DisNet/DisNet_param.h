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

#pragma once

// define NON_TINY if the YOLOv3 is not tiny version.
// #define NON_TINY

#define IMAGE_W 576
#define IMAGE_H 288
#define PROC_W 576
#define PROC_H 288

#define CLS_THRESHOLD 0.3f
#define NMS_THRESHOLD 0.45f
#define OBJ_THRESHOLD 0.2f

// For output of TinyYOLOv3
#define NUM_CLASS 80
#define NUM_BOX_PER_TILE   3

#define FILENAME_WEIGHTS "YOLOv3_weights.bin"
#define FILENAME_WEIGHTS2 "DisNet_weights.bin"

