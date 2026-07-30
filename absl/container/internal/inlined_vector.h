// Copyright 2019 The Abseil Authors.
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

#ifndef ABSL_CONTAINER_INTERNAL_INLINED_VECTOR_H_
#define ABSL_CONTAINER_INTERNAL_INLINED_VECTOR_H_

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <iterator>
#include <limits>
#include <memory>
#include <new>
#include <type_traits>
#include <utility>

#include "absl/base/attributes.h"
#include "absl/base/config.h"
#include "absl/base/internal/hardening.h"
#include "absl/base/macros.h"
#include "absl/container/internal/compressed_tuple.h"
#include "absl/memory/memory.h"
#include "absl/meta/type_traits.h"
#include "absl/types/span.h"

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace inlined_vector_internal {

// GCC does not deal very well with the below code
#if !defined(__clang__) && defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif

template <typename A>
using AllocatorTraits = std::allocator_traits<A>;
template <typename A>
using ValueType = typename AllocatorTraits<A>::value_type;
template <typename A>
using SizeType = typename AllocatorTraits<A>::size_type;
template <typename A>
using Pointer = typename AllocatorTraits<A>::pointer;
template <typename A>
using ConstPointer = typename AllocatorTraits<A>::const_pointer;
template <typename A>
using SizeType = typename AllocatorTraits<A>::size_type;
template <typename A>
using DifferenceType = typename AllocatorTraits<A>::difference_type;
template <typename A>
using Reference = ValueType<A>&;
template <typename A>
using ConstReference = const ValueType<A>&;
template <typename A>
using Iterator = Pointer<A>;
template <typename A>
using ConstIterator = ConstPointer<A>;
template <typename A>
using ReverseIterator = typename std::reverse_iterator<Iterator<A>>;
template <typename A>
using ConstReverseIterator = typename std::reverse_iterator<ConstIterator<A>>;
template <typename A>
using MoveIterator = typename std::move_iterator<Iterator<A>>;

template <typename A>
using IsMoveAssignOk = std::is_move_assignable<ValueType<A>>;
template <typename A>
using IsSwapOk = absl::type_traits_internal::IsSwappable<ValueType<A>>;

template <typename A, bool IsTriviallyDestructible =
                          std::is_trivially_destructible_v<ValueType<A>> &&
                          std::is_same_v<A, std::allocator<ValueType<A>>>>
struct DestroyAdapter;

template <typename A>
struct DestroyAdapter<A, /* IsTriviallyDestructible */ false> {
  static void DestroyElements(A& allocator, Pointer<A> destroy_first,
                              SizeType<A> destroy_size) {
    for (SizeType<A> i = destroy_size; i != 0;) {
      --i;
      AllocatorTraits<A>::destroy(allocator, destroy_first + i);
    }
  }
};

template <typename A>
struct DestroyAdapter<A, /* IsTriviallyDestructible */ true> {
  static void DestroyElements(A& allocator, Pointer<A> destroy_first,
                              SizeType<A> destroy_size) {
    static_cast<void>(allocator);
    static_cast<void>(destroy_first);
    static_cast<void>(destroy_size);
  }
};

template <typename A>
struct Allocation {
  Pointer<A> data = nullptr;
  SizeType<A> capacity = 0;
};

template <typename A,
          bool IsOverAligned =
              (alignof(ValueType<A>) > ABSL_INTERNAL_DEFAULT_NEW_ALIGNMENT)>
struct MallocAdapter {
  static Allocation<A> Allocate(A& allocator, SizeType<A> requested_capacity) {
    return {AllocatorTraits<A>::allocate(allocator, requested_capacity),
            requested_capacity};
  }

  static void Deallocate(A& allocator, Pointer<A> pointer,
                         SizeType<A> capacity) {
    AllocatorTraits<A>::deallocate(allocator, pointer, capacity);
  }
};

template <typename A, typename ValueAdapter>
void ConstructElements(absl::type_identity_t<A>& allocator,
                       Pointer<A> construct_first, ValueAdapter& values,
                       SizeType<A> construct_size) {
  for (SizeType<A> i = 0; i < construct_size; ++i) {
    ABSL_INTERNAL_TRY { values.ConstructNext(allocator, construct_first + i); }
    ABSL_INTERNAL_CATCH_ANY {
      DestroyAdapter<A>::DestroyElements(allocator, construct_first, i);
      ABSL_INTERNAL_RETHROW;
    }
  }
}

template <typename A, typename ValueAdapter>
void AssignElements(Pointer<A> assign_first, ValueAdapter& values,
                    SizeType<A> assign_size) { __builtin_trap() /* STUB: not implemented */; }

template <typename A>
struct StorageView {
  Pointer<A> data;
  SizeType<A> size;
  SizeType<A> capacity;
};

template <typename A, typename Iterator>
class IteratorValueAdapter {
 public:
  explicit IteratorValueAdapter(const Iterator& it) : it_(it) { __builtin_trap() /* STUB: not implemented */; }

  void ConstructNext(A& allocator, Pointer<A> construct_at) { __builtin_trap() /* STUB: not implemented */; }

  void AssignNext(Pointer<A> assign_at) { __builtin_trap() /* STUB: not implemented */; }

 private:
  Iterator it_;
};

template <typename A>
class CopyValueAdapter {
 public:
  explicit CopyValueAdapter(ConstPointer<A> p) : ptr_(p) { __builtin_trap() /* STUB: not implemented */; }

  void ConstructNext(A& allocator, Pointer<A> construct_at) { __builtin_trap() /* STUB: not implemented */; }

  void AssignNext(Pointer<A> assign_at) { __builtin_trap() /* STUB: not implemented */; }

 private:
  ConstPointer<A> ptr_;
};

template <typename A>
class DefaultValueAdapter {
 public:
  explicit DefaultValueAdapter() { __builtin_trap() /* STUB: not implemented */; }

  void ConstructNext(A& allocator, Pointer<A> construct_at) { __builtin_trap() /* STUB: not implemented */; }

  void AssignNext(Pointer<A> assign_at) { __builtin_trap() /* STUB: not implemented */; }
};

template <typename A>
class AllocationTransaction {
 public:
  explicit AllocationTransaction(A& allocator)
      : allocator_data_(allocator, nullptr), capacity_(0) { __builtin_trap() /* STUB: not implemented */; }

  ~AllocationTransaction() { __builtin_trap() /* STUB: not implemented */; }

  AllocationTransaction(const AllocationTransaction&) = delete;
  void operator=(const AllocationTransaction&) = delete;

  A& GetAllocator() { __builtin_trap() /* STUB: not implemented */; }
  Pointer<A>& GetData() { __builtin_trap() /* STUB: not implemented */; }
  SizeType<A>& GetCapacity() { __builtin_trap() /* STUB: not implemented */; }

  bool DidAllocate() { __builtin_trap() /* STUB: not implemented */; }

  Pointer<A> Allocate(SizeType<A> requested_capacity) { __builtin_trap() /* STUB: not implemented */; }

  [[nodiscard]] Allocation<A> Release() && { __builtin_trap() /* STUB: not implemented */; }

 private:
  void Reset() { __builtin_trap() /* STUB: not implemented */; }

  container_internal::CompressedTuple<A, Pointer<A>> allocator_data_;
  SizeType<A> capacity_;
};

template <typename A>
class ConstructionTransaction {
 public:
  explicit ConstructionTransaction(A& allocator)
      : allocator_data_(allocator, nullptr), size_(0) { __builtin_trap() /* STUB: not implemented */; }

  ~ConstructionTransaction() { __builtin_trap() /* STUB: not implemented */; }

  ConstructionTransaction(const ConstructionTransaction&) = delete;
  void operator=(const ConstructionTransaction&) = delete;

  A& GetAllocator() { __builtin_trap() /* STUB: not implemented */; }
  Pointer<A>& GetData() { __builtin_trap() /* STUB: not implemented */; }
  SizeType<A>& GetSize() { __builtin_trap() /* STUB: not implemented */; }

  bool DidConstruct() { __builtin_trap() /* STUB: not implemented */; }
  template <typename ValueAdapter>
  void Construct(Pointer<A> data, ValueAdapter& values, SizeType<A> size) { __builtin_trap() /* STUB: not implemented */; }
  void Commit() && { __builtin_trap() /* STUB: not implemented */; }

 private:
  container_internal::CompressedTuple<A, Pointer<A>> allocator_data_;
  SizeType<A> size_;
};

template <typename T, size_t N, typename A>
class Storage {
 public:
  struct MemcpyPolicy {};
  struct ElementwiseAssignPolicy {};
  struct ElementwiseSwapPolicy {};
  struct ElementwiseConstructPolicy {};

  using MoveAssignmentPolicy = std::conditional_t<
      // Fast path: if the value type can be trivially move assigned and
      // destroyed, and we know the allocator doesn't do anything fancy, then
      // it's safe for us to simply adopt the contents of the storage for
      // `other` and remove its own reference to them. It's as if we had
      // individually move-assigned each value and then destroyed the original.
      std::conjunction_v<std::is_trivially_move_assignable<ValueType<A>>,
                         std::is_trivially_destructible<ValueType<A>>,
                         std::is_same<A, std::allocator<ValueType<A>>>>,
      MemcpyPolicy,
      // Otherwise we use move assignment if possible. If not, we simulate
      // move assignment using move construction.
      //
      // Note that this is in contrast to e.g. std::vector and std::optional,
      // which are themselves not move-assignable when their contained type is
      // not.
      std::conditional_t<IsMoveAssignOk<A>::value, ElementwiseAssignPolicy,
                         ElementwiseConstructPolicy>>;

  // The policy to be used specifically when swapping inlined elements.
  using SwapInlinedElementsPolicy = std::conditional_t<
      // Fast path: if the value type can be trivially relocated, and we
      // know the allocator doesn't do anything fancy, then it's safe for us
      // to simply swap the bytes in the inline storage. It's as if we had
      // relocated the first vector's elements into temporary storage,
      // relocated the second's elements into the (now-empty) first's,
      // and then relocated from temporary storage into the second.
      std::conjunction_v<absl::is_trivially_relocatable<ValueType<A>>,
                         std::is_same<A, std::allocator<ValueType<A>>>>,
      MemcpyPolicy,
      std::conditional_t<IsSwapOk<A>::value, ElementwiseSwapPolicy,
                         ElementwiseConstructPolicy>>;

  static SizeType<A> NextCapacity(SizeType<A> current_capacity) { __builtin_trap() /* STUB: not implemented */; }

  static SizeType<A> ComputeCapacity(SizeType<A> current_capacity,
                                     SizeType<A> requested_capacity) { __builtin_trap() /* STUB: not implemented */; }

  // ---------------------------------------------------------------------------
  // Storage Constructors and Destructor
  // ---------------------------------------------------------------------------

  Storage() : metadata_(A(), /* size and is_allocated */ 0u) { __builtin_trap() /* STUB: not implemented */; }

  explicit Storage(const A& allocator)
      : metadata_(allocator, /* size and is_allocated */ 0u) { __builtin_trap() /* STUB: not implemented */; }

  ~Storage() { __builtin_trap() /* STUB: not implemented */; }

  // ---------------------------------------------------------------------------
  // Storage Member Accessors
  // ---------------------------------------------------------------------------

  SizeType<A>& GetSizeAndIsAllocated() { __builtin_trap() /* STUB: not implemented */; }

  const SizeType<A>& GetSizeAndIsAllocated() const { __builtin_trap() /* STUB: not implemented */; }

  SizeType<A> GetSize() const { __builtin_trap() /* STUB: not implemented */; }

  bool GetIsAllocated() const { __builtin_trap() /* STUB: not implemented */; }

  Pointer<A> GetAllocatedData() { __builtin_trap() /* STUB: not implemented */; }

  ConstPointer<A> GetAllocatedData() const { __builtin_trap() /* STUB: not implemented */; }

  // ABSL_ATTRIBUTE_NO_SANITIZE_CFI is used because the memory pointed to may be
  // uninitialized, a common pattern in allocate()+construct() APIs.
  // https://clang.llvm.org/docs/ControlFlowIntegrity.html#bad-cast-checking
  // NOTE: When this was written, LLVM documentation did not explicitly
  // mention that casting `char*` and using `reinterpret_cast` qualifies
  // as a bad cast.
  ABSL_ATTRIBUTE_NO_SANITIZE_CFI Pointer<A> GetInlinedData() { __builtin_trap() /* STUB: not implemented */; }

  ABSL_ATTRIBUTE_NO_SANITIZE_CFI ConstPointer<A> GetInlinedData() const { __builtin_trap() /* STUB: not implemented */; }

  SizeType<A> GetAllocatedCapacity() const { __builtin_trap() /* STUB: not implemented */; }

  SizeType<A> GetInlinedCapacity() const { __builtin_trap() /* STUB: not implemented */; }

  StorageView<A> MakeStorageView() { __builtin_trap() /* STUB: not implemented */; }

  A& GetAllocator() { __builtin_trap() /* STUB: not implemented */; }

  const A& GetAllocator() const { __builtin_trap() /* STUB: not implemented */; }

  // ---------------------------------------------------------------------------
  // Storage Member Mutators
  // ---------------------------------------------------------------------------

  ABSL_ATTRIBUTE_NOINLINE void InitFrom(const Storage& other);

  template <typename ValueAdapter>
  void Initialize(ValueAdapter values, SizeType<A> new_size);

  template <typename ValueAdapter>
  void Assign(ValueAdapter values, SizeType<A> new_size);

  template <typename ValueAdapter>
  void Resize(ValueAdapter values, SizeType<A> new_size);

  template <typename ValueAdapter>
  Iterator<A> Insert(ConstIterator<A> pos, ValueAdapter values,
                     SizeType<A> insert_count);

  template <typename... Args>
  Reference<A> EmplaceBack(Args&&... args);

  Iterator<A> Erase(ConstIterator<A> from, ConstIterator<A> to);

  void Reserve(SizeType<A> requested_capacity);

  void ShrinkToFit();

  void Swap(Storage* other_storage_ptr);

  void SetIsAllocated() { __builtin_trap() /* STUB: not implemented */; }

  void UnsetIsAllocated() { __builtin_trap() /* STUB: not implemented */; }

  void SetSize(SizeType<A> size) { __builtin_trap() /* STUB: not implemented */; }

  void SetAllocatedSize(SizeType<A> size) { __builtin_trap() /* STUB: not implemented */; }

  void SetInlinedSize(SizeType<A> size) { __builtin_trap() /* STUB: not implemented */; }

  void AddSize(SizeType<A> count) { __builtin_trap() /* STUB: not implemented */; }

  void SubtractSize(SizeType<A> count) { __builtin_trap() /* STUB: not implemented */; }

  void SetAllocation(Allocation<A> allocation) { __builtin_trap() /* STUB: not implemented */; }

  void MemcpyFrom(const Storage& other_storage) { __builtin_trap() /* STUB: not implemented */; }

  void DeallocateIfAllocated() { __builtin_trap() /* STUB: not implemented */; }

 private:
  ABSL_ATTRIBUTE_NOINLINE void DestroyContents();

  using Metadata = container_internal::CompressedTuple<A, SizeType<A>>;

  struct Allocated {
    Pointer<A> allocated_data;
    SizeType<A> allocated_capacity;
  };

  // `kOptimalInlinedSize` is an automatically adjusted inlined capacity of the
  // `InlinedVector`. Sometimes, it is possible to increase the capacity (from
  // the user requested `N`) without increasing the size of the `InlinedVector`.
  static constexpr size_t kOptimalInlinedSize =
      (std::max)(N, sizeof(Allocated) / sizeof(ValueType<A>));

  struct Inlined {
    alignas(ValueType<A>) unsigned char inlined_data[sizeof(
        ValueType<A>[kOptimalInlinedSize])];
  };

  union Data {
    Allocated allocated;
    Inlined inlined;
  };

  void SwapN(ElementwiseSwapPolicy, Storage* other, SizeType<A> n);
  void SwapN(ElementwiseConstructPolicy, Storage* other, SizeType<A> n);

  void SwapInlinedElements(MemcpyPolicy, Storage* other);
  template <typename NotMemcpyPolicy>
  void SwapInlinedElements(NotMemcpyPolicy, Storage* other);

  template <typename... Args>
  ABSL_ATTRIBUTE_NOINLINE Reference<A> EmplaceBackSlow(Args&&... args);

  Metadata metadata_;
  Data data_;
};

template <typename T, size_t N, typename A>
void Storage<T, N, A>::DestroyContents() { __builtin_trap() /* STUB: not implemented */; }

template <typename T, size_t N, typename A>
void Storage<T, N, A>::InitFrom(const Storage& other) { __builtin_trap() /* STUB: not implemented */; }

template <typename T, size_t N, typename A>
template <typename ValueAdapter>
auto Storage<T, N, A>::Initialize(ValueAdapter values,
                                  SizeType<A> new_size) -> void { __builtin_trap() /* STUB: not implemented */; }

template <typename T, size_t N, typename A>
template <typename ValueAdapter>
auto Storage<T, N, A>::Assign(ValueAdapter values,
                              SizeType<A> new_size) -> void { __builtin_trap() /* STUB: not implemented */; }

template <typename T, size_t N, typename A>
template <typename ValueAdapter>
auto Storage<T, N, A>::Resize(ValueAdapter values,
                              SizeType<A> new_size) -> void { __builtin_trap() /* STUB: not implemented */; }

template <typename T, size_t N, typename A>
template <typename ValueAdapter>
auto Storage<T, N, A>::Insert(ConstIterator<A> pos, ValueAdapter values,
                              SizeType<A> insert_count) -> Iterator<A> { __builtin_trap() /* STUB: not implemented */; }

template <typename T, size_t N, typename A>
template <typename... Args>
auto Storage<T, N, A>::EmplaceBack(Args&&... args) -> Reference<A> { __builtin_trap() /* STUB: not implemented */; }

template <typename T, size_t N, typename A>
template <typename... Args>
auto Storage<T, N, A>::EmplaceBackSlow(Args&&... args) -> Reference<A> { __builtin_trap() /* STUB: not implemented */; }

template <typename T, size_t N, typename A>
auto Storage<T, N, A>::Erase(ConstIterator<A> from,
                             ConstIterator<A> to) -> Iterator<A> { __builtin_trap() /* STUB: not implemented */; }

template <typename T, size_t N, typename A>
auto Storage<T, N, A>::Reserve(SizeType<A> requested_capacity) -> void { __builtin_trap() /* STUB: not implemented */; }

template <typename T, size_t N, typename A>
auto Storage<T, N, A>::ShrinkToFit() -> void { __builtin_trap() /* STUB: not implemented */; }

template <typename T, size_t N, typename A>
auto Storage<T, N, A>::Swap(Storage* other_storage_ptr) -> void { __builtin_trap() /* STUB: not implemented */; }

template <typename T, size_t N, typename A>
void Storage<T, N, A>::SwapN(ElementwiseSwapPolicy, Storage* other,
                             SizeType<A> n) { __builtin_trap() /* STUB: not implemented */; }

template <typename T, size_t N, typename A>
void Storage<T, N, A>::SwapN(ElementwiseConstructPolicy, Storage* other,
                             SizeType<A> n) { __builtin_trap() /* STUB: not implemented */; }

template <typename T, size_t N, typename A>
void Storage<T, N, A>::SwapInlinedElements(MemcpyPolicy, Storage* other) { __builtin_trap() /* STUB: not implemented */; }

template <typename T, size_t N, typename A>
template <typename NotMemcpyPolicy>
void Storage<T, N, A>::SwapInlinedElements(NotMemcpyPolicy policy,
                                           Storage* other) { __builtin_trap() /* STUB: not implemented */; }

// End ignore "array-bounds"
#if !defined(__clang__) && defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

}  // namespace inlined_vector_internal
ABSL_NAMESPACE_END
}  // namespace absl

#endif  // ABSL_CONTAINER_INTERNAL_INLINED_VECTOR_H_
