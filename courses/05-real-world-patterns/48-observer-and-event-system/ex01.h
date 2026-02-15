// Exercise 01: Simple Event Emitter
//
// PROBLEM:
//   An event emitter lets you register callback functions and then
//   invoke them all when something interesting happens. This is the
//   foundation of the Observer pattern: the emitter (subject) does not
//   know who is listening; it just fires the event.
//
// TODO:
//   Implement Emitter:
//     1. on(callback) -- register a std::function<void()> to be called
//        on emit. Store it in a vector.
//     2. emit() -- call all registered callbacks in order.
//     3. listener_count() -- return the number of registered listeners.
//
// HINT:
//   - A simple std::vector<std::function<void()>> is all you need.

#pragma once

#include <functional>
#include <vector>
#include <testkit/testkit.h>

class Emitter {
    std::vector<std::function<void()>> listeners_;

public:
    // Register a callback to be invoked on emit().
    void on(std::function<void()> callback) {
        TODO();
    }

    // Invoke all registered callbacks in registration order.
    void emit() {
        TODO();
    }

    // Return the number of registered listeners.
    std::size_t listener_count() const {
        TODO();
    }
};
