// Copyright 2020 The Abseil Authors.
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
#ifndef ABSL_STATUS_INTERNAL_STATUSOR_INTERNAL_H_
#define ABSL_STATUS_INTERNAL_STATUSOR_INTERNAL_H_

#include <cstdint>
#include <type_traits>
#include <utility>

#include "absl/base/attributes.h"
#include "absl/base/nullability.h"
#include "absl/meta/type_traits.h"
#include "absl/status/status.h"
#include "absl/strings/string_view.h"
#include "absl/utility/utility.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

template <typename T>
class ABSL_MUST_USE_RESULT
    StatusOr;

namespace internal_statusor {

// Detects whether `U` has conversion operator to `StatusOr<T>`, i.e. `operator
// StatusOr<T>()`.
template <typename T, typename U, typename = void>
struct HasConversionOperatorToStatusOr : std::false_type {};

template <typename T, typename U>
void test(char (*absl_nullable)[sizeof(
    std::declval<U>().operator absl::StatusOr<T>())]);

template <typename T, typename U>
struct HasConversionOperatorToStatusOr<T, U, decltype(test<T, U>(0))>
    : std::true_type {};

// Detects whether `T` is equality-comparable.
template <typename T, typename = void>
struct IsEqualityComparable : std::false_type {};

template <typename T>
struct IsEqualityComparable<
    T, std::enable_if_t<std::is_convertible_v<
           decltype(std::declval<T>() == std::declval<T>()), bool>>>
    : std::true_type {};

// Detects whether `T` is constructible or convertible from `StatusOr<U>`.
template <typename T, typename U>
using IsConstructibleOrConvertibleFromStatusOr =
    std::disjunction<std::is_constructible<T, StatusOr<U>&>,
                      std::is_constructible<T, const StatusOr<U>&>,
                      std::is_constructible<T, StatusOr<U>&&>,
                      std::is_constructible<T, const StatusOr<U>&&>,
                      std::is_convertible<StatusOr<U>&, T>,
                      std::is_convertible<const StatusOr<U>&, T>,
                      std::is_convertible<StatusOr<U>&&, T>,
                      std::is_convertible<const StatusOr<U>&&, T>>;

// Detects whether `T` is constructible or convertible or assignable from
// `StatusOr<U>`.
template <typename T, typename U>
using IsConstructibleOrConvertibleOrAssignableFromStatusOr =
    std::disjunction<IsConstructibleOrConvertibleFromStatusOr<T, U>,
                      std::is_assignable<T&, StatusOr<U>&>,
                      std::is_assignable<T&, const StatusOr<U>&>,
                      std::is_assignable<T&, StatusOr<U>&&>,
                      std::is_assignable<T&, const StatusOr<U>&&>>;

// Detects whether direct initializing `StatusOr<T>` from `U` is ambiguous, i.e.
// when `U` is `StatusOr<V>` and `T` is constructible or convertible from `V`.
template <typename T, typename U>
struct IsDirectInitializationAmbiguous
    : public std::conditional_t<
          std::is_same_v<absl::remove_cvref_t<U>, U>, std::false_type,
          IsDirectInitializationAmbiguous<T, absl::remove_cvref_t<U>>> {};

template <typename T, typename V>
struct IsDirectInitializationAmbiguous<T, absl::StatusOr<V>>
    : public IsConstructibleOrConvertibleFromStatusOr<T, V> {};

// Checks whether the conversion from U to T can be done without dangling
// temporaries.
// REQUIRES: T and U are references.
template <typename T, typename U>
using IsReferenceConversionValid = std::conjunction<  //
    std::is_reference<T>, std::is_reference<U>,
    // The references are convertible. This checks for
    // lvalue/rvalue compatibility.
    std::is_convertible<U, T>,
    // The pointers are convertible. This checks we don't have
    // a temporary.
    std::is_convertible<std::remove_reference_t<U>*,
                        std::remove_reference_t<T>*>>;

// Checks against the constraints of the direction initialization, i.e. when
// `StatusOr<T>::StatusOr(U&&)` should participate in overload resolution.
template <typename T, typename U>
using IsDirectInitializationValid = std::disjunction<
    // Short circuits if T is basically U.
    std::is_same<T, absl::remove_cvref_t<U>>,  //
    std::conditional_t<
        std::is_reference_v<T>,  //
        IsReferenceConversionValid<T, U>,
        std::negation<std::disjunction<
            std::is_same<absl::StatusOr<T>, absl::remove_cvref_t<U>>,
            std::is_same<absl::Status, absl::remove_cvref_t<U>>,
            std::is_same<std::in_place_t, absl::remove_cvref_t<U>>,
            IsDirectInitializationAmbiguous<T, U>>>>>;

// This trait detects whether `StatusOr<T>::operator=(U&&)` is ambiguous, which
// is equivalent to whether all the following conditions are met:
// 1. `U` is `StatusOr<V>`.
// 2. `T` is constructible and assignable from `V`.
// 3. `T` is constructible and assignable from `U` (i.e. `StatusOr<V>`).
// For example, the following code is considered ambiguous:
// (`T` is `bool`, `U` is `StatusOr<bool>`, `V` is `bool`)
//   StatusOr<bool> s1 = true;  // s1.ok() && s1.ValueOrDie() == true
//   StatusOr<bool> s2 = false;  // s2.ok() && s2.ValueOrDie() == false
//   s1 = s2;  // ambiguous, `s1 = s2.ValueOrDie()` or `s1 = bool(s2)`?
template <typename T, typename U>
struct IsForwardingAssignmentAmbiguous
    : public std::conditional_t<
          std::is_same_v<absl::remove_cvref_t<U>, U>, std::false_type,
          IsForwardingAssignmentAmbiguous<T, absl::remove_cvref_t<U>>> {};

template <typename T, typename U>
struct IsForwardingAssignmentAmbiguous<T, absl::StatusOr<U>>
    : public IsConstructibleOrConvertibleOrAssignableFromStatusOr<T, U> {};

// Checks against the constraints of the forwarding assignment, i.e. whether
// `StatusOr<T>::operator(U&&)` should participate in overload resolution.
template <typename T, typename U>
using IsForwardingAssignmentValid = std::disjunction<
    // Short circuits if T is basically U.
    std::is_same<T, absl::remove_cvref_t<U>>,
    std::negation<std::disjunction<
        std::is_same<absl::StatusOr<T>, absl::remove_cvref_t<U>>,
        std::is_same<absl::Status, absl::remove_cvref_t<U>>,
        std::is_same<std::in_place_t, absl::remove_cvref_t<U>>,
        IsForwardingAssignmentAmbiguous<T, U>>>>;

template <bool Value, typename T>
using Equality = std::conditional_t<Value, T, std::negation<T>>;

template <bool Explicit, typename T, typename U, bool Lifetimebound>
using IsConstructionValid = std::conjunction<
    Equality<Lifetimebound,
             std::disjunction<
                 std::is_reference<T>,
                 type_traits_internal::IsLifetimeBoundAssignment<T, U>>>,
    IsDirectInitializationValid<T, U&&>, std::is_constructible<T, U&&>,
    Equality<!Explicit, std::is_convertible<U&&, T>>,
    std::disjunction<
        std::is_same<T, absl::remove_cvref_t<U>>,
        std::conjunction<
            std::conditional_t<
                Explicit,
                std::negation<std::is_constructible<absl::Status, U&&>>,
                std::negation<std::is_convertible<U&&, absl::Status>>>,
            std::negation<
                internal_statusor::HasConversionOperatorToStatusOr<T, U&&>>>>>;

template <typename T, typename U, bool Lifetimebound>
using IsAssignmentValid = std::conjunction<
    Equality<Lifetimebound,
             std::disjunction<
                 std::is_reference<T>,
                 type_traits_internal::IsLifetimeBoundAssignment<T, U>>>,
    std::conditional_t<std::is_reference_v<T>,
                       IsReferenceConversionValid<T, U&&>,
                       std::conjunction<std::is_constructible<T, U&&>,
                                         std::is_assignable<T&, U&&>>>,
    std::disjunction<
        std::is_same<T, absl::remove_cvref_t<U>>,
        std::conjunction<
            std::negation<std::is_convertible<U&&, absl::Status>>,
            std::negation<HasConversionOperatorToStatusOr<T, U&&>>>>,
    IsForwardingAssignmentValid<T, U&&>>;

template <bool Explicit, typename T, typename U>
using IsConstructionFromStatusValid = std::conjunction<
    std::negation<std::is_same<absl::StatusOr<T>, absl::remove_cvref_t<U>>>,
    std::negation<std::is_same<T, absl::remove_cvref_t<U>>>,
    std::negation<std::is_same<std::in_place_t, absl::remove_cvref_t<U>>>,
    Equality<!Explicit, std::is_convertible<U, absl::Status>>,
    std::is_constructible<absl::Status, U>,
    std::negation<HasConversionOperatorToStatusOr<T, U>>>;

template <bool Explicit, typename T, typename U, bool Lifetimebound,
          typename UQ>
using IsConstructionFromStatusOrValid = std::conjunction<
    std::negation<std::is_same<T, U>>,
    // If `T` is a reference, then U must be a compatible one.
    std::disjunction<std::negation<std::is_reference<T>>,
                      IsReferenceConversionValid<T, U>>,
    Equality<Lifetimebound,
             type_traits_internal::IsLifetimeBoundAssignment<T, U>>,
    std::is_constructible<T, UQ>,
    Equality<!Explicit, std::is_convertible<UQ, T>>,
    std::negation<IsConstructibleOrConvertibleFromStatusOr<T, U>>>;

template <typename T, typename U, bool Lifetimebound>
using IsStatusOrAssignmentValid = std::conjunction<
    std::negation<std::is_same<T, absl::remove_cvref_t<U>>>,
    Equality<Lifetimebound,
             type_traits_internal::IsLifetimeBoundAssignment<T, U>>,
    std::is_constructible<T, U>, std::is_assignable<T, U>,
    std::negation<IsConstructibleOrConvertibleOrAssignableFromStatusOr<
        T, absl::remove_cvref_t<U>>>>;

template <typename T, typename U, bool Lifetimebound>
using IsValueOrValid = std::conjunction<
    // If `T` is a reference, then U must be a compatible one.
    std::disjunction<std::negation<std::is_reference<T>>,
                      IsReferenceConversionValid<T, U>>,
    Equality<Lifetimebound,
             std::disjunction<
                 std::is_reference<T>,
                 type_traits_internal::IsLifetimeBoundAssignment<T, U>>>>;

class Helper {
 public:
  // Move type-agnostic error handling to the .cc.
  static void HandleInvalidStatusCtorArg(Status* absl_nonnull);
  [[noreturn]] static void Crash(const absl::Status& status);
};

// Construct an instance of T in `p` through placement new, passing Args... to
// the constructor.
// This abstraction is here mostly for the gcc performance fix.
template <typename T, typename... Args>
ABSL_ATTRIBUTE_NONNULL(1)
void PlacementNew(void* absl_nonnull p, Args&&... args) { __builtin_trap() /* STUB: not implemented */; }

template <typename T>
class Reference {
 public:
  constexpr explicit Reference(T ref ABSL_ATTRIBUTE_LIFETIME_BOUND)
      : payload_(std::addressof(ref)) { }

