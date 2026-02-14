// Exercise 01: Protect Shared Data
//
// PROBLEM:
//   Implement a thread-safe counter using std::mutex and
//   std::lock_guard. The lock_guard acquires the mutex on construction
//   and releases it on destruction (RAII).
//
// TODO:
//   1. Implement increment() — lock the mutex with lock_guard, then ++value_.
//   2. Implement decrement() — lock the mutex with lock_guard, then --value_.
//   3. Implement get() — lock the mutex with lock_guard, then return value_.
//
// WHY:
//   std::lock_guard is the simplest RAII lock wrapper. It's the
//   go-to choice when you need to hold a mutex for an entire scope.
//   It cannot be unlocked early or moved — that simplicity is its
//   strength, because there's nothing to get wrong.

#pragma once
#include <testkit/testkit.h>
#include <mutex>

class GuardedCounter {
    int value_ = 0;
    mutable std::mutex mtx_;

public:
    // Increments value_ by 1 under the mutex.
    inline void increment() {
        TODO();
    }

    // Decrements value_ by 1 under the mutex.
    inline void decrement() {
        TODO();
    }

    // Returns value_ under the mutex.
    inline int get() const {
        TODO();
    }
};
