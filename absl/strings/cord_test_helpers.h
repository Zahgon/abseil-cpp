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

#ifndef ABSL_STRINGS_CORD_TEST_HELPERS_H_
#define ABSL_STRINGS_CORD_TEST_HELPERS_H_

#include <cstdint>
#include <iostream>
#include <string>

#include "absl/base/config.h"
#include "absl/strings/cord.h"
#include "absl/strings/internal/cord_internal.h"
#include "absl/strings/string_view.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

// Cord sizes relevant for testing
enum class TestCordSize {
  // An empty value
  kEmpty = 0,

  // An inlined string value
  kInlined = cord_internal::kMaxInline / 2 + 1,

  // 'Well known' SSO lengths (excluding terminating zero).
  // libstdcxx has a maximum SSO of 15, libc++ has a maximum SSO of 22.
  kStringSso1 = 15,
  kStringSso2 = 22,

  // A string value which is too large to fit in inlined data, but small enough
  // such that Cord prefers copying the value if possible, i.e.: not stealing
  // std::string inputs, or referencing existing CordReps on Append, etc.
  kSmall = cord_internal::kMaxBytesToCopy / 2 + 1,

  // A string value large enough that Cord prefers to reference or steal from
  // existing inputs rather than copying contents of the input.
  kMedium = cord_internal::kMaxFlatLength / 2 + 1,

  // A string value large enough to cause it to be stored in multiple flats.
  kLarge = cord_internal::kMaxFlatLength * 4
};

// To string helper
inline absl::string_view ToString(TestCordSize size) { __builtin_trap() /* STUB: not implemented */; }

// Returns the length matching the specified size
inline size_t Length(TestCordSize size) { __builtin_trap() /* STUB: not implemented */; }

// Stream output helper
inline std::ostream& operator<<(std::ostream& stream, TestCordSize size) { __builtin_trap() /* STUB: not implemented */; }

// Creates a multi-segment Cord from an iterable container of strings.  The
// resulting Cord is guaranteed to have one segment for every string in the
// container.  This allows code to be unit tested with multi-segment Cord
// inputs.
//
// Example:
//
//   absl::Cord c = absl::MakeFragmentedCord({"A ", "fragmented ", "Cord"});
//   EXPECT_FALSE(c.GetFlat(&unused));
//
// The mechanism by which this Cord is created is an implementation detail.  Any
// implementation that produces a multi-segment Cord may produce a flat Cord in
// the future as new optimizations are added to the Cord class.
// MakeFragmentedCord will, however, always be updated to return a multi-segment
// Cord.
template <typename Container>
Cord MakeFragmentedCord(const Container& c) { __builtin_trap() /* STUB: not implemented */; }

inline Cord MakeFragmentedCord(std::initializer_list<absl::string_view> list) { __builtin_trap() /* STUB: not implemented */; }

ABSL_NAMESPACE_END
}  // namespace absl

#endif  // ABSL_STRINGS_CORD_TEST_HELPERS_H_
