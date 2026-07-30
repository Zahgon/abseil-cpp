// Copyright 2026 The Abseil Authors.
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
// File: internal/any_span.h
// -----------------------------------------------------------------------------
//
// Helper types and functions used by AnySpan. This file should only be
// included by any_span.h.
#ifndef ABSL_TYPES_INTERNAL_ANY_SPAN_H_
#define ABSL_TYPES_INTERNAL_ANY_SPAN_H_

#include <algorithm>
#include <cstddef>
#include <functional>
#include <type_traits>

#include "absl/base/config.h"
#include "absl/base/internal/raw_logging.h"
#include "absl/base/optimization.h"
#include "absl/meta/type_traits.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

template <typename T>
class AnySpan;

namespace any_span_transform {
struct IdentityT;
struct DerefT;
}  // namespace any_span_transform

namespace any_span_internal {

//
// IsAnySpan inherits from true_type if T is an instance of AnySpan.
//

template <typename T>
struct IsAnySpan : public std::false_type {};

template <typename T>
struct IsAnySpan<AnySpan<T>> : public std::true_type {};

// A type suitable for storing any function pointer. The standard allows
// function pointers to round-trip through other function pointers, but void* is
// implementation defined.
using FunPtr = void (*)();

// Whether a transform will be copied and therefore does not have to outlive
// the AnySpan.
template <typename Transform>
constexpr bool kIsTransformCopied =
    std::is_function_v<std::remove_pointer_t<Transform>>;

// Type to pass as extra argument to TransformPtr to ensure that our
// assumption about Transform copyability is valid.
template <typename Transform>
using IsTransformCopied = std::bool_constant<kIsTransformCopied<Transform>>;

// A pointer to the transform function or functor that should be applied to
// elements of the container.
class TransformPtr {
 public:
  TransformPtr() = default;

  // Construct from ptr to function.
  template <typename R, typename... Args, typename CopiedTransform>
  explicit TransformPtr(R (*f)(Args...),
                        CopiedTransform copied_transform [[maybe_unused]])
      : fun_ptr_(reinterpret_cast<FunPtr>(f)) { __builtin_trap() /* STUB: not implemented */; }

  // Construct from any other invokable object.
  template <typename T, typename CopiedTransform>
  explicit TransformPtr(const T& t,
                        CopiedTransform copied_transform [[maybe_unused]])
      : ptr_(&t) { __builtin_trap() /* STUB: not implemented */; }

  // Casts the pointer to the given type.
  template <typename Transform>
  auto get() const { __builtin_trap() /* STUB: not implemented */; }

 private:
  union {
    const void* ptr_ = nullptr;
    FunPtr fun_ptr_;
  };
};

// A void* pointer to the container and transform functor. These are always cast
// to the correct type since we create this object and the GetterFunction at the
// same time (from one of the Make*Getter functions below).
struct TransformedContainer {
  // The container or array.
  void* ptr;

  // The transform being applied to the container.
  TransformPtr transform;
};

// Applies transform (at the correct type) to the argument and returns the
// result. Does some validity checking to make sure the result is not a
// temporary (proxy containers are not allowed).
template <typename T, typename Transform, typename U>
T& ApplyTransform(TransformPtr transform, U& u) { __builtin_trap() /* STUB: not implemented */; }

// The return type of GetterFunction<T>. GetterFunctions return non-const
// references to support mutable -> const conversion of spans without additional
// indirection.
template <typename T>
using GetterFunctionResult = std::remove_const_t<T>&;

// A type of function pointer that can return an element of a
// TransformedContainer.  This is used so that we can type-erase with a simple
// function pointer instead of a vtable. Doing things this way has less pointer
// indirection.
template <typename T>
using GetterFunction = GetterFunctionResult<T> (*)(const TransformedContainer&,
                                                   std::size_t);

// A GetterFunction that works on arrays.
template <typename T, typename Element, typename Transform>
GetterFunctionResult<T> GetFromArray(const TransformedContainer& container,
                                     std::size_t i) { __builtin_trap() /* STUB: not implemented */; }

// A GetterFunction that works on containers.
template <typename T, typename Container, typename Transform>
GetterFunctionResult<T> GetFromContainer(const TransformedContainer& container,
                                         std::size_t i) { __builtin_trap() /* STUB: not implemented */; }

// A GetterFunction that crashes, indicating an invalid AnySpan has been
// accessed..
template <typename T>
GetterFunctionResult<T> GetFromUninitialized(const TransformedContainer&,
                                             std::size_t) { __builtin_trap() /* STUB: not implemented */; }

//
// ArrayTag and PtrArrayTag are GetterFunctions that are never called. They are
// used as a tag so Getter::Get can access flat arrays without a function
// pointer.
//

template <typename T>
GetterFunctionResult<T> ArrayTag(const TransformedContainer&, std::size_t) { __builtin_trap() /* STUB: not implemented */; }

template <typename T>
GetterFunctionResult<T> PtrArrayTag(const TransformedContainer&, std::size_t) { __builtin_trap() /* STUB: not implemented */; }

//
// HasSize<Container> inherets from true_type if Container has a size() member.
// false_type otherwise.
//

template <typename, typename = void>
struct HasSize : public std::false_type {};

template <class Container>
struct HasSize<Container,
               std::void_t<decltype(std::declval<Container&>().size())>>
    : public std::true_type {};

//
// TypeOfData<Container>::type is the return type of data() if Container has a
// data() member. It is NoData otherwise.
//

struct NoData {};

template <typename, typename = void>
struct TypeOfData {
  using type = NoData;
};

template <class Container>
struct TypeOfData<Container,
                  std::void_t<decltype(std::declval<Container&>().data())>> {
  using type = decltype(std::declval<Container&>().data());
};

// Element type of container based on operator[].
template <class Container>
using ElementType =
    std::remove_reference_t<decltype(std::declval<Container&>()[0])>;

// Element type of container when elements are dereferenced.
template <class Container>
using DerefElementType =
    std::remove_reference_t<decltype(*std::declval<ElementType<Container>>())>;

// DataIsValid is true_type if Container has a data() member that returns a
// pointer to the type returned by operator[], false_type if there is no data()
// member or if the types disagree.
template <class Container>
using DataIsValid =
    std::is_same<ElementType<Container>*, typename TypeOfData<Container>::type>;

// Used to access elements of a container or array.
template <typename T>
struct Getter {
  Getter() { __builtin_trap() /* STUB: not implemented */; }

