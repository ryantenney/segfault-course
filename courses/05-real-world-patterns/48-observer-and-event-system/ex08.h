// Exercise 08: Ordered Dispatch
//
// PROBLEM:
//   Some systems guarantee that listeners are notified in the exact
//   order they subscribed. This matters when listeners depend on each
//   other (e.g., a logger must run before a metrics collector that
//   reads the logger's output).
//
//   In this exercise, each listener has an explicit priority (lower
//   number = called first). Listeners with the same priority are
//   called in registration order.
//
// TODO:
//   Implement OrderedEmitter:
//     1. on(priority, callback) -- register a callback with an integer
//        priority. Lower priority values are invoked first.
//     2. emit() -- invoke callbacks sorted by priority, then by
//        registration order within the same priority.
//     3. listener_count() -- number of registered listeners.
//
// HINT:
//   - Store entries with (priority, sequence_number, callback).
//   - Sort by (priority, sequence_number) before invoking.
//   - Alternatively, keep them sorted on insertion.

#pragma once

#include <algorithm>
#include <cstdint>
#include <functional>
#include <vector>
#include <testkit/testkit.h>

class OrderedEmitter {
    struct Entry {
        int priority;
        uint64_t sequence;
        std::function<void()> callback;
    };
    std::vector<Entry> listeners_;
    uint64_t next_seq_ = 0;

public:
    // Register a callback with a given priority (lower = called first).
    void on(int priority, std::function<void()> callback) {
        TODO();
    }

    // Invoke all callbacks in priority order (then registration order).
    void emit() {
        TODO();
    }

    // Number of registered listeners.
    std::size_t listener_count() const {
        TODO();
    }
};
