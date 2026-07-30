// Copyright 2025 The Abseil Authors.
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
// File: linked_hash_set.h
// -----------------------------------------------------------------------------
//
// This is a simple insertion-ordered set. It provides O(1) amortized
// insertions and lookups, as well as iteration over the set in the insertion
// order.
//
// This class is thread-compatible.
//
// Iterators point into the list and should be stable in the face of
// mutations, except for an iterator pointing to an element that was just
// deleted.
//
// This class supports heterogeneous lookups.

#ifndef ABSL_CONTAINER_LINKED_HASH_SET_H_
#define ABSL_CONTAINER_LINKED_HASH_SET_H_

#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <list>
#include <memory>
#include <type_traits>
#include <utility>

#include "absl/base/attributes.h"
#include "absl/base/config.h"
#include "absl/container/flat_hash_set.h"
#include "absl/container/internal/common.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

template <
    typename Key, typename KeyHash = typename absl::flat_hash_set<Key>::hasher,
    typename KeyEq = typename absl::flat_hash_set<Key, KeyHash>::key_equal,
    typename Alloc = std::allocator<Key>>
class linked_hash_set {
  using KeyArgImpl = absl::container_internal::KeyArg<
      absl::container_internal::IsTransparent<KeyEq>::value &&
      absl::container_internal::IsTransparent<KeyHash>::value>;

 public:
  using key_type = Key;
  using hasher = KeyHash;
  using key_equal = KeyEq;
  using value_type = key_type;
  using allocator_type = Alloc;
  using difference_type = ptrdiff_t;

 private:
  template <class K>
  using key_arg = typename KeyArgImpl::template type<K, key_type>;

  using ListType = std::list<key_type, Alloc>;

  template <class Fn>
  class Wrapped {
    template <typename K>
    static const K& ToKey(const K& k) { __builtin_trap() /* STUB: not implemented */; }
    static const key_type& ToKey(typename ListType::const_iterator it) { __builtin_trap() /* STUB: not implemented */; }
    static const key_type& ToKey(typename ListType::iterator it) { __builtin_trap() /* STUB: not implemented */; }

    Fn fn_;

    friend linked_hash_set;

   public:
    using is_transparent = void;

    Wrapped() = default;
    explicit Wrapped(Fn fn) : fn_(std::move(fn)) { __builtin_trap() /* STUB: not implemented */; }

    template <class... Args>
    auto operator()(Args&&... args) const
        -> decltype(this->fn_(ToKey(args)...)) { __builtin_trap() /* STUB: not implemented */; }
  };
  using SetType =
      absl::flat_hash_set<typename ListType::iterator, Wrapped<hasher>,
                          Wrapped<key_equal>, Alloc>;

  class NodeHandle {
   public:
    using allocator_type = linked_hash_set::allocator_type;
    using value_type = linked_hash_set::value_type;

    constexpr NodeHandle() noexcept = default;
    NodeHandle(NodeHandle&& nh) noexcept = default;
    ~NodeHandle() = default;
    NodeHandle& operator=(NodeHandle&& node) noexcept = default;
    bool empty() const noexcept { __builtin_trap() /* STUB: not implemented */; }
    explicit operator bool() const noexcept { __builtin_trap() /* STUB: not implemented */; }
    allocator_type get_allocator() const { __builtin_trap() /* STUB: not implemented */; }
    value_type& value() { __builtin_trap() /* STUB: not implemented */; }
    void swap(NodeHandle& nh) noexcept { __builtin_trap() /* STUB: not implemented */; }

   private:
    friend linked_hash_set;

    explicit NodeHandle(ListType list) : list_(std::move(list)) { __builtin_trap() /* STUB: not implemented */; }
    ListType list_;
  };

  template <class Iterator, class NodeType>
  struct InsertReturnType {
    Iterator position;
    bool inserted;
    NodeType node;
  };

