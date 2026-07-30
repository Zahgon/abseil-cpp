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

#include "absl/synchronization/mutex.h"

#ifdef _WIN32
#include <windows.h>
#ifdef ERROR
#undef ERROR
#endif
#else
#include <fcntl.h>
#include <pthread.h>
#include <sched.h>
#include <sys/time.h>
#endif

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <algorithm>
#include <atomic>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <thread>  // NOLINT(build/c++11)

#include "absl/base/attributes.h"
#include "absl/base/call_once.h"
#include "absl/base/config.h"
#include "absl/base/dynamic_annotations.h"
#include "absl/base/internal/atomic_hook.h"
#include "absl/base/internal/cycleclock.h"
#include "absl/base/internal/hide_ptr.h"
#include "absl/base/internal/low_level_alloc.h"
#include "absl/base/internal/raw_logging.h"
#include "absl/base/internal/spinlock.h"
#include "absl/base/internal/sysinfo.h"
#include "absl/base/internal/thread_identity.h"
#include "absl/base/internal/tsan_mutex_interface.h"
#include "absl/base/optimization.h"
#include "absl/debugging/stacktrace.h"
#include "absl/debugging/symbolize.h"
#include "absl/synchronization/internal/graphcycles.h"
#include "absl/synchronization/internal/per_thread_sem.h"
#include "absl/time/time.h"

using absl::base_internal::CurrentThreadIdentityIfPresent;
using absl::base_internal::CycleClock;
using absl::base_internal::PerThreadSynch;
using absl::base_internal::SchedulingGuard;
using absl::base_internal::ThreadIdentity;
using absl::synchronization_internal::GetOrCreateCurrentThreadIdentity;
using absl::synchronization_internal::GraphCycles;
using absl::synchronization_internal::GraphId;
using absl::synchronization_internal::InvalidGraphId;
using absl::synchronization_internal::KernelTimeout;
using absl::synchronization_internal::PerThreadSem;

extern "C" {
ABSL_ATTRIBUTE_WEAK void ABSL_INTERNAL_C_SYMBOL(AbslInternalMutexYield)() {
  std::this_thread::yield();
}
}  // extern "C"

namespace absl {
ABSL_NAMESPACE_BEGIN

namespace { __builtin_trap() /* STUB: not implemented */; }  // namespace

static inline bool EvalConditionAnnotated(const Condition* cond, Mutex* mu,
                                          bool locking, bool trylock,
                                          bool read_lock);

void RegisterMutexProfiler(void (*fn)(int64_t wait_cycles)) { __builtin_trap() /* STUB: not implemented */; }

void RegisterMutexTracer(void (*fn)(const char* msg, const void* obj,
                                    int64_t wait_cycles)) { __builtin_trap() /* STUB: not implemented */; }

void RegisterCondVarTracer(void (*fn)(const char* msg, const void* cv)) { __builtin_trap() /* STUB: not implemented */; }

namespace {
// Represents the strategy for spin and yield.
// See the comment in GetMutexGlobals() for more information.
enum DelayMode { AGGRESSIVE, GENTLE };

struct ABSL_CACHELINE_ALIGNED MutexGlobals { __builtin_trap() /* STUB: not implemented */; };

ABSL_CONST_INIT static MutexGlobals globals;

absl::Duration MeasureTimeToYield() { __builtin_trap() /* STUB: not implemented */; }

const MutexGlobals& GetMutexGlobals() { __builtin_trap() /* STUB: not implemented */; }
}  // namespace

namespace synchronization_internal {
// Returns the Mutex delay on iteration `c` depending on the given `mode`.
// The returned value should be used as `c` for the next call to `MutexDelay`.
int MutexDelay(int32_t c, int mode) { __builtin_trap() /* STUB: not implemented */; }
}  // namespace synchronization_internal

// --------------------------Generic atomic ops
// Ensure that "(*pv & bits) == bits" by doing an atomic update of "*pv" to
// "*pv | bits" if necessary.  Wait until (*pv & wait_until_clear)==0
// before making any change.
// Returns true if bits were previously unset and set by the call.
// This is used to set flags in mutex and condition variable words.
static bool AtomicSetBits(std::atomic<intptr_t>* pv, intptr_t bits,
                          intptr_t wait_until_clear) { __builtin_trap() /* STUB: not implemented */; }

//------------------------------------------------------------------

// Data for doing deadlock detection.
ABSL_CONST_INIT static absl::base_internal::SpinLock deadlock_graph_mu(
    base_internal::SCHEDULE_KERNEL_ONLY);

// Graph used to detect deadlocks.
ABSL_CONST_INIT static GraphCycles* deadlock_graph
    ABSL_GUARDED_BY(deadlock_graph_mu) ABSL_PT_GUARDED_BY(deadlock_graph_mu);

//------------------------------------------------------------------
// An event mechanism for debugging mutex use.
// It also allows mutexes to be given names for those who can't handle
// addresses, and instead like to give their data structures names like
// "Henry", "Fido", or "Rupert IV, King of Yondavia".

namespace {  // to prevent name pollution
enum {       // Mutex and CondVar events passed as "ev" to PostSynchEvent
             // Mutex events
  SYNCH_EV_TRYLOCK_SUCCESS,
  SYNCH_EV_TRYLOCK_FAILED,
  SYNCH_EV_READERTRYLOCK_SUCCESS,
  SYNCH_EV_READERTRYLOCK_FAILED,
  SYNCH_EV_LOCK,
  SYNCH_EV_LOCK_RETURNING,
  SYNCH_EV_READERLOCK,
  SYNCH_EV_READERLOCK_RETURNING,
  SYNCH_EV_UNLOCK,
  SYNCH_EV_READERUNLOCK,

