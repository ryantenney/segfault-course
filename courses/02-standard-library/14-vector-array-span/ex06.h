// Exercise 06: Fixed-Size with std::array
//
// std::array<T, N> is a fixed-size container that wraps a C-style array.
// Unlike raw arrays, it knows its size, supports .at() for bounds checking,
// and has full value semantics (copyable, assignable, comparable).
//
//   std::array<int, 3> a = {1, 2, 3};
//   a.size();    // 3 (compile-time constant)
//   a[0];        // unchecked access
//   a.at(5);     // throws std::out_of_range
//
// TODO:
//   Implement the four functions below.

#pragma once

#include <testkit/testkit.h>
#include <array>
#include <cstddef>
#include <stdexcept>

// Return a std::array<int, 5> with all elements set to zero.
// Hint: value-initialize with {} or use .fill(0).
inline std::array<int, 5> make_zeros() {
    TODO();
}

// Return the sum of all elements in the array.
inline int array_sum(const std::array<int, 5>& arr) {
    TODO();
}

// Return the element at `index` using .at().
// Let std::out_of_range propagate if the index is invalid.
inline int safe_array_access(const std::array<int, 5>& arr, std::size_t index) {
    TODO();
}

// Return a copy of the array with elements in reverse order.
inline std::array<int, 5> reverse_array(const std::array<int, 5>& arr) {
    TODO();
}
