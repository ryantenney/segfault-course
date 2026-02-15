// Exercise 04: Thread-safe Pool
//
// PROBLEM:
//   In a multi-threaded server, many threads share one pool. Without
//   synchronization, concurrent acquire/release calls corrupt the
//   internal data structure. A mutex protects the pool; a condition
//   variable lets threads block when the pool is empty instead of
//   throwing immediately.
//
// TODO:
//   Implement ThreadSafePool<T>:
//     1. Constructor: takes a vector<T> of initial objects.
//     2. acquire() -- lock the mutex, wait on the cv until an object
//        is available, pop and return it.
//     3. release(T obj) -- lock the mutex, push the object back,
//        notify one waiting thread.
//     4. available() -- return current count (under lock).
//
// HINT:
//   - Use std::unique_lock with cv_.wait() and a predicate that checks
//     !objects_.empty().
//   - release() should notify_one() after pushing.

#pragma once

#include <condition_variable>
#include <mutex>
#include <vector>
#include <testkit/testkit.h>

template <typename T>
class ThreadSafePool {
    std::mutex mtx_;
    std::condition_variable cv_;
    std::vector<T> objects_;

public:
    // Stock the pool with initial objects.
    explicit ThreadSafePool(std::vector<T> initial)
        : objects_(std::move(initial)) {}

    // Acquire an object, blocking until one is available.
    T acquire() {
        TODO();
    }

    // Return an object to the pool and wake one waiting thread.
    void release(T obj) {
        TODO();
    }

    // Return the number of currently available objects.
    std::size_t available() {
        std::lock_guard<std::mutex> lock(mtx_);
        return objects_.size();
    }
};
