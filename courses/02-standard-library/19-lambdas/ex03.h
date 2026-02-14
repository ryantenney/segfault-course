// Exercise 03: Capture by Value
//
// By default, capture by value creates a const copy of the variable
// inside the lambda. To modify the copy, use the `mutable` keyword:
//
//   int x = 10;
//   auto fn = [x]() mutable {
//       ++x;        // modifies the lambda's own copy
//       return x;
//   };
//   fn();           // returns 11
//   fn();           // returns 12
//   // x is still 10 -- the original is unchanged
//
// Key insight: the lambda's captured copy is independent of the original
// variable. Successive calls to a mutable lambda accumulate state inside
// the lambda without affecting the outside world.
//
// TODO:
//   1. Implement make_counter() -- return a lambda that captures an
//      initial value by value (mutable) and returns it incremented
//      on each call.
//   2. Implement demonstrate_value_capture() -- capture `value` by value,
//      call the lambda `n` times. Return a pair of (lambda's final
//      return value, original value). The original must be unchanged.
//   3. Implement accumulate_calls() -- return a lambda that captures an
//      initial string by value (mutable) and appends each argument
//      to it, returning the accumulated string.

#pragma once

#include <functional>
#include <string>
#include <utility>
#include <testkit/testkit.h>

// Return a lambda that starts from `start` and returns the current
// value, incrementing it each time it is called.
// First call returns `start`, second returns `start + 1`, etc.
inline std::function<int()> make_counter(int start) {
    TODO();
}

// Capture `value` by value in a mutable lambda that increments its copy.
// Call the lambda `n` times. Return {last lambda return value, original value}.
inline std::pair<int, int> demonstrate_value_capture(int value, int n) {
    TODO();
}

// Return a lambda that captures `initial` by value (mutable) and
// appends each string argument to it, returning the accumulated result.
inline std::function<std::string(const std::string&)> accumulate_calls(
        std::string initial) {
    TODO();
}
