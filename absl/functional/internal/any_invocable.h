// Copyright 2022 The Abseil Authors.
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
// Implementation details for `absl::AnyInvocable`

#ifndef ABSL_FUNCTIONAL_INTERNAL_ANY_INVOCABLE_H_
#define ABSL_FUNCTIONAL_INTERNAL_ANY_INVOCABLE_H_

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// This implementation chooses between local storage and remote storage for   //
// the contained target object based on the target object's size, alignment   //
// requirements, and whether or not it has a nothrow move constructor.        //
// Additional optimizations are performed when the object is a trivially      //
// copyable type [basic.types].                                               //
//                                                                            //
// There are three datamembers per `AnyInvocable` instance                    //
//                                                                            //
// 1) A union containing either                                               //
//        - A pointer to the target object referred to via a void*, or        //
//        - the target object, emplaced into a raw char buffer                //
//                                                                            //
// 2) A function pointer to a "manager" function operation that takes a       //
//    discriminator and logically branches to either perform a move operation //
//    or destroy operation based on that discriminator.                       //
//                                                                            //
// 3) A function pointer to an "invoker" function operation that invokes the  //
//    target object, directly returning the result.                           //
//                                                                            //
// When in the logically empty state, the manager function is an empty        //
// function and the invoker function is one that would be undefined behavior  //
// to call.                                                                   //
//                                                                            //
// An additional optimization is performed when converting from one           //
// AnyInvocable to another where only the noexcept specification and/or the   //
// cv/ref qualifiers of the function type differ. In these cases, the         //
// conversion works by "moving the guts", similar to if they were the same    //
// exact type, as opposed to having to perform an additional layer of         //
// wrapping through remote storage.                                           //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

// IWYU pragma: private, include "absl/functional/any_invocable.h"

#include <cassert>
#include <cstddef>
#include <cstring>
#include <exception>
#include <functional>
#include <memory>
#include <new>
#include <type_traits>
#include <utility>

#include "absl/base/attributes.h"
#include "absl/base/config.h"
#include "absl/base/macros.h"
#include "absl/base/nullability.h"
#include "absl/base/optimization.h"
#include "absl/meta/type_traits.h"
#include "absl/utility/utility.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

// Defined in functional/any_invocable.h
template <class Sig>
class ABSL_NULLABILITY_COMPATIBLE AnyInvocable;

namespace internal_any_invocable {

// Constants relating to the small-object-storage for AnyInvocable
enum StorageProperty : std::size_t {
  kAlignment = alignof(std::max_align_t),  // The alignment of the storage
  kStorageSize = sizeof(void*) * 2         // The size of the storage
};

////////////////////////////////////////////////////////////////////////////////
//
// A metafunction for checking if a type is an AnyInvocable instantiation.
// This is used during conversion operations.
template <class T>
struct IsAnyInvocable : std::false_type {};

template <class Sig>
struct IsAnyInvocable<AnyInvocable<Sig>> : std::true_type {};
//
////////////////////////////////////////////////////////////////////////////////

// A metafunction that tells us whether or not a target function type should be
// stored locally in the small object optimization storage
template <class T>
constexpr bool IsStoredLocally() { return {}; }

// An implementation of std::remove_cvref_t of C++20.
template <class T>
using RemoveCVRef = std::remove_cv_t<std::remove_reference_t<T>>;

// An implementation of std::invoke_r of C++23.
template <class ReturnType, class F, class... P>
ReturnType InvokeR(F&& f, P&&... args) { __builtin_trap() /* STUB: not implemented */; }

//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///
// A metafunction that takes a "T" corresponding to a parameter type of the
// user's specified function type, and yields the parameter type to use for the
// type-erased invoker. In order to prevent observable moves, this must be
// either a reference or, if the type is trivial, the original parameter type
// itself. Since the parameter type may be incomplete at the point that this
// metafunction is used, we can only do this optimization for scalar types
// rather than for any trivial type.
template <typename T>
T ForwardImpl(std::true_type);

template <typename T>
T&& ForwardImpl(std::false_type);

// NOTE: We deliberately use an intermediate struct instead of a direct alias,
// as a workaround for b/206991861 on MSVC versions < 1924.
template <class T>
struct ForwardedParameter {
  using type =
      decltype((ForwardImpl<T>)(std::bool_constant<std::is_scalar_v<T>>()));
};

template <class T>
using ForwardedParameterType = typename ForwardedParameter<T>::type;
//
////////////////////////////////////////////////////////////////////////////////

// A discriminator when calling the "manager" function that describes operation
// type-erased operation should be invoked.
//
// "dispose" specifies that the manager should perform a destroy.
//
// "relocate_from_to" specifies that the manager should perform a move.
//
// "relocate_from_to_and_query_rust" is identical to "relocate_from_to" for C++
// managers, but instructs Rust managers to perform a special operation that
// can be detected by the caller.
enum class FunctionToCall : unsigned char {
  dispose,
  relocate_from_to,
  relocate_from_to_and_query_rust,
};

// The portion of `AnyInvocable` state that contains either a pointer to the
// target object or the object itself in local storage
union TypeErasedState {
  struct {
    // A pointer to the type-erased object when remotely stored
    void* target;
    // The size of the object for `RemoteManagerTrivial`
    std::size_t size;
  } remote;

