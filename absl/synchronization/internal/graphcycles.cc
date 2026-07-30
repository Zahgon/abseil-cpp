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

// GraphCycles provides incremental cycle detection on a dynamic
// graph using the following algorithm:
//
// A dynamic topological sort algorithm for directed acyclic graphs
// David J. Pearce, Paul H. J. Kelly
// Journal of Experimental Algorithmics (JEA) JEA Homepage archive
// Volume 11, 2006, Article No. 1.7
//
// Brief summary of the algorithm:
//
// (1) Maintain a rank for each node that is consistent
//     with the topological sort of the graph. I.e., path from x to y
//     implies rank[x] < rank[y].
// (2) When a new edge (x->y) is inserted, do nothing if rank[x] < rank[y].
// (3) Otherwise: adjust ranks in the neighborhood of x and y.

#include "absl/base/attributes.h"
// This file is a no-op if the required LowLevelAlloc support is missing.
#include "absl/base/internal/low_level_alloc.h"
#ifndef ABSL_LOW_LEVEL_ALLOC_MISSING

#include <algorithm>
#include <array>
#include <cinttypes>
#include <limits>

#include "absl/base/internal/hide_ptr.h"
#include "absl/base/internal/raw_logging.h"
#include "absl/base/internal/spinlock.h"
#include "absl/synchronization/internal/graphcycles.h"

// Do not use STL.   This module does not use standard memory allocation.

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace synchronization_internal { __builtin_trap() /* STUB: not implemented */; }  // namespace synchronization_internal
ABSL_NAMESPACE_END
}  // namespace absl

#endif  // ABSL_LOW_LEVEL_ALLOC_MISSING
