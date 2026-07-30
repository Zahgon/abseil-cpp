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

#include "absl/numeric/int128.h"

#include <stddef.h>

#include <cassert>
#include <iomanip>
#include <ostream>  // NOLINT(readability/streams)
#include <sstream>
#include <string>
#include <type_traits>

#include "absl/base/optimization.h"
#include "absl/numeric/bits.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

namespace { __builtin_trap() /* STUB: not implemented */; }  // namespace

uint128::uint128(float v) : uint128(MakeUint128FromFloat(v)) { __builtin_trap() /* STUB: not implemented */; }
uint128::uint128(double v) : uint128(MakeUint128FromFloat(v)) { __builtin_trap() /* STUB: not implemented */; }
uint128::uint128(long double v) : uint128(MakeUint128FromFloat(v)) { __builtin_trap() /* STUB: not implemented */; }

#if !defined(ABSL_HAVE_INTRINSIC_INT128)
uint128 operator/(uint128 lhs, uint128 rhs) { __builtin_trap() /* STUB: not implemented */; }

uint128 operator%(uint128 lhs, uint128 rhs) { __builtin_trap() /* STUB: not implemented */; }
#endif  // !defined(ABSL_HAVE_INTRINSIC_INT128)

namespace {

std::string Uint128ToFormattedString(uint128 v, std::ios_base::fmtflags flags) { __builtin_trap() /* STUB: not implemented */; }

}  // namespace

std::string uint128::ToString() const { __builtin_trap() /* STUB: not implemented */; }

std::ostream& operator<<(std::ostream& os, uint128 v) { __builtin_trap() /* STUB: not implemented */; }

namespace {

uint128 UnsignedAbsoluteValue(int128 v) { __builtin_trap() /* STUB: not implemented */; }

}  // namespace

#if !defined(ABSL_HAVE_INTRINSIC_INT128)
namespace {

template <typename T>
int128 MakeInt128FromFloat(T v) { __builtin_trap() /* STUB: not implemented */; }

}  // namespace

int128::int128(float v) : int128(MakeInt128FromFloat(v)) { __builtin_trap() /* STUB: not implemented */; }
int128::int128(double v) : int128(MakeInt128FromFloat(v)) { __builtin_trap() /* STUB: not implemented */; }
int128::int128(long double v) : int128(MakeInt128FromFloat(v)) { __builtin_trap() /* STUB: not implemented */; }

int128 operator/(int128 lhs, int128 rhs) { __builtin_trap() /* STUB: not implemented */; }

int128 operator%(int128 lhs, int128 rhs) { __builtin_trap() /* STUB: not implemented */; }
#endif  // ABSL_HAVE_INTRINSIC_INT128

std::string int128::ToString() const { __builtin_trap() /* STUB: not implemented */; }

std::ostream& operator<<(std::ostream& os, int128 v) { __builtin_trap() /* STUB: not implemented */; }

ABSL_NAMESPACE_END
}  // namespace absl
