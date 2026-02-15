// Exercise 03: Multi-event Dispatcher
//
// PROBLEM:
//   A real event system handles many different event types — "click",
//   "hover", "submit", etc. The dispatcher uses an event name (string)
//   as a key and keeps a separate list of callbacks for each event.
//
// TODO:
//   Implement Dispatcher:
//     1. on(event_name, callback) -- register a callback for a named event.
//     2. emit(event_name) -- invoke all callbacks registered for that
//        event, in registration order. If no listeners exist for the
//        event, do nothing.
//     3. listener_count(event_name) -- number of listeners for that event.
//
// HINT:
//   - Use std::unordered_map<std::string, std::vector<std::function<void()>>>.
//   - operator[] on the map auto-inserts an empty vector if the key
//     is missing, which can be handy.

#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>
#include <testkit/testkit.h>

class Dispatcher {
    std::unordered_map<std::string, std::vector<std::function<void()>>>
        listeners_;

public:
    // Register a callback for a named event.
    void on(const std::string& event_name, std::function<void()> callback) {
        TODO();
    }

    // Invoke all callbacks registered for the given event.
    void emit(const std::string& event_name) {
        TODO();
    }

    // Return the number of listeners for the given event.
    std::size_t listener_count(const std::string& event_name) const {
        TODO();
    }
};
