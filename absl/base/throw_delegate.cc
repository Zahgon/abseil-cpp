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

#include "absl/base/throw_delegate.h"

#include <cstdlib>
#include <functional>
#include <new>
#include <stdexcept>

#include "absl/base/config.h"
#include "absl/base/internal/raw_logging.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

void ThrowStdLogicError(const std::string& what_arg) { __builtin_trap() /* STUB: not implemented */; }
void ThrowStdLogicError(const char* what_arg) { __builtin_trap() /* STUB: not implemented */; }
void ThrowStdInvalidArgument(const std::string& what_arg) { __builtin_trap() /* STUB: not implemented */; }
void ThrowStdInvalidArgument(const char* what_arg) { __builtin_trap() /* STUB: not implemented */; }

void ThrowStdDomainError(const std::string& what_arg) { __builtin_trap() /* STUB: not implemented */; }
void ThrowStdDomainError(const char* what_arg) { __builtin_trap() /* STUB: not implemented */; }

void ThrowStdLengthError(const std::string& what_arg) { __builtin_trap() /* STUB: not implemented */; }
void ThrowStdLengthError(const char* what_arg) { __builtin_trap() /* STUB: not implemented */; }

void ThrowStdOutOfRange(const std::string& what_arg) { __builtin_trap() /* STUB: not implemented */; }
void ThrowStdOutOfRange(const char* what_arg) { __builtin_trap() /* STUB: not implemented */; }

void ThrowStdRuntimeError(const std::string& what_arg) { __builtin_trap() /* STUB: not implemented */; }
void ThrowStdRuntimeError(const char* what_arg) { __builtin_trap() /* STUB: not implemented */; }

void ThrowStdRangeError(const std::string& what_arg) { __builtin_trap() /* STUB: not implemented */; }
void ThrowStdRangeError(const char* what_arg) { __builtin_trap() /* STUB: not implemented */; }

void ThrowStdOverflowError(const std::string& what_arg) { __builtin_trap() /* STUB: not implemented */; }
void ThrowStdOverflowError(const char* what_arg) { __builtin_trap() /* STUB: not implemented */; }

void ThrowStdUnderflowError(const std::string& what_arg) { __builtin_trap() /* STUB: not implemented */; }
void ThrowStdUnderflowError(const char* what_arg) { __builtin_trap() /* STUB: not implemented */; }

void ThrowStdBadFunctionCall() { __builtin_trap() /* STUB: not implemented */; }

void ThrowStdBadAlloc() { __builtin_trap() /* STUB: not implemented */; }

void ThrowStdBadArrayNewLength() { __builtin_trap() /* STUB: not implemented */; }

ABSL_NAMESPACE_END
}  // namespace absl