  // Local-storage for the type-erased object when small and trivial enough
  alignas(kAlignment) unsigned char storage[kStorageSize];
};

// A typed accessor for the object in `TypeErasedState` storage
template <class T>
T& ObjectInLocalStorage(TypeErasedState* const state) { __builtin_trap() /* STUB: not implemented */; }

// The type for functions issuing lifetime-related operations: move and dispose
// A pointer to such a function is contained in each `AnyInvocable` instance.
// NOTE: When specifying `FunctionToCall::`dispose, the same state must be
// passed as both "from" and "to".
using ManagerType = void(FunctionToCall /*operation*/,
                         TypeErasedState* /*from*/,
                         TypeErasedState* /*to*/) noexcept(true);

// The type for functions issuing the actual invocation of the object
// A pointer to such a function is contained in each AnyInvocable instance.
template <bool SigIsNoexcept, class ReturnType, class... P>
using InvokerType = ReturnType(
    TypeErasedState*, ForwardedParameterType<P>...) noexcept(SigIsNoexcept);

// The manager that is used when AnyInvocable is empty
inline void EmptyManager(FunctionToCall /*operation*/,
                         TypeErasedState* /*from*/,
                         TypeErasedState* /*to*/) noexcept { __builtin_trap() /* STUB: not implemented */; }

// The manager that is used when a target function is in local storage and is
// a trivially copyable type.
inline void LocalManagerTrivial(FunctionToCall /*operation*/,
                                TypeErasedState* const from,
                                TypeErasedState* const to) noexcept { __builtin_trap() /* STUB: not implemented */; }

// The manager that is used when a target function is in local storage and is
// not a trivially copyable type.
template <class T>
void LocalManagerNontrivial(FunctionToCall operation,
                            TypeErasedState* const from,
                            TypeErasedState* const to) noexcept { __builtin_trap() /* STUB: not implemented */; }

// The invoker that is used when a target function is in local storage
// Note: QualTRef here is the target function type along with cv and reference
// qualifiers that must be used when calling the function.
template <bool SigIsNoexcept, class ReturnType, class QualTRef, class... P>
ReturnType LocalInvoker(
    TypeErasedState* const state,
    ForwardedParameterType<P>... args) noexcept(SigIsNoexcept) { __builtin_trap() /* STUB: not implemented */; }

// The manager that is used when a target function is in remote storage and it
// has a trivial destructor
inline void RemoteManagerTrivial(FunctionToCall operation,
                                 TypeErasedState* const from,
                                 TypeErasedState* const to) noexcept { __builtin_trap() /* STUB: not implemented */; }

// The manager that is used when a target function is in remote storage and the
// destructor of the type is not trivial
template <class T>
void RemoteManagerNontrivial(FunctionToCall operation,
                             TypeErasedState* const from,
                             TypeErasedState* const to) noexcept { __builtin_trap() /* STUB: not implemented */; }

// The invoker that is used when a target function is in remote storage
template <bool SigIsNoexcept, class ReturnType, class QualTRef, class... P>
ReturnType RemoteInvoker(
    TypeErasedState* const state,
    ForwardedParameterType<P>... args) noexcept(SigIsNoexcept) { __builtin_trap() /* STUB: not implemented */; }

////////////////////////////////////////////////////////////////////////////////
//
// A metafunction that checks if a type T is an instantiation of
// std::in_place_type_t (needed for constructor constraints of AnyInvocable).
template <class T>
struct IsInPlaceType : std::false_type {};

template <class T>
struct IsInPlaceType<std::in_place_type_t<T>> : std::true_type {};
//
////////////////////////////////////////////////////////////////////////////////

// A constructor name-tag used with CoreImpl (below) to request the
// conversion-constructor. QualDecayedTRef is the decayed-type of the object to
// wrap, along with the cv and reference qualifiers that must be applied when
// performing an invocation of the wrapped object.
template <class QualDecayedTRef>
struct TypedConversionConstruct {};

// A helper base class for all core operations of AnyInvocable. Most notably,
// this class creates the function call operator and constraint-checkers so that
// the top-level class does not have to be a series of partial specializations.
//
// Note: This definition exists (as opposed to being a declaration) so that if
// the user of the top-level template accidentally passes a template argument
// that is not a function type, they will get a static_assert in AnyInvocable's
// class body rather than an error stating that Impl is not defined.
template <class Sig>
class Impl {};  // Note: This is partially-specialized later.

// A std::unique_ptr deleter that deletes memory allocated via ::operator new.
#if defined(__cpp_sized_deallocation)
class TrivialDeleter {
 public:
  explicit TrivialDeleter(std::size_t size) : size_(size) { __builtin_trap() /* STUB: not implemented */; }

