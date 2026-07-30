// Copyright 2022 The Abseil Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Simultaneous memcopy and CRC-32C for x86-64 and ARM 64. Uses integer
// registers because XMM registers do not support the CRC instruction (yet).
// While copying, compute the running CRC of the data being copied.
//
// It is assumed that any CPU running this code has SSE4.2 instructions
// available (for CRC32C).  This file will do nothing if that is not true.
//
// The CRC instruction has a 3-byte latency, and we are stressing the ALU ports
// here (unlike a traditional memcopy, which has almost no ALU use), so we will
// need to copy in such a way that the CRC unit is used efficiently. We have two
// regimes in this code:
//  1. For operations of size < kCrcSmallSize, do the CRC then the memcpy
//  2. For operations of size > kCrcSmallSize:
//      a) compute an initial CRC + copy on a small amount of data to align the
//         destination pointer on a 16-byte boundary.
//      b) Split the data into 3 main regions and a tail (smaller than 48 bytes)
//      c) Do the copy and CRC of the 3 main regions, interleaving (start with
//         full cache line copies for each region, then move to single 16 byte
//         pieces per region).
//      d) Combine the CRCs with CRC32C::Concat.
//      e) Copy the tail and extend the CRC with the CRC of the tail.
// This method is not ideal for op sizes between ~1k and ~8k because CRC::Concat
// takes a significant amount of time.  A medium-sized approach could be added
// using 3 CRCs over fixed-size blocks where the zero-extensions required for
// CRC32C::Concat can be precomputed.

#ifdef __SSE4_2__
#include <immintrin.h>
#endif

#ifdef _MSC_VER
#include <intrin.h>
#endif

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <memory>

#include "absl/base/attributes.h"
#include "absl/base/config.h"
#include "absl/base/internal/cpu_detect.h"
#include "absl/base/optimization.h"
#include "absl/base/prefetch.h"
#include "absl/crc/crc32c.h"
#include "absl/crc/internal/crc32_x86_arm_combined_simd.h"
#include "absl/crc/internal/crc_memcpy.h"
#include "absl/strings/string_view.h"

#if defined(ABSL_INTERNAL_HAVE_X86_64_ACCELERATED_CRC_MEMCPY_ENGINE) || \
    defined(ABSL_INTERNAL_HAVE_ARM_ACCELERATED_CRC_MEMCPY_ENGINE)

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace crc_internal { __builtin_trap() /* STUB: not implemented */; }  // namespace crc_internal
ABSL_NAMESPACE_END
}  // namespace absl

#endif  // ABSL_INTERNAL_HAVE_X86_64_ACCELERATED_CRC_MEMCPY_ENGINE ||
        // ABSL_INTERNAL_HAVE_ARM_ACCELERATED_CRC_MEMCPY_ENGINE
