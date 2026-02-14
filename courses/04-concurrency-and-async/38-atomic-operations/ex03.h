// Exercise 03: Atomic Flag Spinlock
//
// PROBLEM:
//   std::atomic_flag is the most primitive atomic type. It supports exactly
//   two operations: test_and_set() and clear(). Unlike std::atomic<bool>,
//   it is guaranteed to be lock-free on every platform.
//
//   A spinlock is the simplest possible mutex: lock() spins in a loop
//   calling test_and_set() until it succeeds, and unlock() calls clear().
//
//   Spinlocks are useful when the critical section is very short and
//   contention is low. For longer critical sections, use std::mutex.
//
// TODO:
//   Implement the Spinlock class:
//     1. lock() -- spin until test_and_set() returns false (meaning
//        we acquired the lock).
//     2. unlock() -- clear the flag.
//
// HINT:
//   - std::atomic_flag starts in a clear state with ATOMIC_FLAG_INIT or
//     value-initialization.
//   - test_and_set() atomically sets the flag and returns the OLD value.
//     If the old value was false, you acquired the lock.
//   - clear() releases the lock.

#pragma once

#include <atomic>
#include <testkit/testkit.h>

class Spinlock {
    std::atomic_flag flag_ = ATOMIC_FLAG_INIT;

public:
    // Acquire the lock. Spins until successful.
    void lock() {
        TODO();
    }

    // Release the lock.
    void unlock() {
        TODO();
    }
};
