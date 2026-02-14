// Exercise 03: Transform Elements
//
// std::transform applies a function to each element of a range and writes
// the results to a destination range. It's the C++ equivalent of "map" in
// functional programming.
//
//   std::transform(src.begin(), src.end(), dst.begin(), func);
//
// The destination must have enough space, or you can use std::back_inserter
// to grow it dynamically:
//
//   std::transform(src.begin(), src.end(), std::back_inserter(dst), func);
//
// There's also a binary form that takes two input ranges:
//
//   std::transform(a.begin(), a.end(), b.begin(),
//                  std::back_inserter(dst), binary_func);
//
// TODO:
//   1. Implement to_uppercase() — transform a vector of strings to uppercase.
//   2. Implement square_all() — transform a vector of ints to their squares.
//   3. Implement pairwise_sum() — use the binary form of transform to add
//      corresponding elements of two vectors.

#pragma once

#include <algorithm>
#include <cctype>
#include <iterator>
#include <string>
#include <vector>
#include <testkit/testkit.h>

// Return a new vector where each string is converted to uppercase.
// Hint: transform each string by transforming each character with std::toupper.
inline std::vector<std::string> to_uppercase(const std::vector<std::string>& vec) {
    TODO();
}

// Return a new vector where each element is the square of the original.
inline std::vector<int> square_all(const std::vector<int>& vec) {
    TODO();
}

// Return a new vector where each element is the sum of corresponding
// elements from `a` and `b`.
// Precondition: a.size() == b.size().
inline std::vector<int> pairwise_sum(const std::vector<int>& a,
                                     const std::vector<int>& b) {
    TODO();
}
