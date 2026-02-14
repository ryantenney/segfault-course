// Exercise 01: Basic Wait/Notify
//
// PROBLEM:
//   std::condition_variable lets one thread wait until another thread signals
//   that something has happened. It always works together with a std::mutex
//   and a shared predicate (a bool or similar flag).
//
//   The basic pattern:
//     - The waiting thread locks the mutex, then calls cv.wait(lock).
//     - The notifying thread locks the mutex, sets the flag, unlocks, then
//       calls cv.notify_one() or cv.notify_all().
//
// TODO:
//   Implement the Notifier class:
//     1. notify()  -- set the ready flag to true, then notify one waiter.
//     2. wait()    -- block until the ready flag is true.
//
// HINT:
//   - Protect the flag with a std::mutex.
//   - In wait(), use a std::unique_lock and cv.wait() with a predicate
//     lambda that checks the flag.
//   - In notify(), lock the mutex, set the flag, unlock, and call
//     cv.notify_one().

#pragma once

#include <condition_variable>
#include <mutex>
#include <testkit/testkit.h>

class Notifier {
    std::mutex mtx_;
    std::condition_variable cv_;
    bool ready_ = false;

public:
    // Signal that the event has occurred.
    // Sets the ready flag to true and wakes one waiting thread.
    void notify() {
        TODO();
    }

    // Block until the ready flag is true.
    void wait() {
        TODO();
    }

    // Returns the current value of the ready flag (for testing).
    bool is_ready() {
        std::lock_guard<std::mutex> lock(mtx_);
        return ready_;
    }
};