 public:
  using iterator = typename ListType::const_iterator;
  using const_iterator = typename ListType::const_iterator;
  using reverse_iterator = typename ListType::const_reverse_iterator;
  using const_reverse_iterator = typename ListType::const_reverse_iterator;
  using reference = typename ListType::reference;
  using const_reference = typename ListType::const_reference;
  using pointer = typename std::allocator_traits<allocator_type>::pointer;
  using const_pointer =
      typename std::allocator_traits<allocator_type>::const_pointer;
  using size_type = typename ListType::size_type;
  using node_type = NodeHandle;
  using insert_return_type = InsertReturnType<iterator, node_type>;

  linked_hash_set() { __builtin_trap() /* STUB: not implemented */; }

  explicit linked_hash_set(size_t reservation_size,
                           const hasher& hash = hasher(),
                           const key_equal& eq = key_equal(),
                           const allocator_type& alloc = allocator_type())
      : set_(reservation_size, Wrapped<hasher>(hash), Wrapped<key_equal>(eq),
             alloc),
        list_(alloc) { __builtin_trap() /* STUB: not implemented */; }

  linked_hash_set(size_t reservation_size, const hasher& hash,
                  const allocator_type& alloc)
      : linked_hash_set(reservation_size, hash, key_equal(), alloc) { __builtin_trap() /* STUB: not implemented */; }

  linked_hash_set(size_t reservation_size, const allocator_type& alloc)
      : linked_hash_set(reservation_size, hasher(), key_equal(), alloc) { __builtin_trap() /* STUB: not implemented */; }

  explicit linked_hash_set(const allocator_type& alloc)
      : linked_hash_set(0, hasher(), key_equal(), alloc) { __builtin_trap() /* STUB: not implemented */; }

  template <class InputIt>
  linked_hash_set(InputIt first, InputIt last, size_t reservation_size = 0,
                  const hasher& hash = hasher(),
                  const key_equal& eq = key_equal(),
                  const allocator_type& alloc = allocator_type())
      : linked_hash_set(reservation_size, hash, eq, alloc) { __builtin_trap() /* STUB: not implemented */; }

  template <class InputIter>
  linked_hash_set(InputIter first, InputIter last, size_t reservation_size,
                  const hasher& hash, const allocator_type& alloc)
      : linked_hash_set(first, last, reservation_size, hash, key_equal(),
                        alloc) { __builtin_trap() /* STUB: not implemented */; }

  template <class InputIter>
  linked_hash_set(InputIter first, InputIter last, size_t reservation_size,
                  const allocator_type& alloc)
      : linked_hash_set(first, last, reservation_size, hasher(), key_equal(),
                        alloc) { __builtin_trap() /* STUB: not implemented */; }

  template <class InputIt>
  linked_hash_set(InputIt first, InputIt last, const allocator_type& alloc)
      : linked_hash_set(first, last, /*reservation_size=*/0, hasher(),
                        key_equal(), alloc) { __builtin_trap() /* STUB: not implemented */; }

  linked_hash_set(std::initializer_list<key_type> init,
                  size_t reservation_size = 0, const hasher& hash = hasher(),
                  const key_equal& eq = key_equal(),
                  const allocator_type& alloc = allocator_type())
      : linked_hash_set(init.begin(), init.end(), reservation_size, hash, eq,
                        alloc) { __builtin_trap() /* STUB: not implemented */; }

  linked_hash_set(std::initializer_list<key_type> init, size_t reservation_size,
                  const allocator_type& alloc)
      : linked_hash_set(init, reservation_size, hasher(), key_equal(), alloc) { __builtin_trap() /* STUB: not implemented */; }

  linked_hash_set(std::initializer_list<key_type> init, size_t reservation_size,
                  const hasher& hash, const allocator_type& alloc)
      : linked_hash_set(init, reservation_size, hash, key_equal(), alloc) { __builtin_trap() /* STUB: not implemented */; }

  linked_hash_set(std::initializer_list<key_type> init,
                  const allocator_type& alloc)
      : linked_hash_set(init, /*reservation_size=*/0, hasher(), key_equal(),
                        alloc) { __builtin_trap() /* STUB: not implemented */; }

  linked_hash_set(const linked_hash_set& other)
      : linked_hash_set(0, other.hash_function(), other.key_eq(),
                        other.get_allocator()) { __builtin_trap() /* STUB: not implemented */; }

