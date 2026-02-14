// Exercise 05: Swap via References
//
// PROBLEM:
//   Writing a swap function requires modifying the caller's variables.
//   Pass-by-value won't work because it operates on copies. You need
//   pass-by-reference.
//
// TODO:
//   1. Implement `swap_ints(int& a, int& b)` to swap the two values.
//   2. Implement `sort_three(int& a, int& b, int& c)` so that after
//      the call, a <= b <= c. Use swap_ints.
//
// WHY:
//   References are aliases — another name for the same object. When
//   you modify a reference parameter, you modify the caller's variable
//   directly. This is the fundamental mechanism for "output parameters"
//   in C++.

#pragma once

#include <testkit/testkit.h>

// Swap the values of a and b using a temporary variable
inline void swap_ints(int& a, int& b) {
    TODO();
}

// Sort three values in-place so that a <= b <= c
// Hint: use swap_ints in a simple bubble-sort pattern
inline void sort_three(int& a, int& b, int& c) {
    TODO();
}
