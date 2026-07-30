//
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
//
// -----------------------------------------------------------------------------
// File: bit_gen_ref.h
// -----------------------------------------------------------------------------
//
// This header defines a bit generator "reference" class, for use in interfaces
// that take both Abseil (e.g. `absl::BitGen`) and standard library (e.g.
// `std::mt19937`) bit generators.

#ifndef ABSL_RANDOM_BIT_GEN_REF_H_
#define ABSL_RANDOM_BIT_GEN_REF_H_

#include <cstdint>
#include <limits>
#include <type_traits>

#include "absl/base/attributes.h"
#include "absl/base/config.h"
#include "absl/base/fast_type_id.h"
#include "absl/meta/type_traits.h"
#include "absl/random/internal/fast_uniform_bits.h"
#include "absl/random/internal/traits.h"
#include "absl/random/mocking_access.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

// -----------------------------------------------------------------------------
// absl::BitGenRef
// -----------------------------------------------------------------------------
//
// `absl::BitGenRef` is a type-erasing class that provides a generator-agnostic
// non-owning "reference" interface for use in place of any specific uniform
// random bit generator (URBG). This class may be used for both Abseil
// (e.g. `absl::BitGen`, `absl::InsecureBitGen`) and Standard library (e.g
// `std::mt19937`, `std::minstd_rand`) bit generators.
//
// Like other reference classes, `absl::BitGenRef` does not own the
// underlying bit generator, and the underlying instance must outlive the
// `absl::BitGenRef`.
//
// `absl::BitGenRef` is particularly useful when used with an
// `absl::MockingBitGen` to test specific paths in functions which use random
// values.
//
// Example:
//    void TakesBitGenRef(absl::BitGenRef gen) {
//      int x = absl::Uniform<int>(gen, 0, 1000);
//    }
//
class BitGenRef { __builtin_trap() /* STUB: not implemented */; };

ABSL_NAMESPACE_END
}  // namespace absl

#endif  // ABSL_RANDOM_BIT_GEN_REF_H_