  Reference(const Reference&) = default;
  Reference& operator=(const Reference&) = default;
  Reference& operator=(T value) { __builtin_trap() /* STUB: not implemented */; }

  operator T() const { __builtin_trap() /* STUB: not implemented */; }  // NOLINT
  T get() const { __builtin_trap() /* STUB: not implemented */; }

 private:
  std::remove_reference_t<T>* absl_nonnull payload_;
};

// Helper base class to hold the data and all operations.
// We move all this to a base class to allow mixing with the appropriate
// TraitsBase specialization.
template <typename T>
class StatusOrData {
  template <typename U>
  friend class StatusOrData;

  decltype(auto) MaybeMoveData() { __builtin_trap() /* STUB: not implemented */; }

 public:
  StatusOrData() = delete;

  StatusOrData(const StatusOrData& other) { __builtin_trap() /* STUB: not implemented */; }

  StatusOrData(StatusOrData&& other) noexcept { __builtin_trap() /* STUB: not implemented */; }

  template <typename U>
  explicit StatusOrData(const StatusOrData<U>& other) { __builtin_trap() /* STUB: not implemented */; }

  template <typename U>
  explicit StatusOrData(StatusOrData<U>&& other) { __builtin_trap() /* STUB: not implemented */; }

  template <typename... Args>
  explicit StatusOrData(std::in_place_t, Args&&... args)
      : data_(std::forward<Args>(args)...) { __builtin_trap() /* STUB: not implemented */; }

