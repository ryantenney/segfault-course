// Exercise 02: Atomic Load/Store
//
// PROBLEM:
//   std::atomic provides explicit load() and store() member functions that
//   make it clear you're performing an atomic operation. These are preferred
//   over implicit conversions in production code because they make the intent
//   obvious and allow you to specify a memory order.
//
//     std::atomic<bool> flag{false};
//     flag.store(true);          // atomic store
//     bool val = flag.load();    // atomic load
//
// TODO:
//   Implement the AtomicFlag class:
//     1. set() -- atomically store true.
//     2. clear() -- atomically store false.
//     3. is_set() -- atomically load and return the value.
//
// HINT:
//   - Use store() and load() explicitly.
//   - std::atomic<bool> is the right type here.

#pragma once

#include <atomic>
#include <testkit/testkit.h>

class AtomicFlag {
    std::atomic<bool> flag_{false};

public:
    // Atomically set the flag to true.
    void set() {
        TODO();
    }

    // Atomically set the flag to false.
    void clear() {
        TODO();
    }

    // Atomically load and return the flag value.
    bool is_set() {
        TODO();
    }
};
