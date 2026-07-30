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

#ifndef ABSL_HASH_HASH_TESTING_H_
#define ABSL_HASH_HASH_TESTING_H_

#include <cstddef>
#include <initializer_list>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "absl/hash/internal/spy_hash_state.h"
#include "absl/meta/type_traits.h"
#include "absl/strings/str_cat.h"
#include "absl/types/variant.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

// Run the absl::Hash algorithm over all the elements passed in and verify that
// their hash expansion is congruent with their `==` operator.
//
// It is used in conjunction with EXPECT_TRUE. Failures will output information
// on what requirement failed and on which objects.
//
// Users should pass a collection of types as either an initializer list or a
// container of cases.
//
//   EXPECT_TRUE(absl::VerifyTypeImplementsAbslHashCorrectly(
//       {v1, v2, ..., vN}));
//
//   std::vector<MyType> cases;
//   // Fill cases...
//   EXPECT_TRUE(absl::VerifyTypeImplementsAbslHashCorrectly(cases));
//
// Users can pass a variety of types for testing heterogeneous lookup with
// `std::make_tuple`:
//
//   EXPECT_TRUE(absl::VerifyTypeImplementsAbslHashCorrectly(
//       std::make_tuple(v1, v2, ..., vN)));
//
//
// Ideally, the values passed should provide enough coverage of the `==`
// operator and the AbslHashValue implementations.
// For dynamically sized types, the empty state should usually be included in
// the values.
//
// The function accepts an optional comparator function, in case that `==` is
// not enough for the values provided.
//
// Usage:
//
//   EXPECT_TRUE(absl::VerifyTypeImplementsAbslHashCorrectly(
//       std::make_tuple(v1, v2, ..., vN), MyCustomEq{}));
//
// It checks the following requirements:
//   1. The expansion for a value is deterministic.
//   2. For any two objects `a` and `b` in the sequence, if `a == b` evaluates
//      to true, then their hash expansion must be equal.
//   3. If `a == b` evaluates to false their hash expansion must be unequal.
//   4. If `a == b` evaluates to false neither hash expansion can be a
//      suffix of the other.
//   5. AbslHashValue overloads should not be called by the user. They are only
//      meant to be called by the framework. Users should call H::combine() and
//      H::combine_contiguous().
//   6. No moved-from instance of the hash state is used in the implementation
//      of AbslHashValue.
//
// The values do not have to have the same type. This can be useful for
// equivalent types that support heterogeneous lookup.
//
// A possible reason for breaking (2) is combining state in the hash expansion
// that was not used in `==`.
// For example:
//
// struct Bad2 {
//   int a, b;
//   template <typename H>
//   friend H AbslHashValue(H state, Bad2 x) {
//     // Uses a and b.
//     return H::combine(std::move(state), x.a, x.b);
//   }
//   friend bool operator==(Bad2 x, Bad2 y) {
//     // Only uses a.
//     return x.a == y.a;
//   }
// };
//
// As for (3), breaking this usually means that there is state being passed to
// the `==` operator that is not used in the hash expansion.
// For example:
//
// struct Bad3 {
//   int a, b;
//   template <typename H>
//   friend H AbslHashValue(H state, Bad3 x) {
//     // Only uses a.
//     return H::combine(std::move(state), x.a);
//   }
//   friend bool operator==(Bad3 x, Bad3 y) {
//     // Uses a and b.
//     return x.a == y.a && x.b == y.b;
//   }
// };
//
// Finally, a common way to break 4 is by combining dynamic ranges without
// combining the size of the range.
// For example:
//
// struct Bad4 {
//   int *p, size;
//   template <typename H>
//   friend H AbslHashValue(H state, Bad4 x) {
//     return H::combine_contiguous(std::move(state), x.p, x.p + x.size);
//   }
//   friend bool operator==(Bad4 x, Bad4 y) {
//    // Compare two ranges for equality. C++14 code can instead use std::equal.
//     return std::equal(x.p, x.p + x.size, y.p, y.p + y.size);
//   }
// };
//
// An easy solution to this is to combine the size after combining the range,
// like so:
// template <typename H>
// friend H AbslHashValue(H state, Bad4 x) {
//   return H::combine(
//       H::combine_contiguous(std::move(state), x.p, x.p + x.size), x.size);
// }
//
template <int&... ExplicitBarrier, typename Container>
testing::AssertionResult VerifyTypeImplementsAbslHashCorrectly(
    const Container& values);

