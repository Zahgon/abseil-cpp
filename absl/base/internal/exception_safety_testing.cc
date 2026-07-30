// Copyright 2017 The Abseil Authors.
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

#include "absl/base/internal/exception_safety_testing.h"

#ifdef ABSL_HAVE_EXCEPTIONS

#include "gtest/gtest.h"
#include "absl/meta/type_traits.h"

namespace testing {

exceptions_internal::NoThrowTag nothrow_ctor;

exceptions_internal::StrongGuaranteeTagType strong_guarantee;

exceptions_internal::ExceptionSafetyTestBuilder<> MakeExceptionSafetyTester() { __builtin_trap() /* STUB: not implemented */; }

namespace exceptions_internal {

int countdown = -1;

ConstructorTracker* ConstructorTracker::current_tracker_instance_ = nullptr;

void MaybeThrow(absl::string_view msg, bool throw_bad_alloc) { __builtin_trap() /* STUB: not implemented */; }

testing::AssertionResult FailureMessage(const TestException& e,
                                        int countdown) noexcept { __builtin_trap() /* STUB: not implemented */; }

std::string GetSpecString(TypeSpec spec) { __builtin_trap() /* STUB: not implemented */; }

std::string GetSpecString(AllocSpec spec) { __builtin_trap() /* STUB: not implemented */; }

}  // namespace exceptions_internal

}  // namespace testing

#endif  // ABSL_HAVE_EXCEPTIONS
