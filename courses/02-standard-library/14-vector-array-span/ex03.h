// Exercise 03: Bounds-Safe Access
//
// std::vector provides two ways to access elements:
//   - operator[](i): fast, no bounds checking (UB if i >= size())
//   - .at(i):        bounds-checked, throws std::out_of_range if invalid
//
// Use .at() when the index comes from untrusted input or when safety
// matters more than raw speed.
//
// TODO:
//   Implement the three functions below using .at() for bounds-safe access.

#pragma once

#include <testkit/testkit.h>
#include <vector>
#include <cstddef>
#include <stdexcept>

// Return the element at the given index using .at().
// Let std::out_of_range propagate if the index is invalid.
inline int safe_element(const std::vector<int>& v, std::size_t index) {
    TODO();
}

// Sum the elements from index `start` to `end` (inclusive) using .at().
// Let std::out_of_range propagate if any index is invalid.
inline int safe_sum(const std::vector<int>& v, std::size_t start, std::size_t end) {
    TODO();
}

// Return the element at `index` if valid, otherwise return `default_val`.
// Use .at() inside a try/catch block.
inline int get_or_default(const std::vector<int>& v, std::size_t index, int default_val) {
    TODO();
}
