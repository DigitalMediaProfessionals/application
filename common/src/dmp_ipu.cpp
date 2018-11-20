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

#include <cstdlib>
#include <cstdio>
#include <string.h>

#include "dmp_ipu.h"

#define LOG(...) fprintf(stdout, __VA_ARGS__); fflush(stdout);
#define ERR(...) fprintf(stderr, __VA_ARGS__); fflush(stderr);

void DMPIPUConfig::ConfigUseTEX(uint8_t format, uint16_t width, uint16_t height, uint8_t transpose,
                                int8_t ridx, int8_t gidx, int8_t bidx, int8_t aidx,
                                uint8_t cnv_type, const uint8_t *cnv_param, 
                                uint8_t ncolor_lut, uint32_t *lut) {
  cmd.use_tex    = 1;
  cmd.fmt_tex    = format;
  cmd.tex_width  = width;
  cmd.tex_height = height;
  cmd.transpose  = transpose;
  cmd.ridx = ridx;
  cmd.gidx = gidx;
  cmd.bidx = bidx;
  cmd.aidx = aidx;
  cmd.cnv_type = cnv_type;
  if(cnv_param) {
    for(unsigned i = 0; i < sizeof(cmd.cnv_param) / sizeof(cmd.cnv_param[0]); i++) {
      cmd.cnv_param[i] = cnv_param[i];
    }
  }
  cmd.ncolor_lut = ncolor_lut;
  for(unsigned i = 0; i < ncolor_lut; i++) {
    cmd.lut[i] = lut[i];
  }
}

int DMPIPUConfig::ConfigUseRD(uint8_t format, uint16_t width, uint16_t height, int32_t stride) {
  if(cmd.rect_width != 0 && cmd.rect_width != width) {
    return -1;
  }
  if(cmd.rect_height != 0 && cmd.rect_height != height) {
    return -1;
  }
  cmd.use_rd      = 1;
  cmd.fmt_rd      = format;
  cmd.rect_width  = width;
  cmd.rect_height = height;
  cmd.stride_rd   = stride ? stride : width;

  return 0;
}

int DMPIPUConfig::ConfigWR(uint8_t format, uint16_t width, uint16_t height, int32_t stride) {
  if(cmd.rect_width != 0 && cmd.rect_width != width) {
    return -1;
  }
  if(cmd.rect_height != 0 && cmd.rect_height != height) {
    return -1;
  }
  cmd.fmt_wr      = format;
  cmd.rect_width  = width;
  cmd.rect_height = height;
  cmd.stride_wr   = stride ? stride : width;

  return 0;
}

void DMPIPUConfig::ConfigUseConstAlpha(uint8_t alpha) {
  cmd.use_const_alpha = 1;
  cmd.alpha = alpha;
}

void DMPIPUConfig::ConfigUseBLF() {
  cmd.blf = 1;
}

void DMPIPUConfig::Clear() {
  memset(&cmd, 0, sizeof(cmd));
  cmd.header.version = 0;
  cmd.header.size = sizeof(cmd);
  cmd.header.device_type = DMP_DV_DEV_IPU;
}

struct dmp_dv_cmdraw_ipu_v0 *DMPIPUConfig::get_rawcmd() {
  return &cmd;
}

DMPIPU::DMPIPU() {
  Clear(false);
}

static inline size_t CalcEntireImageSize(uint32_t width, uint32_t height, int32_t stride) {
  uint32_t st_abs = std::abs(stride);
  return height * std::max(st_abs, width);
}

static int GetPixelSize(int fmt) {
  switch(fmt) {
    case DMP_DV_RGBFP16:
      return 6;
    case DMP_DV_RGB888:
      return 3;
    case DMP_DV_RGBA8888:
      return 4;
    case DMP_DV_LUT:
      return 1;
    default:
      return -1;
  }
}

static int AllocAndMapDMPDVMem(dmp_dv_context ctx, 
                  dmp_dv_mem &mem, uint8_t *&map, size_t size) {
  mem = nullptr;
  map = nullptr;

  mem = dmp_dv_mem_alloc(ctx, size);
  if(!mem) {
    return -1;
  }
  map = dmp_dv_mem_map(mem);
  if(!map) {
    dmp_dv_mem_release(mem);
    mem = nullptr;
    return -1;
  }

  return 0;
}

