// Exercise 06: Spinlock with Backoff
//
// PROBLEM:
//   A naive spinlock hammers the CPU by spinning in a tight loop on
//   test_and_set(). This wastes power and can hurt performance on
//   hyper-threaded cores because the spinning thread monopolizes the
//   execution unit.
//
//   A simple improvement: call std::this_thread::yield() inside the
//   spin loop. yield() tells the OS scheduler that this thread has
//   nothing useful to do right now, allowing other threads (including
//   the one holding the lock) to run.
//
// TODO:
//   Implement the BackoffSpinlock class:
//     1. lock() -- spin on test_and_set(), calling yield() on each failed
//        attempt.
//     2. unlock() -- clear the flag.
//
// HINT:
//   - The structure is identical to Exercise 03, but add a yield() call
//     inside the spin loop.
//   - std::this_thread::yield() is in <thread>.

#pragma once

#include <atomic>
#include <thread>
#include <testkit/testkit.h>

class BackoffSpinlock {
    std::atomic_flag flag_ = ATOMIC_FLAG_INIT;

public:
    // Acquire the lock. Yields on contention.
    void lock() {
        TODO();
    }

    // Release the lock.
    void unlock() {
        TODO();
    }
};
