// Exercise 07: Accept a Span Parameter
//
// std::span<const T> is a non-owning view over contiguous elements. It
// stores just a pointer and a length, so it's cheap to pass by value.
//
// A function that takes span<const int> can accept data from:
//   - std::vector<int>
//   - std::array<int, N>
//   - int[] (C-style arrays)
//   - subranges of any of the above
//
// This is more flexible than taking const vector<int>& because it doesn't
// force the caller to use a specific container type.
//
// TODO:
//   Implement the three functions below using std::span<const int>.

#pragma once

#include <testkit/testkit.h>
#include <span>
#include <utility>

// Return the sum of all elements in the span.
inline int span_sum(std::span<const int> data) {
    TODO();
}

// Return true if the span contains the given value, false otherwise.
inline bool span_contains(std::span<const int> data, int value) {
    TODO();
}

// Return a pair containing the minimum and maximum values in the span.
// You may assume the span is non-empty.
inline std::pair<int, int> span_min_max(std::span<const int> data) {
    TODO();
}
