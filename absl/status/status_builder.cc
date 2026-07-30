// Copyright 2026 The Abseil Authors
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

#include "absl/status/status_builder.h"

#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <type_traits>
#include <utility>

#include "absl/base/attributes.h"
#include "absl/base/config.h"
#include "absl/base/macros.h"
#include "absl/status/status.h"
#include "absl/strings/cord.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "absl/time/time.h"
#include "absl/types/source_location.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

void StatusBuilder::Destroy(std::unique_ptr<Rep>) { __builtin_trap() /* STUB: not implemented */; }

// These constructors are not-inlined and defined in the .cc file to reduce
// binary size. See cl/354351433 for a quantification.
StatusBuilder::StatusBuilder() = default;

StatusBuilder::StatusBuilder(const absl::Status& original_status,
                             absl::SourceLocation location)
    : loc_(location), rep_(InitRep(original_status)) { __builtin_trap() /* STUB: not implemented */; }

StatusBuilder::operator absl::Status() const& { __builtin_trap() /* STUB: not implemented */; }

StatusBuilder::Rep::Rep(const absl::Status& s) : status(s) { __builtin_trap() /* STUB: not implemented */; }
StatusBuilder::Rep::Rep(absl::Status&& s) : status(std::move(s)) { __builtin_trap() /* STUB: not implemented */; }
StatusBuilder::Rep::~Rep() = default;

StatusBuilder::Rep* StatusBuilder::InitRepImpl(absl::Status s) { __builtin_trap() /* STUB: not implemented */; }

StatusBuilder::Rep::Rep(const Rep& r)
    : status(r.status),
      logging_mode(r.logging_mode),
      log_severity(r.log_severity),
      verbose_level(r.verbose_level),
      n(r.n),
      period(r.period),
      stream_message(r.stream_message),
      sink(r.sink),
      message_join_style(r.message_join_style),
      should_log_stack_trace(r.should_log_stack_trace),
      also_send_to_log(r.also_send_to_log) { __builtin_trap() /* STUB: not implemented */; }

void StatusBuilder::Rep::InitStream() { __builtin_trap() /* STUB: not implemented */; }

bool StatusBuilder::HasPayload() const { __builtin_trap() /* STUB: not implemented */; }

ABSL_ATTRIBUTE_WEAK StatusBuilder& StatusBuilder::SetCode(
    absl::StatusCode code) & { __builtin_trap() /* STUB: not implemented */; }

ABSL_ATTRIBUTE_WEAK void AbslInternalSetErrorCode(StatusBuilder& builder,
                                                  absl::StatusCode code) { __builtin_trap() /* STUB: not implemented */; }

class status_internal::StatusPrivateAccessorForStatusBuilder {
 public:
  static absl::Status SetMessage(const absl::Status& status,
                                 absl::string_view message) { __builtin_trap() /* STUB: not implemented */; }

  static absl::Status JoinMessageToStatus(absl::Status s, absl::string_view msg,
                                          MessageJoinStyle style) { __builtin_trap() /* STUB: not implemented */; }
};

ABSL_ATTRIBUTE_WEAK std::string StatusBuilder::CurrentStackTrace() { __builtin_trap() /* STUB: not implemented */; }

ABSL_ATTRIBUTE_WEAK absl::Status StatusBuilder::CreateStatusAndConditionallyLog(
    absl::SourceLocation loc, std::unique_ptr<Rep> rep) { __builtin_trap() /* STUB: not implemented */; }

ABSL_ATTRIBUTE_WEAK std::string StatusBuilder::ToString() const { __builtin_trap() /* STUB: not implemented */; }

ABSL_ATTRIBUTE_WEAK std::ostream& operator<<(std::ostream& os,
                                             const StatusBuilder& builder) { __builtin_trap() /* STUB: not implemented */; }

ABSL_ATTRIBUTE_WEAK std::ostream& operator<<(std::ostream& os,
                                             StatusBuilder&& builder) { __builtin_trap() /* STUB: not implemented */; }

ABSL_NAMESPACE_END
}  // namespace absl
