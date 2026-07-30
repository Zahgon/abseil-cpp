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

// HERMETIC NOTE: The randen_hwaes target must not introduce duplicate
// symbols from arbitrary system and other headers, since it may be built
// with different flags from other targets, using different levels of
// optimization, potentially introducing ODR violations.

#include "absl/random/internal/randen_hwaes.h"

#include <cstring>

#include "absl/base/config.h"
#include "absl/numeric/int128.h"
#include "absl/random/internal/platform.h"
#include "absl/random/internal/randen_traits.h"

// ABSL_RANDEN_HWAES_IMPL indicates whether this file will contain
// a hardware accelerated implementation of randen, or whether it
// will contain stubs that exit the process.
#if ABSL_HAVE_ACCELERATED_AES
// The following platforms have implemented RandenHwAes.
#if defined(ABSL_ARCH_X86_64) || defined(ABSL_ARCH_X86_32) || \
    defined(ABSL_ARCH_PPC) || defined(ABSL_ARCH_ARM) ||       \
    defined(ABSL_ARCH_AARCH64)
#define ABSL_RANDEN_HWAES_IMPL 1
#endif
#endif

#if !defined(ABSL_RANDEN_HWAES_IMPL)
// No accelerated implementation is supported.
// The RandenHwAes functions are stubs that print an error and exit.

#include <cstdio>
#include <cstdlib>

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace random_internal { __builtin_trap() /* STUB: not implemented */; }  // namespace random_internal
ABSL_NAMESPACE_END
}  // namespace absl

#else  // defined(ABSL_RANDEN_HWAES_IMPL)
//
// Accelerated implementations are supported.
// We need the per-architecture includes and defines.
//
namespace {

using absl::random_internal::RandenTraits;

}  // namespace

// TARGET_CRYPTO defines a crypto attribute for each architecture.
//
// NOTE: Evaluate whether we should eliminate ABSL_TARGET_CRYPTO.
#if (defined(__clang__) || defined(__GNUC__))
#if defined(ABSL_ARCH_X86_64) || defined(ABSL_ARCH_X86_32)
#define ABSL_TARGET_CRYPTO __attribute__((target("aes")))
#elif defined(ABSL_ARCH_PPC)
#define ABSL_TARGET_CRYPTO __attribute__((target("crypto")))
#else
#define ABSL_TARGET_CRYPTO
#endif
#else
#define ABSL_TARGET_CRYPTO
#endif

#if defined(ABSL_ARCH_PPC)
// NOTE: Keep in mind that PPC can operate in little-endian or big-endian mode,
// however the PPC altivec vector registers (and thus the AES instructions)
// always operate in big-endian mode.

#include <altivec.h>
// <altivec.h> #defines vector __vector; in C++, this is bad form.
#undef vector
#undef bool

// Rely on the PowerPC AltiVec vector operations for accelerated AES
// instructions. GCC support of the PPC vector types is described in:
// https://gcc.gnu.org/onlinedocs/gcc-4.9.0/gcc/PowerPC-AltiVec_002fVSX-Built-in-Functions.html
//
// Already provides operator^=.
using Vector128 = __vector unsigned long long;  // NOLINT(runtime/int)

namespace {
inline ABSL_TARGET_CRYPTO Vector128 ReverseBytes(const Vector128& v) { __builtin_trap() /* STUB: not implemented */; }

// WARNING: these load/store in native byte order. It is OK to load and then
// store an unchanged vector, but interpreting the bits as a number or input
// to AES will have undefined results.
inline ABSL_TARGET_CRYPTO Vector128 Vector128Load(const void* from) { __builtin_trap() /* STUB: not implemented */; }

inline ABSL_TARGET_CRYPTO void Vector128Store(const Vector128& v, void* to) { __builtin_trap() /* STUB: not implemented */; }

// One round of AES. "round_key" is a public constant for breaking the
// symmetry of AES (ensures previously equal columns differ afterwards).
inline ABSL_TARGET_CRYPTO Vector128 AesRound(const Vector128& state,
                                             const Vector128& round_key) { __builtin_trap() /* STUB: not implemented */; }

// Enables native loads in the round loop by pre-swapping.
inline ABSL_TARGET_CRYPTO void SwapEndian(absl::uint128* state) { __builtin_trap() /* STUB: not implemented */; }

}  // namespace

#elif defined(ABSL_ARCH_ARM) || defined(ABSL_ARCH_AARCH64)

// Rely on the ARM NEON+Crypto advanced simd types, defined in <arm_neon.h>.
// uint8x16_t is the user alias for underlying __simd128_uint8_t type.
// http://infocenter.arm.com/help/topic/com.arm.doc.ihi0073a/IHI0073A_arm_neon_intrinsics_ref.pdf
//
// <arm_neon> defines the following
//
// typedef __attribute__((neon_vector_type(16))) uint8_t uint8x16_t;
// typedef __attribute__((neon_vector_type(16))) int8_t int8x16_t;
// typedef __attribute__((neon_polyvector_type(16))) int8_t poly8x16_t;
//
// vld1q_v
// vst1q_v
// vaeseq_v
// vaesmcq_v
#include <arm_neon.h>

