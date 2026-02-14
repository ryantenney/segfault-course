// Exercise 06: notify_one vs notify_all (Barrier)
//
// PROBLEM:
//   - notify_one() wakes exactly one waiting thread (chosen by the OS).
//   - notify_all() wakes ALL waiting threads.
//
//   A barrier is a synchronization point where a group of threads must
//   all arrive before any of them can proceed. This requires notify_all()
//   because every waiting thread needs to wake up.
//
// TODO:
//   Implement the Barrier class:
//     1. Constructor takes the number of threads (count).
//     2. arrive_and_wait() -- increment the arrival count, then:
//        - If this is the last thread to arrive, notify all waiters.
//        - Otherwise, wait until all threads have arrived.
//
// HINT:
//   - Track the number of arrivals.
//   - The predicate for wait should check if arrivals == expected count.
//   - The last arriving thread must call notify_all(), not notify_one().

#pragma once

#include <condition_variable>
#include <cstddef>
#include <mutex>
#include <testkit/testkit.h>

class Barrier {
    std::mutex mtx_;
    std::condition_variable cv_;
    std::size_t expected_;
    std::size_t arrived_ = 0;

public:
    explicit Barrier(std::size_t count) : expected_(count) {}

    // Called by each thread. Blocks until all threads have arrived.
    void arrive_and_wait() {
        TODO();
    }

    // Returns the number of threads that have arrived so far (for testing).
    std::size_t arrived() {
        std::lock_guard<std::mutex> lock(mtx_);
        return arrived_;
    }
};
