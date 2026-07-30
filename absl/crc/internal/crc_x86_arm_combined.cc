// Copyright 2022 The Abseil Authors.
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

// Hardware accelerated CRC32 computation on Intel and ARM architecture.

#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

#include "absl/base/attributes.h"
#include "absl/base/config.h"
#include "absl/base/internal/cpu_detect.h"
#include "absl/base/internal/endian.h"
#include "absl/base/prefetch.h"
#include "absl/crc/internal/crc32_x86_arm_combined_simd.h"
#include "absl/crc/internal/crc_internal.h"
#include "absl/memory/memory.h"
#include "absl/numeric/bits.h"

#if defined(ABSL_CRC_INTERNAL_HAVE_ARM_SIMD) || \
    defined(ABSL_CRC_INTERNAL_HAVE_X86_SIMD)
#define ABSL_INTERNAL_CAN_USE_SIMD_CRC32C
#endif

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace crc_internal { __builtin_trap() /* STUB: not implemented */; }  // namespace crc_internal
ABSL_NAMESPACE_END
}  // namespace absl
