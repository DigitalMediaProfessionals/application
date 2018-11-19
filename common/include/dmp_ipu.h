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
#include <string.h>

#include "dmp_network.h"

class DMPIPUConfig(void) {
  public:

    DMPIPUConfig(void) {
      memset(&cmd, 0, sizeof(cmd));
    }

    /// @brief configure to use texture buffer
    /// @param width Width. This can be 0 if a texture buffer is given from CDMP_Network object.
    /// @param heigh Height. This can be 0 if a texture buffer is given from CDMP_Network object.
    /// @param cnv_param see struct dmp_dv_cmdraw_ipu_v0.cnv_param . If given, this length must be 3.
    /// @detail each parametes corresponds to members of struct dmp_dv_cmdraw_ipu_v0
    ///         width  <-> tex_width
    ///         height <-> tex_height
    ///         format <-> fmt_tex
    ///
    ///         The default values of ridx, gidx, bidx and aidx are the same value of the case 
    ///                                                           where pixel format is RGB888.
    ///
    void ConfigUseTEX(uint8_t format, uint16_t width = 0, uint16_t height = 0, int transpose = 0,
                      int8_t ridx = 2, int8_t gidx = 1, int8_t bidx = 0, int8_t aidx = -1,
                      uint8_t cnv_type = DMP_DV_CNV_FP16_SUB, const uint8_t *cnv_param = nullptr);
 
    /// @brief configure to use texture buffer
    /// @param width Width. This must be the same as width of write buffer.
    /// @param height Height. This must be the same as height of write buffer.
    void ConfigUseRD(uint16_t width, uint16_t height, uint8_t format);

    /// @brief configure of write buffer
    /// @param width Width. This can be 0 if a write buffer is given from CDMP_Network object. 
    ///                               If not 0, this must be the same as width of read buffer.
    /// @param heigh Height. This can be 0 if a write buffer is given from CDMP_Network object.
    ///                               If not 0, this must be the same as height of read buffer.
    void ConfigWR(uint8_t format, uint16_t width = 0, uint16_t height = 0);

    /// @brief configure to use constant alpha value
    void ConfigUseConstAlpha(uint8_t alpha);

    /// @brief configure to use BLF
    void ConfigUseBLF(void);

    /// @brief getter for cmd
    const struct dmp_dv_cmdraw_ipu_v0 *get_dmp_dv_cmdraw_ipu_v0(void);

  private:
    struct dmp_dv_cmdraw_ipu_v0 cmd;
}

class DMPIPU {
  public:
    /// @brief Destructor.
    virtual ~DMPIPU(void) {
      ReleaseResources();
    };

    /// @brief initializer
    Initialize(const DMPIPUConfig &initializer);

    /// @brief initializer for preprocessing network input
    Initialize(const DMPIPUConfig &initializer, const CDMP_Network &net);

    /// @brief initializer for postprocessing network output
    Initialize(const DMPIPUConfig &initializer, const CDMP_Network &net, int i_output);

    /// @brief run
    int Run(void);

    /// @brief return texture buffer address
    void *get_tex_addr_cpu(void);

    /// @brief return read buffer address
    void *get_rd_addr_cpu(void);

    /// @brief return write buffer address
    void *get_wr_addr_cpu(void);

    /// @brief return if this IPU is connected to network input
    bool is_preprocessing(void);

    /// @brief return if this IPU is connected to network output
    bool is_postprocessing(void);

  private:
    friend class CDMP_Network;

    void ReleaseResources(void);

    struct dmp_dv_buf tex;
    struct dmp_dv_buf rd;
    struct dmp_dv_buf wr;
    void   *tex_map;
    void   *rd_map;
    void   *wr_map;

    const CDMP_Network &net;
}
