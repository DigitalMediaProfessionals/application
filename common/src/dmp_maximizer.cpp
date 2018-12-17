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

#include "dmp_maximizer.h"

#define LOG(...) fprintf(stdout, __VA_ARGS__); fflush(stdout);
#define ERR(...) fprintf(stderr, __VA_ARGS__); fflush(stderr);

DMPMaximizer::DMPMaximizer() {
  Clear(false);
}

DMPMaximizer::~DMPMaximizer() {
  Clear();
}

static int AllocAndMapDMPDVMem(dmp_dv_context ctx, dmp_dv_mem &mem,
                                     uint8_t *&map, size_t size) {
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

int DMPMaximizer::Initialize(uint16_t width, uint16_t height, uint8_t nclass,
                              CDMP_Network *net, int i_output) {
  struct dmp_dv_cmdraw_maximizer_v0 cmd;
  const fpga_layer *layer = net->output_layers_[i_output];
  size_t tmp_sz = 0;
  int r = 0;

  if(initialized) {
    ERR("DMPIPU is already initialized\n");
    return -1;
  }

  this->width = width;
  this->height = height;
  this->nclass = nclass;

  // create context
  if(net) {
    ctx = net->ctx_;
  } else {
    ctx = dmp_dv_context_create();
    if(!ctx) {
      ERR("Failed to create dmp_dv_context for Maximizer: %s\n", dmp_dv_get_last_error_message());
      r = -1;
      goto error;
    }
  }

  // allocate and map input buffer
  if(net) {
    in.mem = net->io_mem_;
    in.offs = layer->output_offs;
  } else {
    tmp_sz = width * height * nclass * sizeof(__fp16);
    r = AllocAndMapDMPDVMem(ctx, in.mem, in_map, tmp_sz);
    if(r) {
      ERR("Failed to allocate and map %luB dmp_dv_mem for input buffer to Maximizer: %s\n",
          tmp_sz, dmp_dv_get_last_error_message());
      goto error;
    }
  }

  // allocate and map output buffer
  tmp_sz = width * height * sizeof(uint8_t);
  r = AllocAndMapDMPDVMem(ctx, out.mem, out_map, tmp_sz);
  if(r) {
    ERR("Failed to allocate and map %luB dmp_dv_mem for output buffer to Maximizer: %s\n",
        tmp_sz, dmp_dv_get_last_error_message());
    goto error;
  }

  // initialize cmdlist
  cmd.header.version     = 0;
  cmd.header.size        = sizeof(cmd);
  cmd.header.device_type = DMP_DV_DEV_MAXIMIZER;
  cmd.input_buf.mem   = in.mem;
  cmd.input_buf.offs  = in.offs;
  cmd.output_buf.mem  = out.mem;
  cmd.output_buf.offs = out.offs;
  cmd.width  = width;
  cmd.height = height;
  cmd.nclass = nclass;
  r = InitializeCmdlist(&cmd);
  if(r) {
    ERR("Failed to initialize cmdlist for Maximizer: %s\n",
        dmp_dv_get_last_error_message());
    goto error;
  }

error:
  if(r) {
    Clear();
  }
  return r;
}

int DMPMaximizer::Run() {
  int64_t id = dmp_dv_cmdlist_exec(cmdlist);
  if(id < 0) {
    ERR("Failed to execute cmdlist for Maximizer: %s\n",
        dmp_dv_get_last_error_message());
    return -1;
  }

  int ret = dmp_dv_cmdlist_wait(cmdlist, id);
  if(ret) {
    ERR("Failed on wainting execution of dmp_dv_cmdlist for Maximizer: %s\n",
        dmp_dv_get_last_error_message());
  }

  return ret;
}

uint16_t DMPMaximizer::get_width() {
  return width;
}

uint16_t DMPMaximizer::get_height() {
  return height;
}

uint8_t DMPMaximizer::get_nclass() {
  return nclass;
}

uint8_t *DMPMaximizer::get_in_addr_cpu() const {
  return in.mem ? in_map + in.offs : nullptr;
}

uint8_t *DMPMaximizer::get_out_addr_cpu() const {
  return out.mem ? out_map + out.offs : nullptr;
}


int DMPMaximizer::InitializeCmdlist(struct dmp_dv_cmdraw_maximizer_v0 *cmd) {
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

void DMPMaximizer::Clear(bool release_resources) {
  if(release_resources) {
    dmp_dv_cmdlist_release(cmdlist);
    dmp_dv_context_release(ctx);
    if(in_map) {
      dmp_dv_mem_unmap(in.mem);
    }
    if(out_map
        && out_map != in_map) {
      dmp_dv_mem_unmap(out.mem);
    }
    dmp_dv_mem_release(in.mem);
    dmp_dv_mem_release(out.mem);
  }

  ctx = nullptr;
  cmdlist = nullptr;
  
  memset(&in, 0, sizeof(in));
  memset(&out, 0, sizeof(out));

  in_map = nullptr;
  out_map = nullptr;

  i_output = 0;
  net      = nullptr;

  initialized = false;
}