  void operator()(void* target) const { __builtin_trap() /* STUB: not implemented */; }

 private:
  std::size_t size_;
};
#else   // __cpp_sized_deallocation
class TrivialDeleter {
 public:
  explicit TrivialDeleter(std::size_t) { __builtin_trap() /* STUB: not implemented */; }

  void operator()(void* target) const { __builtin_trap() /* STUB: not implemented */; }
};
#endif  // __cpp_sized_deallocation

template <bool SigIsNoexcept, class ReturnType, class... P>
class CoreImpl;

constexpr bool IsCompatibleConversion(void*, void*) { return {}; }
template <bool NoExceptSrc, bool NoExceptDest, class... T>
constexpr bool IsCompatibleConversion(CoreImpl<NoExceptSrc, T...>*,
                                      CoreImpl<NoExceptDest, T...>*) { return {}; }

// A helper base class for all core operations of AnyInvocable that do not
// depend on the cv/ref qualifiers of the function type.
template <bool SigIsNoexcept, class ReturnType, class... P>
class CoreImpl {
 public:
  using result_type = ReturnType;

  CoreImpl() noexcept : manager_(EmptyManager), invoker_(nullptr) { __builtin_trap() /* STUB: not implemented */; }

  // Note: QualDecayedTRef here includes the cv-ref qualifiers associated with
  // the invocation of the Invocable. The unqualified type is the target object
  // type to be stored.
  template <class QualDecayedTRef, class F>
  explicit CoreImpl(TypedConversionConstruct<QualDecayedTRef>, F&& f) { __builtin_trap() /* STUB: not implemented */; }

  // Note: QualTRef here includes the cv-ref qualifiers associated with the
  // invocation of the Invocable. The unqualified type is the target object
  // type to be stored.
  template <class QualTRef, class... Args>
  explicit CoreImpl(std::in_place_type_t<QualTRef>, Args&&... args) { __builtin_trap() /* STUB: not implemented */; }

  CoreImpl(CoreImpl&& other) noexcept { __builtin_trap() /* STUB: not implemented */; }

  CoreImpl& operator=(CoreImpl&& other) noexcept { __builtin_trap() /* STUB: not implemented */; }

  ~CoreImpl() { __builtin_trap() /* STUB: not implemented */; }