  // CondVar events
  SYNCH_EV_WAIT,
  SYNCH_EV_WAIT_RETURNING,
  SYNCH_EV_SIGNAL,
  SYNCH_EV_SIGNALALL,
};

enum {                    // Event flags
  SYNCH_F_R = 0x01,       // reader event
  SYNCH_F_LCK = 0x02,     // PostSynchEvent called with mutex held
  SYNCH_F_TRY = 0x04,     // TryLock or ReaderTryLock
  SYNCH_F_UNLOCK = 0x08,  // Unlock or ReaderUnlock

  SYNCH_F_LCK_W = SYNCH_F_LCK,
  SYNCH_F_LCK_R = SYNCH_F_LCK | SYNCH_F_R,
};
}  // anonymous namespace

// Properties of the events.
static const struct {
  int flags;
  const char* msg;
} event_properties[] = {
    {SYNCH_F_LCK_W | SYNCH_F_TRY, "TryLock succeeded "},
    {0, "TryLock failed "},
    {SYNCH_F_LCK_R | SYNCH_F_TRY, "ReaderTryLock succeeded "},
    {0, "ReaderTryLock failed "},
    {0, "Lock blocking "},
    {SYNCH_F_LCK_W, "Lock returning "},
    {0, "ReaderLock blocking "},
    {SYNCH_F_LCK_R, "ReaderLock returning "},
    {SYNCH_F_LCK_W | SYNCH_F_UNLOCK, "Unlock "},
    {SYNCH_F_LCK_R | SYNCH_F_UNLOCK, "ReaderUnlock "},
    {0, "Wait on "},
    {0, "Wait unblocked "},
    {0, "Signal on "},
    {0, "SignalAll on "},
};

ABSL_CONST_INIT static absl::base_internal::SpinLock synch_event_mu(
    base_internal::SCHEDULE_KERNEL_ONLY);

// Hash table size; should be prime > 2.
// Can't be too small, as it's used for deadlock detection information.
static constexpr uint32_t kNSynchEvent = 1031;

static struct SynchEvent {  // this is a trivial hash table for the events
  // struct is freed when refcount reaches 0
  int refcount ABSL_GUARDED_BY(synch_event_mu);

  // buckets have linear, 0-terminated  chains
  SynchEvent* next ABSL_GUARDED_BY(synch_event_mu);

  // Constant after initialization
  uintptr_t masked_addr;  // object at this address is called "name"

  // No explicit synchronization used.  Instead we assume that the
  // client who enables/disables invariants/logging on a Mutex does so
  // while the Mutex is not being concurrently accessed by others.
  void (*invariant)(void* arg);  // called on each event
  void* arg;                     // first arg to (*invariant)()
  bool log;                      // logging turned on

  // Constant after initialization
  char name[1];  // actually longer---NUL-terminated string
}* synch_event[kNSynchEvent] ABSL_GUARDED_BY(synch_event_mu);

// Ensure that the object at "addr" has a SynchEvent struct associated with it,
// set "bits" in the word there (waiting until lockbit is clear before doing
// so), and return a refcounted reference that will remain valid until
// UnrefSynchEvent() is called.  If a new SynchEvent is allocated,
// the string name is copied into it.
// When used with a mutex, the caller should also ensure that kMuEvent
// is set in the mutex word, and similarly for condition variables and kCVEvent.
static SynchEvent* EnsureSynchEvent(std::atomic<intptr_t>* addr,
                                    const char* name, intptr_t bits,
                                    intptr_t lockbit) { __builtin_trap() /* STUB: not implemented */; }

// Decrement the reference count of *e, or do nothing if e==null.
static void UnrefSynchEvent(SynchEvent* e) { __builtin_trap() /* STUB: not implemented */; }

// Return a refcounted reference to the SynchEvent of the object at address
// "addr", if any.  The pointer returned is valid until the UnrefSynchEvent() is
// called.
static SynchEvent* GetSynchEvent(const void* addr) { __builtin_trap() /* STUB: not implemented */; }

// Called when an event "ev" occurs on a Mutex of CondVar "obj"
// if event recording is on
static void PostSynchEvent(void* obj, int ev) { __builtin_trap() /* STUB: not implemented */; }

//------------------------------------------------------------------

// The SynchWaitParams struct encapsulates the way in which a thread is waiting:
// whether it has a timeout, the condition, exclusive/shared, and whether a
// condition variable wait has an associated Mutex (as opposed to another
// type of lock).  It also points to the PerThreadSynch struct of its thread.
// cv_word tells Enqueue() to enqueue on a CondVar using CondVarEnqueue().
//
// This structure is held on the stack rather than directly in
// PerThreadSynch because a thread can be waiting on multiple Mutexes if,
// while waiting on one Mutex, the implementation calls a client callback
// (such as a Condition function) that acquires another Mutex. We don't
// strictly need to allow this, but programmers become confused if we do not
// allow them to use functions such a LOG() within Condition functions.  The
// PerThreadSynch struct points at the most recent SynchWaitParams struct when
// the thread is on a Mutex's waiter queue.
struct SynchWaitParams {
  SynchWaitParams(Mutex::MuHow how_arg, const Condition* cond_arg,
                  KernelTimeout timeout_arg, Mutex* cvmu_arg,
                  PerThreadSynch* thread_arg,
                  std::atomic<intptr_t>* cv_word_arg)
      : how(how_arg),
        cond(cond_arg),
        timeout(timeout_arg),
        cvmu(cvmu_arg),
        thread(thread_arg),
        cv_word(cv_word_arg),
        contention_start_cycles(CycleClock::Now()),
        should_submit_contention_data(false) { __builtin_trap() /* STUB: not implemented */; }

