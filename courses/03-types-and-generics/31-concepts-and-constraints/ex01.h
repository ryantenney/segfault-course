// Exercise 01: Simple Concept
//
// PROBLEM:
//   Before C++20, constraining template parameters required SFINAE hacks
//   or static_assert.  Concepts provide a clean, readable way to express
//   requirements on template arguments.
//
// TODO:
//   1. Fix the `Numeric` concept below.  Currently it accepts ALL types
//      (the constraint is just `true`).  Change it to accept only
//      arithmetic types using std::is_arithmetic_v<T>.
//
//   2. Add the Numeric constraint to `add` and `multiply`.
//      Change `template<typename T>` to `template<Numeric T>`.
//
//   3. Implement the `add` and `multiply` function bodies.
//
// WHY:
//   Concepts make template error messages dramatically better.  Instead of
//   pages of SFINAE failures, you get a clear message like "constraint
//   Numeric not satisfied for type std::string."

#pragma once

#include <testkit/testkit.h>
#include <type_traits>

// Fix this concept: replace `true` with `std::is_arithmetic_v<T>`.
template<typename T>
concept Numeric = true;  // TODO: change to std::is_arithmetic_v<T>

// Add two numeric values.
// TODO: Constrain with Numeric: change to template<Numeric T>
template<typename T>
T add(T a, T b) {
    TODO();
}

// Multiply two numeric values.
// TODO: Constrain with Numeric: change to template<Numeric T>
template<typename T>
T multiply(T a, T b) {
    TODO();
}
