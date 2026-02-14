// Exercise 01: Callback Registration
//
// std::function<R(Args...)> is a general-purpose polymorphic function wrapper.
// It can hold any callable target: lambdas, function pointers, functors, or
// the result of std::bind. This makes it ideal for callback-based APIs where
// the caller decides what code runs.
//
// Basic usage:
//   std::function<void(int)> cb = [](int x) { /* ... */ };
//   cb(42);  // invoke the stored callable
//
// A default-constructed std::function is empty. Calling an empty
// std::function throws std::bad_function_call.
//
// TODO:
//   1. Implement register_callback() — store the given callback.
//   2. Implement fire() — invoke the stored callback with the given value.
//   3. Implement has_callback() — return whether a callback is registered.

#pragma once

#include <testkit/testkit.h>
#include <functional>

class CallbackHolder {
    std::function<void(int)> callback_;

public:
    // Store `cb` as the callback.
    inline void register_callback(std::function<void(int)> cb) {
        TODO();
    }

    // Invoke the stored callback with `value`.
    // If no callback is registered, do nothing.
    inline void fire(int value) {
        TODO();
    }

    // Return true if a callback is currently registered.
    inline bool has_callback() const {
        TODO();
    }
};
