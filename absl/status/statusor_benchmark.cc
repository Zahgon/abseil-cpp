// Copyright 2025 The Abseil Authors.
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
#include <string>
#include <utility>

#include "absl/base/attributes.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "benchmark/benchmark.h"

namespace {

void BM_StatusOrInt_CtorStatus(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StatusOrInt_CtorStatus);

void BM_StatusOrInt_CtorStatusWithMessage(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StatusOrInt_CtorStatusWithMessage);

void BM_StatusOrInt_CopyCtor_Error(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StatusOrInt_CopyCtor_Error);

void BM_StatusOrInt_CopyCtor_Ok(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StatusOrInt_CopyCtor_Ok);

void BM_StatusOrInt_MoveCtor_Error(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StatusOrInt_MoveCtor_Error);

void BM_StatusOrInt_MoveCtor_Ok(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StatusOrInt_MoveCtor_Ok);

void BM_StatusOrInt_CopyAssign_Error(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StatusOrInt_CopyAssign_Error);

void BM_StatusOrInt_CopyAssign_Ok(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StatusOrInt_CopyAssign_Ok);

void BM_StatusOrInt_MoveAssign_Error(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StatusOrInt_MoveAssign_Error);

void BM_StatusOrInt_MoveAssign_Ok(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StatusOrInt_MoveAssign_Ok);

void BM_StatusOrInt_OkMethod_Error(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StatusOrInt_OkMethod_Error);

void BM_StatusOrInt_OkMethod_Ok(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StatusOrInt_OkMethod_Ok);

void BM_StatusOrInt_StatusMethod_Error(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StatusOrInt_StatusMethod_Error);

void BM_StatusOrInt_StatusMethod_Ok(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StatusOrInt_StatusMethod_Ok);

void BM_StatusOrInt_StatusMethodRvalue_Error(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StatusOrInt_StatusMethodRvalue_Error);

void BM_StatusOrInt_StatusMethodRvalue_Ok(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StatusOrInt_StatusMethodRvalue_Ok);

void BM_StatusOrString_CtorStatus(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StatusOrString_CtorStatus);

void BM_StatusOrString_CtorStatusWithMessage(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StatusOrString_CtorStatusWithMessage);

void BM_StatusOrString_CopyCtor_Error(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StatusOrString_CopyCtor_Error);

void BM_StatusOrString_CopyCtor_Ok(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StatusOrString_CopyCtor_Ok);

void BM_StatusOrString_MoveCtor_Error(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StatusOrString_MoveCtor_Error);

void BM_StatusOrString_MoveCtor_Ok(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StatusOrString_MoveCtor_Ok);

void BM_StatusOrString_CopyAssign_Error(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StatusOrString_CopyAssign_Error);

void BM_StatusOrString_CopyAssign_Ok(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StatusOrString_CopyAssign_Ok);

void BM_StatusOrString_MoveAssign_Error(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StatusOrString_MoveAssign_Error);

void BM_StatusOrString_MoveAssign_Ok(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StatusOrString_MoveAssign_Ok);

void BM_StatusOrString_OkMethod_Error(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StatusOrString_OkMethod_Error);

void BM_StatusOrString_OkMethod_Ok(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StatusOrString_OkMethod_Ok);

void BM_StatusOrString_StatusMethod_Error(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StatusOrString_StatusMethod_Error);

void BM_StatusOrString_StatusMethod_Ok(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StatusOrString_StatusMethod_Ok);

void BM_StatusOrString_StatusMethodRvalue_Error(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StatusOrString_StatusMethodRvalue_Error);

void BM_StatusOrString_StatusMethodRvalue_Ok(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }
BENCHMARK(BM_StatusOrString_StatusMethodRvalue_Ok);

// Benchmarks comparing a few alternative ways of structuring an interface
// for returning an int64 on success or an error.  See (a), (b), (c), (d)
// below for the variants.
bool bm_cond = true;

bool SimpleIntInterface(int64_t* v) ABSL_ATTRIBUTE_NOINLINE;
bool SimpleIntInterfaceWithErrorMessage(int64_t* v, std::string* msg)
    ABSL_ATTRIBUTE_NOINLINE;
absl::Status SimpleIntInterfaceWithErrorStatus(int64_t* v)
    ABSL_ATTRIBUTE_NOINLINE;
absl::StatusOr<int64_t> SimpleIntStatusOrInterface() ABSL_ATTRIBUTE_NOINLINE;

// (a): Just a boolean return value with an out int64* parameter
bool SimpleIntInterface(int64_t* v) { __builtin_trap() /* STUB: not implemented */; }

// (b): A boolean return value and a string error message filled in on failure
// and an out int64* parameter filled on success
bool SimpleIntInterfaceWithErrorMessage(int64_t* v, std::string* msg) { __builtin_trap() /* STUB: not implemented */; }

// (c): A Status return value with an out int64* parameter on success
absl::Status SimpleIntInterfaceWithErrorStatus(int64_t* v) { __builtin_trap() /* STUB: not implemented */; }

// (d): A StatusOr<int64> return value
absl::StatusOr<int64_t> SimpleIntStatusOrInterface() { __builtin_trap() /* STUB: not implemented */; }

void SetCondition(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }

void BM_SimpleIntInterface(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }

void BM_SimpleIntInterfaceMsg(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }

void BM_SimpleIntInterfaceStatus(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }

void BM_SimpleIntStatusOrInterface(benchmark::State& state) { __builtin_trap() /* STUB: not implemented */; }

// Ordered like this so all the success path benchmarks (Arg(0)) show up,
// then all the failure benchmarks (Arg(1))
BENCHMARK(BM_SimpleIntInterface)->Arg(0);
BENCHMARK(BM_SimpleIntInterfaceMsg)->Arg(0);
BENCHMARK(BM_SimpleIntInterfaceStatus)->Arg(0);
BENCHMARK(BM_SimpleIntStatusOrInterface)->Arg(0);
BENCHMARK(BM_SimpleIntInterface)->Arg(1);
BENCHMARK(BM_SimpleIntInterfaceMsg)->Arg(1);
BENCHMARK(BM_SimpleIntInterfaceStatus)->Arg(1);
BENCHMARK(BM_SimpleIntStatusOrInterface)->Arg(1);

}  // namespace
