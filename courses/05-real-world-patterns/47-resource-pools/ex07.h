// Exercise 07: Pool with Timeout
//
// PROBLEM:
//   Blocking forever on an empty pool is dangerous in production. A
//   timeout-based pool waits up to N milliseconds for a resource to
//   become available. If the timeout expires, it returns std::nullopt
//   instead of blocking indefinitely.
//
// TODO:
//   Implement TimeoutPool<T>:
//     1. Constructor: takes a vector<T> of initial objects.
//     2. try_acquire(std::chrono::milliseconds timeout) -- lock the
//        mutex, wait on the cv with the given timeout. If an object
//        becomes available before the timeout, pop and return it.
//        Otherwise return std::nullopt.
//     3. release(T obj) -- push back and notify one waiter.
//     4. available() -- current count (under lock).
//
// HINT:
//   - Use cv_.wait_for(lock, timeout, predicate). It returns the
//     predicate result (true if woken because predicate was satisfied,
//     false if timed out).

#pragma once

#include <chrono>
#include <condition_variable>
#include <mutex>
#include <optional>
#include <vector>
#include <testkit/testkit.h>

template <typename T>
class TimeoutPool {
    std::mutex mtx_;
    std::condition_variable cv_;
    std::vector<T> objects_;

public:
    // Stock the pool with initial objects.
    explicit TimeoutPool(std::vector<T> initial)
        : objects_(std::move(initial)) {}

    // Try to acquire an object within the given timeout.
    // Returns the object, or std::nullopt if the timeout expired.
    std::optional<T> try_acquire(std::chrono::milliseconds timeout) {
        TODO();
    }

    // Return an object to the pool and wake one waiter.
    void release(T obj) {
        TODO();
    }

    // Number of currently available objects.
    std::size_t available() {
        std::lock_guard<std::mutex> lock(mtx_);
        return objects_.size();
    }
};