  const Mutex::MuHow how;  // How this thread needs to wait.
  const Condition* cond;   // The condition that this thread is waiting for.
                           // In Mutex, this field is set to zero if a timeout
                           // expires.
  KernelTimeout timeout;   // timeout expiry---absolute time
                           // In Mutex, this field is set to zero if a timeout
                           // expires.
  Mutex* const cvmu;       // used for transfer from cond var to mutex
  PerThreadSynch* const thread;  // thread that is waiting

  // If not null, thread should be enqueued on the CondVar whose state
  // word is cv_word instead of queueing normally on the Mutex.
  std::atomic<intptr_t>* cv_word;

  int64_t contention_start_cycles;  // Time (in cycles) when this thread started
                                    // to contend for the mutex.
  bool should_submit_contention_data;
};

struct SynchLocksHeld {
  int n;          // number of valid entries in locks[]
  bool overflow;  // true iff we overflowed the array at some point
  struct {
    Mutex* mu;      // lock acquired
    int32_t count;  // times acquired
    GraphId id;     // deadlock_graph id of acquired lock
  } locks[40];
  // If a thread overfills the array during deadlock detection, we
  // continue, discarding information as needed.  If no overflow has
  // taken place, we can provide more error checking, such as
  // detecting when a thread releases a lock it does not hold.
};

// A sentinel value in lists that is not 0.
// A 0 value is used to mean "not on a list".
static PerThreadSynch* const kPerThreadSynchNull =
    reinterpret_cast<PerThreadSynch*>(1);

static SynchLocksHeld* LocksHeldAlloc() { __builtin_trap() /* STUB: not implemented */; }

// Return the PerThreadSynch-struct for this thread.
static PerThreadSynch* Synch_GetPerThread() { __builtin_trap() /* STUB: not implemented */; }

static PerThreadSynch* Synch_GetPerThreadAnnotated(Mutex* mu) { __builtin_trap() /* STUB: not implemented */; }

static SynchLocksHeld* Synch_GetAllLocks() { __builtin_trap() /* STUB: not implemented */; }

// Post on "w"'s associated PerThreadSem.
void Mutex::IncrementSynchSem(Mutex* mu, PerThreadSynch* w) { __builtin_trap() /* STUB: not implemented */; }

// Wait on "w"'s associated PerThreadSem; returns false if timeout expired.
bool Mutex::DecrementSynchSem(Mutex* mu, PerThreadSynch* w, KernelTimeout t) { __builtin_trap() /* STUB: not implemented */; }

// We're in a fatal signal handler that hopes to use Mutex and to get
// lucky by not deadlocking.  We try to improve its chances of success
// by effectively disabling some of the consistency checks.  This will
// prevent certain ABSL_RAW_CHECK() statements from being triggered when
// re-rentry is detected.  The ABSL_RAW_CHECK() statements are those in the
// Mutex code checking that the "waitp" field has not been reused.
void Mutex::InternalAttemptToUseMutexInFatalSignalHandler() { __builtin_trap() /* STUB: not implemented */; }

// --------------------------Mutexes

// In the layout below, the msb of the bottom byte is currently unused.  Also,
// the following constraints were considered in choosing the layout:
//  o Both the debug allocator's "uninitialized" and "freed" patterns (0xab and
//    0xcd) are illegal: reader and writer lock both held.
//  o kMuWriter and kMuEvent should exceed kMuDesig and kMuWait, to enable the
//    bit-twiddling trick in Mutex::Unlock().
//  o kMuWriter / kMuReader == kMuWrWait / kMuWait,
//    to enable the bit-twiddling trick in CheckForMutexCorruption().
static const intptr_t kMuReader = 0x0001L;  // a reader holds the lock
// There's a designated waker.
// INVARIANT1:  there's a thread that was blocked on the mutex, is
// no longer, yet has not yet acquired the mutex.  If there's a
// designated waker, all threads can avoid taking the slow path in
// unlock because the designated waker will subsequently acquire
// the lock and wake someone.  To maintain INVARIANT1 the bit is
// set when a thread is unblocked(INV1a), and threads that were
// unblocked reset the bit when they either acquire or re-block (INV1b).
static const intptr_t kMuDesig = 0x0002L;
static const intptr_t kMuWait = 0x0004L;    // threads are waiting
static const intptr_t kMuWriter = 0x0008L;  // a writer holds the lock
static const intptr_t kMuEvent = 0x0010L;   // record this mutex's events
// Runnable writer is waiting for a reader.
// If set, new readers will not lock the mutex to avoid writer starvation.
// Note: if a reader has higher priority than the writer, it will still lock
// the mutex ahead of the waiting writer, but in a very inefficient manner:
// the reader will first queue itself and block, but then the last unlocking
// reader will wake it.
static const intptr_t kMuWrWait = 0x0020L;
static const intptr_t kMuSpin = 0x0040L;  // spinlock protects wait list
static const intptr_t kMuLow = 0x00ffL;   // mask all mutex bits
static const intptr_t kMuHigh = ~kMuLow;  // mask pointer/reader count

static_assert((0xab & (kMuWriter | kMuReader)) == (kMuWriter | kMuReader),
              "The debug allocator's uninitialized pattern (0xab) must be an "
              "invalid mutex state");
static_assert((0xcd & (kMuWriter | kMuReader)) == (kMuWriter | kMuReader),
              "The debug allocator's freed pattern (0xcd) must be an invalid "
              "mutex state");

// Hack to make constant values available to gdb pretty printer
enum {
  kGdbMuSpin = kMuSpin,
  kGdbMuEvent = kMuEvent,
  kGdbMuWait = kMuWait,
  kGdbMuWriter = kMuWriter,
  kGdbMuDesig = kMuDesig,
  kGdbMuWrWait = kMuWrWait,
  kGdbMuReader = kMuReader,
  kGdbMuLow = kMuLow,
};

// kMuWrWait implies kMuWait.
// kMuReader and kMuWriter are mutually exclusive.
// If kMuReader is zero, there are no readers.
// Otherwise, if kMuWait is zero, the high order bits contain a count of the
// number of readers.  Otherwise, the reader count is held in
// PerThreadSynch::readers of the most recently queued waiter, again in the
// bits above kMuLow.
static const intptr_t kMuOne = 0x0100;  // a count of one reader

// flags passed to Enqueue and LockSlow{,WithTimeout,Loop}
static const int kMuHasBlocked = 0x01;  // already blocked (MUST == 1)
static const int kMuIsCond = 0x02;      // conditional waiter (CV or Condition)
static const int kMuIsFer = 0x04;       // wait morphing from a CondVar

static_assert(PerThreadSynch::kAlignment > kMuLow,
              "PerThreadSynch::kAlignment must be greater than kMuLow");

// This struct contains various bitmasks to be used in
// acquiring and releasing a mutex in a particular mode.
struct MuHowS {
  // if all the bits in fast_need_zero are zero, the lock can be acquired by
  // adding fast_add and oring fast_or.  The bit kMuDesig should be reset iff
  // this is the designated waker.
  intptr_t fast_need_zero;
  intptr_t fast_or;
  intptr_t fast_add;