/// @detail This allocates buffers that will be used but no memory is assigned to.
int DMPIPU::AllocAndMapEachMem(struct dmp_dv_cmdraw_ipu_v0 *cmd) {
  dmp_dv_mem mem = nullptr;
  uint8_t *map = nullptr;
  uint64_t offs = 0;
  size_t tex_sz = 0;
  size_t rd_sz = 0;
  size_t wr_sz = 0;
  int ret = 0;

  tex_sz = cmd->use_tex != 0 && cmd->tex.mem == nullptr 
            ? CalcEntireImageSize(cmd->tex_width, cmd->tex_height, cmd->tex_width) * GetPixelSize(cmd->fmt_tex)
            : 0;
  rd_sz = cmd->use_rd != 0 && cmd->rd.mem == nullptr 
            ? CalcEntireImageSize(cmd->rect_width, cmd->rect_height, cmd->stride_rd) * GetPixelSize(cmd->fmt_rd)
            : 0;
  wr_sz = cmd->wr.mem == nullptr
            ? CalcEntireImageSize(cmd->rect_width, cmd->rect_height, cmd->stride_wr) * GetPixelSize(cmd->fmt_wr)
            : 0;

  ret = AllocAndMapDMPDVMem(this->ctx, mem, map, tex_sz + rd_sz + wr_sz);
  if(ret) {
    goto error;
  }
  if(tex_sz) {
    this->tex.mem  = mem;
    this->tex.offs = offs;
    this->tex_map  = map;
    cmd->tex.mem   = this->tex.mem;
    cmd->tex.offs  = this->tex.offs;
    offs += tex_sz;
  }
  if(rd_sz) {
    this->rd.mem  = mem;
    this->rd.offs = offs;
    this->rd_map  = map;
    cmd->rd.mem   = this->rd.mem;
    cmd->rd.offs  = this->rd.offs + (cmd->stride_rd < 0; rd_sz - cmd->rect_width : 0);
    offs += rd_sz;
  }
  if(wr_sz) {
    this->wr.mem  = mem;
    this->wr.offs = offs;
    this->wr_map  = map;
    cmd->wr.mem   = this->wr.mem;
    cmd->wr.offs  = this->wr.offs + (cmd->stride_wr < 0 ? wr_sz - cmd->rect_width : 0);
    offs += wr_sz;
  }

error:
  return ret;
}

int DMPIPU::Initialize(DMPIPUConfig &initializer) {
  struct dmp_dv_cmdraw_ipu_v0 cmd;
  int ret = 0;
  
  if(initialized) {
    ERR("DMPIPU is already initialized\n");
    return -1;
  }

  memcpy(&cmd, initializer.get_rawcmd(), sizeof(cmd));

  ctx = dmp_dv_context_create();
  if(!ctx) {
    ret = -1;
    goto error;
  }
  ret = AllocAndMapEachMem(&cmd);
  if(ret){
    goto error;
  }
  ret = InitializeCmdlist(&cmd);

error:
  if(ret) {
    Clear();
  } else {
    initialized = true;
  }

  return ret;
}

int DMPIPU::InitializePreproc(DMPIPUConfig &initializer, const CDMP_Network &net) {
  struct dmp_dv_cmdraw_ipu_v0 cmd;
  const fpga_layer &layer = net.layers_[0];
  int ret = 0;

  if(initialized) {
    ERR("DMPIPU is already initialized\n");
    return -1;
  }

  memcpy(&cmd, initializer.get_rawcmd(), sizeof(cmd));

  if(!cmd.fmt_wr && cmd.fmt_wr != DMP_DV_RGBFP16) {
    ret = -2;
    goto error;
  }

  // get info from layer
  if(!cmd.fmt_wr) {
    cmd.fmt_wr = DMP_DV_RGBFP16;
  }
  if(!cmd.rect_height) {
    cmd.rect_height = layer.input_dim[0];
  }
  if(!cmd.rect_width) {
    cmd.rect_width = layer.input_dim[1];
  }
  if(!cmd.stride_wr) {
    cmd.stride_wr = layer.input_dim[1];
  }

  // get members from net
  this->wr.mem  = net.io_mem_;
  this->wr.offs = layer.input_offs;
  this->ctx      = net.ctx_;
  this->net      = &net;
  this->i_output = -1;
  dmp_dv_mem_retain(this->wr.mem);
  dmp_dv_context_retain(this->ctx);
  this->wr_map = dmp_dv_mem_map(this->wr.mem);
  if(!this->wr_map) {
    ret = -1;
    goto error;
  }

  ret = AllocAndMapEachMem(&cmd);
  if(ret) {
    goto error;
  }
  ret = InitializeCmdlist(&cmd);

error:
  if(ret) {
    Clear();
  } else {
    initialized = true;
  }

  return ret;
}

