// Exercise 02: Reserve and Capacity
//
// std::vector manages its own memory. When you push_back and the internal
// buffer is full, the vector allocates a larger buffer (typically 2x),
// copies/moves all elements, and frees the old buffer.
//
// - size():     number of elements currently in the vector
// - capacity(): number of elements the vector can hold before reallocating
// - reserve(n): preallocate room for at least n elements (size unchanged)
//
// If you know in advance how many elements you'll add, calling reserve()
// upfront avoids repeated reallocations.
//
// TODO:
//   Implement the three functions below.

#pragma once

#include <testkit/testkit.h>
#include <vector>
#include <cstddef>

// Reserve space for `count` elements, then push the values 0, 1, 2, ...,
// count-1 into the vector. Return the vector.
inline std::vector<int> reserved_push(std::size_t count) {
    TODO();
}

// Create an empty vector, reserve `n` elements, and return the capacity.
// The capacity should be at least `n`.
inline std::size_t capacity_after_reserve(std::size_t n) {
    TODO();
}

// Starting from an empty vector, push the values 0 through count-1 one at
// a time. Count how many times the capacity changes during this process
// and return that count. (The initial change from 0 to non-zero counts.)
inline int grow_and_report(std::size_t count) {
    TODO();
}
