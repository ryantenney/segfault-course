// Exercise 02: Const Iteration
//
// When you only need to read elements, use const iterators: cbegin() and
// cend(). These return iterators through which you cannot modify the
// underlying element. Using const iterators makes your intent clear and
// prevents accidental mutation.
//
//   auto it = vec.cbegin();   // const_iterator
//   // *it = 42;              // ERROR: cannot assign through const_iterator
//
// In range-for loops, `const auto&` gives the same read-only guarantee:
//   for (const auto& elem : vec) { ... }
//
// TODO:
//   1. Implement contains() — use cbegin()/cend() to search for a value
//      in a vector without modifying it.
//   2. Implement build_comma_string() — use const iteration to join all
//      strings with ", " separators (no trailing separator).
//   3. Implement first_positive() — return a const_iterator to the first
//      positive element, or cend() if none exists.

#pragma once

#include <string>
#include <vector>
#include <testkit/testkit.h>

// Return true if `value` is found in `vec`.
// Use cbegin()/cend() for read-only traversal.
inline bool contains(const std::vector<int>& vec, int value) {
    TODO();
}

// Join all strings with ", " as separator.
// Example: {"a", "b", "c"} -> "a, b, c"
// Empty vector returns "".
inline std::string build_comma_string(const std::vector<std::string>& vec) {
    TODO();
}

// Return a const_iterator to the first positive (> 0) element.
// If no positive element exists, return vec.cend().
inline std::vector<int>::const_iterator
first_positive(const std::vector<int>& vec) {
    TODO();
}
