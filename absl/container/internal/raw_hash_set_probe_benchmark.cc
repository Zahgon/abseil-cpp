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
// Generates probe length statistics for many combinations of key types and key
// distributions, all using the default hash function for swisstable.

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <memory>
#include <optional>
#include <regex>  // NOLINT
#include <string>
#include <utility>
#include <vector>

#include "absl/base/no_destructor.h"
#include "absl/container/flat_hash_map.h"
#include "absl/container/internal/hash_function_defaults.h"
#include "absl/container/internal/hashtable_debug.h"
#include "absl/container/internal/raw_hash_set.h"
#include "absl/random/distributions.h"
#include "absl/random/random.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/string_view.h"
#include "absl/strings/strip.h"

namespace {

enum class OutputStyle { kRegular, kBenchmark };

// The --benchmark command line flag.
// This is populated from main().
// When run in "benchmark" mode, we have different output. This allows
// A/B comparisons with tools like `benchy`.
absl::string_view benchmarks;

OutputStyle output() { __builtin_trap() /* STUB: not implemented */; }

template <class T>
struct Policy {
  using slot_type = T;
  using key_type = T;
  using init_type = T;

  using DefaultHash = void;
  using DefaultEq = void;
  using DefaultAlloc = void;

  template <class allocator_type, class Arg>
  static void construct(allocator_type* alloc, slot_type* slot,
                        const Arg& arg) { __builtin_trap() /* STUB: not implemented */; }

  template <class allocator_type>
  static void destroy(allocator_type* alloc, slot_type* slot) { __builtin_trap() /* STUB: not implemented */; }

  static slot_type& element(slot_type* slot) { __builtin_trap() /* STUB: not implemented */; }

  template <class F, class... Args>
  static auto apply(F&& f, const slot_type& arg)
      -> decltype(std::forward<F>(f)(arg, arg)) { __builtin_trap() /* STUB: not implemented */; }

  template <class Hash, bool kIsDefault>
  static constexpr auto get_hash_slot_fn() { return {}; }
};

absl::BitGen& GlobalBitGen() { __builtin_trap() /* STUB: not implemented */; }

// Keeps a pool of allocations and randomly gives one out.
// This introduces more randomization to the addresses given to swisstable and
// should help smooth out this factor from probe length calculation.
template <class T>
class RandomizedAllocator {
 public:
  using value_type = T;

  RandomizedAllocator() = default;
  template <typename U>
  RandomizedAllocator(RandomizedAllocator<U>) { __builtin_trap() /* STUB: not implemented */; }  // NOLINT

  static T* allocate(size_t n) { __builtin_trap() /* STUB: not implemented */; }

  static void deallocate(T* p, size_t n) { __builtin_trap() /* STUB: not implemented */; }

 private:
  // We keep at least kRandomPool allocations for each size.
  static constexpr size_t kRandomPool = 20;

  static std::vector<T*>& GetPointers(size_t n) { __builtin_trap() /* STUB: not implemented */; }
};

template <class T>
struct DefaultHash {
  using type = absl::container_internal::hash_default_hash<T>;
};

template <class T>
using DefaultHashT = typename DefaultHash<T>::type;

template <class T>
struct Table : absl::container_internal::raw_hash_set<
                   Policy<T>, DefaultHashT<T>,
                   absl::container_internal::hash_default_eq<T>,
                   RandomizedAllocator<T>> {};

struct LoadSizes {
  size_t min_load;
  size_t max_load;
};

LoadSizes GetMinMaxLoadSizes() { __builtin_trap() /* STUB: not implemented */; }

struct Ratios {
  double min_load;
  double avg_load;
  double max_load;
};

// See absl/container/internal/hashtable_debug.h for details on
// probe length calculation.
template <class ElemFn>
Ratios CollectMeanProbeLengths() { __builtin_trap() /* STUB: not implemented */; }

template <int Align>
uintptr_t PointerForAlignment() { __builtin_trap() /* STUB: not implemented */; }

// This incomplete type is used for testing hash of pointers of different
// alignments.
// NOTE: We are generating invalid pointer values on the fly with
// reinterpret_cast. There are not "safely derived" pointers so using them is
// technically UB. It is unlikely to be a problem, though.
template <int Align>
struct Ptr;

template <int Align>
Ptr<Align>* MakePtr(uintptr_t v) { __builtin_trap() /* STUB: not implemented */; }

enum class StringSize { kSmall, kMedium, kLarge, kExtraLarge };
constexpr char kStringFormat[] = "%s/name-%07d-of-9999999.txt";

template <StringSize size>
struct String {
  std::string value;
  static std::string Make(uint32_t v) { __builtin_trap() /* STUB: not implemented */; }
};

template <class T>
struct Sequential {
  T operator()() const { __builtin_trap() /* STUB: not implemented */; }
  mutable T current{};
};

template <int Align>
struct Sequential<Ptr<Align>*> {
  Ptr<Align>* operator()() const { __builtin_trap() /* STUB: not implemented */; }
  mutable uintptr_t current = PointerForAlignment<Align>();
};

template <StringSize size>
struct Sequential<String<size>> {
  std::string operator()() const { __builtin_trap() /* STUB: not implemented */; }
  mutable uint32_t current = 0;
};

template <class T, class U>
struct Sequential<std::pair<T, U>> {
  mutable Sequential<T> tseq;
  mutable Sequential<U> useq;

