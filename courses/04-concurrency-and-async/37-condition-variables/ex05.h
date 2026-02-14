// Exercise 05: One-shot Event
//
// PROBLEM:
//   A one-shot event (sometimes called a latch) is a synchronization
//   primitive that starts in an unsignaled state. Once signal() is called,
//   all current and future calls to wait() return immediately. Unlike a
//   Notifier, calling signal() multiple times is harmless.
//
//   This is conceptually similar to std::latch(1) from C++20, but we'll
//   build it from scratch with a condition variable.
//
// TODO:
//   Implement the Event class:
//     1. signal() -- set the signaled flag and wake all waiters.
//     2. wait() -- block until the event is signaled.
//     3. is_signaled() -- return whether signal() has been called.
//
// HINT:
//   - Use notify_all() in signal() so that multiple waiters all wake up.
//   - Use the predicate overload of cv.wait() in wait().

#pragma once

#include <condition_variable>
#include <mutex>
#include <testkit/testkit.h>

class Event {
    std::mutex mtx_;
    std::condition_variable cv_;
    bool signaled_ = false;

public:
    // Signal the event. All current and future waiters should unblock.
    void signal() {
        TODO();
    }

    // Block until the event has been signaled.
    void wait() {
        TODO();
    }

    // Returns true if signal() has been called.
    bool is_signaled() {
        std::lock_guard<std::mutex> lock(mtx_);
        return signaled_;
    }
};
