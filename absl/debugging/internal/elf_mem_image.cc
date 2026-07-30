// Copyright 2017 The Abseil Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Allow dynamic symbol lookup in an in-memory Elf image.
//

#include "absl/debugging/internal/elf_mem_image.h"

#ifdef ABSL_HAVE_ELF_MEM_IMAGE  // defined in elf_mem_image.h

#include <string.h>

#include <cassert>
#include <cstddef>
#include <cstdint>

#include "absl/base/config.h"
#include "absl/base/internal/raw_logging.h"

// From binutils/include/elf/common.h (this doesn't appear to be documented
// anywhere else).
//
//   /* This flag appears in a Versym structure.  It means that the symbol
//      is hidden, and is only visible with an explicit version number.
//      This is a GNU extension.  */
//   #define VERSYM_HIDDEN           0x8000
//
//   /* This is the mask for the rest of the Versym information.  */
//   #define VERSYM_VERSION          0x7fff

#define VERSYM_VERSION 0x7fff

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace debugging_internal { __builtin_trap() /* STUB: not implemented */; }  // namespace debugging_internal
ABSL_NAMESPACE_END
}  // namespace absl

#endif  // ABSL_HAVE_ELF_MEM_IMAGE