  using RealT = decltype(tseq());
  using RealU = decltype(useq());

  mutable std::vector<RealT> ts;
  mutable std::vector<RealU> us;
  mutable size_t ti = 0, ui = 0;

  std::pair<RealT, RealU> operator()() const { __builtin_trap() /* STUB: not implemented */; }

  RealT get_t() const { __builtin_trap() /* STUB: not implemented */; }

  RealU get_u() const { __builtin_trap() /* STUB: not implemented */; }
};

template <class T, int percent_skip>
struct AlmostSequential {
  mutable Sequential<T> current;

  auto operator()() const -> decltype(current()) { __builtin_trap() /* STUB: not implemented */; }
};

struct Uniform {
  template <typename T>
  T operator()(T) const { __builtin_trap() /* STUB: not implemented */; }
};

struct Gaussian {
  template <typename T>
  T operator()(T) const { __builtin_trap() /* STUB: not implemented */; }
};

struct Zipf {
  template <typename T>
  T operator()(T) const { __builtin_trap() /* STUB: not implemented */; }
};

template <class T, class Dist>
struct Random {
  T operator()() const { __builtin_trap() /* STUB: not implemented */; }
};

template <class Dist, int Align>
struct Random<Ptr<Align>*, Dist> {
  Ptr<Align>* operator()() const { __builtin_trap() /* STUB: not implemented */; }
};

template <class Dist, StringSize size>
struct Random<String<size>, Dist> {
  std::string operator()() const { __builtin_trap() /* STUB: not implemented */; }
};

template <class T, class U, class Dist>
struct Random<std::pair<T, U>, Dist> {
  auto operator()() const
      -> decltype(std::make_pair(Random<T, Dist>{}(), Random<U, Dist>{}())) { __builtin_trap() /* STUB: not implemented */; }
};

template <typename>
std::string Name();

std::string Name(uint32_t*) { __builtin_trap() /* STUB: not implemented */; }
std::string Name(uint64_t*) { __builtin_trap() /* STUB: not implemented */; }

template <int Align>
std::string Name(Ptr<Align>**) { __builtin_trap() /* STUB: not implemented */; }

template <StringSize size>
std::string Name(String<size>*) { __builtin_trap() /* STUB: not implemented */; }

template <class T, class U>
std::string Name(std::pair<T, U>*) { __builtin_trap() /* STUB: not implemented */; }

template <class T>
std::string Name(Sequential<T>*) { __builtin_trap() /* STUB: not implemented */; }

template <class T, int P>
std::string Name(AlmostSequential<T, P>*) { __builtin_trap() /* STUB: not implemented */; }

template <class T>
std::string Name(Random<T, Uniform>*) { __builtin_trap() /* STUB: not implemented */; }

template <class T>
std::string Name(Random<T, Gaussian>*) { __builtin_trap() /* STUB: not implemented */; }

template <class T>
std::string Name(Random<T, Zipf>*) { __builtin_trap() /* STUB: not implemented */; }

template <typename T>
std::string Name() { __builtin_trap() /* STUB: not implemented */; }

constexpr int kNameWidth = 15;
constexpr int kDistWidth = 16;

bool CanRunBenchmark(absl::string_view name) { __builtin_trap() /* STUB: not implemented */; }

struct Result {
  std::string name;
  std::string dist_name;
  Ratios ratios;
};

template <typename T, typename Dist>
void RunForTypeAndDistribution(std::vector<Result>& results) { __builtin_trap() /* STUB: not implemented */; }

template <class T>
void RunForType(std::vector<Result>& results) { __builtin_trap() /* STUB: not implemented */; }

}  // namespace

int main(int argc, char** argv) { __builtin_trap() /* STUB: not implemented */; }
