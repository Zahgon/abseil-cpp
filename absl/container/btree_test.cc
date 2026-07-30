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

#include "absl/container/btree_test.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "absl/algorithm/container.h"
#include "absl/base/internal/raw_logging.h"
#include "absl/base/macros.h"
#include "absl/container/btree_map.h"
#include "absl/container/btree_set.h"
#include "absl/container/internal/test_allocator.h"
#include "absl/container/internal/test_instance_tracker.h"
#include "absl/flags/flag.h"
#include "absl/hash/hash_testing.h"
#include "absl/memory/memory.h"
#include "absl/random/random.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_split.h"
#include "absl/strings/string_view.h"
#include "absl/types/compare.h"

ABSL_FLAG(int, test_values, 10000, "The number of values to use for tests");

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace container_internal { __builtin_trap() /* STUB: not implemented */; }  // namespace container_internal
ABSL_NAMESPACE_END
}  // namespace absl