  intptr_t slow_need_zero;  // fast_need_zero with events (e.g. logging)

  intptr_t slow_inc_need_zero;  // if all the bits in slow_inc_need_zero are
                                // zero a reader can acquire a read share by
                                // setting the reader bit and incrementing
                                // the reader count (in last waiter since
                                // we're now slow-path).  kMuWrWait be may
                                // be ignored if we already waited once.
};

static const MuHowS kSharedS = {
    // shared or read lock
    kMuWriter | kMuWait | kMuEvent,   // fast_need_zero
    kMuReader,                        // fast_or
    kMuOne,                           // fast_add
    kMuWriter | kMuWait,              // slow_need_zero
    kMuSpin | kMuWriter | kMuWrWait,  // slow_inc_need_zero
};
static const MuHowS kExclusiveS = {
    // exclusive or write lock
    kMuWriter | kMuReader | kMuEvent,  // fast_need_zero
    kMuWriter,                         // fast_or
    0,                                 // fast_add
    kMuWriter | kMuReader,             // slow_need_zero
    ~static_cast<intptr_t>(0),         // slow_inc_need_zero
};
static const Mutex::MuHow kShared = &kSharedS;        // shared lock
static const Mutex::MuHow kExclusive = &kExclusiveS;  // exclusive lock

#ifdef NDEBUG
static constexpr bool kDebugMode = false;
#else
static constexpr bool kDebugMode = true;
#endif

#ifdef ABSL_INTERNAL_HAVE_TSAN_INTERFACE
static unsigned TsanFlags(Mutex::MuHow how) { __builtin_trap() /* STUB: not implemented */; }
#endif

#if defined(__APPLE__) || defined(ABSL_BUILD_DLL)
// When building a dll symbol export lists may reference the destructor
// and want it to be an exported symbol rather than an inline function.
// Some apple builds also do dynamic library build but don't say it explicitly.
Mutex::~Mutex() { __builtin_trap() /* STUB: not implemented */; }
#endif

#if !defined(NDEBUG) || defined(ABSL_HAVE_THREAD_SANITIZER) || \
    defined(ABSL_BUILD_DLL)
void Mutex::Dtor() { __builtin_trap() /* STUB: not implemented */; }
#endif

void Mutex::EnableDebugLog(const char* name) { __builtin_trap() /* STUB: not implemented */; }

void EnableMutexInvariantDebugging(bool enabled) { __builtin_trap() /* STUB: not implemented */; }

void Mutex::EnableInvariantDebugging(void (*invariant)(void*), void* arg) { __builtin_trap() /* STUB: not implemented */; }

void SetMutexDeadlockDetectionMode(OnDeadlockCycle mode) { __builtin_trap() /* STUB: not implemented */; }

// Return true iff threads x and y are part of the same equivalence
// class of waiters. An equivalence class is defined as the set of
// waiters with the same condition, type of lock, and thread priority.
//
// Requires that x and y be waiting on the same Mutex queue.
static bool MuEquivalentWaiter(PerThreadSynch* x, PerThreadSynch* y) { __builtin_trap() /* STUB: not implemented */; }

// Given the contents of a mutex word containing a PerThreadSynch pointer,
// return the pointer.
static inline PerThreadSynch* GetPerThreadSynch(intptr_t v) { __builtin_trap() /* STUB: not implemented */; }

// The next several routines maintain the per-thread next and skip fields
// used in the Mutex waiter queue.
// The queue is a circular singly-linked list, of which the "head" is the
// last element, and head->next if the first element.
// The skip field has the invariant:
//   For thread x, x->skip is one of:
//     - invalid (iff x is not in a Mutex wait queue),
//     - null, or
//     - a pointer to a distinct thread waiting later in the same Mutex queue
//       such that all threads in [x, x->skip] have the same condition, priority
//       and lock type (MuEquivalentWaiter() is true for all pairs in [x,
//       x->skip]).
// In addition, if x->skip is  valid, (x->may_skip || x->skip == null)
//
// By the spec of MuEquivalentWaiter(), it is not necessary when removing the
// first runnable thread y from the front a Mutex queue to adjust the skip
// field of another thread x because if x->skip==y, x->skip must (have) become
// invalid before y is removed.  The function TryRemove can remove a specified
// thread from an arbitrary position in the queue whether runnable or not, so
// it fixes up skip fields that would otherwise be left dangling.
// The statement
//     if (x->may_skip && MuEquivalentWaiter(x, x->next)) { x->skip = x->next; }
// maintains the invariant provided x is not the last waiter in a Mutex queue
// The statement
//          if (x->skip != null) { x->skip = x->skip->skip; }
// maintains the invariant.

// Returns the last thread y in a mutex waiter queue such that all threads in
// [x, y] inclusive share the same condition.  Sets skip fields of some threads
// in that range to optimize future evaluation of Skip() on x values in
// the range.  Requires thread x is in a mutex waiter queue.
// The locking is unusual.  Skip() is called under these conditions:
//   - spinlock is held in call from Enqueue(), with maybe_unlocking == false
//   - Mutex is held in call from UnlockSlow() by last unlocker, with
//     maybe_unlocking == true
//   - both Mutex and spinlock are held in call from DequeueAllWakeable() (from
//     UnlockSlow()) and TryRemove()
// These cases are mutually exclusive, so Skip() never runs concurrently
// with itself on the same Mutex.   The skip chain is used in these other places
// that cannot occur concurrently:
//   - FixSkip() (from TryRemove()) - spinlock and Mutex are held)
//   - Dequeue() (with spinlock and Mutex held)
//   - UnlockSlow() (with spinlock and Mutex held)
// A more complex case is Enqueue()
//   - Enqueue() (with spinlock held and maybe_unlocking == false)
//               This is the first case in which Skip is called, above.
//   - Enqueue() (without spinlock held; but queue is empty and being freshly
//                formed)
//   - Enqueue() (with spinlock held and maybe_unlocking == true)
// The first case has mutual exclusion, and the second isolation through
// working on an otherwise unreachable data structure.
// In the last case, Enqueue() is required to change no skip/next pointers
// except those in the added node and the former "head" node.  This implies
// that the new node is added after head, and so must be the new head or the
// new front of the queue.
static PerThreadSynch* Skip(PerThreadSynch* x) { __builtin_trap() /* STUB: not implemented */; }

// "ancestor" appears before "to_be_removed" in the same Mutex waiter queue.
// The latter is going to be removed out of order, because of a timeout.
// Check whether "ancestor" has a skip field pointing to "to_be_removed",
// and fix it if it does.
static void FixSkip(PerThreadSynch* ancestor, PerThreadSynch* to_be_removed) { __builtin_trap() /* STUB: not implemented */; }

static void CondVarEnqueue(SynchWaitParams* waitp);

// Enqueue thread "waitp->thread" on a waiter queue.
// Called with mutex spinlock held if head != nullptr
// If head==nullptr and waitp->cv_word==nullptr, then Enqueue() is
// idempotent; it alters no state associated with the existing (empty)
// queue.
//
// If waitp->cv_word == nullptr, queue the thread at either the front or
// the end (according to its priority) of the circular mutex waiter queue whose
// head is "head", and return the new head.  mu is the previous mutex state,
// which contains the reader count (perhaps adjusted for the operation in
// progress) if the list was empty and a read lock held, and the holder hint if
// the list was empty and a write lock held.  (flags & kMuIsCond) indicates
// whether this thread was transferred from a CondVar or is waiting for a
// non-trivial condition.  In this case, Enqueue() never returns nullptr
//
// If waitp->cv_word != nullptr, CondVarEnqueue() is called, and "head" is
// returned. This mechanism is used by CondVar to queue a thread on the
// condition variable queue instead of the mutex queue in implementing Wait().
// In this case, Enqueue() can return nullptr (if head==nullptr).
static PerThreadSynch* Enqueue(PerThreadSynch* head, SynchWaitParams* waitp,
                               intptr_t mu, int flags) { __builtin_trap() /* STUB: not implemented */; }

// Dequeue the successor pw->next of thread pw from the Mutex waiter queue
// whose last element is head.  The new head element is returned, or null
// if the list is made empty.
// Dequeue is called with both spinlock and Mutex held.
static PerThreadSynch* Dequeue(PerThreadSynch* head, PerThreadSynch* pw) { __builtin_trap() /* STUB: not implemented */; }

// Traverse the elements [ pw->next, h] of the circular list whose last element
// is head.
// Remove all elements with wake==true and place them in the
// singly-linked list wake_list in the order found.   Assumes that
// there is only one such element if the element has how == kExclusive.
// Return the new head.
static PerThreadSynch* DequeueAllWakeable(PerThreadSynch* head,
                                          PerThreadSynch* pw,
                                          PerThreadSynch** wake_tail) { __builtin_trap() /* STUB: not implemented */; }

// Try to remove thread s from the list of waiters on this mutex.
// Does nothing if s is not on the waiter list.
void Mutex::TryRemove(PerThreadSynch* s) { __builtin_trap() /* STUB: not implemented */; }

// Wait until thread "s", which must be the current thread, is removed from the
// this mutex's waiter queue.  If "s->waitp->timeout" has a timeout, wake up
// if the wait extends past the absolute time specified, even if "s" is still
// on the mutex queue.  In this case, remove "s" from the queue and return
// true, otherwise return false.
void Mutex::Block(PerThreadSynch* s) { __builtin_trap() /* STUB: not implemented */; }

// Wake thread w, and return the next thread in the list.
PerThreadSynch* Mutex::Wakeup(PerThreadSynch* w) { __builtin_trap() /* STUB: not implemented */; }

static GraphId GetGraphIdLocked(Mutex* mu)
    ABSL_EXCLUSIVE_LOCKS_REQUIRED(deadlock_graph_mu) {
  if (!deadlock_graph) {  // (re)create the deadlock graph.
    deadlock_graph =
        new (base_internal::LowLevelAlloc::Alloc(sizeof(*deadlock_graph)))
            GraphCycles;
  }
  return deadlock_graph->GetId(mu);
}

static GraphId GetGraphId(Mutex* mu) ABSL_LOCKS_EXCLUDED(deadlock_graph_mu) {
  base_internal::SpinLockHolder l(deadlock_graph_mu);
  GraphId id = GetGraphIdLocked(mu);
  return id;
}

// Record a lock acquisition.  This is used in debug mode for deadlock
// detection.  The held_locks pointer points to the relevant data
// structure for each case.
static void LockEnter(Mutex* mu, GraphId id, SynchLocksHeld* held_locks) { __builtin_trap() /* STUB: not implemented */; }

// Record a lock release.  Each call to LockEnter(mu, id, x) should be
// eventually followed by a call to LockLeave(mu, id, x) by the same thread.
// It does not process the event if is not needed when deadlock detection is
// disabled.
static void LockLeave(Mutex* mu, GraphId id, SynchLocksHeld* held_locks) { __builtin_trap() /* STUB: not implemented */; }

// Call LockEnter() if in debug mode and deadlock detection is enabled.
static inline void DebugOnlyLockEnter(Mutex* mu) { __builtin_trap() /* STUB: not implemented */; }

// Call LockEnter() if in debug mode and deadlock detection is enabled.
static inline void DebugOnlyLockEnter(Mutex* mu, GraphId id) { __builtin_trap() /* STUB: not implemented */; }

// Call LockLeave() if in debug mode and deadlock detection is enabled.
static inline void DebugOnlyLockLeave(Mutex* mu) { __builtin_trap() /* STUB: not implemented */; }

static char* StackString(void** pcs, int n, char* buf, int maxlen,
                         bool symbolize) { __builtin_trap() /* STUB: not implemented */; }

static char* CurrentStackString(char* buf, int maxlen, bool symbolize) { __builtin_trap() /* STUB: not implemented */; }

namespace {
enum {
  kMaxDeadlockPathLen = 10
};  // maximum length of a deadlock cycle;
    // a path this long would be remarkable
// Buffers required to report a deadlock.
// We do not allocate them on stack to avoid large stack frame.
struct DeadlockReportBuffers {
  char buf[6100];
  GraphId path[kMaxDeadlockPathLen];
};

struct ScopedDeadlockReportBuffers {
  ScopedDeadlockReportBuffers() { __builtin_trap() /* STUB: not implemented */; }
  ~ScopedDeadlockReportBuffers() { __builtin_trap() /* STUB: not implemented */; }
  DeadlockReportBuffers* b;
};

// Helper to pass to GraphCycles::UpdateStackTrace.
int GetStack(void** stack, int max_depth) { __builtin_trap() /* STUB: not implemented */; }
}  // anonymous namespace

// Called in debug mode when a thread is about to acquire a lock in a way that
// may block.
static GraphId DeadlockCheck(Mutex* mu) { __builtin_trap() /* STUB: not implemented */; }

// Invoke DeadlockCheck() iff we're in debug mode and
// deadlock checking has been enabled.
static inline GraphId DebugOnlyDeadlockCheck(Mutex* mu) { __builtin_trap() /* STUB: not implemented */; }

void Mutex::ForgetDeadlockInfo() { __builtin_trap() /* STUB: not implemented */; }

void Mutex::AssertNotHeld() const { __builtin_trap() /* STUB: not implemented */; }

// Attempt to acquire *mu, and return whether successful.  The implementation
// may spin for a short while if the lock cannot be acquired immediately.
static bool TryAcquireWithSpinning(std::atomic<intptr_t>* mu) { __builtin_trap() /* STUB: not implemented */; }

void Mutex::lock() { __builtin_trap() /* STUB: not implemented */; }

void Mutex::lock_shared() { __builtin_trap() /* STUB: not implemented */; }

bool Mutex::LockWhenCommon(const Condition& cond,
                           synchronization_internal::KernelTimeout t,
                           bool write) { __builtin_trap() /* STUB: not implemented */; }

bool Mutex::AwaitCommon(const Condition& cond, KernelTimeout t) { __builtin_trap() /* STUB: not implemented */; }

bool Mutex::try_lock() { __builtin_trap() /* STUB: not implemented */; }

ABSL_ATTRIBUTE_NOINLINE bool Mutex::TryLockSlow() { __builtin_trap() /* STUB: not implemented */; }

bool Mutex::try_lock_shared() { __builtin_trap() /* STUB: not implemented */; }

ABSL_ATTRIBUTE_NOINLINE bool Mutex::ReaderTryLockSlow() { __builtin_trap() /* STUB: not implemented */; }

void Mutex::unlock() { __builtin_trap() /* STUB: not implemented */; }

// Requires v to represent a reader-locked state.
static bool ExactlyOneReader(intptr_t v) { __builtin_trap() /* STUB: not implemented */; }

void Mutex::unlock_shared() { __builtin_trap() /* STUB: not implemented */; }

// Clears the designated waker flag in the mutex if this thread has blocked, and
// therefore may be the designated waker.
static intptr_t ClearDesignatedWakerMask(int flag) { __builtin_trap() /* STUB: not implemented */; }

// Conditionally ignores the existence of waiting writers if a reader that has
// already blocked once wakes up.
static intptr_t IgnoreWaitingWritersMask(int flag) { __builtin_trap() /* STUB: not implemented */; }

// Internal version of LockWhen().  See LockSlowWithDeadline()
ABSL_ATTRIBUTE_NOINLINE void Mutex::LockSlow(MuHow how, const Condition* cond,
                                             int flags) { __builtin_trap() /* STUB: not implemented */; }

// Compute cond->Eval() and tell race detectors that we do it under mutex mu.
static inline bool EvalConditionAnnotated(const Condition* cond, Mutex* mu,
                                          bool locking, bool trylock,
                                          bool read_lock) { __builtin_trap() /* STUB: not implemented */; }

// Compute cond->Eval() hiding it from race detectors.
// We are hiding it because inside of UnlockSlow we can evaluate a predicate
// that was just added by a concurrent Lock operation; Lock adds the predicate
// to the internal Mutex list without actually acquiring the Mutex
// (it only acquires the internal spinlock, which is rightfully invisible for
// tsan). As the result there is no tsan-visible synchronization between the
// addition and this thread. So if we would enable race detection here,
// it would race with the predicate initialization.
static inline bool EvalConditionIgnored(Mutex* mu, const Condition* cond) { __builtin_trap() /* STUB: not implemented */; }

// Internal equivalent of *LockWhenWithDeadline(), where
//   "t" represents the absolute timeout; !t.has_timeout() means "forever".
//   "how" is "kShared" (for ReaderLockWhen) or "kExclusive" (for LockWhen)
// In flags, bits are ored together:
// - kMuHasBlocked indicates that the client has already blocked on the call so
//   the designated waker bit must be cleared and waiting writers should not
//   obstruct this call
// - kMuIsCond indicates that this is a conditional acquire (condition variable,
//   Await,  LockWhen) so contention profiling should be suppressed.
bool Mutex::LockSlowWithDeadline(MuHow how, const Condition* cond,
                                 KernelTimeout t, int flags) { __builtin_trap() /* STUB: not implemented */; }

// RAW_CHECK_FMT() takes a condition, a printf-style format string, and
// the printf-style argument list.   The format string must be a literal.
// Arguments after the first are not evaluated unless the condition is true.
#define RAW_CHECK_FMT(cond, ...)                                   \
  do {                                                             \
    if (ABSL_PREDICT_FALSE(!(cond))) {                             \
      ABSL_RAW_LOG(FATAL, "Check " #cond " failed: " __VA_ARGS__); \
    }                                                              \
  } while (0)

static void CheckForMutexCorruption(intptr_t v, const char* label) { __builtin_trap() /* STUB: not implemented */; }

void Mutex::LockSlowLoop(SynchWaitParams* waitp, int flags) { __builtin_trap() /* STUB: not implemented */; }

// Unlock this mutex, which is held by the current thread.
// If waitp is non-zero, it must be the wait parameters for the current thread
// which holds the lock but is not runnable because its condition is false
// or it is in the process of blocking on a condition variable; it must requeue
// itself on the mutex/condvar to wait for its condition to become true.
ABSL_ATTRIBUTE_NOINLINE void Mutex::UnlockSlow(SynchWaitParams* waitp) { __builtin_trap() /* STUB: not implemented */; }

// Used by CondVar implementation to reacquire mutex after waking from
// condition variable.  This routine is used instead of Lock() because the
// waiting thread may have been moved from the condition variable queue to the
// mutex queue without a wakeup, by Trans().  In that case, when the thread is
// finally woken, the woken thread will believe it has been woken from the
// condition variable (i.e. its PC will be in when in the CondVar code), when
// in fact it has just been woken from the mutex.  Thus, it must enter the slow
// path of the mutex in the same state as if it had just woken from the mutex.
// That is, it must ensure to clear kMuDesig (INV1b).
void Mutex::Trans(MuHow how) { __builtin_trap() /* STUB: not implemented */; }

// Used by CondVar implementation to effectively wake thread w from the
// condition variable.  If this mutex is free, we simply wake the thread.
// It will later acquire the mutex with high probability.  Otherwise, we
// enqueue thread w on this mutex.
void Mutex::Fer(PerThreadSynch* w) { __builtin_trap() /* STUB: not implemented */; }

void Mutex::AssertHeld() const { __builtin_trap() /* STUB: not implemented */; }

void Mutex::AssertReaderHeld() const { __builtin_trap() /* STUB: not implemented */; }

// -------------------------------- condition variables
static const intptr_t kCvSpin = 0x0001L;   // spinlock protects waiter list
static const intptr_t kCvEvent = 0x0002L;  // record events

static const intptr_t kCvLow = 0x0003L;  // low order bits of CV

// Hack to make constant values available to gdb pretty printer
enum {
  kGdbCvSpin = kCvSpin,
  kGdbCvEvent = kCvEvent,
  kGdbCvLow = kCvLow,
};

static_assert(PerThreadSynch::kAlignment > kCvLow,
              "PerThreadSynch::kAlignment must be greater than kCvLow");

void CondVar::EnableDebugLog(const char* name) { __builtin_trap() /* STUB: not implemented */; }

// Remove thread s from the list of waiters on this condition variable.
void CondVar::Remove(PerThreadSynch* s) { __builtin_trap() /* STUB: not implemented */; }

// Queue thread waitp->thread on condition variable word cv_word using
// wait parameters waitp.
// We split this into a separate routine, rather than simply doing it as part
// of WaitCommon().  If we were to queue ourselves on the condition variable
// before calling Mutex::UnlockSlow(), the Mutex code might be re-entered (via
// the logging code, or via a Condition function) and might potentially attempt
// to block this thread.  That would be a problem if the thread were already on
// a condition variable waiter queue.  Thus, we use the waitp->cv_word to tell
// the unlock code to call CondVarEnqueue() to queue the thread on the condition
// variable queue just before the mutex is to be unlocked, and (most
// importantly) after any call to an external routine that might re-enter the
// mutex code.
static void CondVarEnqueue(SynchWaitParams* waitp) { __builtin_trap() /* STUB: not implemented */; }

bool CondVar::WaitCommon(Mutex* mutex, KernelTimeout t) { __builtin_trap() /* STUB: not implemented */; }

void CondVar::Signal() { __builtin_trap() /* STUB: not implemented */; }

void CondVar::SignalAll() { __builtin_trap() /* STUB: not implemented */; }

void ReleasableMutexLock::Release() { __builtin_trap() /* STUB: not implemented */; }

#ifdef ABSL_HAVE_THREAD_SANITIZER
extern "C" void __tsan_read1(void* addr);
#else
#define __tsan_read1(addr)  // do nothing if TSan not enabled
#endif

// A function that just returns its argument, dereferenced
static bool Dereference(void* arg) { __builtin_trap() /* STUB: not implemented */; }

ABSL_CONST_INIT const Condition Condition::kTrue;

Condition::Condition(bool (*func)(void*), void* arg)
    : eval_(&CallVoidPtrFunction), arg_(arg) { __builtin_trap() /* STUB: not implemented */; }

bool Condition::CallVoidPtrFunction(const Condition* c) { __builtin_trap() /* STUB: not implemented */; }

Condition::Condition(const bool* cond)
    : eval_(CallVoidPtrFunction),
      // const_cast is safe since Dereference does not modify arg
      arg_(const_cast<bool*>(cond)) { __builtin_trap() /* STUB: not implemented */; }

bool Condition::Eval() const { __builtin_trap() /* STUB: not implemented */; }

bool Condition::GuaranteedEqual(const Condition* a, const Condition* b) { __builtin_trap() /* STUB: not implemented */; }

ABSL_NAMESPACE_END
}  // namespace absl
