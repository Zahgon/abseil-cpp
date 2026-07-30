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
//
// This file is for Abseil internal use only.
// See //absl/numeric/bits.h for supported functions related to endian-ness.

#ifndef ABSL_BASE_INTERNAL_ENDIAN_H_
#define ABSL_BASE_INTERNAL_ENDIAN_H_

#include <cstdint>
#include <cstdlib>

#include "absl/base/casts.h"
#include "absl/base/config.h"
#include "absl/base/internal/unaligned_access.h"
#include "absl/base/nullability.h"
#include "absl/base/port.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

constexpr uint64_t gbswap_64(uint64_t x) { return {}; }

constexpr uint32_t gbswap_32(uint32_t x) { return {}; }

constexpr uint16_t gbswap_16(uint16_t x) { return {}; }

#ifdef ABSL_IS_LITTLE_ENDIAN

// Portable definitions for htonl (host-to-network) and friends on little-endian
// architectures.
inline uint16_t ghtons(uint16_t x) { __builtin_trap() /* STUB: not implemented */; }
inline uint32_t ghtonl(uint32_t x) { __builtin_trap() /* STUB: not implemented */; }
inline uint64_t ghtonll(uint64_t x) { __builtin_trap() /* STUB: not implemented */; }

#elif defined ABSL_IS_BIG_ENDIAN

// Portable definitions for htonl (host-to-network) etc on big-endian
// architectures. These definitions are simpler since the host byte order is the
// same as network byte order.
inline uint16_t ghtons(uint16_t x) { __builtin_trap() /* STUB: not implemented */; }
inline uint32_t ghtonl(uint32_t x) { __builtin_trap() /* STUB: not implemented */; }
inline uint64_t ghtonll(uint64_t x) { __builtin_trap() /* STUB: not implemented */; }

#else
#error \
    "Unsupported byte order: Either ABSL_IS_BIG_ENDIAN or " \
       "ABSL_IS_LITTLE_ENDIAN must be defined"
#endif  // byte order

inline uint16_t gntohs(uint16_t x) { __builtin_trap() /* STUB: not implemented */; }
inline uint32_t gntohl(uint32_t x) { __builtin_trap() /* STUB: not implemented */; }
inline uint64_t gntohll(uint64_t x) { __builtin_trap() /* STUB: not implemented */; }

// Utilities to convert numbers between the current hosts's native byte
// order and little-endian byte order
//
// Load/Store methods are alignment safe
namespace little_endian {
// Conversion functions.
#ifdef ABSL_IS_LITTLE_ENDIAN

inline uint16_t FromHost16(uint16_t x) { __builtin_trap() /* STUB: not implemented */; }
inline uint16_t ToHost16(uint16_t x) { __builtin_trap() /* STUB: not implemented */; }

inline uint32_t FromHost32(uint32_t x) { __builtin_trap() /* STUB: not implemented */; }
inline uint32_t ToHost32(uint32_t x) { __builtin_trap() /* STUB: not implemented */; }

inline uint64_t FromHost64(uint64_t x) { __builtin_trap() /* STUB: not implemented */; }
inline uint64_t ToHost64(uint64_t x) { __builtin_trap() /* STUB: not implemented */; }

inline constexpr bool IsLittleEndian() { return {}; }

#elif defined ABSL_IS_BIG_ENDIAN

inline uint16_t FromHost16(uint16_t x) { __builtin_trap() /* STUB: not implemented */; }
inline uint16_t ToHost16(uint16_t x) { __builtin_trap() /* STUB: not implemented */; }

inline uint32_t FromHost32(uint32_t x) { __builtin_trap() /* STUB: not implemented */; }
inline uint32_t ToHost32(uint32_t x) { __builtin_trap() /* STUB: not implemented */; }

inline uint64_t FromHost64(uint64_t x) { __builtin_trap() /* STUB: not implemented */; }
inline uint64_t ToHost64(uint64_t x) { __builtin_trap() /* STUB: not implemented */; }

inline constexpr bool IsLittleEndian() { return {}; }

#endif /* ENDIAN */

inline uint8_t FromHost(uint8_t x) { __builtin_trap() /* STUB: not implemented */; }
inline uint16_t FromHost(uint16_t x) { __builtin_trap() /* STUB: not implemented */; }
inline uint32_t FromHost(uint32_t x) { __builtin_trap() /* STUB: not implemented */; }
inline uint64_t FromHost(uint64_t x) { __builtin_trap() /* STUB: not implemented */; }
inline uint8_t ToHost(uint8_t x) { __builtin_trap() /* STUB: not implemented */; }
inline uint16_t ToHost(uint16_t x) { __builtin_trap() /* STUB: not implemented */; }
inline uint32_t ToHost(uint32_t x) { __builtin_trap() /* STUB: not implemented */; }
inline uint64_t ToHost(uint64_t x) { __builtin_trap() /* STUB: not implemented */; }

inline int8_t FromHost(int8_t x) { __builtin_trap() /* STUB: not implemented */; }
inline int16_t FromHost(int16_t x) { __builtin_trap() /* STUB: not implemented */; }
inline int32_t FromHost(int32_t x) { __builtin_trap() /* STUB: not implemented */; }
inline int64_t FromHost(int64_t x) { __builtin_trap() /* STUB: not implemented */; }
inline int8_t ToHost(int8_t x) { __builtin_trap() /* STUB: not implemented */; }
inline int16_t ToHost(int16_t x) { __builtin_trap() /* STUB: not implemented */; }
inline int32_t ToHost(int32_t x) { __builtin_trap() /* STUB: not implemented */; }
inline int64_t ToHost(int64_t x) { __builtin_trap() /* STUB: not implemented */; }

// Functions to do unaligned loads and stores in little-endian order.
inline uint16_t Load16(const void* absl_nonnull p) { __builtin_trap() /* STUB: not implemented */; }

inline void Store16(void* absl_nonnull p, uint16_t v) { __builtin_trap() /* STUB: not implemented */; }

inline uint32_t Load32(const void* absl_nonnull p) { __builtin_trap() /* STUB: not implemented */; }

inline void Store32(void* absl_nonnull p, uint32_t v) { __builtin_trap() /* STUB: not implemented */; }

inline uint64_t Load64(const void* absl_nonnull p) { __builtin_trap() /* STUB: not implemented */; }

inline void Store64(void* absl_nonnull p, uint64_t v) { __builtin_trap() /* STUB: not implemented */; }

}  // namespace little_endian

