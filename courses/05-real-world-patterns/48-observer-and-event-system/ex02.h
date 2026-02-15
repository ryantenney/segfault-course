// Exercise 02: Subscription ID
//
// PROBLEM:
//   With only on() and emit(), you can never unsubscribe. In practice
//   you need to remove listeners (e.g., when a UI component is
//   destroyed). The solution: on() returns a unique subscription ID,
//   and off(id) removes that specific listener.
//
// TODO:
//   Implement IdEmitter:
//     1. on(callback) -- register a callback and return a unique
//        integer subscription ID (start at 1, increment).
//     2. off(id) -- remove the listener with the given ID. Return true
//        if it was found and removed, false otherwise.
//     3. emit() -- call all remaining callbacks in registration order.
//     4. listener_count() -- number of active listeners.
//
// HINT:
//   - Use a std::vector of pairs (id, callback) or a helper struct.
//   - For off(), you can use std::remove_if + erase (the erase-remove
//     idiom) or simply iterate and erase.

#pragma once

#include <cstdint>
#include <functional>
#include <vector>
#include <testkit/testkit.h>

class IdEmitter {
    struct Entry {
        uint64_t id;
        std::function<void()> callback;
    };
    std::vector<Entry> listeners_;
    uint64_t next_id_ = 1;

public:
    // Register a callback. Returns a unique subscription ID.
    uint64_t on(std::function<void()> callback) {
        TODO();
    }

    // Remove the listener with the given ID. Returns true if found.
    bool off(uint64_t id) {
        TODO();
    }

    // Invoke all registered callbacks in registration order.
    void emit() {
        TODO();
    }

    // Number of currently registered listeners.
    std::size_t listener_count() const {
        TODO();
    }
};
