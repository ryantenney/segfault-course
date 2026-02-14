// Exercise 03: Scoped Lock for Multiple Mutexes
//
// PROBLEM:
//   When you need to lock two (or more) mutexes at the same time,
//   locking them one at a time risks deadlock if another thread locks
//   them in the opposite order. std::scoped_lock (C++17) locks multiple
//   mutexes simultaneously using a deadlock-avoidance algorithm.
//
// TODO:
//   Implement safe_swap() that swaps the values inside two LockedBox
//   objects. Use std::scoped_lock to lock both mutexes at once.
//
// HINT:
//   std::scoped_lock lock(a.mutex(), b.mutex());
//   std::swap(a.value(), b.value());
//
// WHY:
//   Deadlock is one of the hardest concurrency bugs to debug. It
//   happens when two threads each hold one lock and wait for the other.
//   std::scoped_lock eliminates this by locking all mutexes atomically
//   using std::lock() internally.

#pragma once
#include <testkit/testkit.h>
#include <mutex>

class LockedBox {
    int value_;
    mutable std::mutex mtx_;

public:
    explicit LockedBox(int v) : value_(v) {}

    std::mutex& mutex() const { return mtx_; }
    int& value() { return value_; }
    int value() const { return value_; }
};

// Swaps the values of a and b, locking both mutexes with scoped_lock.
inline void safe_swap(LockedBox& a, LockedBox& b) {
    TODO();
}
