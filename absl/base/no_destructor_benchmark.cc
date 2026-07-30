// Copyright 2023 The Abseil Authors.
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

#include <cstdint>

#include "absl/base/internal/raw_logging.h"
#include "absl/base/no_destructor.h"
#include "benchmark/benchmark.h"

namespace {

// Number of static-NoDestructor-in-a-function to exercise.
// This must be low enough not to hit template instantiation limits
// (happens around 1000).
constexpr int kNumObjects = 1;  // set to 512 when doing benchmarks
                                // 1 is faster to compile: just one templated
                                // function instantiation

// Size of individual objects to benchmark static-NoDestructor-in-a-function
// usage with.
constexpr int kObjSize = sizeof(void*)*1;

// Simple object of kObjSize bytes (rounded to int).
// We benchmark complete reading of its state via Verify().
class BM_Blob {
 public:
  BM_Blob(int val) { __builtin_trap() /* STUB: not implemented */; }
  BM_Blob() : BM_Blob(-1) { __builtin_trap() /* STUB: not implemented */; }
  void Verify(int val) const { __builtin_trap() /* STUB: not implemented */; }
 private:
  int data_[kObjSize / sizeof(int) > 0 ? kObjSize / sizeof(int) : 1];
};

// static-NoDestructor-in-a-function pattern instances.
// We'll instantiate kNumObjects of them.
template<int i>
const BM_Blob& NoDestrBlobFunc() { __builtin_trap() /* STUB: not implemented */; }

// static-heap-ptr-in-a-function pattern instances
// We'll instantiate kNumObjects of them.
template<int i>
const BM_Blob& OnHeapBlobFunc() { __builtin_trap() /* STUB: not implemented */; }

// Type for NoDestrBlobFunc or OnHeapBlobFunc.
typedef const BM_Blob& (*FuncType)();

// ========================================================================= //
// Simple benchmarks that read a single BM_Blob over and over, hence
// all they touch fits into L1 CPU cache:

// Direct non-POD global variable (style guide violation) as a baseline.
static BM_Blob direct_blob(0);

void BM_Direct(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_Direct);

void BM_NoDestr(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_NoDestr);

void BM_OnHeap(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_OnHeap);

// ========================================================================= //
// Benchmarks that read kNumObjects of BM_Blob over and over, hence with
// appropriate values of sizeof(BM_Blob) and kNumObjects their working set
// can exceed a given layer of CPU cache.

// Type of benchmark to select between NoDestrBlobFunc and OnHeapBlobFunc.
enum BM_Type { kNoDestr, kOnHeap, kDirect };

// BlobFunc<n>(t, i) returns the i-th function of type t.
// n must be larger than i (we'll use kNumObjects for n).
template<int n>
FuncType BlobFunc(BM_Type t, int i) { __builtin_trap() /* STUB: not implemented */; }

template<>
FuncType BlobFunc<0>(BM_Type t, int i) { __builtin_trap() /* STUB: not implemented */; }

// Direct non-POD global variables (style guide violation) as a baseline.
static BM_Blob direct_blobs[kNumObjects];

// Helper that cheaply maps benchmark iteration to randomish index in
// [0, kNumObjects).
int RandIdx(int i) { __builtin_trap() /* STUB: not implemented */; }

// Generic benchmark working with kNumObjects for any of the possible BM_Type.
template <BM_Type t>
void BM_Many(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }

void BM_DirectMany(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
void BM_NoDestrMany(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
void BM_OnHeapMany(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }

BENCHMARK(BM_DirectMany);
BENCHMARK(BM_NoDestrMany);
BENCHMARK(BM_OnHeapMany);

}  // namespace
