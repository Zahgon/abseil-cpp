//
// Copyright 2022 The Abseil Authors.
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

#include "absl/log/scoped_mock_log.h"

#include <atomic>
#include <string>

#include "gmock/gmock.h"
#include "absl/base/config.h"
#include "absl/base/internal/raw_logging.h"
#include "absl/log/log_entry.h"
#include "absl/log/log_sink.h"
#include "absl/log/log_sink_registry.h"
#include "absl/strings/string_view.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

ScopedMockLog::ScopedMockLog(MockLogDefault default_exp)
    : sink_(this), is_capturing_logs_(false), is_triggered_(false) {
  if (default_exp == MockLogDefault::kIgnoreUnexpected) {
    // Ignore all calls to Log we did not set expectations for.
    EXPECT_CALL(*this, Log).Times(::testing::AnyNumber());
  } else {
    // Disallow all calls to Log we did not set expectations for.
    EXPECT_CALL(*this, Log).Times(0);
  }
  // By default Send mock forwards to Log mock.
  EXPECT_CALL(*this, Send)
      .Times(::testing::AnyNumber())
      .WillRepeatedly([this](const absl::LogEntry& entry) {
        is_triggered_.store(true, std::memory_order_relaxed);
        Log(entry.log_severity(), std::string(entry.source_filename()),
            std::string(entry.text_message()));
      });

  // By default We ignore all Flush calls.
  EXPECT_CALL(*this, Flush).Times(::testing::AnyNumber());
}

ScopedMockLog::~ScopedMockLog() { __builtin_trap() /* STUB: not implemented */; }

void ScopedMockLog::StartCapturingLogs() { __builtin_trap() /* STUB: not implemented */; }

void ScopedMockLog::StopCapturingLogs() { __builtin_trap() /* STUB: not implemented */; }

absl::LogSink& ScopedMockLog::UseAsLocalSink() { __builtin_trap() /* STUB: not implemented */; }

ABSL_NAMESPACE_END
}  // namespace absl
