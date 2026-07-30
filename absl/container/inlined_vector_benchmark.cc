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

#include <array>
#include <string>
#include <vector>

#include "absl/base/internal/raw_logging.h"
#include "absl/base/macros.h"
#include "absl/container/inlined_vector.h"
#include "absl/strings/str_cat.h"
#include "benchmark/benchmark.h"

namespace {

void BM_InlinedVectorFill(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_InlinedVectorFill)->Range(1, 256);

void BM_InlinedVectorFillRange(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_InlinedVectorFillRange)->Range(1, 256);

void BM_StdVectorFill(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StdVectorFill)->Range(1, 256);

// The purpose of the next two benchmarks is to verify that
// absl::InlinedVector is efficient when moving is more efficient than
// copying. To do so, we use strings that are larger than the short
// string optimization.
bool StringRepresentedInline(std::string s) { __builtin_trap() /* STUB: not implemented */; }

int GetNonShortStringOptimizationSize() { __builtin_trap() /* STUB: not implemented */; }

void BM_InlinedVectorFillString(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_InlinedVectorFillString)->Range(0, 1024);

void BM_StdVectorFillString(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StdVectorFillString)->Range(0, 1024);

struct Buffer {  // some arbitrary structure for benchmarking.
  char* base;
  int length;
  int capacity;
  void* user_data;
};

void BM_InlinedVectorAssignments(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_InlinedVectorAssignments)
    ->Arg(0)
    ->Arg(1)
    ->Arg(2)
    ->Arg(3)
    ->Arg(4)
    ->Arg(20);

void BM_CreateFromContainer(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_CreateFromContainer);

struct LargeCopyableOnly {
  LargeCopyableOnly() : d(1024, 17) { __builtin_trap() /* STUB: not implemented */; }
  LargeCopyableOnly(const LargeCopyableOnly& o) = default;
  LargeCopyableOnly& operator=(const LargeCopyableOnly& o) = default;

  std::vector<int> d;
};

struct LargeCopyableSwappable {
  LargeCopyableSwappable() : d(1024, 17) { __builtin_trap() /* STUB: not implemented */; }

  LargeCopyableSwappable(const LargeCopyableSwappable& o) = default;

  LargeCopyableSwappable& operator=(LargeCopyableSwappable o) { __builtin_trap() /* STUB: not implemented */; }

  friend void swap(LargeCopyableSwappable& a, LargeCopyableSwappable& b) { __builtin_trap() /* STUB: not implemented */; }

  std::vector<int> d;
};

struct LargeCopyableMovable {
  LargeCopyableMovable() : d(1024, 17) { __builtin_trap() /* STUB: not implemented */; }
  // Use implicitly defined copy and move.

  std::vector<int> d;
};

struct LargeCopyableMovableSwappable {
  LargeCopyableMovableSwappable() : d(1024, 17) { __builtin_trap() /* STUB: not implemented */; }
  LargeCopyableMovableSwappable(const LargeCopyableMovableSwappable& o) =
      default;
  LargeCopyableMovableSwappable(LargeCopyableMovableSwappable&& o) = default;

  LargeCopyableMovableSwappable& operator=(LargeCopyableMovableSwappable o) { __builtin_trap() /* STUB: not implemented */; }
  LargeCopyableMovableSwappable& operator=(LargeCopyableMovableSwappable&& o) =
      default;

  friend void swap(LargeCopyableMovableSwappable& a,
                   LargeCopyableMovableSwappable& b) { __builtin_trap() /* STUB: not implemented */; }