  // Check whether or not the AnyInvocable is in the empty state.
  bool HasValue() const { __builtin_trap() /* STUB: not implemented */; }

  // Effects: Puts the object into its empty state.
  void Clear() { __builtin_trap() /* STUB: not implemented */; }

  // Use local (inline) storage for applicable target object types.
  template <class QualTRef, class... Args>
  void InitializeStorage(Args&&... args) { __builtin_trap() /* STUB: not implemented */; }

  template <class T, class... Args>
  void InitializeRemoteManager(Args&&... args) { __builtin_trap() /* STUB: not implemented */; }

  //////////////////////////////////////////////////////////////////////////////
  //
  // Type trait to determine if the template argument is an AnyInvocable whose
  // function type is compatible enough with ours such that we can
  // "move the guts" out of it when moving, rather than having to place a new
  // object into remote storage.

  template <typename Other>
  struct IsCompatibleAnyInvocable {
    static constexpr bool value = false;
  };

  template <typename Sig>
  struct IsCompatibleAnyInvocable<AnyInvocable<Sig>> {
    static constexpr bool value =
        (IsCompatibleConversion)(static_cast<
                                     typename AnyInvocable<Sig>::CoreImpl*>(
                                     nullptr),
                                 static_cast<CoreImpl*>(nullptr));
  };

  //
  //////////////////////////////////////////////////////////////////////////////

