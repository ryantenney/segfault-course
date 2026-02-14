// Exercise 01: Fixed Thread Vector
//
// PROBLEM:
//   Implement BasicPool that creates N std::jthread worker threads.
//   The threads should wait on a condition variable (idle loop) and
//   stop cleanly when the pool is destroyed. Provide a size() method
//   returning the number of threads.
//
// TODO:
//   1. Implement the constructor to create N threads.
//   2. Implement size() to return the thread count.
//   3. Implement the gate() helper (called by tests to check TODO state).
//
// WHY:
//   A thread pool starts with a fixed number of pre-created threads.
//   Using std::jthread ensures automatic joining on destruction — the
//   threads request-stop and join without explicit cleanup code.

#pragma once
#include <testkit/testkit.h>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

class BasicPool {
    std::vector<std::jthread> workers_;
    std::mutex mutex_;
    std::condition_variable_any cv_;

public:
    // Creates a pool with `n` worker threads.
    // Each thread should loop: lock the mutex, wait on the cv with a
    // stop_token check, and exit when stop is requested.
    explicit BasicPool(std::size_t n) {
        gate();  // gates on TODO() — safe before any threads are launched
        for (std::size_t i = 0; i < n; ++i) {
            workers_.emplace_back([this](std::stop_token st) {
                std::unique_lock lock(mutex_);
                cv_.wait(lock, st, [&st] { return st.stop_requested(); });
            });
        }
    }

    // No TODO() in destructor — noexcept by default.
    ~BasicPool() {
        cv_.notify_all();
        // jthreads auto-join and request stop.
    }

    // Returns the number of threads in the pool.
    std::size_t size() const {
        return workers_.size();
    }

    // Gate function: tests call this first to trigger TODO() before
    // any concurrent code runs.
    void gate() {
        TODO();
    }

    // Non-copyable, non-movable.
    BasicPool(const BasicPool&) = delete;
    BasicPool& operator=(const BasicPool&) = delete;
};
