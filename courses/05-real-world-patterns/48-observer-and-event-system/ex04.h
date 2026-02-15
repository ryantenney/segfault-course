// Exercise 04: Event with Payload
//
// PROBLEM:
//   Events usually carry data. A "temperature_changed" event might carry
//   the new temperature; a "message_received" event carries the message
//   text. The emitter needs to be parameterized on the payload type.
//
// TODO:
//   Implement TypedEmitter<T>:
//     1. on(callback) -- register a std::function<void(const T&)>.
//     2. emit(value) -- call all callbacks with the given value.
//     3. listener_count() -- number of registered listeners.
//
// HINT:
//   - This is just a template version of the exercise 01 Emitter,
//     but the callback signature is void(const T&).

#pragma once

#include <functional>
#include <vector>
#include <testkit/testkit.h>

template <typename T>
class TypedEmitter {
    std::vector<std::function<void(const T&)>> listeners_;

public:
    // Register a callback that receives the emitted value.
    void on(std::function<void(const T&)> callback) {
        TODO();
    }

    // Emit an event with the given value to all listeners.
    void emit(const T& value) {
        TODO();
    }

    // Return the number of registered listeners.
    std::size_t listener_count() const {
        TODO();
    }
};