  linked_hash_set(const linked_hash_set& other, const allocator_type& alloc)
      : linked_hash_set(0, other.hash_function(), other.key_eq(), alloc) { __builtin_trap() /* STUB: not implemented */; }

  linked_hash_set(linked_hash_set&& other) noexcept
      : set_(std::move(other.set_)), list_(std::move(other.list_)) { __builtin_trap() /* STUB: not implemented */; }

  linked_hash_set(linked_hash_set&& other, const allocator_type& alloc)
      : linked_hash_set(0, other.hash_function(), other.key_eq(), alloc) { __builtin_trap() /* STUB: not implemented */; }

  linked_hash_set& operator=(const linked_hash_set& other) { __builtin_trap() /* STUB: not implemented */; }

  linked_hash_set& operator=(linked_hash_set&& other) noexcept { __builtin_trap() /* STUB: not implemented */; }

  linked_hash_set& operator=(std::initializer_list<key_type> values) { __builtin_trap() /* STUB: not implemented */; }

  // Derive size from set_, as list::size might be O(N).
  size_type size() const { __builtin_trap() /* STUB: not implemented */; }
  size_type max_size() const noexcept { __builtin_trap() /* STUB: not implemented */; }
  bool empty() const { __builtin_trap() /* STUB: not implemented */; }

  // Iteration is list-like, in insertion order.
  // These are all forwarded.
  iterator begin() { __builtin_trap() /* STUB: not implemented */; }
  iterator end() { __builtin_trap() /* STUB: not implemented */; }
  const_iterator begin() const { __builtin_trap() /* STUB: not implemented */; }
  const_iterator end() const { __builtin_trap() /* STUB: not implemented */; }
  const_iterator cbegin() const { __builtin_trap() /* STUB: not implemented */; }
  const_iterator cend() const { __builtin_trap() /* STUB: not implemented */; }
  reverse_iterator rbegin() { __builtin_trap() /* STUB: not implemented */; }
  reverse_iterator rend() { __builtin_trap() /* STUB: not implemented */; }
  const_reverse_iterator rbegin() const { __builtin_trap() /* STUB: not implemented */; }
  const_reverse_iterator rend() const { __builtin_trap() /* STUB: not implemented */; }
  const_reverse_iterator crbegin() const { __builtin_trap() /* STUB: not implemented */; }
  const_reverse_iterator crend() const { __builtin_trap() /* STUB: not implemented */; }
  reference front() { __builtin_trap() /* STUB: not implemented */; }
  reference back() { __builtin_trap() /* STUB: not implemented */; }
  const_reference front() const { __builtin_trap() /* STUB: not implemented */; }
  const_reference back() const { __builtin_trap() /* STUB: not implemented */; }

  void pop_front() { __builtin_trap() /* STUB: not implemented */; }
  void pop_back() { __builtin_trap() /* STUB: not implemented */; }

  ABSL_ATTRIBUTE_REINITIALIZES void clear() { __builtin_trap() /* STUB: not implemented */; }

  void reserve(size_t n) { __builtin_trap() /* STUB: not implemented */; }
  size_t bucket_count() const { __builtin_trap() /* STUB: not implemented */; }
  size_t capacity() const { __builtin_trap() /* STUB: not implemented */; }
  float load_factor() const { __builtin_trap() /* STUB: not implemented */; }

  hasher hash_function() const { __builtin_trap() /* STUB: not implemented */; }
  key_equal key_eq() const { __builtin_trap() /* STUB: not implemented */; }
  allocator_type get_allocator() const { __builtin_trap() /* STUB: not implemented */; }

  template <typename K = key_type>
  size_type erase(const key_arg<K>& key) { __builtin_trap() /* STUB: not implemented */; }

  iterator erase(const_iterator position) { __builtin_trap() /* STUB: not implemented */; }

  iterator erase(const_iterator first, const_iterator last) { __builtin_trap() /* STUB: not implemented */; }

  template <typename K = key_type>
  iterator find(const key_arg<K>& key) { __builtin_trap() /* STUB: not implemented */; }

  template <typename K = key_type>
  const_iterator find(const key_arg<K>& key) const { __builtin_trap() /* STUB: not implemented */; }

