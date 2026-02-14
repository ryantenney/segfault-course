// Exercise 02: Compound Requirements
//
// PROBLEM:
//   A concept can require multiple operations on a type using a
//   `requires` expression with compound requirements.  Each requirement
//   is a statement that must be valid for the concept to be satisfied.
//
// TODO:
//   1. Fix the `Displayable` concept below.  Currently it accepts ALL
//      types.  Replace `true` with a requires expression that checks:
//      - Comparison with < : { a < b } -> std::convertible_to<bool>
//      - Comparison with == : { a == b } -> std::convertible_to<bool>
//      - A .to_string() method: { a.to_string() } -> std::convertible_to<std::string>
//
//      Syntax:
//        template<typename T>
//        concept Displayable = requires(T a, T b) {
//            { a < b }        -> std::convertible_to<bool>;
//            { a == b }       -> std::convertible_to<bool>;
//            { a.to_string() } -> std::convertible_to<std::string>;
//        };
//
//   2. Add the Displayable constraint to `compare_and_display`.
//
//   3. Implement `compare_and_display` -- if a < b, return a.to_string();
//      otherwise return b.to_string().
//
// WHY:
//   Compound requirements let you express rich interfaces in a single
//   concept.  The `-> std::convertible_to<R>` constraint checks that
//   the expression returns a type convertible to R.

#pragma once

#include <testkit/testkit.h>
#include <concepts>
#include <string>

// Fix this concept: replace `true` with the compound requirements.
template<typename T>
concept Displayable = true;  // TODO: add requires(T a, T b) { ... }

// Return the string representation of the smaller value.
// If a < b, return a.to_string(); otherwise return b.to_string().
// TODO: Constrain with the Displayable concept.
template<typename T>
std::string compare_and_display(const T& a, const T& b) {
    TODO();
}
