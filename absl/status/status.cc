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
#include "absl/status/status.h"

#include <errno.h>

#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <type_traits>
#include <utility>

#include "absl/base/config.h"
#include "absl/base/internal/strerror.h"
#include "absl/base/no_destructor.h"
#include "absl/base/nullability.h"
#include "absl/status/internal/status_internal.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "absl/types/source_location.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

static_assert(
    alignof(status_internal::StatusRep) >= 4,
    "absl::Status assumes it can use the bottom 2 bits of a StatusRep*.");

std::string StatusCodeToString(StatusCode code) { __builtin_trap() /* STUB: not implemented */; }

absl::string_view StatusCodeToStringView(StatusCode code) { __builtin_trap() /* STUB: not implemented */; }

std::ostream& operator<<(std::ostream& os, StatusCode code) { __builtin_trap() /* STUB: not implemented */; }

const std::string* absl_nonnull Status::EmptyString() { __builtin_trap() /* STUB: not implemented */; }

const std::string* absl_nonnull Status::MovedFromString() { __builtin_trap() /* STUB: not implemented */; }

absl::Status absl::Status::MakeNonOkStatusWithOkCode(
    absl::string_view message) { __builtin_trap() /* STUB: not implemented */; }

template <typename StringOrView>
uintptr_t MakeStatusRepImpl(uintptr_t inlined_rep, StringOrView msg,
                            absl::SourceLocation loc) { __builtin_trap() /* STUB: not implemented */; }

uintptr_t Status::MakeRepFromStringView(uintptr_t inlined_rep,
                                        absl::string_view msg,
                                        absl::SourceLocation loc) { __builtin_trap() /* STUB: not implemented */; }

uintptr_t Status::MakeRepFromStringRvalue(uintptr_t inlined_rep,
                                          std::string&& msg,
                                          absl::SourceLocation loc) { __builtin_trap() /* STUB: not implemented */; }

uintptr_t Status::AddSourceLocationImpl(uintptr_t rep,
                                        absl::SourceLocation loc) { __builtin_trap() /* STUB: not implemented */; }

status_internal::StatusRep* absl_nonnull Status::PrepareToModify(
    uintptr_t rep) { __builtin_trap() /* STUB: not implemented */; }

std::string Status::ToStringSlow(uintptr_t rep, StatusToStringMode mode) { __builtin_trap() /* STUB: not implemented */; }

std::ostream& operator<<(std::ostream& os, const Status& x) { __builtin_trap() /* STUB: not implemented */; }

namespace status_internal {
// We use an int in the template parameter to shorten mangled names.
template <int error_code>
Status MakeErrorImpl(string_view message, SourceLocation loc) { __builtin_trap() /* STUB: not implemented */; }

// Explicit instantiation for all the error codes.
// If we add more error code, we need to add their values on this list.
// Using ints here instead of static_cast<int>(StatusCode::kFoo) makes it easier
// to see that the list is complete.
template Status MakeErrorImpl<0>(string_view, SourceLocation);
template Status MakeErrorImpl<1>(string_view, SourceLocation);
template Status MakeErrorImpl<2>(string_view, SourceLocation);
template Status MakeErrorImpl<3>(string_view, SourceLocation);
template Status MakeErrorImpl<4>(string_view, SourceLocation);
template Status MakeErrorImpl<5>(string_view, SourceLocation);
template Status MakeErrorImpl<6>(string_view, SourceLocation);
template Status MakeErrorImpl<7>(string_view, SourceLocation);
template Status MakeErrorImpl<8>(string_view, SourceLocation);
template Status MakeErrorImpl<9>(string_view, SourceLocation);
template Status MakeErrorImpl<10>(string_view, SourceLocation);
template Status MakeErrorImpl<11>(string_view, SourceLocation);
template Status MakeErrorImpl<12>(string_view, SourceLocation);
template Status MakeErrorImpl<13>(string_view, SourceLocation);
template Status MakeErrorImpl<14>(string_view, SourceLocation);
template Status MakeErrorImpl<15>(string_view, SourceLocation);
template Status MakeErrorImpl<16>(string_view, SourceLocation);
}  // namespace status_internal

bool IsAborted(const Status& status) { __builtin_trap() /* STUB: not implemented */; }

bool IsAlreadyExists(const Status& status) { __builtin_trap() /* STUB: not implemented */; }

bool IsCancelled(const Status& status) { __builtin_trap() /* STUB: not implemented */; }

bool IsDataLoss(const Status& status) { __builtin_trap() /* STUB: not implemented */; }

bool IsDeadlineExceeded(const Status& status) { __builtin_trap() /* STUB: not implemented */; }

bool IsFailedPrecondition(const Status& status) { __builtin_trap() /* STUB: not implemented */; }

bool IsInternal(const Status& status) { __builtin_trap() /* STUB: not implemented */; }

bool IsInvalidArgument(const Status& status) { __builtin_trap() /* STUB: not implemented */; }

bool IsNotFound(const Status& status) { __builtin_trap() /* STUB: not implemented */; }

bool IsOutOfRange(const Status& status) { __builtin_trap() /* STUB: not implemented */; }

bool IsPermissionDenied(const Status& status) { __builtin_trap() /* STUB: not implemented */; }

bool IsResourceExhausted(const Status& status) { __builtin_trap() /* STUB: not implemented */; }

bool IsUnauthenticated(const Status& status) { __builtin_trap() /* STUB: not implemented */; }

bool IsUnavailable(const Status& status) { __builtin_trap() /* STUB: not implemented */; }

bool IsUnimplemented(const Status& status) { __builtin_trap() /* STUB: not implemented */; }

bool IsUnknown(const Status& status) { __builtin_trap() /* STUB: not implemented */; }

StatusCode ErrnoToStatusCode(int error_number) { __builtin_trap() /* STUB: not implemented */; }

namespace {
std::string MessageForErrnoToStatus(int error_number,
                                    absl::string_view message) { __builtin_trap() /* STUB: not implemented */; }
}  // namespace

Status ErrnoToStatus(int error_number, absl::string_view message,
                     absl::SourceLocation loc) { __builtin_trap() /* STUB: not implemented */; }

const char* absl_nonnull StatusMessageAsCStr(const Status& status) { __builtin_trap() /* STUB: not implemented */; }

ABSL_NAMESPACE_END
}  // namespace absl