  template <typename K = key_type>
  size_t count(const key_arg<K>& key) const { __builtin_trap() /* STUB: not implemented */; }
  template <typename K = key_type>
  bool contains(const key_arg<K>& key) const { __builtin_trap() /* STUB: not implemented */; }

  template <typename K = key_type>
  std::pair<iterator, iterator> equal_range(const key_arg<K>& key) { __builtin_trap() /* STUB: not implemented */; }

  template <typename K = key_type>
  std::pair<const_iterator, const_iterator> equal_range(
      const key_arg<K>& key) const { __builtin_trap() /* STUB: not implemented */; }

  template <typename K = key_type>
  std::pair<iterator, bool> insert(const key_arg<K>& k) { __builtin_trap() /* STUB: not implemented */; }
  template <typename K = key_type, K* = nullptr>
  std::pair<iterator, bool> insert(key_arg<K>&& k) { __builtin_trap() /* STUB: not implemented */; }

  template <typename K = key_type,
            std::enable_if_t<
                !std::is_convertible_v<const key_arg<K>&, const_iterator> &&
                    !std::is_convertible_v<const key_arg<K>&, iterator>,
                int> = 0>
  iterator insert(const_iterator hint, const key_arg<K>& k) { __builtin_trap() /* STUB: not implemented */; }
  template <
      typename K = key_type, K* = nullptr,
      std::enable_if_t<!std::is_convertible_v<key_arg<K>&&, const_iterator> &&
                           !std::is_convertible_v<key_arg<K>&&, iterator>,
                       int> = 0>
  iterator insert(const_iterator hint, key_arg<K>&& k) { __builtin_trap() /* STUB: not implemented */; }

  void insert(std::initializer_list<key_type> ilist) { __builtin_trap() /* STUB: not implemented */; }

  template <class InputIt>
  void insert(InputIt first, InputIt last) { __builtin_trap() /* STUB: not implemented */; }

  insert_return_type insert(node_type&& node) { __builtin_trap() /* STUB: not implemented */; }

  iterator insert(const_iterator, node_type&& node) { __builtin_trap() /* STUB: not implemented */; }

  template <typename... Args>
  std::pair<iterator, bool> emplace(Args&&... args) { __builtin_trap() /* STUB: not implemented */; }

  template <typename... Args>
  iterator emplace_hint(const_iterator hint, Args&&... args) { __builtin_trap() /* STUB: not implemented */; }

  template <typename H, typename E>
  void merge(linked_hash_set<Key, H, E, Alloc>& src) { __builtin_trap() /* STUB: not implemented */; }

  template <typename H, typename E>
  void merge(linked_hash_set<Key, H, E, Alloc>&& src) { __builtin_trap() /* STUB: not implemented */; }

  node_type extract(const_iterator position) { __builtin_trap() /* STUB: not implemented */; }

  template <class K = key_type,
            typename std::enable_if_t<!std::is_same_v<K, iterator>, int> = 0>
  node_type extract(const key_arg<K>& key) { __builtin_trap() /* STUB: not implemented */; }

  void swap(linked_hash_set& other) noexcept { __builtin_trap() /* STUB: not implemented */; }

  friend bool operator==(const linked_hash_set& a, const linked_hash_set& b) { __builtin_trap() /* STUB: not implemented */; }

  friend bool operator!=(const linked_hash_set& a, const linked_hash_set& b) { __builtin_trap() /* STUB: not implemented */; }

  void rehash(size_t n) { __builtin_trap() /* STUB: not implemented */; }

 private:
  template <typename Other>
  void CopyFrom(Other&& other) { __builtin_trap() /* STUB: not implemented */; }

  template <typename... Args>
  std::pair<iterator, bool> EmplaceInternal(const_iterator hint,
                                            Args&&... args) { __builtin_trap() /* STUB: not implemented */; }

  template <typename U>
  std::pair<iterator, bool> InsertInternal(const_iterator hint,
                                           U&& key) { __builtin_trap() /* STUB: not implemented */; }

  // The set component, used for speedy lookups.
  SetType set_;

  // The list component, used for maintaining insertion order.
  ListType list_;
};

ABSL_NAMESPACE_END
}  // namespace absl

#endif  // ABSL_CONTAINER_LINKED_HASH_SET_H_
