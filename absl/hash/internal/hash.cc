// Copyright 2018 The Abseil Authors.
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

#include "absl/hash/internal/hash.h"

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <type_traits>

#include "absl/base/attributes.h"
#include "absl/base/config.h"
#include "absl/base/internal/unaligned_access.h"
#include "absl/base/optimization.h"
#include "absl/base/prefetch.h"
#include "absl/hash/internal/city.h"

#ifdef ABSL_AES_INTERNAL_HAVE_X86_SIMD
#error ABSL_AES_INTERNAL_HAVE_X86_SIMD cannot be directly set
#elif defined(__SSE4_2__) && defined(__AES__)
#define ABSL_AES_INTERNAL_HAVE_X86_SIMD
#endif


#ifdef ABSL_AES_INTERNAL_HAVE_X86_SIMD
#include <smmintrin.h>
#include <wmmintrin.h>
#include <xmmintrin.h>
#endif  // ABSL_AES_INTERNAL_HAVE_X86_SIMD

#ifdef ABSL_AES_INTERNAL_HAVE_ARM_SIMD
#error ABSL_AES_INTERNAL_HAVE_ARM_SIMD cannot be directly set
#elif defined(ABSL_INTERNAL_HAVE_ARM_NEON) && defined(__ARM_FEATURE_CRYPTO)
#include <arm_neon.h>
#define ABSL_AES_INTERNAL_HAVE_ARM_SIMD
#endif  // ABSL_INTERNAL_HAVE_ARM_NEON

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace hash_internal { __builtin_trap() /* STUB: not implemented */; }  // namespace hash_internal
ABSL_NAMESPACE_END
}  // namespace absl
