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
 */

#pragma once

#include "dmp_dv.h"
#include "dmp_dv_cmdraw_v0.h"
#include "dmp_network.h"

class DMPMaximizer {
  public:
    /// @brief Constructor
    DMPMaximizer();

    /// @brief Destructor.
    virtual ~DMPMaximizer();

    /// @brief Initialize this maximizer
    /// @param width Width
    /// @param height Height
    /// @param nclass Number of classes in a pixel
    /// @CDMP_Network Network object. If NULL, 
    int Initialize(uint16_t width, uint16_t height, uint8_t nclass,
                    CDMP_Network *net = nullptr, int i_output = 0);

    /// @brief run
    int Run();

    /// @brief return width
    uint16_t get_width();

    /// @brief return height
    uint16_t get_height();

    /// @brief return number of classes in a pixel
    uint8_t get_nclass();

    /// @brief return input buffer address
    uint8_t *get_in_addr_cpu() const;

    /// @brief return output buffer address
    uint8_t *get_out_addr_cpu() const;

    /// @brief return if this maximizer is connected to network output
    bool is_connected_to_network() const;

  private:
    void Clear(bool release_resources=true);

    int InitializeCmdlist(struct dmp_dv_cmdraw_maximizer_v0 *cmd);

    dmp_dv_context ctx;
    dmp_dv_cmdlist cmdlist;
    struct dmp_dv_buf in;
    struct dmp_dv_buf out;
    uint8_t *in_map;
    uint8_t *out_map;

    int i_output;
    const CDMP_Network *net;

    uint16_t width;
    uint16_t height;
    uint8_t nclass;

    bool initialized;
};
