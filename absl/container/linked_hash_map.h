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
// File: linked_hash_map.h
// -----------------------------------------------------------------------------
//
// This is a simple insertion-ordered map. It provides O(1) amortized
// insertions and lookups, as well as iteration over the map in the insertion
// order.
//
// This class is thread-compatible.
//
// Iterators point into the list and should be stable in the face of
// mutations, except for an iterator pointing to an element that was just
// deleted.
//
// This class supports heterogeneous lookups.

#ifndef ABSL_CONTAINER_LINKED_HASH_MAP_H_
#define ABSL_CONTAINER_LINKED_HASH_MAP_H_

#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <list>
#include <memory>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>

#include "absl/base/attributes.h"
#include "absl/base/config.h"
#include "absl/base/optimization.h"
#include "absl/base/throw_delegate.h"
#include "absl/container/flat_hash_set.h"
#include "absl/container/internal/common.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

template <typename Key, typename Value,
          typename KeyHash = typename absl::flat_hash_set<Key>::hasher,
          typename KeyEq =
              typename absl::flat_hash_set<Key, KeyHash>::key_equal,
          typename Alloc = std::allocator<std::pair<const Key, Value>>>
class linked_hash_map {
  using KeyArgImpl = absl::container_internal::KeyArg<
      absl::container_internal::IsTransparent<KeyEq>::value &&
      absl::container_internal::IsTransparent<KeyHash>::value>;

 public:
  using key_type = Key;
  using mapped_type = Value;
  using hasher = KeyHash;
  using key_equal = KeyEq;
  using value_type = std::pair<const key_type, mapped_type>;
  using allocator_type = Alloc;
  using difference_type = ptrdiff_t;

 private:
  template <class K>
  using key_arg = typename KeyArgImpl::template type<K, key_type>;

  using ListType = std::list<value_type, Alloc>;

  template <class Fn>
  class Wrapped {
    template <typename K>
    static const K& ToKey(const K& k) { __builtin_trap() /* STUB: not implemented */; }
    static const key_type& ToKey(typename ListType::const_iterator it) { __builtin_trap() /* STUB: not implemented */; }
    static const key_type& ToKey(typename ListType::iterator it) { __builtin_trap() /* STUB: not implemented */; }

    Fn fn_;

    friend linked_hash_map;

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
    using key_type = linked_hash_map::key_type;
    using mapped_type = linked_hash_map::mapped_type;
    using allocator_type = linked_hash_map::allocator_type;

    constexpr NodeHandle() noexcept = default;
    NodeHandle(NodeHandle&& nh) noexcept = default;
    ~NodeHandle() = default;
    NodeHandle& operator=(NodeHandle&& node) noexcept = default;
    bool empty() const noexcept { __builtin_trap() /* STUB: not implemented */; }
    explicit operator bool() const noexcept { __builtin_trap() /* STUB: not implemented */; }
    allocator_type get_allocator() const { __builtin_trap() /* STUB: not implemented */; }
    const key_type& key() const { __builtin_trap() /* STUB: not implemented */; }
    mapped_type& mapped() { __builtin_trap() /* STUB: not implemented */; }
    void swap(NodeHandle& nh) noexcept { __builtin_trap() /* STUB: not implemented */; }

   private:
    friend linked_hash_map;

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
  using iterator = typename ListType::iterator;
  using const_iterator = typename ListType::const_iterator;
  using reverse_iterator = typename ListType::reverse_iterator;
  using const_reverse_iterator = typename ListType::const_reverse_iterator;
  using reference = typename ListType::reference;
  using const_reference = typename ListType::const_reference;
  using size_type = typename ListType::size_type;
  using pointer = typename std::allocator_traits<allocator_type>::pointer;
  using const_pointer =
      typename std::allocator_traits<allocator_type>::const_pointer;
  using node_type = NodeHandle;
  using insert_return_type = InsertReturnType<iterator, node_type>;

  linked_hash_map() { __builtin_trap() /* STUB: not implemented */; }

  explicit linked_hash_map(size_t reservation_size,
                           const hasher& hash = hasher(),
                           const key_equal& eq = key_equal(),
                           const allocator_type& alloc = allocator_type())
      : set_(reservation_size, Wrapped<hasher>(hash), Wrapped<key_equal>(eq),
             alloc),
        list_(alloc) { __builtin_trap() /* STUB: not implemented */; }

