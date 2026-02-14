// Exercise 07: Timed Wait
//
// PROBLEM:
//   Sometimes you don't want to wait forever. condition_variable::wait_for()
//   lets you specify a timeout. If the condition isn't met within the timeout,
//   it returns std::cv_status::timeout (or false with the predicate overload).
//
//   This is essential for building responsive systems that can detect stalls
//   or implement retry logic.
//
// TODO:
//   Implement the TimedEvent class:
//     1. signal() -- set the signaled flag and wake all waiters.
//     2. wait_for_ms(unsigned ms) -- wait up to `ms` milliseconds for
//        the event to be signaled. Return true if signaled, false if
//        timed out.
//
// HINT:
//   - Use cv.wait_for(lock, duration, predicate) which returns bool.
//   - std::chrono::milliseconds(ms) converts unsigned to a duration.

#pragma once

#include <chrono>
#include <condition_variable>
#include <mutex>
#include <testkit/testkit.h>

class TimedEvent {
    std::mutex mtx_;
    std::condition_variable cv_;
    bool signaled_ = false;

public:
    // Signal the event. Wake all waiters.
    void signal() {
        TODO();
    }

    // Wait up to `ms` milliseconds for the event to be signaled.
    // Returns true if signaled, false if timed out.
    bool wait_for_ms(unsigned ms) {
        TODO();
    }

    // Returns true if signal() has been called.
    bool is_signaled() {
        std::lock_guard<std::mutex> lock(mtx_);
        return signaled_;
    }
};
