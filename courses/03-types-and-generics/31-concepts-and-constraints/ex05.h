// Exercise 05: Concept-Based Overloading
//
// PROBLEM:
//   Concepts can be used to select between different function overloads.
//   If you have two overloads constrained by different concepts, the
//   compiler picks the one whose concept is satisfied by the argument type.
//
// TODO:
//   1. Fix the `Integral` concept -- replace `true` with std::is_integral_v<T>.
//   2. Fix the `FloatingPoint` concept -- replace `true` with
//      std::is_floating_point_v<T>.
//   3. Add Integral constraint to the first `describe` overload.
//   4. Add FloatingPoint constraint to the second `describe` overload
//      (uncomment it and constrain it).
//   5. Implement both `describe` overloads.
//   6. Add constraints and implement both `double_it` overloads similarly.
//
//   IMPORTANT: You must constrain BOTH overloads -- otherwise the
//   compiler can't distinguish between them and reports ambiguity.
//
// WHY:
//   Before concepts, overloading on type categories required complex
//   SFINAE (`enable_if`).  Concepts make this clean and readable:
//   each overload states exactly what types it accepts.

#pragma once

#include <testkit/testkit.h>
#include <string>
#include <type_traits>

// Fix these concepts: replace `true` with the proper type trait check.
template<typename T>
concept Integral = true;  // TODO: std::is_integral_v<T>

template<typename T>
concept FloatingPoint = true;  // TODO: std::is_floating_point_v<T>

// Describe an integral value.
// TODO: Constrain with Integral concept.
// Return: "integer: " + std::to_string(value)
template<typename T>
std::string describe(T value) {
    TODO();
}

// TODO: Uncomment and constrain with FloatingPoint concept.
// Describe a floating-point value.
// Return: "float: " + std::to_string(value)
//
// template<FloatingPoint T>
// std::string describe(T value) {
//     TODO();
// }

// Double an integral value.
// TODO: Constrain with Integral concept.
template<typename T>
T double_it(T value) {
    TODO();
}

// TODO: Uncomment and constrain with FloatingPoint concept.
// Double a floating-point value.
//
// template<FloatingPoint T>
// T double_it(T value) {
//     TODO();
// }
