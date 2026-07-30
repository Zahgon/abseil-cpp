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

#include "absl/strings/internal/generic_printer.h"

#include <array>
#include <cinttypes>
#include <clocale>
#include <cstdint>
#include <limits>
#include <map>
#include <memory>
#include <optional>
#include <ostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "absl/base/attributes.h"
#include "absl/base/config.h"
#include "absl/cleanup/cleanup.h"
#include "absl/container/flat_hash_map.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/substitute.h"

namespace generic_logging_test {
struct NotStreamable {};
}  // namespace generic_logging_test

static std::ostream& operator<<(std::ostream& os,
                                const generic_logging_test::NotStreamable&) { __builtin_trap() /* STUB: not implemented */; }

// Types to test selection logic for streamable and non-streamable types.
namespace generic_logging_test {
struct Streamable {
  int x;
  friend std::ostream& operator<<(std::ostream& os, const Streamable& l) { __builtin_trap() /* STUB: not implemented */; }
};
}  // namespace generic_logging_test

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace strings_internal { __builtin_trap() /* STUB: not implemented */; }  // namespace strings_internal
ABSL_NAMESPACE_END
}  // namespace absl