  TypeErasedState state_;
  ManagerType* manager_;
  InvokerType<SigIsNoexcept, ReturnType, P...>* invoker_;
};

// A constructor name-tag used with Impl to request the
// conversion-constructor
struct ConversionConstruct {};

////////////////////////////////////////////////////////////////////////////////
//
// A metafunction that is normally an identity metafunction except that when
// given a std::reference_wrapper<T>, it yields T&. This is necessary because
// currently std::reference_wrapper's operator() is not conditionally noexcept,
// so when checking if such an Invocable is nothrow-invocable, we must pull out
// the underlying type.
template <class T>
struct UnwrapStdReferenceWrapperImpl {
  using type = T;
};

template <class T>
struct UnwrapStdReferenceWrapperImpl<std::reference_wrapper<T>> {
  using type = T&;
};

template <class T>
using UnwrapStdReferenceWrapper =
    typename UnwrapStdReferenceWrapperImpl<T>::type;
//
////////////////////////////////////////////////////////////////////////////////

// An alias that always yields std::true_type (used with constraints) where
// substitution failures happen when forming the template arguments.
//
// NOTE: We avoid std::void_t here to avoid a bug in GCC < 11:
// https://godbolt.org/z/sxbfGMdcb
template <class... T>
using TrueAlias = std::bool_constant<sizeof(std::common_type<T...>*) != 0>;

/*SFINAE constraints for the conversion-constructor.*/
template <class Sig, class F,
          class = std::enable_if_t<
              !std::is_same_v<RemoveCVRef<F>, AnyInvocable<Sig>>>>
using CanConvert =
    TrueAlias<std::enable_if_t<!IsInPlaceType<RemoveCVRef<F>>::value>,
              std::enable_if_t<Impl<Sig>::template CallIsValid<F>::value>,
              std::enable_if_t<
                  Impl<Sig>::template CallIsNoexceptIfSigIsNoexcept<F>::value>,
              std::enable_if_t<std::is_constructible_v<std::decay_t<F>, F>>>;

/*SFINAE constraints for the std::in_place constructors.*/
template <class Sig, class F, class... Args>
using CanEmplace = TrueAlias<
    std::enable_if_t<Impl<Sig>::template CallIsValid<F>::value>,
    std::enable_if_t<
        Impl<Sig>::template CallIsNoexceptIfSigIsNoexcept<F>::value>,
    std::enable_if_t<std::is_constructible_v<std::decay_t<F>, Args...>>>;

/*SFINAE constraints for the conversion-assign operator.*/
template <class Sig, class F,
          class = std::enable_if_t<
              !std::is_same_v<RemoveCVRef<F>, AnyInvocable<Sig>>>>
using CanAssign =
    TrueAlias<std::enable_if_t<Impl<Sig>::template CallIsValid<F>::value>,
              std::enable_if_t<
                  Impl<Sig>::template CallIsNoexceptIfSigIsNoexcept<F>::value>,
              std::enable_if_t<std::is_constructible_v<std::decay_t<F>, F>>>;

/*SFINAE constraints for the reference-wrapper conversion-assign operator.*/
template <class Sig, class F>
using CanAssignReferenceWrapper = TrueAlias<
    std::enable_if_t<
        Impl<Sig>::template CallIsValid<std::reference_wrapper<F>>::value>,
    std::enable_if_t<Impl<Sig>::template CallIsNoexceptIfSigIsNoexcept<
        std::reference_wrapper<F>>::value>>;

// The constraint for checking whether or not a call meets the noexcept
// callability requirements. We use a preprocessor macro because specifying it
// this way as opposed to a disjunction/branch can improve the user-side error
// messages and avoids an instantiation of std::is_nothrow_invocable_r in the
// cases where the user did not specify a noexcept function type.
//
// The disjunction below is because we can't rely on std::is_nothrow_invocable_r
// to give the right result when ReturnType is non-moveable in toolchains that
// don't treat non-moveable result types correctly. For example this was the
// case in libc++ before commit c3a24882 (2022-05).
#define ABSL_INTERNAL_ANY_INVOCABLE_NOEXCEPT_CONSTRAINT_true(inv_quals)     \
  std::enable_if_t<std::disjunction_v<                                      \
      std::is_nothrow_invocable_r<                                          \
          ReturnType, UnwrapStdReferenceWrapper<std::decay_t<F>> inv_quals, \
          P...>,                                                            \
      std::conjunction<                                                     \
          std::is_nothrow_invocable<                                        \
              UnwrapStdReferenceWrapper<std::decay_t<F>> inv_quals, P...>,  \
          std::is_same<                                                     \
              ReturnType,                                                   \
              std::invoke_result_t<                                         \
                  UnwrapStdReferenceWrapper<std::decay_t<F>> inv_quals,     \
                  P...>>>>>

#define ABSL_INTERNAL_ANY_INVOCABLE_NOEXCEPT_CONSTRAINT_false(inv_quals)
//
////////////////////////////////////////////////////////////////////////////////

// A macro to generate partial specializations of Impl with the different
// combinations of supported cv/reference qualifiers and noexcept specifier.
//
// Here, `cv` are the cv-qualifiers if any, `ref` is the ref-qualifier if any,
// inv_quals is the reference type to be used when invoking the target, and
// noex is "true" if the function type is noexcept, or false if it is not.
//
// The CallIsValid condition is more complicated than simply using
// std::is_invocable_r because we can't rely on it to give the right result
// when ReturnType is non-moveable in toolchains that don't treat non-moveable
// result types correctly. For example this was the case in libc++ before commit
// c3a24882 (2022-05).
#define ABSL_INTERNAL_ANY_INVOCABLE_IMPL_(cv, ref, inv_quals, noex)            \
  template <class ReturnType, class... P>                                      \
  class Impl<ReturnType(P...) cv ref noexcept(noex)>                           \
      : public CoreImpl<noex, ReturnType, P...> {                              \
   public:                                                                     \
    /*The base class, which contains the datamembers and core operations*/     \
    using Core = CoreImpl<noex, ReturnType, P...>;                             \
                                                                               \
    /*SFINAE constraint to check if F is invocable with the proper signature*/ \
    template <class F>                                                         \
    using CallIsValid = TrueAlias<std::enable_if_t<std::disjunction<           \
        std::is_invocable_r<ReturnType, std::decay_t<F> inv_quals, P...>,      \
        std::is_same<ReturnType,                                               \
                     std::invoke_result_t<std::decay_t<F> inv_quals, P...>>>:: \
                                                       value>>;                \
                                                                               \
    /*SFINAE constraint to check if F is nothrow-invocable when necessary*/    \
    template <class F>                                                         \
    using CallIsNoexceptIfSigIsNoexcept =                                      \
        TrueAlias<ABSL_INTERNAL_ANY_INVOCABLE_NOEXCEPT_CONSTRAINT_##noex(      \
            inv_quals)>;                                                       \
                                                                               \
    /*Put the AnyInvocable into an empty state.*/                              \
    Impl() = default;                                                          \
                                                                               \
    /*The implementation of a conversion-constructor from "f*/                 \
    /*This forwards to Core, attaching inv_quals so that the base class*/      \
    /*knows how to properly type-erase the invocation.*/                       \
    template <class F>                                                         \
    explicit Impl(ConversionConstruct, F&& f)                                  \
        : Core(TypedConversionConstruct<std::decay_t<F> inv_quals>(),          \
               std::forward<F>(f)) { __builtin_trap() /* STUB: not implemented */; }                                          \
                                                                               \
    /*Forward along the in-place construction parameters.*/                    \
    template <class T, class... Args>                                          \
    explicit Impl(std::in_place_type_t<T>, Args&&... args)                     \
        : Core(std::in_place_type<std::decay_t<T> inv_quals>,                  \
               std::forward<Args>(args)...) { __builtin_trap() /* STUB: not implemented */; }                                 \
                                                                               \
    /*Raises a fatal error when the AnyInvocable is invoked after a move*/     \
    static ReturnType InvokedAfterMove(                                        \
        TypeErasedState*, ForwardedParameterType<P>...) noexcept(noex) { __builtin_trap() /* STUB: not implemented */; }                                                                          \
                                                                               \
    InvokerType<noex, ReturnType, P...>* ExtractInvoker() cv {                 \
      using QualifiedTestType = int cv ref;                                    \
      auto* invoker = this->invoker_;                                          \
      if (!std::is_const_v<QualifiedTestType> &&                               \
          std::is_rvalue_reference_v<QualifiedTestType>) {                     \
        ABSL_ASSERT([this]() {                                                 \
          /* We checked that this isn't const above, so const_cast is safe */  \
          const_cast<Impl*>(this)->invoker_ = InvokedAfterMove;                \
          return this->HasValue();                                             \
        }());                                                                  \
      }                                                                        \
      return invoker;                                                          \
    }                                                                          \
                                                                               \
    /*The actual invocation operation with the proper signature*/              \
    ReturnType operator()(P... args) cv ref noexcept(noex) { __builtin_trap() /* STUB: not implemented */; }                                                                          \
  }

