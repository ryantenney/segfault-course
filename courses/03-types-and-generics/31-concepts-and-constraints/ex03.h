// Exercise 03: Requires Clause on Function
//
// PROBLEM:
//   Instead of defining a named concept, you can add a `requires` clause
//   directly on a function template.  This is useful when the constraint
//   is simple or used only once.
//
// TODO:
//   1. Add a `requires` clause to `absolute_value` so it only accepts
//      types where std::is_signed_v<T> is true.
//
//      Syntax:
//        template<typename T>
//        T absolute_value(T x) requires std::is_signed_v<T> { ... }
//
//   2. Implement absolute_value -- return x if x >= 0, else return -x.
//
//   3. Add a `requires` clause to `clamp_value` so it only accepts types
//      that support < comparison.
//
//      Syntax:
//        template<typename T>
//        T clamp_value(T val, T lo, T hi) requires std::totally_ordered<T> { ... }
//
//   4. Implement clamp_value -- if val < lo return lo; if hi < val return
//      hi; otherwise return val.
//
// WHY:
//   The `requires` clause gives you fine-grained control over which
//   types are accepted, directly at the function declaration.  The
//   compiler can produce clear error messages when the constraint fails.

#pragma once

#include <testkit/testkit.h>
#include <concepts>
#include <type_traits>

// Return the absolute value of x.
// TODO: Add requires clause: requires std::is_signed_v<T>
template<typename T>
T absolute_value(T x) {
    TODO();
}

// Clamp val to the range [lo, hi].
// TODO: Add requires clause so T must be totally ordered.
// Use: requires std::totally_ordered<T>
template<typename T>
T clamp_value(T val, T lo, T hi) {
    TODO();
}