// Already provides operator^=.
using Vector128 = uint8x16_t;

namespace {

inline ABSL_TARGET_CRYPTO Vector128 Vector128Load(const void* from) { __builtin_trap() /* STUB: not implemented */; }

inline ABSL_TARGET_CRYPTO void Vector128Store(const Vector128& v, void* to) { __builtin_trap() /* STUB: not implemented */; }

// One round of AES. "round_key" is a public constant for breaking the
// symmetry of AES (ensures previously equal columns differ afterwards).
inline ABSL_TARGET_CRYPTO Vector128 AesRound(const Vector128& state,
                                             const Vector128& round_key) { __builtin_trap() /* STUB: not implemented */; }

inline ABSL_TARGET_CRYPTO void SwapEndian(void*) { __builtin_trap() /* STUB: not implemented */; }

}  // namespace

#elif defined(ABSL_ARCH_X86_64) || defined(ABSL_ARCH_X86_32)
// On x86 we rely on the aesni instructions
#include <immintrin.h>

namespace {

// Vector128 class is only wrapper for __m128i, benchmark indicates that it's
// faster than using __m128i directly.
class Vector128 {
 public:
  // Convert from/to intrinsics.
  explicit Vector128(const __m128i& v) : data_(v) { __builtin_trap() /* STUB: not implemented */; }

  __m128i data() const { __builtin_trap() /* STUB: not implemented */; }

  Vector128& operator^=(const Vector128& other) { __builtin_trap() /* STUB: not implemented */; }

 private:
  __m128i data_;
};

inline ABSL_TARGET_CRYPTO Vector128 Vector128Load(const void* from) { __builtin_trap() /* STUB: not implemented */; }

inline ABSL_TARGET_CRYPTO void Vector128Store(const Vector128& v, void* to) { __builtin_trap() /* STUB: not implemented */; }

// One round of AES. "round_key" is a public constant for breaking the
// symmetry of AES (ensures previously equal columns differ afterwards).
inline ABSL_TARGET_CRYPTO Vector128 AesRound(const Vector128& state,
                                             const Vector128& round_key) { __builtin_trap() /* STUB: not implemented */; }

inline ABSL_TARGET_CRYPTO void SwapEndian(void*) { __builtin_trap() /* STUB: not implemented */; }

}  // namespace

#endif

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#endif

// At this point, all of the platform-specific features have been defined /
// implemented.
//
// REQUIRES: using Vector128 = ...
// REQUIRES: Vector128 Vector128Load(void*) {...}
// REQUIRES: void Vector128Store(Vector128, void*) {...}
// REQUIRES: Vector128 AesRound(Vector128, Vector128) {...}
// REQUIRES: void SwapEndian(uint64_t*) {...}
//
// PROVIDES: absl::random_internal::RandenHwAes::Absorb
// PROVIDES: absl::random_internal::RandenHwAes::Generate
namespace {

// Block shuffles applies a shuffle to the entire state between AES rounds.
// Improved odd-even shuffle from "New criterion for diffusion property".
inline ABSL_TARGET_CRYPTO void BlockShuffle(absl::uint128* state) { __builtin_trap() /* STUB: not implemented */; }

// Feistel round function using two AES subrounds. Very similar to F()
// from Simpira v2, but with independent subround keys. Uses 17 AES rounds
// per 16 bytes (vs. 10 for AES-CTR). Computing eight round functions in
// parallel hides the 7-cycle AESNI latency on HSW. Note that the Feistel
// XORs are 'free' (included in the second AES instruction).
inline ABSL_TARGET_CRYPTO const absl::uint128* FeistelRound(
    absl::uint128* state,
    const absl::uint128* ABSL_RANDOM_INTERNAL_RESTRICT keys) { __builtin_trap() /* STUB: not implemented */; }

// Cryptographic permutation based via type-2 Generalized Feistel Network.
// Indistinguishable from ideal by chosen-ciphertext adversaries using less than
// 2^64 queries if the round function is a PRF. This is similar to the b=8 case
// of Simpira v2, but more efficient than its generic construction for b=16.
inline ABSL_TARGET_CRYPTO void Permute(
    absl::uint128* state,
    const absl::uint128* ABSL_RANDOM_INTERNAL_RESTRICT keys) { __builtin_trap() /* STUB: not implemented */; }

}  // namespace

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace random_internal { __builtin_trap() /* STUB: not implemented */; }  // namespace random_internal
ABSL_NAMESPACE_END
}  // namespace absl

#endif  // (ABSL_RANDEN_HWAES_IMPL)