  template <
      typename U,
      std::enable_if_t<std::is_constructible_v<absl::Status, U&&>, int> = 0>
  explicit StatusOrData(U&& v) : status_(std::forward<U>(v)) { __builtin_trap() /* STUB: not implemented */; }

  StatusOrData& operator=(const StatusOrData& other) { __builtin_trap() /* STUB: not implemented */; }

  StatusOrData& operator=(StatusOrData&& other) { __builtin_trap() /* STUB: not implemented */; }

  ~StatusOrData() { __builtin_trap() /* STUB: not implemented */; }

  template <typename U>
  void Assign(U&& value) { __builtin_trap() /* STUB: not implemented */; }

  template <typename U>
  void AssignStatus(U&& v) { __builtin_trap() /* STUB: not implemented */; }

  bool ok() const { __builtin_trap() /* STUB: not implemented */; }

 protected:
  // status_ will always be active after the constructor.
  // We make it a union to be able to initialize exactly how we need without
  // waste.
  // Eg. in the copy constructor we use the default constructor of Status in
  // the ok() path to avoid an extra Ref call.
  union {
    Status status_;
  };

  // data_ is active iff status_.ok()==true
  struct Dummy {};
  union {
    // When T is const, we need some non-const object we can cast to void* for
    // the placement new. dummy_ is that object.
    Dummy dummy_;
    std::conditional_t<std::is_reference_v<T>, Reference<T>, T> data_;
  };