  linked_hash_map(size_t reservation_size, const hasher& hash,
                  const allocator_type& alloc)
      : linked_hash_map(reservation_size, hash, key_equal(), alloc) { __builtin_trap() /* STUB: not implemented */; }

  linked_hash_map(size_t reservation_size, const allocator_type& alloc)
      : linked_hash_map(reservation_size, hasher(), key_equal(), alloc) { __builtin_trap() /* STUB: not implemented */; }

  explicit linked_hash_map(const allocator_type& alloc)
      : linked_hash_map(0, hasher(), key_equal(), alloc) { __builtin_trap() /* STUB: not implemented */; }

  template <class InputIt>
  linked_hash_map(InputIt first, InputIt last, size_t reservation_size = 0,
                  const hasher& hash = hasher(),
                  const key_equal& eq = key_equal(),
                  const allocator_type& alloc = allocator_type())
      : linked_hash_map(reservation_size, hash, eq, alloc) { __builtin_trap() /* STUB: not implemented */; }

  template <class InputIt>
  linked_hash_map(InputIt first, InputIt last, size_t reservation_size,
                  const hasher& hash, const allocator_type& alloc)
      : linked_hash_map(first, last, reservation_size, hash, key_equal(),
                        alloc) { __builtin_trap() /* STUB: not implemented */; }

  template <class InputIt>
  linked_hash_map(InputIt first, InputIt last, size_t reservation_size,
                  const allocator_type& alloc)
      : linked_hash_map(first, last, reservation_size, hasher(), key_equal(),
                        alloc) { __builtin_trap() /* STUB: not implemented */; }

  template <class InputIt>
  linked_hash_map(InputIt first, InputIt last, const allocator_type& alloc)
      : linked_hash_map(first, last, /*reservation_size=*/0, hasher(),
                        key_equal(), alloc) { __builtin_trap() /* STUB: not implemented */; }

  linked_hash_map(std::initializer_list<value_type> init,
                  size_t reservation_size = 0, const hasher& hash = hasher(),
                  const key_equal& eq = key_equal(),
                  const allocator_type& alloc = allocator_type())
      : linked_hash_map(init.begin(), init.end(), reservation_size, hash, eq,
                        alloc) { __builtin_trap() /* STUB: not implemented */; }

  linked_hash_map(std::initializer_list<value_type> init,
                  size_t reservation_size, const hasher& hash,
                  const allocator_type& alloc)
      : linked_hash_map(init, reservation_size, hash, key_equal(), alloc) { __builtin_trap() /* STUB: not implemented */; }

  linked_hash_map(std::initializer_list<value_type> init,
                  size_t reservation_size, const allocator_type& alloc)
      : linked_hash_map(init, reservation_size, hasher(), key_equal(), alloc) { __builtin_trap() /* STUB: not implemented */; }

  linked_hash_map(std::initializer_list<value_type> init,
                  const allocator_type& alloc)
      : linked_hash_map(init, /*reservation_size=*/0, hasher(), key_equal(),
                        alloc) { __builtin_trap() /* STUB: not implemented */; }

  linked_hash_map(const linked_hash_map& other)
      : linked_hash_map(0, other.hash_function(), other.key_eq(),
                        other.get_allocator()) { __builtin_trap() /* STUB: not implemented */; }

  linked_hash_map(const linked_hash_map& other, const allocator_type& alloc)
      : linked_hash_map(0, other.hash_function(), other.key_eq(), alloc) { __builtin_trap() /* STUB: not implemented */; }

  linked_hash_map(linked_hash_map&& other) noexcept
      : set_(std::move(other.set_)), list_(std::move(other.list_)) { __builtin_trap() /* STUB: not implemented */; }

  linked_hash_map(linked_hash_map&& other, const allocator_type& alloc)
      : linked_hash_map(0, other.hash_function(), other.key_eq(), alloc) { __builtin_trap() /* STUB: not implemented */; }

  linked_hash_map& operator=(const linked_hash_map& other) { __builtin_trap() /* STUB: not implemented */; }

  linked_hash_map& operator=(linked_hash_map&& other) noexcept { __builtin_trap() /* STUB: not implemented */; }

  linked_hash_map& operator=(std::initializer_list<value_type> values) { __builtin_trap() /* STUB: not implemented */; }

