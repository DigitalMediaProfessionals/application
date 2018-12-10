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


DMPMaximizer::DMPMaximizer() {
  Clear(false);
}

DMPMaximizer::~DMPMaximizer() {
  Clear();
}

int DMPMaximizer::Initialize(uint16_t width, uint16_t height, uint8_t nclass,
                              CDMP_Network *net, int i_output) {
  // TODO:impl
}

int DMPMaximizer::Run() {
  // TODO:impl
}

uint16_t DMPMaximizer::get_width() {
  return width;
}

uint16_t get_height() {
  return height;
}

uint8_t get_nclass() {
  return nclass;
}

uint8_t *get_in_addr_cpu() const {
  return in.mem ? in_map + in.offs : nullptr;
}

uint8_t *get_out_addr_cpu() const {
  return out.mem ? out_map + out.offs : nullptr;
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
