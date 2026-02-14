// Exercise 03: Scoped Lock (Manual)
//
// PROBLEM:
//   If you lock a mutex and forget to unlock it (or an exception fires
//   before you reach the unlock), the mutex stays locked forever and
//   your program deadlocks. RAII ensures the mutex is always unlocked
//   when the guard goes out of scope.
//
// TODO:
//   Implement ScopedLock:
//   - Constructor: call mtx.lock()
//   - Destructor: call mtx.unlock()
//   This is a simplified version of std::lock_guard.
//
// WHY:
//   std::lock_guard and std::unique_lock are RAII wrappers around
//   mutexes. Building one yourself shows why RAII is the standard
//   pattern for mutex management in C++.

#pragma once
#include <mutex>
#include <string>
#include <testkit/testkit.h>

class ScopedLock {
    // TODO: Add a reference to a std::mutex
public:
    // Lock the mutex.
    explicit ScopedLock(std::mutex& mtx) {
        TODO();
    }

    // Unlock the mutex.
    ~ScopedLock() {
        // TODO: call unlock() on the stored mutex reference
    }

    // Non-copyable
    ScopedLock(const ScopedLock&) = delete;
    ScopedLock& operator=(const ScopedLock&) = delete;
};

// A thread-safe counter using ScopedLock.
class SafeCounter {
    int value_ = 0;
    mutable std::mutex mtx_;
public:
    void increment() {
        TODO();
        // HINT: Create a ScopedLock, then modify value_
    }

    int get() const {
        TODO();
        // HINT: Create a ScopedLock, then return value_
    }
};