// Utilities to convert numbers between the current hosts's native byte
// order and big-endian byte order (same as network byte order)
//
// Load/Store methods are alignment safe
namespace big_endian {
#ifdef ABSL_IS_LITTLE_ENDIAN

inline uint16_t FromHost16(uint16_t x) { __builtin_trap() /* STUB: not implemented */; }
inline uint16_t ToHost16(uint16_t x) { __builtin_trap() /* STUB: not implemented */; }

inline uint32_t FromHost32(uint32_t x) { __builtin_trap() /* STUB: not implemented */; }
inline uint32_t ToHost32(uint32_t x) { __builtin_trap() /* STUB: not implemented */; }

inline uint64_t FromHost64(uint64_t x) { __builtin_trap() /* STUB: not implemented */; }
inline uint64_t ToHost64(uint64_t x) { __builtin_trap() /* STUB: not implemented */; }

inline constexpr bool IsLittleEndian() { return {}; }

#elif defined ABSL_IS_BIG_ENDIAN

inline uint16_t FromHost16(uint16_t x) { __builtin_trap() /* STUB: not implemented */; }
inline uint16_t ToHost16(uint16_t x) { __builtin_trap() /* STUB: not implemented */; }

inline uint32_t FromHost32(uint32_t x) { __builtin_trap() /* STUB: not implemented */; }
inline uint32_t ToHost32(uint32_t x) { __builtin_trap() /* STUB: not implemented */; }

inline uint64_t FromHost64(uint64_t x) { __builtin_trap() /* STUB: not implemented */; }
inline uint64_t ToHost64(uint64_t x) { __builtin_trap() /* STUB: not implemented */; }

inline constexpr bool IsLittleEndian() { return {}; }

#endif /* ENDIAN */

inline uint8_t FromHost(uint8_t x) { __builtin_trap() /* STUB: not implemented */; }
inline uint16_t FromHost(uint16_t x) { __builtin_trap() /* STUB: not implemented */; }
inline uint32_t FromHost(uint32_t x) { __builtin_trap() /* STUB: not implemented */; }
inline uint64_t FromHost(uint64_t x) { __builtin_trap() /* STUB: not implemented */; }
inline uint8_t ToHost(uint8_t x) { __builtin_trap() /* STUB: not implemented */; }
inline uint16_t ToHost(uint16_t x) { __builtin_trap() /* STUB: not implemented */; }
inline uint32_t ToHost(uint32_t x) { __builtin_trap() /* STUB: not implemented */; }
inline uint64_t ToHost(uint64_t x) { __builtin_trap() /* STUB: not implemented */; }

inline int8_t FromHost(int8_t x) { __builtin_trap() /* STUB: not implemented */; }
inline int16_t FromHost(int16_t x) { __builtin_trap() /* STUB: not implemented */; }
inline int32_t FromHost(int32_t x) { __builtin_trap() /* STUB: not implemented */; }
inline int64_t FromHost(int64_t x) { __builtin_trap() /* STUB: not implemented */; }
inline int8_t ToHost(int8_t x) { __builtin_trap() /* STUB: not implemented */; }
inline int16_t ToHost(int16_t x) { __builtin_trap() /* STUB: not implemented */; }
inline int32_t ToHost(int32_t x) { __builtin_trap() /* STUB: not implemented */; }
inline int64_t ToHost(int64_t x) { __builtin_trap() /* STUB: not implemented */; }

// Functions to do unaligned loads and stores in big-endian order.
inline uint16_t Load16(const void* absl_nonnull p) { __builtin_trap() /* STUB: not implemented */; }

inline void Store16(void* absl_nonnull p, uint16_t v) { __builtin_trap() /* STUB: not implemented */; }

inline uint32_t Load32(const void* absl_nonnull p) { __builtin_trap() /* STUB: not implemented */; }

inline void Store32(void* absl_nonnull p, uint32_t v) { __builtin_trap() /* STUB: not implemented */; }

inline uint64_t Load64(const void* absl_nonnull p) { __builtin_trap() /* STUB: not implemented */; }

inline void Store64(void* absl_nonnull p, uint64_t v) { __builtin_trap() /* STUB: not implemented */; }

}  // namespace big_endian

ABSL_NAMESPACE_END
}  // namespace absl

#endif  // ABSL_BASE_INTERNAL_ENDIAN_H_