// A convenience macro that defines specializations for the noexcept(true) and
// noexcept(false) forms, given the other properties.
#define ABSL_INTERNAL_ANY_INVOCABLE_IMPL(cv, ref, inv_quals)    \
  ABSL_INTERNAL_ANY_INVOCABLE_IMPL_(cv, ref, inv_quals, false); \
  ABSL_INTERNAL_ANY_INVOCABLE_IMPL_(cv, ref, inv_quals, true)

// Non-ref-qualified partial specializations
ABSL_INTERNAL_ANY_INVOCABLE_IMPL(, , &);
ABSL_INTERNAL_ANY_INVOCABLE_IMPL(const, , const&);

// Lvalue-ref-qualified partial specializations
ABSL_INTERNAL_ANY_INVOCABLE_IMPL(, &, &);
ABSL_INTERNAL_ANY_INVOCABLE_IMPL(const, &, const&);

// Rvalue-ref-qualified partial specializations
ABSL_INTERNAL_ANY_INVOCABLE_IMPL(, &&, &&);
ABSL_INTERNAL_ANY_INVOCABLE_IMPL(const, &&, const&&);

// Undef the detail-only macros.
#undef ABSL_INTERNAL_ANY_INVOCABLE_IMPL
#undef ABSL_INTERNAL_ANY_INVOCABLE_IMPL_
#undef ABSL_INTERNAL_ANY_INVOCABLE_NOEXCEPT_CONSTRAINT_false
#undef ABSL_INTERNAL_ANY_INVOCABLE_NOEXCEPT_CONSTRAINT_true

}  // namespace internal_any_invocable
ABSL_NAMESPACE_END
}  // namespace absl

#endif  // ABSL_FUNCTIONAL_INTERNAL_ANY_INVOCABLE_H_
