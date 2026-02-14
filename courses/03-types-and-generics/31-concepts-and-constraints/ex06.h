// Exercise 06: Standard Library Concepts
//
// PROBLEM:
//   The C++20 standard library provides a rich set of pre-defined concepts
//   in <concepts>.  Using them is preferred over rolling your own -- they're
//   well-tested, well-specified, and recognized by the compiler for better
//   error messages.
//
// TODO:
//   1. Implement `to_int` constrained with std::integral -- converts the
//      integral value to int using static_cast<int>.
//
//   2. Implement `halve` constrained with std::floating_point -- returns
//      the value divided by 2.0.
//
//   3. Implement `stringify` constrained with std::convertible_to<std::string>.
//      It should convert the value to std::string (using the implicit
//      conversion that convertible_to guarantees).
//
//   4. Implement `are_equal` constrained with std::equality_comparable.
//      Returns true if a == b.
//
// WHY:
//   The <concepts> header defines concepts for fundamental type properties
//   (integral, floating_point), conversions (convertible_to, constructible_from),
//   comparison (equality_comparable, totally_ordered), and more.  Learning
//   to use them saves you from redefining common constraints.

#pragma once

#include <testkit/testkit.h>
#include <concepts>
#include <string>

// Convert an integral value to int.
// Constrain with: std::integral
template<std::integral T>
int to_int(T value) {
    TODO();
}

// Halve a floating-point value.
// Constrain with: std::floating_point
template<std::floating_point T>
T halve(T value) {
    TODO();
}

// Convert a value to std::string using implicit conversion.
// Constrain with: std::convertible_to<std::string>
template<typename T>
    requires std::convertible_to<T, std::string>
std::string stringify(T value) {
    TODO();
}

// Check if two values are equal.
// Constrain with: std::equality_comparable
template<std::equality_comparable T>
bool are_equal(const T& a, const T& b) {
    TODO();
}
