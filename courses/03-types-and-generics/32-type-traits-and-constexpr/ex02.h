// Exercise 02: if constexpr Branching
//
// `if constexpr (condition)` evaluates the condition at compile time. The
// branch that is NOT taken is discarded entirely -- it doesn't even need to
// be valid code for the given type. This is how you write a single template
// function that does different things for different kinds of types.
//
// Without `if constexpr`, both branches must compile for every T. With it,
// only the taken branch is compiled, so you can safely call methods that only
// exist on certain types.
//
// TODO:
//   1. Implement stringify<T>(value):
//      - If T is arithmetic (std::is_arithmetic_v<T>), use
//        std::to_string(value) to convert it.
//      - If T is a std::string, return value directly.
//      - Otherwise, return the string "(unknown)".
//
//   2. Implement default_value<T>():
//      - If T is integral, return T{0}.
//      - If T is floating point, return T{0.0}.
//      - If T is a std::string, return an empty string.
//      - Otherwise, return T{} (value-initialization).

#pragma once

#include <testkit/testkit.h>
#include <string>
#include <type_traits>

// Convert a value to its string representation using if constexpr.
template <typename T>
std::string stringify(const T& value) {
    TODO();
}

// Return the "default" value for a type using if constexpr.
template <typename T>
T default_value() {
    TODO();
}