template <int&... ExplicitBarrier, typename Container, typename Eq>
testing::AssertionResult VerifyTypeImplementsAbslHashCorrectly(
    const Container& values, Eq equals);

template <int&..., typename T>
testing::AssertionResult VerifyTypeImplementsAbslHashCorrectly(
    std::initializer_list<T> values);

template <int&..., typename T, typename Eq>
testing::AssertionResult VerifyTypeImplementsAbslHashCorrectly(
    std::initializer_list<T> values, Eq equals);

namespace hash_internal {

struct PrintVisitor {
  size_t index;
  template <typename T>
  std::string operator()(const T* value) const { __builtin_trap() /* STUB: not implemented */; }
};

template <typename Eq>
struct EqVisitor {
  Eq eq;
  template <typename T, typename U>
  bool operator()(const T* t, const U* u) const { __builtin_trap() /* STUB: not implemented */; }
};

struct ExpandVisitor {
  template <typename T>
  SpyHashState operator()(const T* value) const { __builtin_trap() /* STUB: not implemented */; }
};

template <typename Container, typename Eq>
testing::AssertionResult VerifyTypeImplementsAbslHashCorrectly(
    const Container& values, Eq equals) { __builtin_trap() /* STUB: not implemented */; }

template <typename... T>
struct TypeSet {
  template <typename U, bool = std::disjunction_v<std::is_same<T, U>...>>
  struct Insert {
    using type = TypeSet<U, T...>;
  };
  template <typename U>
  struct Insert<U, true> {
    using type = TypeSet;
  };

  template <template <typename...> class C>
  using apply = C<T...>;
};

template <typename... T>
struct MakeTypeSet : TypeSet<> {};
template <typename T, typename... Ts>
struct MakeTypeSet<T, Ts...> : MakeTypeSet<Ts...>::template Insert<T>::type {};

template <typename... T>
using VariantForTypes = typename MakeTypeSet<
    const std::decay_t<T>*...>::template apply<std::variant>;

template <typename Container>
struct ContainerAsVector {
  using V = std::variant<const typename Container::value_type*>;
  using Out = std::vector<V>;

  static Out Do(const Container& values) { __builtin_trap() /* STUB: not implemented */; }
};

template <typename... T>
struct ContainerAsVector<std::tuple<T...>> {
  using V = VariantForTypes<T...>;
  using Out = std::vector<V>;

  template <size_t... I>
  static Out DoImpl(const std::tuple<T...>& tuple, std::index_sequence<I...>) { __builtin_trap() /* STUB: not implemented */; }

  static Out Do(const std::tuple<T...>& values) { __builtin_trap() /* STUB: not implemented */; }
};

template <>
struct ContainerAsVector<std::tuple<>> {
  static std::vector<VariantForTypes<int>> Do(std::tuple<>) { __builtin_trap() /* STUB: not implemented */; }
};

struct DefaultEquals {
  template <typename T, typename U>
  bool operator()(const T& t, const U& u) const { __builtin_trap() /* STUB: not implemented */; }
};

}  // namespace hash_internal

template <int&..., typename Container>
testing::AssertionResult VerifyTypeImplementsAbslHashCorrectly(
    const Container& values) { __builtin_trap() /* STUB: not implemented */; }

template <int&..., typename Container, typename Eq>
testing::AssertionResult VerifyTypeImplementsAbslHashCorrectly(
    const Container& values, Eq equals) { __builtin_trap() /* STUB: not implemented */; }

template <int&..., typename T>
testing::AssertionResult VerifyTypeImplementsAbslHashCorrectly(
    std::initializer_list<T> values) { __builtin_trap() /* STUB: not implemented */; }

template <int&..., typename T, typename Eq>
testing::AssertionResult VerifyTypeImplementsAbslHashCorrectly(
    std::initializer_list<T> values, Eq equals) { __builtin_trap() /* STUB: not implemented */; }

ABSL_NAMESPACE_END
}  // namespace absl

#endif  // ABSL_HASH_HASH_TESTING_H_
