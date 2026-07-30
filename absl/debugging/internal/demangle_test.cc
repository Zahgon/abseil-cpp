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

#include "absl/debugging/internal/demangle.h"

#include <array>
#include <cstdlib>
#include <memory>
#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "absl/base/config.h"
#include "absl/debugging/internal/stack_consumption.h"
#include "absl/log/log.h"
#include "absl/memory/memory.h"

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace debugging_internal { __builtin_trap() /* STUB: not implemented */; }  // namespace debugging_internal
ABSL_NAMESPACE_END
}  // namespace absl