  // Derive size_ from set_, as list::size might be O(N).
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
  size_t capacity() const { __builtin_trap() /* STUB: not implemented */; }
  size_t bucket_count() const { __builtin_trap() /* STUB: not implemented */; }
  float load_factor() const { __builtin_trap() /* STUB: not implemented */; }

  hasher hash_function() const { __builtin_trap() /* STUB: not implemented */; }
  key_equal key_eq() const { __builtin_trap() /* STUB: not implemented */; }
  allocator_type get_allocator() const { __builtin_trap() /* STUB: not implemented */; }

  template <class K = key_type>
  size_type erase(const key_arg<K>& key) { __builtin_trap() /* STUB: not implemented */; }

  iterator erase(const_iterator position) { __builtin_trap() /* STUB: not implemented */; }

  iterator erase(iterator position) { __builtin_trap() /* STUB: not implemented */; }

  iterator erase(iterator first, iterator last) { __builtin_trap() /* STUB: not implemented */; }

  iterator erase(const_iterator first, const_iterator last) { __builtin_trap() /* STUB: not implemented */; }

  template <class K = key_type>
  iterator find(const key_arg<K>& key) { __builtin_trap() /* STUB: not implemented */; }

  template <class K = key_type>
  const_iterator find(const key_arg<K>& key) const { __builtin_trap() /* STUB: not implemented */; }

  template <class K = key_type>
  size_type count(const key_arg<K>& key) const { __builtin_trap() /* STUB: not implemented */; }
  template <class K = key_type>
  bool contains(const key_arg<K>& key) const { __builtin_trap() /* STUB: not implemented */; }

  template <class K = key_type>
  mapped_type& at(const key_arg<K>& key) { __builtin_trap() /* STUB: not implemented */; }

  template <class K = key_type>
  const mapped_type& at(const key_arg<K>& key) const { __builtin_trap() /* STUB: not implemented */; }

  template <class K = key_type>
  std::pair<iterator, iterator> equal_range(const key_arg<K>& key) { __builtin_trap() /* STUB: not implemented */; }

  template <class K = key_type>
  std::pair<const_iterator, const_iterator> equal_range(
      const key_arg<K>& key) const { __builtin_trap() /* STUB: not implemented */; }

  template <class K = key_type>
  mapped_type& operator[](const key_arg<K>& key) { __builtin_trap() /* STUB: not implemented */; }

  template <class K = key_type, K* = nullptr>
  mapped_type& operator[](key_arg<K>&& key) { __builtin_trap() /* STUB: not implemented */; }

  std::pair<iterator, bool> insert(const value_type& v) { __builtin_trap() /* STUB: not implemented */; }
  std::pair<iterator, bool> insert(value_type&& v) { __builtin_trap() /* STUB: not implemented */; }

  iterator insert(const_iterator, const value_type& v) { __builtin_trap() /* STUB: not implemented */; }
  iterator insert(const_iterator, value_type&& v) { __builtin_trap() /* STUB: not implemented */; }

  void insert(std::initializer_list<value_type> ilist) { __builtin_trap() /* STUB: not implemented */; }

  template <class InputIt>
  void insert(InputIt first, InputIt last) { __builtin_trap() /* STUB: not implemented */; }

  insert_return_type insert(node_type&& node) { __builtin_trap() /* STUB: not implemented */; }

  iterator insert(const_iterator, node_type&& node) { __builtin_trap() /* STUB: not implemented */; }

  // The last two template parameters ensure that both arguments are rvalues
  // (lvalue arguments are handled by the overloads below). This is necessary
  // for supporting bitfield arguments.
  //
  //   union { int n : 1; };
  //   linked_hash_map<int, int> m;
  //   m.insert_or_assign(n, n);
  template <class K = key_type, class V = mapped_type, K* = nullptr,
            V* = nullptr>
  std::pair<iterator, bool> insert_or_assign(key_arg<K>&& k, V&& v) { __builtin_trap() /* STUB: not implemented */; }

  template <class K = key_type, class V = mapped_type, K* = nullptr>
  std::pair<iterator, bool> insert_or_assign(key_arg<K>&& k, const V& v) { __builtin_trap() /* STUB: not implemented */; }

  template <class K = key_type, class V = mapped_type, V* = nullptr>
  std::pair<iterator, bool> insert_or_assign(const key_arg<K>& k, V&& v) { __builtin_trap() /* STUB: not implemented */; }

