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

class CKerasSqueezeNet : public CDMP_Network {
 private:
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 0 | FPGA-Layer | Convolution | (227, 227, 3) | (56, 56, 64) | - | - |
  | 0-0 | conv1 | Convolution | (227, 227, 3) | (113, 113, 64) | - | 5248 |
  | 0-0 | pool1 | Pooling | (113, 113, 64) | (56, 56, 64) | - | - |

  */
  void Layer_0();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 1 | FPGA-Layer | Convolution | (56, 56, 64) | (56, 56, 16) | - | - |
  | 1-0 | fire2/squeeze1x1 | Convolution | (56, 56, 64) | (56, 56, 16) | - | 1696 |

  */
  void Layer_1();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 2 | FPGA-Layer | Convolution | (56, 56, 16) | (56, 56, 128) | - | - |
  | 2-0 | fire2/expand1x1 | Convolution | (56, 56, 16) | (56, 56, 64) | - | 5248 |
  | 2-1 | fire2/expand3x3 | Convolution | (56, 56, 16) | (56, 56, 64) | - | 9856 |

  */
  void Layer_2();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 3 | FPGA-Layer | Convolution | (56, 56, 128) | (56, 56, 16) | - | - |
  | 3-0 | fire3/squeeze1x1 | Convolution | (56, 56, 128) | (56, 56, 16) | - | 2848 |

  */
  void Layer_3();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 4 | FPGA-Layer | Convolution | (56, 56, 16) | (28, 28, 128) | - | - |
  | 4-0 | fire3/expand1x1 | Convolution | (56, 56, 16) | (56, 56, 64) | - | 5248 |
  | 4-0 | pool3 | Pooling | (56, 56, 128) | (28, 28, 128) | - | - |
  | 4-1 | fire3/expand3x3 | Convolution | (56, 56, 16) | (56, 56, 64) | - | 9856 |
  | 4-1 | pool3 | Pooling | (56, 56, 128) | (28, 28, 128) | - | - |

  */
  void Layer_4();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 5 | FPGA-Layer | Convolution | (28, 28, 128) | (28, 28, 32) | - | - |
  | 5-0 | fire4/squeeze1x1 | Convolution | (28, 28, 128) | (28, 28, 32) | - | 5184 |

  */
  void Layer_5();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 6 | FPGA-Layer | Convolution | (28, 28, 32) | (28, 28, 256) | - | - |
  | 6-0 | fire4/expand1x1 | Convolution | (28, 28, 32) | (28, 28, 128) | - | 9984 |
  | 6-1 | fire4/expand3x3 | Convolution | (28, 28, 32) | (28, 28, 128) | - | 37632 |

  */
  void Layer_6();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 7 | FPGA-Layer | Convolution | (28, 28, 256) | (28, 28, 32) | - | - |
  | 7-0 | fire5/squeeze1x1 | Convolution | (28, 28, 256) | (28, 28, 32) | - | 9792 |

  */
  void Layer_7();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 8 | FPGA-Layer | Convolution | (28, 28, 32) | (14, 14, 256) | - | - |
  | 8-0 | fire5/expand1x1 | Convolution | (28, 28, 32) | (28, 28, 128) | - | 9984 |
  | 8-0 | pool5 | Pooling | (28, 28, 256) | (14, 14, 256) | - | - |
  | 8-1 | fire5/expand3x3 | Convolution | (28, 28, 32) | (28, 28, 128) | - | 37632 |
  | 8-1 | pool5 | Pooling | (28, 28, 256) | (14, 14, 256) | - | - |

  */
  void Layer_8();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 9 | FPGA-Layer | Convolution | (14, 14, 256) | (14, 14, 48) | - | - |
  | 9-0 | fire6/squeeze1x1 | Convolution | (14, 14, 256) | (14, 14, 48) | - | 14432 |

  */
  void Layer_9();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 10 | FPGA-Layer | Convolution | (14, 14, 48) | (14, 14, 384) | - | - |
  | 10-0 | fire6/expand1x1 | Convolution | (14, 14, 48) | (14, 14, 192) | - | 14720 |
  | 10-1 | fire6/expand3x3 | Convolution | (14, 14, 48) | (14, 14, 192) | - | 83840 |

  */
  void Layer_10();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 11 | FPGA-Layer | Convolution | (14, 14, 384) | (14, 14, 48) | - | - |
  | 11-0 | fire7/squeeze1x1 | Convolution | (14, 14, 384) | (14, 14, 48) | - | 21344 |

  */
  void Layer_11();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 12 | FPGA-Layer | Convolution | (14, 14, 48) | (14, 14, 384) | - | - |
  | 12-0 | fire7/expand1x1 | Convolution | (14, 14, 48) | (14, 14, 192) | - | 14720 |
  | 12-1 | fire7/expand3x3 | Convolution | (14, 14, 48) | (14, 14, 192) | - | 83840 |

  */
  void Layer_12();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 13 | FPGA-Layer | Convolution | (14, 14, 384) | (14, 14, 64) | - | - |
  | 13-0 | fire8/squeeze1x1 | Convolution | (14, 14, 384) | (14, 14, 64) | - | 28288 |

  */
  void Layer_13();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 14 | FPGA-Layer | Convolution | (14, 14, 64) | (14, 14, 512) | - | - |
  | 14-0 | fire8/expand1x1 | Convolution | (14, 14, 64) | (14, 14, 256) | - | 19456 |
  | 14-1 | fire8/expand3x3 | Convolution | (14, 14, 64) | (14, 14, 256) | - | 148480 |

  */
  void Layer_14();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 15 | FPGA-Layer | Convolution | (14, 14, 512) | (14, 14, 64) | - | - |
  | 15-0 | fire9/squeeze1x1 | Convolution | (14, 14, 512) | (14, 14, 64) | - | 37504 |

  */
  void Layer_15();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 16 | FPGA-Layer | Convolution | (14, 14, 64) | (14, 14, 512) | - | - |
  | 16-0 | fire9/expand1x1 | Convolution | (14, 14, 64) | (14, 14, 256) | - | 19456 |
  | 16-1 | fire9/expand3x3 | Convolution | (14, 14, 64) | (14, 14, 256) | - | 148480 |

  */
  void Layer_16();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 17 | FPGA-Layer | Convolution | (14, 14, 512) | (14, 14, 1000) | - | - |
  | 17-0 | conv10 | Convolution | (14, 14, 512) | (14, 14, 1000) | - | 578512 |

  */
  void Layer_17();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 18 | FPGA-Layer | Convolution | (14, 14, 1000) | (2, 2, 1000) | - | - |
  | 18-0 | global_average_pooling2d_1_7 | Pooling | (14, 14, 1000) | (2, 2, 1000) | - | - |

  */
  void Layer_18();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 19 | FPGA-Layer | Convolution | (2, 2, 1000) | (1, 1, 1000) | - | - |
  | 19-0 | global_average_pooling2d_1_2 | Pooling | (2, 2, 1000) | (1, 1, 1000) | - | - |

  */
  void Layer_19();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 20 | FPGA-Layer | SoftMax | (1, 1, 1000) | (1, 1, 1000) | - | - |

  */
  void Layer_20();

 public:
  virtual bool Initialize();
  CKerasSqueezeNet();
  virtual ~CKerasSqueezeNet();
};
