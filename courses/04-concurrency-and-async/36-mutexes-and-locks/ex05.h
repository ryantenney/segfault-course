// Exercise 05: Timed Lock
//
// PROBLEM:
//   std::timed_mutex supports try_lock_for() — attempt to acquire
//   the lock, but give up after a timeout. This is useful when you
//   want bounded waiting.
//
// TODO:
//   Implement try_lock_for_ms() that:
//   1. Creates a unique_lock with a try_lock_for duration of `ms`
//      milliseconds on w.mutex().
//   2. If the lock was acquired, set w.value() to 1 and return true.
//   3. If the timeout expired, return false without modifying the value.
//
// HINT:
//   std::unique_lock<std::timed_mutex> lock(w.mutex(),
//       std::chrono::milliseconds(ms));
//   if (lock.owns_lock()) { ... }
//
// WHY:
//   In real systems, waiting forever for a lock is often unacceptable.
//   Timed locks let you implement timeouts, fallback strategies, and
//   health monitoring.

#pragma once
#include <testkit/testkit.h>
#include <chrono>
#include <mutex>

class TimedMutexWrapper {
    int value_ = 0;
    std::timed_mutex mtx_;

public:
    std::timed_mutex& mutex() { return mtx_; }
    int value() const { return value_; }
    void set_value(int v) { value_ = v; }
};

// Tries to acquire the lock for `ms` milliseconds.
// If acquired, sets w.value() to 1 and returns true.
// If timeout expires, returns false.
inline bool try_lock_for_ms(TimedMutexWrapper& w, int ms) {
    TODO();
}
