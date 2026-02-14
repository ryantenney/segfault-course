// Exercise 01: Throw and Catch
//
// C++ uses exceptions for error handling in many standard library operations.
// You throw an exception with `throw` and catch it with try/catch.
//
// std::runtime_error is the most common exception type for general errors.
// It takes a string message and inherits from std::exception.
//
// TODO:
//   1. Implement divide() — return a / b, but throw std::runtime_error
//      with message "division by zero" if b is 0.
//   2. Implement safe_divide() — call divide() inside a try/catch.
//      On success, return the result. If a runtime_error is caught,
//      return -1.

#pragma once

#include <stdexcept>
#include <testkit/testkit.h>

// Divide a by b. Throw std::runtime_error("division by zero") if b is 0.
inline int divide(int a, int b) {
    TODO();
}

// Call divide(a, b) and return the result.
// If divide throws std::runtime_error, catch it and return -1.
inline int safe_divide(int a, int b) {
    TODO();
}
