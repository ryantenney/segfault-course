// Exercise 06: Fix the Data Race
//
// PROBLEM:
//   Implement a thread-safe counter class using a mutex. The mutex
//   ensures that only one thread can modify or read the counter at
//   a time, preventing data races.
//
// TODO:
//   1. Implement increment() — lock the mutex, then increment value_.
//   2. Implement get() — lock the mutex, then return value_.
//   Use std::lock_guard<std::mutex> for both.
//
// WHY:
//   While std::atomic works for individual variables, a mutex protects
//   arbitrary sections of code (critical sections). std::lock_guard is
//   an RAII wrapper that locks the mutex in its constructor and unlocks
//   in its destructor — so you can't forget to unlock.

#pragma once
#include <testkit/testkit.h>
#include <mutex>

class ThreadSafeCounter {
    int value_ = 0;
    std::mutex mtx_;

public:
    // Increments the counter by 1 under the mutex.
    inline void increment() {
        TODO();
    }

    // Returns the current value under the mutex.
    inline int get() {
        TODO();
    }
};