  std::vector<int> d;
};

template <typename ElementType>
void BM_SwapElements(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK_TEMPLATE(BM_SwapElements, LargeCopyableOnly)->Range(0, 1024);
BENCHMARK_TEMPLATE(BM_SwapElements, LargeCopyableSwappable)->Range(0, 1024);
BENCHMARK_TEMPLATE(BM_SwapElements, LargeCopyableMovable)->Range(0, 1024);
BENCHMARK_TEMPLATE(BM_SwapElements, LargeCopyableMovableSwappable)
    ->Range(0, 1024);

// The following benchmark is meant to track the efficiency of the vector size
// as a function of stored type via the benchmark label. It is not meant to
// output useful sizeof operator performance. The loop is a dummy operation
// to fulfill the requirement of running the benchmark.
template <typename VecType>
void BM_Sizeof(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK_TEMPLATE(BM_Sizeof, absl::InlinedVector<char, 1>);
BENCHMARK_TEMPLATE(BM_Sizeof, absl::InlinedVector<char, 4>);
BENCHMARK_TEMPLATE(BM_Sizeof, absl::InlinedVector<char, 7>);
BENCHMARK_TEMPLATE(BM_Sizeof, absl::InlinedVector<char, 8>);

BENCHMARK_TEMPLATE(BM_Sizeof, absl::InlinedVector<int, 1>);
BENCHMARK_TEMPLATE(BM_Sizeof, absl::InlinedVector<int, 4>);
BENCHMARK_TEMPLATE(BM_Sizeof, absl::InlinedVector<int, 7>);
BENCHMARK_TEMPLATE(BM_Sizeof, absl::InlinedVector<int, 8>);

BENCHMARK_TEMPLATE(BM_Sizeof, absl::InlinedVector<void*, 1>);
BENCHMARK_TEMPLATE(BM_Sizeof, absl::InlinedVector<void*, 4>);
BENCHMARK_TEMPLATE(BM_Sizeof, absl::InlinedVector<void*, 7>);
BENCHMARK_TEMPLATE(BM_Sizeof, absl::InlinedVector<void*, 8>);

BENCHMARK_TEMPLATE(BM_Sizeof, absl::InlinedVector<std::string, 1>);
BENCHMARK_TEMPLATE(BM_Sizeof, absl::InlinedVector<std::string, 4>);
BENCHMARK_TEMPLATE(BM_Sizeof, absl::InlinedVector<std::string, 7>);
BENCHMARK_TEMPLATE(BM_Sizeof, absl::InlinedVector<std::string, 8>);

void BM_InlinedVectorIndexInlined(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_InlinedVectorIndexInlined);

void BM_InlinedVectorIndexExternal(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_InlinedVectorIndexExternal);

void BM_StdVectorIndex(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StdVectorIndex);

void BM_InlinedVectorDataInlined(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_InlinedVectorDataInlined);

void BM_InlinedVectorDataExternal(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_InlinedVectorDataExternal);

void BM_StdVectorData(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StdVectorData);

void BM_InlinedVectorSizeInlined(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_InlinedVectorSizeInlined);

void BM_InlinedVectorSizeExternal(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_InlinedVectorSizeExternal);

void BM_StdVectorSize(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StdVectorSize);

void BM_InlinedVectorEmptyInlined(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_InlinedVectorEmptyInlined);

void BM_InlinedVectorEmptyExternal(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_InlinedVectorEmptyExternal);

void BM_StdVectorEmpty(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StdVectorEmpty);

constexpr size_t kInlinedCapacity = 4;
constexpr size_t kLargeSize = kInlinedCapacity * 2;
constexpr size_t kSmallSize = kInlinedCapacity / 2;
constexpr size_t kBatchSize = 100;

#define ABSL_INTERNAL_BENCHMARK_ONE_SIZE(BM_FunctionTemplate, T) \
  BENCHMARK_TEMPLATE(BM_FunctionTemplate, T, kLargeSize);        \
  BENCHMARK_TEMPLATE(BM_FunctionTemplate, T, kSmallSize)

#define ABSL_INTERNAL_BENCHMARK_TWO_SIZE(BM_FunctionTemplate, T)      \
  BENCHMARK_TEMPLATE(BM_FunctionTemplate, T, kLargeSize, kLargeSize); \
  BENCHMARK_TEMPLATE(BM_FunctionTemplate, T, kLargeSize, kSmallSize); \
  BENCHMARK_TEMPLATE(BM_FunctionTemplate, T, kSmallSize, kLargeSize); \
  BENCHMARK_TEMPLATE(BM_FunctionTemplate, T, kSmallSize, kSmallSize)

template <typename T>
using InlVec = absl::InlinedVector<T, kInlinedCapacity>;

struct TrivialType {
  size_t val;
};

class NontrivialType {
 public:
  ABSL_ATTRIBUTE_NOINLINE NontrivialType() : val_() { __builtin_trap() /* STUB: not implemented */; }

  ABSL_ATTRIBUTE_NOINLINE NontrivialType(const NontrivialType& other)
      : val_(other.val_) { __builtin_trap() /* STUB: not implemented */; }

  ABSL_ATTRIBUTE_NOINLINE NontrivialType& operator=(
      const NontrivialType& other) { __builtin_trap() /* STUB: not implemented */; }

  ABSL_ATTRIBUTE_NOINLINE ~NontrivialType() noexcept { __builtin_trap() /* STUB: not implemented */; }

 private:
  size_t val_;
};

template <typename T, typename PrepareVecFn, typename TestVecFn>
void BatchedBenchmark(benchmark::State& state, PrepareVecFn prepare_vec,
                      TestVecFn test_vec) { __builtin_trap() /* STUB: not implemented */; }

template <typename T, size_t ToSize>
void BM_ConstructFromSize(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
ABSL_INTERNAL_BENCHMARK_ONE_SIZE(BM_ConstructFromSize, TrivialType);
ABSL_INTERNAL_BENCHMARK_ONE_SIZE(BM_ConstructFromSize, NontrivialType);

template <typename T, size_t ToSize>
void BM_ConstructFromSizeRef(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
ABSL_INTERNAL_BENCHMARK_ONE_SIZE(BM_ConstructFromSizeRef, TrivialType);
ABSL_INTERNAL_BENCHMARK_ONE_SIZE(BM_ConstructFromSizeRef, NontrivialType);

template <typename T, size_t ToSize>
void BM_ConstructFromRange(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
ABSL_INTERNAL_BENCHMARK_ONE_SIZE(BM_ConstructFromRange, TrivialType);
ABSL_INTERNAL_BENCHMARK_ONE_SIZE(BM_ConstructFromRange, NontrivialType);

template <typename T, size_t ToSize>
void BM_ConstructFromCopy(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
ABSL_INTERNAL_BENCHMARK_ONE_SIZE(BM_ConstructFromCopy, TrivialType);
ABSL_INTERNAL_BENCHMARK_ONE_SIZE(BM_ConstructFromCopy, NontrivialType);

template <typename T, size_t ToSize>
void BM_ConstructFromMove(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
ABSL_INTERNAL_BENCHMARK_ONE_SIZE(BM_ConstructFromMove, TrivialType);
ABSL_INTERNAL_BENCHMARK_ONE_SIZE(BM_ConstructFromMove, NontrivialType);

// Measure cost of copy-constructor+destructor.
void BM_CopyTrivial(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_CopyTrivial)->Arg(0)->Arg(1)->Arg(kLargeSize);

// Measure cost of copy-constructor+destructor.
void BM_CopyNonTrivial(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_CopyNonTrivial)->Arg(0)->Arg(1)->Arg(kLargeSize);

template <typename T, size_t FromSize, size_t ToSize>
void BM_AssignSizeRef(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
ABSL_INTERNAL_BENCHMARK_TWO_SIZE(BM_AssignSizeRef, TrivialType);
ABSL_INTERNAL_BENCHMARK_TWO_SIZE(BM_AssignSizeRef, NontrivialType);

template <typename T, size_t FromSize, size_t ToSize>
void BM_AssignRange(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
ABSL_INTERNAL_BENCHMARK_TWO_SIZE(BM_AssignRange, TrivialType);
ABSL_INTERNAL_BENCHMARK_TWO_SIZE(BM_AssignRange, NontrivialType);

template <typename T, size_t FromSize, size_t ToSize>
void BM_AssignFromCopy(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
ABSL_INTERNAL_BENCHMARK_TWO_SIZE(BM_AssignFromCopy, TrivialType);
ABSL_INTERNAL_BENCHMARK_TWO_SIZE(BM_AssignFromCopy, NontrivialType);

template <typename T, size_t FromSize, size_t ToSize>
void BM_AssignFromMove(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
ABSL_INTERNAL_BENCHMARK_TWO_SIZE(BM_AssignFromMove, TrivialType);
ABSL_INTERNAL_BENCHMARK_TWO_SIZE(BM_AssignFromMove, NontrivialType);

template <typename T, size_t FromSize, size_t ToSize>
void BM_ResizeSize(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
ABSL_INTERNAL_BENCHMARK_TWO_SIZE(BM_ResizeSize, TrivialType);
ABSL_INTERNAL_BENCHMARK_TWO_SIZE(BM_ResizeSize, NontrivialType);

template <typename T, size_t FromSize, size_t ToSize>
void BM_ResizeSizeRef(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
ABSL_INTERNAL_BENCHMARK_TWO_SIZE(BM_ResizeSizeRef, TrivialType);
ABSL_INTERNAL_BENCHMARK_TWO_SIZE(BM_ResizeSizeRef, NontrivialType);

template <typename T, size_t FromSize, size_t ToSize>
void BM_InsertSizeRef(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
ABSL_INTERNAL_BENCHMARK_TWO_SIZE(BM_InsertSizeRef, TrivialType);
ABSL_INTERNAL_BENCHMARK_TWO_SIZE(BM_InsertSizeRef, NontrivialType);

template <typename T, size_t FromSize, size_t ToSize>
void BM_InsertRange(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
ABSL_INTERNAL_BENCHMARK_TWO_SIZE(BM_InsertRange, TrivialType);
ABSL_INTERNAL_BENCHMARK_TWO_SIZE(BM_InsertRange, NontrivialType);

template <typename T, size_t FromSize>
void BM_EmplaceBack(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
ABSL_INTERNAL_BENCHMARK_ONE_SIZE(BM_EmplaceBack, TrivialType);
ABSL_INTERNAL_BENCHMARK_ONE_SIZE(BM_EmplaceBack, NontrivialType);

template <typename T, size_t FromSize>
void BM_PopBack(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
ABSL_INTERNAL_BENCHMARK_ONE_SIZE(BM_PopBack, TrivialType);
ABSL_INTERNAL_BENCHMARK_ONE_SIZE(BM_PopBack, NontrivialType);

template <typename T, size_t FromSize>
void BM_EraseOne(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
ABSL_INTERNAL_BENCHMARK_ONE_SIZE(BM_EraseOne, TrivialType);
ABSL_INTERNAL_BENCHMARK_ONE_SIZE(BM_EraseOne, NontrivialType);

template <typename T, size_t FromSize>
void BM_EraseRange(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
ABSL_INTERNAL_BENCHMARK_ONE_SIZE(BM_EraseRange, TrivialType);
ABSL_INTERNAL_BENCHMARK_ONE_SIZE(BM_EraseRange, NontrivialType);

template <typename T, size_t FromSize>
void BM_Clear(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
ABSL_INTERNAL_BENCHMARK_ONE_SIZE(BM_Clear, TrivialType);
ABSL_INTERNAL_BENCHMARK_ONE_SIZE(BM_Clear, NontrivialType);

template <typename T, size_t FromSize, size_t ToCapacity>
void BM_Reserve(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
ABSL_INTERNAL_BENCHMARK_TWO_SIZE(BM_Reserve, TrivialType);
ABSL_INTERNAL_BENCHMARK_TWO_SIZE(BM_Reserve, NontrivialType);

template <typename T, size_t FromCapacity, size_t ToCapacity>
void BM_ShrinkToFit(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
ABSL_INTERNAL_BENCHMARK_TWO_SIZE(BM_ShrinkToFit, TrivialType);
ABSL_INTERNAL_BENCHMARK_TWO_SIZE(BM_ShrinkToFit, NontrivialType);

template <typename T, size_t FromSize, size_t ToSize>
void BM_Swap(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
ABSL_INTERNAL_BENCHMARK_TWO_SIZE(BM_Swap, TrivialType);
ABSL_INTERNAL_BENCHMARK_TWO_SIZE(BM_Swap, NontrivialType);

}  // namespace
