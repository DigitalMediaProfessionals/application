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

class CDisNet : public CDMP_Network {
 private:
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 0 | FPGA-Layer | Convolution | (1, 1, 6) | (1, 1, 100) | - | - |
  | 0-0 | dense_1 | InnerProduct | (1, 1, 6) | (1, 1, 100) | - | 14608 |

  */
  void Layer_0();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 1 | FPGA-Layer | Convolution | (1, 1, 100) | (1, 1, 100) | - | - |
  | 1-0 | dense_2 | InnerProduct | (1, 1, 100) | (1, 1, 100) | - | 29008 |

  */
  void Layer_1();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 2 | FPGA-Layer | Convolution | (1, 1, 100) | (1, 1, 100) | - | - |
  | 2-0 | dense_3 | InnerProduct | (1, 1, 100) | (1, 1, 100) | - | 29008 |

  */
  void Layer_2();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 3 | FPGA-Layer | Convolution | (1, 1, 100) | (1, 1, 100) | - | - |
  | 3-0 | dense_4 | InnerProduct | (1, 1, 100) | (1, 1, 100) | - | 29008 |

  */
  void Layer_3();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 4 | FPGA-Layer | Convolution | (1, 1, 100) | (1, 1, 100) | - | - |
  | 4-0 | dense_5 | InnerProduct | (1, 1, 100) | (1, 1, 100) | - | 29008 |

  */
  void Layer_4();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 5 | FPGA-Layer | Convolution | (1, 1, 100) | (1, 1, 100) | - | - |
  | 5-0 | dense_6 | InnerProduct | (1, 1, 100) | (1, 1, 100) | - | 29008 |

  */
  void Layer_5();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 6 | FPGA-Layer | Convolution | (1, 1, 100) | (1, 1, 1) | - | - |
  | 6-0 | dense_7 | InnerProduct | (1, 1, 100) | (1, 1, 1) | - | 304 |

  */
  void Layer_6();

 public:
  virtual bool Initialize();
  CDisNet();
  virtual ~CDisNet();
};
