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

class DMPIPUConfig {
  public:

    DMPIPUConfig() {
      Clear();
    }

    /// @brief configure to use texture buffer
    /// @param width Width. This can be 0 if a texture buffer is given from CDMP_Network object.
    /// @param heigh Height. This can be 0 if a texture buffer is given from CDMP_Network object.
    /// @param cnv_param see struct dmp_dv_cmdraw_ipu_v0.cnv_param . If given, this length must be 3.
    /// @param ncolor_lut number of colors for LUT. This must be smaller than 33.
    /// @detail each parametes corresponds to members of struct dmp_dv_cmdraw_ipu_v0
    ///         width  <-> tex_width
    ///         height <-> tex_height
    ///         format <-> fmt_tex
    ///
    ///         The default values of ridx, gidx, bidx and aidx are the same value of the case 
    ///                                                           where pixel format is RGB888.
    ///
    void ConfigUseTEX(uint8_t format, uint16_t width = 0, uint16_t height = 0, uint8_t transpose = 0,
                      int8_t ridx = 2, int8_t gidx = 1, int8_t bidx = 0, int8_t aidx = -1,
                      uint8_t cnv_type = DMP_DV_CNV_FP16_SUB, const uint8_t *cnv_param = nullptr,
                      uint8_t ncolor_lut = 0, uint32_t *lut = nullptr);
 
    /// @brief configure to use texture buffer
    /// @param width Width. This must be the same as width of write buffer.
    /// @param height Height. This must be the same as height of write buffer.
    /// @param stride Stride. If 0 is given, set the same value as width.
    /// @return 0 on success, -1 otherwise
    int ConfigUseRD(uint8_t format, uint16_t width, uint16_t height, int32_t stride = 0);

    /// @brief configure of write buffer
    /// @param width Width. This can be 0 if a write buffer is given from CDMP_Network object. 
    ///                               If not 0, this must be the same as width of read buffer.
    /// @param heigh Height. This can be 0 if a write buffer is given from CDMP_Network object.
    ///                               If not 0, this must be the same as height of read buffer.
    /// @param stride Stride. If 0 is given, set the same value as width.
    /// @return 0 on success, -1 otherwise
    int ConfigWR(uint8_t format, uint16_t width = 0, uint16_t height = 0, int32_t stride = 0);

    /// @brief configure to use constant alpha value
    void ConfigUseConstAlpha(uint8_t alpha);

    /// @brief configure to use BLF
    void ConfigUseBLF();

    /// @brief clear configuration
    void Clear();

    /// @brief getter for cmd
    struct dmp_dv_cmdraw_ipu_v0 *get_dmp_dv_cmdraw_ipu_v0();

  private:
    struct dmp_dv_cmdraw_ipu_v0 cmd;
};

class DMPIPU {
  public:
    DMPIPU();

    /// @brief Destructor.
    virtual ~DMPIPU() {
      ReleaseResources();
    };

    /// @brief initializer
    int Initialize(DMPIPUConfig &initializer);

    /// @brief initializer for preprocessing network input
    /// @detail an input buffer of net is assigned to a write buffer of IPU
    int InitializePreproc(DMPIPUConfig &initializer, const CDMP_Network &net);

    /// @brief initializer for postprocessing network output
    /// @detail an output buffer of net is assigned to a texture buffer of IPU
    int InitializePostproc(DMPIPUConfig &initializer, const CDMP_Network &net, int i_output = 0);

    /// @brief run
    int Run();

    /// @brief return texture buffer address
    uint8_t *get_tex_addr_cpu() const;

    /// @brief return read buffer address
    uint8_t *get_rd_addr_cpu() const;

    /// @brief return write buffer address
    uint8_t *get_wr_addr_cpu() const;

    /// @brief return if this IPU is connected to network input
    bool is_preprocessing() const;

    /// @brief return if this IPU is connected to network output
    bool is_postprocessing() const;

  private:
    void Clear();
    void ReleaseResources();

    int InitializeCmdlist(dmp_dv_cmdraw_ipu_v0 *cmd);

    dmp_dv_context ctx;
    dmp_dv_cmdlist cmdlist;

    struct dmp_dv_buf tex;
    struct dmp_dv_buf rd;
    struct dmp_dv_buf wr;
    uint8_t *tex_map;
    uint8_t *rd_map;
    uint8_t *wr_map;

    int i_output;
    const CDMP_Network *net;
};
