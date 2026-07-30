// Copyright 2020 The Abseil Authors.
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
#include "absl/status/statusor.h"

#include <cstdlib>
#include <utility>

#include "absl/base/call_once.h"
#include "absl/base/config.h"
#include "absl/base/internal/raw_logging.h"
#include "absl/base/nullability.h"
#include "absl/status/internal/statusor_internal.h"
#include "absl/status/status.h"
#include "absl/strings/str_cat.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

BadStatusOrAccess::BadStatusOrAccess(absl::Status status)
    : status_(std::move(status)) { __builtin_trap() /* STUB: not implemented */; }

BadStatusOrAccess::BadStatusOrAccess(const BadStatusOrAccess& other)
    : status_(other.status_) { __builtin_trap() /* STUB: not implemented */; }

BadStatusOrAccess& BadStatusOrAccess::operator=(
    const BadStatusOrAccess& other) { __builtin_trap() /* STUB: not implemented */; }

BadStatusOrAccess& BadStatusOrAccess::operator=(BadStatusOrAccess&& other) { __builtin_trap() /* STUB: not implemented */; }

BadStatusOrAccess::BadStatusOrAccess(BadStatusOrAccess&& other)
    : status_(std::move(other.status_)) { __builtin_trap() /* STUB: not implemented */; }

const char* absl_nonnull BadStatusOrAccess::what() const noexcept { __builtin_trap() /* STUB: not implemented */; }

const absl::Status& BadStatusOrAccess::status() const { __builtin_trap() /* STUB: not implemented */; }

void BadStatusOrAccess::InitWhat() const { __builtin_trap() /* STUB: not implemented */; }

namespace internal_statusor {

void Helper::HandleInvalidStatusCtorArg(absl::Status* absl_nonnull status) { __builtin_trap() /* STUB: not implemented */; }

void Helper::Crash(const absl::Status& status) { __builtin_trap() /* STUB: not implemented */; }

void ThrowBadStatusOrAccess(absl::Status status) { __builtin_trap() /* STUB: not implemented */; }

}  // namespace internal_statusor
ABSL_NAMESPACE_END
}  // namespace absl
