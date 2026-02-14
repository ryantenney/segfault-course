// Exercise 01: Generic Max Function
//
// PROBLEM:
//   Writing separate max functions for int, double, string, etc. is tedious
//   and error-prone. Function templates let you write the logic once and
//   have the compiler generate versions for each type you use.
//
// TODO:
//   Implement max_of(T a, T b): return the larger of the two values.
//   Use operator< for comparison.
//
// WHY:
//   Function templates are the foundation of generic programming in C++.
//   The compiler generates ("instantiates") a concrete function for each
//   type you call it with. The template itself is not a function -- it's
//   a recipe for generating functions.

#pragma once

#include <testkit/testkit.h>

// Return the larger of a and b. If equal, return b.
template<typename T>
T max_of(T a, T b) {
    TODO();
}
