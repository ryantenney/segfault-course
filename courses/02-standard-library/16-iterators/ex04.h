// Exercise 04: Reverse Iteration
//
// Every reversible container provides rbegin() and rend() for backwards
// traversal. A reverse_iterator moves "forward" through the container in
// reverse order: ++rit moves toward the front.
//
//   for (auto rit = vec.rbegin(); rit != vec.rend(); ++rit) {
//       // visits elements from back to front
//   }
//
// In a range-for, there's no built-in reverse adapter in C++17, but you
// can use rbegin/rend with a manual loop.
//
// TODO:
//   1. Implement reverse_copy_vec() — build a new vector by iterating
//      the input in reverse using rbegin()/rend().
//   2. Implement last_n_elements() — return the last `n` elements of a
//      vector (in their original order) using reverse iterators.
//   3. Implement find_last() — find the last occurrence of `value` in a
//      vector using reverse iteration. Return its index, or -1 if not found.

#pragma once

#include <vector>
#include <testkit/testkit.h>

// Return a new vector with elements in reverse order.
// Use rbegin()/rend() to iterate the source backwards.
inline std::vector<int> reverse_copy_vec(const std::vector<int>& vec) {
    TODO();
}

// Return the last `n` elements of `vec` in their original order.
// If n >= vec.size(), return a copy of the entire vector.
// Hint: use reverse iterators to find the starting point, then
// construct the result from that range.
inline std::vector<int> last_n_elements(const std::vector<int>& vec, std::size_t n) {
    TODO();
}

// Find the last occurrence of `value` in `vec`.
// Return its index (0-based), or -1 if not found.
// Use rbegin()/rend() for the search.
inline int find_last(const std::vector<int>& vec, int value) {
    TODO();
}
