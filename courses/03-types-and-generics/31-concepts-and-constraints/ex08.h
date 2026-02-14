// Exercise 08: Ad-Hoc Requires Expression
//
// PROBLEM:
//   Sometimes a constraint is too specific or too simple to deserve a
//   named concept.  An inline `requires` expression lets you specify
//   constraints directly at the point of use without naming a concept.
//
// TODO:
//   1. Implement `get_length` -- returns the result of calling .length()
//      on the argument.  Constrain it with an inline requires expression
//      so that it only accepts types with a .length() method returning
//      something convertible to std::size_t.
//
//      Syntax:
//        template<typename T>
//            requires requires(T t) { { t.length() } -> std::convertible_to<std::size_t>; }
//        std::size_t get_length(const T& value) { ... }
//
//   2. Implement `serialize_pair` -- takes two arguments and returns
//      "(" + to_string(a) + ", " + to_string(b) + ")".
//      Constrain it so both types must have a free function to_string
//      (found via ADL or std::to_string) that returns std::string.
//
//      Use an ad-hoc requires on each parameter:
//        template<typename A, typename B>
//            requires requires(A a) { { to_string(a) } -> std::convertible_to<std::string>; }
//                  && requires(B b) { { to_string(b) } -> std::convertible_to<std::string>; }
//        std::string serialize_pair(const A& a, const B& b) { ... }
//
// WHY:
//   Ad-hoc requires expressions are the most flexible constraint
//   mechanism.  They're ideal for one-off constraints that don't need
//   to be reused across multiple functions.

#pragma once

#include <testkit/testkit.h>
#include <concepts>
#include <string>

// Returns the length of a value.
// TODO: Add an ad-hoc requires expression constraining T to have .length().
template<typename T>
std::size_t get_length(const T& value) {
    TODO();
}

// Helper: bring std::to_string into scope for the serialize_pair function.
using std::to_string;

// Serialize two values into a pair string: "(a, b)"
// TODO: Add an ad-hoc requires expression constraining A and B to be
// convertible to string via to_string().
template<typename A, typename B>
std::string serialize_pair(const A& a, const B& b) {
    TODO();
}
