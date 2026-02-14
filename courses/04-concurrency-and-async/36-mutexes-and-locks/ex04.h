// Exercise 04: unique_lock Flexibility
//
// PROBLEM:
//   std::unique_lock is a more flexible alternative to lock_guard. It
//   supports deferred locking, try-locking, timed locking, and manual
//   lock/unlock. Here you'll use try_lock to attempt non-blocking
//   acquisition.
//
// TODO:
//   Implement try_process() that:
//   1. Creates a unique_lock with std::try_to_lock on q.mutex().
//   2. If the lock was acquired (check owns_lock()), pop the front
//      element from q.data() and return it.
//   3. If the lock was not acquired, return -1.
//   If the queue is empty (even if locked), return -1.
//
// WHY:
//   Sometimes you don't want to block waiting for a lock. try_lock
//   lets you attempt acquisition and do something else if the mutex
//   is busy. This is the foundation of lock-free-ish patterns and
//   responsive systems.

#pragma once
#include <testkit/testkit.h>
#include <deque>
#include <mutex>

class SharedQueue {
    std::deque<int> data_;
    mutable std::mutex mtx_;

public:
    void push(int v) {
        std::lock_guard<std::mutex> lock(mtx_);
        data_.push_back(v);
    }

    std::mutex& mutex() const { return mtx_; }
    std::deque<int>& data() { return data_; }
};

// Tries to acquire the lock and pop the front element.
// Returns the element, or -1 if the lock couldn't be acquired
// or the queue is empty.
inline int try_process(SharedQueue& q) {
    TODO();
}
