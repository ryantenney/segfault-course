// Exercise 02: Predicate Wait
//
// PROBLEM:
//   A common bug with condition variables is the "spurious wakeup": the OS
//   may wake your thread even when no one called notify. The fix is to always
//   wait with a predicate -- the two-argument overload of cv.wait():
//
//     cv.wait(lock, [&]{ return some_condition; });
//
//   This is equivalent to:
//     while (!some_condition) cv.wait(lock);
//
//   The predicate is re-checked after every wakeup, guarding against
//   both spurious wakeups and early signals.
//
// TODO:
//   Implement PredicateNotifier:
//     1. set_value(int v) -- store the value and notify all waiters.
//     2. wait_for_value(int target) -- block until the stored value
//        equals target, using the predicate overload of wait().
//
// HINT:
//   - Use cv.wait(lock, predicate) where the predicate checks value_ == target.
//   - Use notify_all() so that waiters with different targets can all re-check.

#pragma once

#include <condition_variable>
#include <mutex>
#include <testkit/testkit.h>

class PredicateNotifier {
    std::mutex mtx_;
    std::condition_variable cv_;
    int value_ = 0;

public:
    // Set the internal value and wake all waiters.
    void set_value(int v) {
        TODO();
    }

    // Block until the internal value equals target.
    // Must use the predicate overload of cv.wait().
    void wait_for_value(int target) {
        TODO();
    }

    // Returns the current value (for testing).
    int get_value() {
        std::lock_guard<std::mutex> lock(mtx_);
        return value_;
    }
};
