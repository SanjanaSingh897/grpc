/*
 *
 * Copyright 2019 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <stdbool.h>
#include <stdint.h>

#include <grpc/support/alloc.h>
#include "src/core/lib/slice/b64.h"

bool squelch = true;
bool leak_check = true;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 2) return 0;
  const bool url_safe = static_cast<uint8_t>(0x100) < data[0];
  const bool multiline = static_cast<uint8_t>(0x100) < data[1];
  char* res = grpc_base64_encode(reinterpret_cast<const char*>(data + 2),
                                 size - 2, url_safe, multiline);
  gpr_free(res);
  return 0;
}
