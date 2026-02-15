// Exercise 07: Event Filtering
//
// PROBLEM:
//   Not every listener cares about every event. A filtering emitter
//   lets each subscriber provide a predicate: the callback is only
//   invoked if the predicate returns true for the emitted value.
//
// TODO:
//   Implement FilterEmitter<T>:
//     1. on(predicate, callback) -- register a callback that is only
//        called when predicate(value) returns true.
//     2. emit(value) -- for each entry, if predicate(value) is true,
//        call the callback with value.
//     3. listener_count() -- total registered listeners (regardless
//        of filter).
//
// HINT:
//   - Store a vector of structs, each holding a predicate
//     (std::function<bool(const T&)>) and a callback
//     (std::function<void(const T&)>).

#pragma once

#include <functional>
#include <vector>
#include <testkit/testkit.h>

template <typename T>
class FilterEmitter {
    struct Entry {
        std::function<bool(const T&)> predicate;
        std::function<void(const T&)> callback;
    };
    std::vector<Entry> listeners_;

public:
    // Register a callback that fires only when predicate is true.
    void on(std::function<bool(const T&)> predicate,
            std::function<void(const T&)> callback) {
        TODO();
    }

    // Emit a value; only matching listeners are notified.
    void emit(const T& value) {
        TODO();
    }

    // Total number of registered listeners.
    std::size_t listener_count() const {
        TODO();
    }
};
