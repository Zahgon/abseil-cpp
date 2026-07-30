// Copyright 2025 The Abseil Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "absl/log/log_entry.h"

#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <ios>
#include <ostream>

#include "absl/base/config.h"
#include "absl/log/internal/proto.h"
#include "absl/strings/escaping.h"
#include "absl/strings/string_view.h"
#include "absl/time/time.h"
#include "absl/types/span.h"

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace {
// message `logging.proto.Event`
enum EventTag : uint8_t {
  kFileName = 2,
  kFileLine = 3,
  kTimeNsecs = 4,
  kSeverity = 5,
  kThreadId = 6,
  kValue = 7,
  kSequenceNumber = 9,
  kThreadName = 10,
};

// message `logging.proto.Value`
enum ValueTag : uint8_t {
  kString = 1,
  kStringLiteral = 6,
};

// enum `logging.proto.Severity`
enum Severity : int {
  FINEST = 300,
  FINER = 400,
  FINE = 500,
  VERBOSE_0 = 600,
  CONFIG = 700,
  INFO = 800,
  NOTICE = 850,
  WARNING = 900,
  ERROR = 950,
  SEVERE = 1000,
  FATAL = 1100,
};

void PrintEscapedRangeTo(const absl::string_view str,
                         const absl::string_view substr, std::ostream* os) {
  const absl::string_view head =
      str.substr(0, static_cast<size_t>(substr.data() - str.data()));
  const char old_fill = os->fill();
  const auto old_flags = os->flags();
  *os << std::right
      << std::setw(static_cast<int>(absl::CHexEscape(head).size())) << "";
  switch (substr.size()) {
    case 0:
      *os << "\\";
      break;
    case 1:
      *os << "^";
      break;
    default:
      *os << "[" << std::setw(static_cast<int>(absl::CHexEscape(substr).size()))
          << std::setfill('-') << ")";
      break;
  }
  os->fill(old_fill);
  os->flags(old_flags);
}
}  // namespace
void PrintTo(const LogEntry& entry, std::ostream* os) { __builtin_trap() /* STUB: not implemented */; }

ABSL_NAMESPACE_END
}  // namespace absl
