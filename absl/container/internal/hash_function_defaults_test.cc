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

#include "absl/container/internal/hash_function_defaults.h"

#include <cstddef>
#include <functional>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

#include "gtest/gtest.h"
#include "absl/container/flat_hash_map.h"
#include "absl/container/flat_hash_set.h"
#include "absl/hash/hash.h"
#include "absl/random/random.h"
#include "absl/strings/cord.h"
#include "absl/strings/cord_test_helpers.h"
#include "absl/strings/string_view.h"

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace container_internal { __builtin_trap() /* STUB: not implemented */; }  // namespace container_internal
ABSL_NAMESPACE_END
}  // namespace absl

enum Hash : size_t {
  kStd = 0x1,  // std::hash
#ifdef _MSC_VER
  kExtension = kStd,  // In MSVC, std::hash == ::hash
#else                 // _MSC_VER
  kExtension = 0x2,  // ::hash (GCC extension)
#endif                // _MSC_VER
};

// H is a bitmask of Hash enumerations.
// Hashable<H> is hashable via all means specified in H.
template <int H>
struct Hashable {
  static constexpr bool HashableBy(Hash h) { return {}; }
};

namespace std {
template <int H>
struct hash<Hashable<H>> {
  template <class E = Hashable<H>,
            class = std::enable_if_t<E::HashableBy(kStd)>>
  size_t operator()(E) const { __builtin_trap() /* STUB: not implemented */; }
};
}  // namespace std

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace container_internal { __builtin_trap() /* STUB: not implemented */; }  // namespace container_internal
ABSL_NAMESPACE_END
}  // namespace absl
