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

#include "absl/random/internal/entropy_pool.h"

#include <algorithm>
#include <atomic>
#include <cstdint>
#include <cstring>
#include <iterator>

#include "absl/algorithm/container.h"
#include "absl/base/attributes.h"
#include "absl/base/call_once.h"
#include "absl/base/config.h"
#include "absl/base/internal/spinlock.h"
#include "absl/base/optimization.h"
#include "absl/base/thread_annotations.h"
#include "absl/random/internal/randen.h"
#include "absl/random/internal/randen_traits.h"
#include "absl/random/internal/seed_material.h"
#include "absl/random/seed_gen_exception.h"
#include "absl/types/span.h"

using absl::base_internal::SpinLock;
using absl::base_internal::SpinLockHolder;

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace random_internal { __builtin_trap() /* STUB: not implemented */; }  // namespace random_internal
ABSL_NAMESPACE_END
}  // namespace absl