  // Handle mutable -> const conversion.
  template <typename LazyT = T,
            typename = std::enable_if_t<std::is_const_v<LazyT>>>
  explicit Getter(const Getter<std::remove_const_t<T>>& other) { __builtin_trap() /* STUB: not implemented */; }

  // Returns the element at the given index.
  T& Get(std::size_t index) const { __builtin_trap() /* STUB: not implemented */; }

  // Returns a Getter offset into this one by pos.
  Getter Offset(std::size_t pos) const { __builtin_trap() /* STUB: not implemented */; }

  // A pointer to a function (or tag function) that specifies how to get an
  // element from the array or container.
  GetterFunction<T> fun = &GetFromUninitialized<T>;

  union {
    T* array;                        // Active if fun == ArrayTag<T>.
    T* const* ptr_array;             // Active if fun == PtrArrayTag<T>.
    TransformedContainer container;  // Active for all other fun.
  };

  // Offset into container. Always 0 for array or ptr_array.
  std::size_t offset = 0;
};

//
// MakeArrayGetter returns a Getter for an array.
//
// MakeArrayGetterImpl is specialised to use ArrayTag<T> when Element == T and
// Transform == IdentityT, and to use PtrArrayTag<T> when Element == T* and
// Transform == DerefT.
//

template <typename SpanElement, typename ArrayElement, typename Transform>
struct MakeArrayGetterImpl {
  template <typename U>
  static Getter<U> Make(ArrayElement* array, const Transform& transform) { __builtin_trap() /* STUB: not implemented */; }
};

// When the span and the array are the same type.
template <typename T>
struct MakeArrayGetterImpl<T, T, any_span_transform::IdentityT> {
  template <typename U>
  static Getter<U> Make(T* array, const any_span_transform::IdentityT&) { __builtin_trap() /* STUB: not implemented */; }
};

// If we are dereferencing an array of mutable elements (T*), it is safe to add
// constness (const T*).
template <typename T>
struct MakeArrayGetterImpl<const T, T, any_span_transform::IdentityT>
    : public MakeArrayGetterImpl<const T, const T,
                                 any_span_transform::IdentityT> {};

// When the array is of pointers to elements of the same type as the span.
template <typename T>
struct MakeArrayGetterImpl<T, T*, any_span_transform::DerefT> {
  template <typename U>
  static Getter<U> Make(T* const* ptr_array,
                        const any_span_transform::DerefT&) { __builtin_trap() /* STUB: not implemented */; }
};

// If we are dereferencing an array that is mutable along any extent, it is safe
// to add constness.
template <typename T>
struct MakeArrayGetterImpl<const T, T*, any_span_transform::DerefT>
    : public MakeArrayGetterImpl<const T, const T*,
                                 any_span_transform::DerefT> {};

template <typename T>
struct MakeArrayGetterImpl<const T, T* const, any_span_transform::DerefT>
    : public MakeArrayGetterImpl<const T, const T*,
                                 any_span_transform::DerefT> {};

template <typename T>
struct MakeArrayGetterImpl<const T, const T* const, any_span_transform::DerefT>
    : public MakeArrayGetterImpl<const T, const T*,
                                 any_span_transform::DerefT> {};

template <typename T, typename Element, typename Transform>
Getter<T> MakeArrayGetter(Element* array, const Transform& transform) { __builtin_trap() /* STUB: not implemented */; }

//
// MakeContainerGetter returns a Getter for a given container. It will pass
// container.data() to MakeArrayGetter if possible, which allows element access
// to be inline.
//
// The first argument to MakeArrayGetterImpl is expected to be of type
// DataIsValid<container>.
//

template <typename T, typename Container, typename Transform>
Getter<T> MakeContainerGetterImpl(
    std::true_type /* DataIsValid<Container> */,
    Container& container,  // NOLINT(runtime/references)
    const Transform& transform) { __builtin_trap() /* STUB: not implemented */; }

template <typename T, typename Container, typename Transform>
Getter<T> MakeContainerGetterImpl(
    std::false_type /* DataIsValid<Container> */,
    Container& container,  // NOLINT(runtime/references)
    const Transform& transform) { __builtin_trap() /* STUB: not implemented */; }

template <typename T, typename Container, typename Transform>
Getter<T> MakeContainerGetter(
    Container& container,  // NOLINT(runtime/references)
    const Transform& transform) { __builtin_trap() /* STUB: not implemented */; }

// Used for testing. Returns true if the given AnySpan performs inline element
// access.
template <typename T>
bool IsCheap(AnySpan<T> s) { __builtin_trap() /* STUB: not implemented */; }

template <typename T>
bool EqualImpl(AnySpan<T> a, AnySpan<T> b) { __builtin_trap() /* STUB: not implemented */; }

}  // namespace any_span_internal
ABSL_NAMESPACE_END
}  // namespace absl

#endif  // ABSL_TYPES_INTERNAL_ANY_SPAN_H_