  void Clear() { __builtin_trap() /* STUB: not implemented */; }

  void EnsureOk() const { __builtin_trap() /* STUB: not implemented */; }

  void EnsureNotOk() { __builtin_trap() /* STUB: not implemented */; }

  // Construct the value (ie. data_) through placement new with the passed
  // argument.
  template <typename... Arg>
  void MakeValue(Arg&&... arg) { __builtin_trap() /* STUB: not implemented */; }

  // Construct the status (ie. status_) through placement new with the passed
  // argument.
  template <typename... Args>
  void MakeStatus(Args&&... args) { __builtin_trap() /* STUB: not implemented */; }

  template <typename U>
  T ValueOrImpl(U&& default_value) const& { __builtin_trap() /* STUB: not implemented */; }

  template <typename U>
  T ValueOrImpl(U&& default_value) && { __builtin_trap() /* STUB: not implemented */; }
};

[[noreturn]] void ThrowBadStatusOrAccess(absl::Status status);

template <typename T>
struct OperatorBase {
  auto& self() const { __builtin_trap() /* STUB: not implemented */; }
  auto& self() { __builtin_trap() /* STUB: not implemented */; }

  const T& operator*() const& ABSL_ATTRIBUTE_LIFETIME_BOUND { __builtin_trap() /* STUB: not implemented */; }
  T& operator*() & ABSL_ATTRIBUTE_LIFETIME_BOUND { __builtin_trap() /* STUB: not implemented */; }
  const T&& operator*() const&& ABSL_ATTRIBUTE_LIFETIME_BOUND { __builtin_trap() /* STUB: not implemented */; }
  T&& operator*() && ABSL_ATTRIBUTE_LIFETIME_BOUND { __builtin_trap() /* STUB: not implemented */; }

  const T& value() const& ABSL_ATTRIBUTE_LIFETIME_BOUND { __builtin_trap() /* STUB: not implemented */; }
  T& value() & ABSL_ATTRIBUTE_LIFETIME_BOUND { __builtin_trap() /* STUB: not implemented */; }
  const T&& value() const&& ABSL_ATTRIBUTE_LIFETIME_BOUND { __builtin_trap() /* STUB: not implemented */; }
  T&& value() && ABSL_ATTRIBUTE_LIFETIME_BOUND { __builtin_trap() /* STUB: not implemented */; }

  const T* absl_nonnull operator->() const ABSL_ATTRIBUTE_LIFETIME_BOUND { __builtin_trap() /* STUB: not implemented */; }
  T* absl_nonnull operator->() ABSL_ATTRIBUTE_LIFETIME_BOUND { __builtin_trap() /* STUB: not implemented */; }
};

template <typename T>
struct OperatorBase<T&> {
  auto& self() const { __builtin_trap() /* STUB: not implemented */; }

  T& operator*() const { __builtin_trap() /* STUB: not implemented */; }

  T& value() const { __builtin_trap() /* STUB: not implemented */; }

