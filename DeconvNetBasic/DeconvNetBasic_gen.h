/*
 *  Copyright 2018 Digital Media Professionals Inc.

 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at

 *      http://www.apache.org/licenses/LICENSE-2.0

 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.

 *  This source code was generated using DMP-DV700 tools.
 */
#pragma once

#include "dmp_network.h"

class CDeconvNetBasic : public CDMP_Network {
 private:
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 0 | FPGA-Layer | Convolution | (320, 240, 3) | (320, 240, 64) | - | - |
  | 0-0 | conv2d_1 | Convolution | (320, 240, 3) | (320, 240, 64) | - | 9344 |

  */
  void Layer_0();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 1 | FPGA-Layer | Convolution | (320, 240, 64) | (160, 120, 64) | - | - |
  | 1-0 | max_pooling2d_1 | Pooling | (320, 240, 64) | (160, 120, 64) | - | - |

  */
  void Layer_1();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 2 | FPGA-Layer | Convolution | (160, 120, 64) | (160, 120, 80) | - | - |
  | 2-0 | conv2d_2 | Convolution | (160, 120, 64) | (160, 120, 80) | - | 92320 |

  */
  void Layer_2();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 3 | FPGA-Layer | Convolution | (160, 120, 80) | (80, 60, 80) | - | - |
  | 3-0 | max_pooling2d_2 | Pooling | (160, 120, 80) | (80, 60, 80) | - | - |

  */
  void Layer_3();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 4 | FPGA-Layer | Convolution | (80, 60, 80) | (80, 60, 96) | - | - |
  | 4-0 | conv2d_3 | Convolution | (80, 60, 80) | (80, 60, 96) | - | 138432 |

  */
  void Layer_4();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 5 | FPGA-Layer | Convolution | (80, 60, 96) | (40, 30, 96) | - | - |
  | 5-0 | max_pooling2d_3 | Pooling | (80, 60, 96) | (40, 30, 96) | - | - |

  */
  void Layer_5();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 6 | FPGA-Layer | Convolution | (40, 30, 96) | (40, 30, 128) | - | - |
  | 6-0 | conv2d_4 | Convolution | (40, 30, 96) | (40, 30, 128) | - | 221440 |

  */
  void Layer_6();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 7 | FPGA-Layer | Convolution | (40, 30, 128) | (40, 30, 128) | - | - |
  | 7-0 | batch_normalization_11 | Convolution | (40, 30, 128) | (40, 30, 128) | - | 18688 |

  */
  void Layer_7();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 8 | FPGA-Layer | Convolution | (40, 30, 128) | (40, 30, 128) | - | - |
  | 8-0 | conv2d_transpose_8 | Convolution | (40, 30, 128) | (40, 30, 128) | - | 295168 |

  */
  void Layer_8();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 9 | FPGA-Layer | Convolution | (40, 30, 128) | (80, 60, 96) | - | - |
  | 9-0 | conv2d_transpose_5 | Convolution | (40, 30, 128) | (80, 60, 96) | - | 221376 |

  */
  void Layer_9();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 10 | FPGA-Layer | Convolution | (80, 60, 96) | (80, 60, 96) | - | - |
  | 10-0 | conv2d_transpose_6 | Convolution | (80, 60, 96) | (80, 60, 96) | - | 166080 |

  */
  void Layer_10();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 11 | FPGA-Layer | Convolution | (80, 60, 96) | (160, 120, 80) | - | - |
  | 11-0 | conv2d_transpose_3 | Convolution | (80, 60, 96) | (160, 120, 80) | - | 138400 |

  */
  void Layer_11();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 12 | FPGA-Layer | Convolution | (160, 120, 80) | (160, 120, 80) | - | - |
  | 12-0 | conv2d_transpose_4 | Convolution | (160, 120, 80) | (160, 120, 80) | - | 115360 |

  */
  void Layer_12();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 13 | FPGA-Layer | Convolution | (160, 120, 80) | (320, 240, 64) | - | - |
  | 13-0 | conv2d_transpose_1 | Convolution | (160, 120, 80) | (320, 240, 64) | - | 92288 |

  */
  void Layer_13();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 14 | FPGA-Layer | Convolution | (320, 240, 64) | (320, 240, 64) | - | - |
  | 14-0 | conv2d_transpose_2 | Convolution | (320, 240, 64) | (320, 240, 64) | - | 73856 |

  */
  void Layer_14();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 15 | FPGA-Layer | Convolution | (320, 240, 64) | (320, 240, 12) | - | - |
  | 15-0 | conv2d_5 | Convolution | (320, 240, 64) | (320, 240, 12) | - | 13856 |

  */
  void Layer_15();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 16 | FPGA-Layer | Flatten | (320, 240, 12) | (921600,) | - | - |

  */
  void Layer_16();

 public:
  virtual bool Initialize();
  CDeconvNetBasic();
  virtual ~CDeconvNetBasic();
};
