// Exercise 04: Work Queue
//
// PROBLEM:
//   A work queue is similar to a bounded buffer but with an unbounded size
//   and a shutdown mechanism. Worker threads call pop() to get the next task.
//   When there's no more work, the owner calls shutdown() so that all blocked
//   pop() calls return a sentinel (empty optional).
//
//   This is the backbone of thread pool implementations.
//
// TODO:
//   Implement WorkQueue<T>:
//     1. push(T item) -- add an item to the queue and wake one waiter.
//     2. pop() -- block until an item is available or shutdown is called.
//        Return std::optional<T>: the item if available, or std::nullopt
//        if the queue is shut down and empty.
//     3. shutdown() -- signal that no more items will be pushed.
//        Wake all waiting threads.
//     4. is_shutdown() -- return whether shutdown has been called.
//
// HINT:
//   - pop() should return items even after shutdown, as long as the queue
//     is not empty. Only return nullopt when shut down AND empty.

#pragma once

#include <condition_variable>
#include <mutex>
#include <optional>
#include <queue>
#include <testkit/testkit.h>

template <typename T>
class WorkQueue {
    std::mutex mtx_;
    std::condition_variable cv_;
    std::queue<T> queue_;
    bool shutdown_ = false;

public:
    // Add an item to the queue and wake one waiter.
    void push(T item) {
        TODO();
    }

    // Remove and return the front item. Blocks if the queue is empty.
    // Returns std::nullopt if the queue is shut down and empty.
    std::optional<T> pop() {
        TODO();
    }

    // Signal that no more items will be pushed. Wake all waiters.
    void shutdown() {
        TODO();
    }

    // Returns true if shutdown() has been called.
    bool is_shutdown() {
        std::lock_guard<std::mutex> lock(mtx_);
        return shutdown_;
    }
};
