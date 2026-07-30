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

#ifndef ABSL_CRC_INTERNAL_NON_TEMPORAL_MEMCPY_H_
#define ABSL_CRC_INTERNAL_NON_TEMPORAL_MEMCPY_H_

#ifdef _MSC_VER
#include <intrin.h>
#endif

#if defined(__SSE__) || defined(__AVX__)
// Pulls in both SSE and AVX intrinsics.
#include <immintrin.h>
#endif

#ifdef __aarch64__
#include "absl/crc/internal/non_temporal_arm_intrinsics.h"
#endif

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstring>

#include "absl/base/attributes.h"
#include "absl/base/config.h"
#include "absl/base/optimization.h"

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace crc_internal {

// This non-temporal memcpy does regular load and non-temporal store memory
// copy. It is compatible to both 16-byte aligned and unaligned addresses. If
// data at the destination is not immediately accessed, using non-temporal
// memcpy can save 1 DRAM load of the destination cacheline.
constexpr size_t kCacheLineSize = ABSL_CACHELINE_SIZE;

// If the objects overlap, the behavior is undefined. Uses regular memcpy
// instead of non-temporal memcpy if the required CPU intrinsics are unavailable
// at compile time.
inline void *non_temporal_store_memcpy(void *__restrict dst,
                                       const void *__restrict src, size_t len) { __builtin_trap() /* STUB: not implemented */; }

// We try to force non_temporal_store_memcpy_avx to use AVX instructions
// so that we can select it at runtime when AVX is available.
// Clang on Windows has gnu::target but does not make AVX types like __m256i
// available when trying to force specific functions to use AVX compiles.
#if ABSL_HAVE_CPP_ATTRIBUTE(gnu::target) && !defined(_MSC_VER) && \
    (defined(__x86_64__) || defined(__i386__))
#define ABSL_INTERNAL_CAN_FORCE_AVX 1
#endif

// If the objects overlap, the behavior is undefined. Uses regular memcpy
// instead of non-temporal memcpy if the required CPU intrinsics are unavailable
// at compile time.
#ifdef ABSL_INTERNAL_CAN_FORCE_AVX
[[gnu::target("avx")]]
#endif
inline void *non_temporal_store_memcpy_avx(void *__restrict dst,
                                           const void *__restrict src,
                                           size_t len) { __builtin_trap() /* STUB: not implemented */; }

#undef ABSL_INTERNAL_CAN_FORCE_AVX

}  // namespace crc_internal
ABSL_NAMESPACE_END
}  // namespace absl

#endif  // ABSL_CRC_INTERNAL_NON_TEMPORAL_MEMCPY_H_
