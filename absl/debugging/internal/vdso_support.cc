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

// Allow dynamic symbol lookup in the kernel VDSO page.
//
// VDSOSupport -- a class representing kernel VDSO (if present).

#include "absl/debugging/internal/vdso_support.h"
#include "absl/base/attributes.h"

#ifdef ABSL_HAVE_VDSO_SUPPORT     // defined in vdso_support.h

#if !defined(__has_include)
#define __has_include(header) 0
#endif

#include <errno.h>
#include <fcntl.h>
#if __has_include(<syscall.h>)
#include <syscall.h>
#elif __has_include(<sys/syscall.h>)
#include <sys/syscall.h>
#endif
#include <unistd.h>

#if !defined(__UCLIBC__) && defined(__GLIBC__) && \
    (__GLIBC__ > 2 || (__GLIBC__ == 2 && __GLIBC_MINOR__ >= 16))
#define ABSL_HAVE_GETAUXVAL
#endif

#ifdef ABSL_HAVE_GETAUXVAL
#include <sys/auxv.h>
#endif

#include "absl/base/dynamic_annotations.h"
#include "absl/base/internal/raw_logging.h"
#include "absl/base/port.h"

#ifndef AT_SYSINFO_EHDR
#define AT_SYSINFO_EHDR 33  // for crosstoolv10
#endif

#if defined(__NetBSD__)
using Elf32_auxv_t = Aux32Info;
using Elf64_auxv_t = Aux64Info;
#endif
#if defined(__FreeBSD__)
#if defined(__ELF_WORD_SIZE) && __ELF_WORD_SIZE == 64
using Elf64_auxv_t = Elf64_Auxinfo;
#endif
using Elf32_auxv_t = Elf32_Auxinfo;
#endif

namespace absl {
ABSL_NAMESPACE_BEGIN
namespace debugging_internal { __builtin_trap() /* STUB: not implemented */; }  // namespace debugging_internal
ABSL_NAMESPACE_END
}  // namespace absl

#endif  // ABSL_HAVE_VDSO_SUPPORT