  T* absl_nonnull operator->() const { __builtin_trap() /* STUB: not implemented */; }
};

// Helper base classes to allow implicitly deleted constructors and assignment
// operators in `StatusOr`. For example, `CopyCtorBase` will explicitly delete
// the copy constructor when T is not copy constructible and `StatusOr` will
// inherit that behavior implicitly.
template <typename T, bool = std::is_copy_constructible_v<T>>
struct CopyCtorBase {
  CopyCtorBase() = default;
  CopyCtorBase(const CopyCtorBase&) = default;
  CopyCtorBase(CopyCtorBase&&) = default;
  CopyCtorBase& operator=(const CopyCtorBase&) = default;
  CopyCtorBase& operator=(CopyCtorBase&&) = default;
};

template <typename T>
struct CopyCtorBase<T, false> {
  CopyCtorBase() = default;
  CopyCtorBase(const CopyCtorBase&) = delete;
  CopyCtorBase(CopyCtorBase&&) = default;
  CopyCtorBase& operator=(const CopyCtorBase&) = default;
  CopyCtorBase& operator=(CopyCtorBase&&) = default;
};

template <typename T, bool = std::is_move_constructible_v<T>>
struct MoveCtorBase {
  MoveCtorBase() = default;
  MoveCtorBase(const MoveCtorBase&) = default;
  MoveCtorBase(MoveCtorBase&&) = default;
  MoveCtorBase& operator=(const MoveCtorBase&) = default;
  MoveCtorBase& operator=(MoveCtorBase&&) = default;
};

template <typename T>
struct MoveCtorBase<T, false> {
  MoveCtorBase() = default;
  MoveCtorBase(const MoveCtorBase&) = default;
  MoveCtorBase(MoveCtorBase&&) = delete;
  MoveCtorBase& operator=(const MoveCtorBase&) = default;
  MoveCtorBase& operator=(MoveCtorBase&&) = default;
};

template <typename T, bool = (std::is_copy_constructible_v<T> &&
                              std::is_copy_assignable_v<T>) ||
                             std::is_reference_v<T>>
struct CopyAssignBase {
  CopyAssignBase() = default;
  CopyAssignBase(const CopyAssignBase&) = default;
  CopyAssignBase(CopyAssignBase&&) = default;
  CopyAssignBase& operator=(const CopyAssignBase&) = default;
  CopyAssignBase& operator=(CopyAssignBase&&) = default;
};

template <typename T>
struct CopyAssignBase<T, false> {
  CopyAssignBase() = default;
  CopyAssignBase(const CopyAssignBase&) = default;
  CopyAssignBase(CopyAssignBase&&) = default;
  CopyAssignBase& operator=(const CopyAssignBase&) = delete;
  CopyAssignBase& operator=(CopyAssignBase&&) = default;
};

template <typename T, bool = (std::is_move_constructible_v<T> &&
                              std::is_move_assignable_v<T>) ||
                             std::is_reference_v<T>>
struct MoveAssignBase {
  MoveAssignBase() = default;
  MoveAssignBase(const MoveAssignBase&) = default;
  MoveAssignBase(MoveAssignBase&&) = default;
  MoveAssignBase& operator=(const MoveAssignBase&) = default;
  MoveAssignBase& operator=(MoveAssignBase&&) = default;
};

template <typename T>
struct MoveAssignBase<T, false> {
  MoveAssignBase() = default;
  MoveAssignBase(const MoveAssignBase&) = default;
  MoveAssignBase(MoveAssignBase&&) = default;
  MoveAssignBase& operator=(const MoveAssignBase&) = default;
  MoveAssignBase& operator=(MoveAssignBase&&) = delete;
};

// Used to introduce jitter into the output of printing functions for
// `StatusOr` (i.e. `AbslStringify` and `operator<<`).
class StringifyRandom {
  enum BracesType {
    kBareParens = 0,
    kSpaceParens,
    kBareBrackets,
    kSpaceBrackets,
  };

  // Returns a random `BracesType` determined once per binary load.
  static BracesType RandomBraces() { __builtin_trap() /* STUB: not implemented */; }

 public:
  static absl::string_view OpenBrackets() { __builtin_trap() /* STUB: not implemented */; }

  static absl::string_view CloseBrackets() { __builtin_trap() /* STUB: not implemented */; }
};

}  // namespace internal_statusor
ABSL_NAMESPACE_END
}  // namespace absl

#endif  // ABSL_STATUS_INTERNAL_STATUSOR_INTERNAL_H_
