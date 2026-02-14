// Exercise 04: Store Callbacks in a Container
//
// Since std::function is a regular type (copyable, movable, assignable), you
// can store multiple callbacks in a std::vector and invoke them all — this is
// the observer/listener pattern.
//
// Example:
//   std::vector<std::function<void(int)>> listeners;
//   listeners.push_back([](int x) { std::cout << x; });
//   for (auto& fn : listeners) fn(42);  // invoke all
//
// TODO:
//   1. Implement subscribe() — add a callback to the list.
//   2. Implement notify() — invoke every stored callback with the given value.
//   3. Implement subscriber_count() — return how many callbacks are registered.
//   4. Implement clear() — remove all callbacks.

#pragma once

#include <testkit/testkit.h>
#include <functional>
#include <vector>
#include <string>

class EventBus {
    std::vector<std::function<void(const std::string&)>> subscribers_;

public:
    // Add a callback to the subscriber list.
    inline void subscribe(std::function<void(const std::string&)> cb) {
        TODO();
    }

    // Invoke every subscriber with `message`.
    inline void notify(const std::string& message) {
        TODO();
    }

    // Return the number of registered subscribers.
    inline std::size_t subscriber_count() const {
        TODO();
    }

    // Remove all subscribers.
    inline void clear() {
        TODO();
    }
};