  template <class K = key_type, class V = mapped_type>
  std::pair<iterator, bool> insert_or_assign(const key_arg<K>& k, const V& v) { __builtin_trap() /* STUB: not implemented */; }

  template <class K = key_type, class V = mapped_type, K* = nullptr,
            V* = nullptr>
  iterator insert_or_assign(const_iterator, key_arg<K>&& k, V&& v) { __builtin_trap() /* STUB: not implemented */; }

  template <class K = key_type, class V = mapped_type, K* = nullptr>
  iterator insert_or_assign(const_iterator, key_arg<K>&& k, const V& v) { __builtin_trap() /* STUB: not implemented */; }

  template <class K = key_type, class V = mapped_type, V* = nullptr>
  iterator insert_or_assign(const_iterator, const key_arg<K>& k, V&& v) { __builtin_trap() /* STUB: not implemented */; }

  template <class K = key_type, class V = mapped_type>
  iterator insert_or_assign(const_iterator, const key_arg<K>& k, const V& v) { __builtin_trap() /* STUB: not implemented */; }

  template <typename... Args>
  std::pair<iterator, bool> emplace(Args&&... args) { __builtin_trap() /* STUB: not implemented */; }

  template <class K = key_type, class... Args, K* = nullptr>
  iterator try_emplace(const_iterator, key_arg<K>&& k, Args&&... args) { __builtin_trap() /* STUB: not implemented */; }

  template <typename... Args>
  iterator emplace_hint(const_iterator, Args&&... args) { __builtin_trap() /* STUB: not implemented */; }

  template <class K = key_type, typename... Args, K* = nullptr>
  std::pair<iterator, bool> try_emplace(key_arg<K>&& key, Args&&... args) { __builtin_trap() /* STUB: not implemented */; }

  template <typename H, typename E>
  void merge(linked_hash_map<Key, Value, H, E, Alloc>& src) { __builtin_trap() /* STUB: not implemented */; }

  template <typename H, typename E>
  void merge(linked_hash_map<Key, Value, H, E, Alloc>&& src) { __builtin_trap() /* STUB: not implemented */; }

  node_type extract(const_iterator position) { __builtin_trap() /* STUB: not implemented */; }

  template <class K = key_type,
            std::enable_if_t<!std::is_same_v<K, iterator>, int> = 0>
  node_type extract(const key_arg<K>& key) { __builtin_trap() /* STUB: not implemented */; }

  template <typename H, typename E>
  void splice(const_iterator, linked_hash_map<Key, Value, H, E, Alloc>& list,
              const_iterator it) { __builtin_trap() /* STUB: not implemented */; }

  template <class K = key_type, typename... Args>
  std::pair<iterator, bool> try_emplace(const key_arg<K>& key, Args&&... args) { __builtin_trap() /* STUB: not implemented */; }

  template <class K = key_type, typename... Args>
  iterator try_emplace(const_iterator, const key_arg<K>& key, Args&&... args) { __builtin_trap() /* STUB: not implemented */; }

  void swap(linked_hash_map& other) noexcept { __builtin_trap() /* STUB: not implemented */; }

  friend bool operator==(const linked_hash_map& a, const linked_hash_map& b) { __builtin_trap() /* STUB: not implemented */; }

  friend bool operator!=(const linked_hash_map& a, const linked_hash_map& b) { __builtin_trap() /* STUB: not implemented */; }

  void rehash(size_t n) { __builtin_trap() /* STUB: not implemented */; }

 private:
  template <typename Other>
  void CopyFrom(Other&& other) { __builtin_trap() /* STUB: not implemented */; }

  template <typename U>
  std::pair<iterator, bool> InsertInternal(U&& pair) { __builtin_trap() /* STUB: not implemented */; }

  template <class K, class V>
  std::pair<iterator, bool> InsertOrAssignInternal(K&& k, V&& v) { __builtin_trap() /* STUB: not implemented */; }

  template <typename K, typename... Args>
  std::pair<iterator, bool> LazyEmplaceInternal(K&& key, Args&&... args) { __builtin_trap() /* STUB: not implemented */; }

  // The set component, used for speedy lookups.
  SetType set_;

  // The list component, used for maintaining insertion order.
  ListType list_;
};

ABSL_NAMESPACE_END
}  // namespace absl

#endif  // ABSL_CONTAINER_LINKED_HASH_MAP_H_
