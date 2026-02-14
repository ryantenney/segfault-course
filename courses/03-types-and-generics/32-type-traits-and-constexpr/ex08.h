// Exercise 08: constexpr with std::array
//
// std::array is fully constexpr in C++17+. You can create, fill, sort, and
// search an array entirely at compile time. This is powerful for building
// precomputed data structures that have zero runtime cost.
//
// TODO:
//   1. Implement constexpr_iota<N>(): Return a std::array<int, N> filled
//      with values {0, 1, 2, ..., N-1}. Mark it `constexpr`.
//
//   2. Implement constexpr_sum(arr): Return the sum of all elements in
//      the array. Use a loop. Mark it `constexpr`.
//
//   3. Implement constexpr_reverse(arr): Return a new array with the
//      elements in reverse order. Mark it `constexpr`.
//
//   4. Implement constexpr_contains(arr, value): Return true if value
//      is found in the array. Mark it `constexpr`.
//
// IMPORTANT: The stubs are NOT marked constexpr yet because they contain
// TODO(). Once you implement each body, add `constexpr` to the function.

#pragma once

#include <testkit/testkit.h>
#include <array>
#include <cstddef>

// Return {0, 1, 2, ..., N-1} as a std::array<int, N>.
// Add `constexpr` once you implement the body.
template <std::size_t N>
std::array<int, N> constexpr_iota() {
    TODO();
}

// Return the sum of all elements in the array.
// Add `constexpr` once you implement the body.
template <std::size_t N>
int constexpr_sum(const std::array<int, N>& arr) {
    TODO();
}

// Return a new array with elements in reverse order.
// Add `constexpr` once you implement the body.
template <std::size_t N>
std::array<int, N> constexpr_reverse(const std::array<int, N>& arr) {
    TODO();
}

// Return true if value is in the array.
// Add `constexpr` once you implement the body.
template <std::size_t N>
bool constexpr_contains(const std::array<int, N>& arr, int value) {
    TODO();
}