int DMPIPU::InitializePostproc(DMPIPUConfig &initializer, const CDMP_Network &net, int i_output) {
  struct dmp_dv_cmdraw_ipu_v0 cmd;
  const fpga_layer *layer = net.output_layers_[i_output];
  int ret = 0;

  if(initialized) {
    ERR("DMPIPU is already initialized\n");
    return -1;
  }

  memcpy(&cmd, initializer.get_rawcmd(), sizeof(cmd));

  // get info from layer
  if(!cmd.tex_height) {
    cmd.tex_height = layer->output_dim[0];
  }
  if(!cmd.tex_width) {
    cmd.tex_width = layer->output_dim[1];
  }

  // get members from net
  this->tex.mem  = net.io_mem_;
  this->tex.offs = layer->output_offs;
  this->ctx      = net.ctx_;
  this->net      = &net;
  this->i_output = -1;
  dmp_dv_mem_retain(this->tex.mem);
  dmp_dv_context_retain(this->ctx);
  this->tex_map = dmp_dv_mem_map(this->tex.mem);
  if(!this->tex_map) {
    ret = -1;
    goto error;
  }

  ret = AllocAndMapEachMem(&cmd);
  if(ret) {
    goto error;
  }
  ret = InitializeCmdlist(&cmd);

error:
  if(ret) {
    Clear();
  } else {
    initialized = true;
  }

  return ret;
}

int DMPIPU::Run() {
  int64_t id = dmp_dv_cmdlist_exec(cmdlist);
  if(id < 0) {
    return -1;
  }

  return dmp_dv_cmdlist_wait(cmdlist, id);
}

uint8_t *DMPIPU::get_tex_addr_cpu() const {
  return tex_map + tex.offs;
}

uint8_t *DMPIPU::get_rd_addr_cpu() const {
  return rd_map + rd.offs;
}

uint8_t *DMPIPU::get_wr_addr_cpu() const {
  return wr_map + wr.offs;
}

bool DMPIPU::is_preprocessing() const {
  return net != nullptr && i_output < 0;
}

bool DMPIPU::is_postprocessing() const {
  return net != nullptr && i_output >= 0;
}

bool DMPIPU::is_initialized() const {
  return initialized;
}

void DMPIPU::Clear(bool release_resources) {
  if(release_resources) {
    dmp_dv_cmdlist_release(cmdlist);
    dmp_dv_context_release(ctx);
    if(tex_map) {
      dmp_dv_mem_unmap(tex.mem);
    }
    if(rd_map
        && rd_map != tex_map) {
      dmp_dv_mem_unmap(rd.mem);
    }
    if(wr_map
        && wr_map != rd_map
        && wr_map != tex_map) {
      dmp_dv_mem_unmap(wr.mem);
    }
    dmp_dv_mem_release(tex.mem);
    dmp_dv_mem_release(rd.mem);
    dmp_dv_mem_release(wr.mem);
  }

  ctx      = nullptr;
  cmdlist  = nullptr;

  memset(&tex, 0, sizeof(tex));
  memset(&wr, 0, sizeof(wr));
  memset(&rd, 0, sizeof(rd));

  tex_map  = nullptr;
  rd_map   = nullptr;
  wr_map   = nullptr;

  i_output = 0;
  net      = nullptr;

  initialized = false;
}

int DMPIPU::InitializeCmdlist(dmp_dv_cmdraw_ipu_v0 *cmd) {
  int ret = 0;

  cmdlist = dmp_dv_cmdlist_create(ctx);
  if(!cmdlist) {
    ret = -1;
    goto error;
  }

  ret = dmp_dv_cmdlist_add_raw(cmdlist, reinterpret_cast<dmp_dv_cmdraw*>(cmd));
  if(ret) {
    goto error;
  }

  ret = dmp_dv_cmdlist_commit(cmdlist);
  if(ret) {
    goto error;
  }

error:
  if(ret) {
    dmp_dv_cmdlist_release(cmdlist);
    cmdlist = nullptr;
  }

  return ret;
}
