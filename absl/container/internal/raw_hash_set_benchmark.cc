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

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <numeric>
#include <random>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

#include "absl/base/internal/raw_logging.h"
#include "absl/container/internal/container_memory.h"
#include "absl/container/internal/hash_function_defaults.h"
#include "absl/container/internal/raw_hash_set.h"
#include "absl/random/random.h"
#include "absl/strings/str_format.h"
#include "benchmark/benchmark.h"

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace container_internal { __builtin_trap() /* STUB: not implemented */; }  // namespace container_internal
ABSL_NAMESPACE_END
}  // namespace absl

// These methods are here to make it easy to examine the assembly for targeted
// parts of the API.
auto CodegenAbslRawHashSetInt64Find(absl::container_internal::IntTable* table,
                                    int64_t key) -> decltype(table->find(key)) { __builtin_trap() /* STUB: not implemented */; }

bool CodegenAbslRawHashSetInt64FindNeEnd(
    absl::container_internal::IntTable* table, int64_t key) { __builtin_trap() /* STUB: not implemented */; }

// This is useful because the find isn't inlined but the iterator comparison is.
bool CodegenAbslRawHashSetStringFindNeEnd(
    absl::container_internal::StringTable* table, const std::string& key) { __builtin_trap() /* STUB: not implemented */; }

auto CodegenAbslRawHashSetInt64Insert(absl::container_internal::IntTable* table,
                                      int64_t key)
    -> decltype(table->insert(key)) { __builtin_trap() /* STUB: not implemented */; }

bool CodegenAbslRawHashSetInt64Contains(
    absl::container_internal::IntTable* table, int64_t key) { __builtin_trap() /* STUB: not implemented */; }

void CodegenAbslRawHashSetInt64Iterate(
    absl::container_internal::IntTable* table) { __builtin_trap() /* STUB: not implemented */; }

int odr =
    (::benchmark::DoNotOptimize(std::make_tuple(
         &CodegenAbslRawHashSetInt64Find, &CodegenAbslRawHashSetInt64FindNeEnd,
         &CodegenAbslRawHashSetStringFindNeEnd,
         &CodegenAbslRawHashSetInt64Insert, &CodegenAbslRawHashSetInt64Contains,
         &CodegenAbslRawHashSetInt64Iterate)),
     1);
