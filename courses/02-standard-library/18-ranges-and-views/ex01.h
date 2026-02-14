// Exercise 01: Ranges Sort and Find
//
// C++20 introduced the std::ranges namespace, which provides constrained
// versions of the classic <algorithm> functions. Instead of passing
// iterator pairs (begin, end), you pass the container directly:
//
//   std::ranges::sort(vec);              // instead of std::sort(vec.begin(), vec.end())
//   auto it = std::ranges::find(vec, x); // instead of std::find(vec.begin(), vec.end(), x)
//
// The ranges versions also return richer types (e.g., subranges) and support
// projections (covered in exercise 6).
//
// TODO:
//   1. Implement sort_ascending() -- sort the vector in ascending order
//      using std::ranges::sort.
//   2. Implement find_value() -- use std::ranges::find to locate a value.
//      Return true if found, false otherwise.
//   3. Implement sort_descending() -- sort in descending order using
//      std::ranges::sort with std::greater<>{} as the comparator.

#pragma once

#include <algorithm>
#include <functional>
#include <ranges>
#include <vector>
#include <testkit/testkit.h>

// Sort the vector in ascending order using std::ranges::sort.
// Return the sorted vector.
inline std::vector<int> sort_ascending(std::vector<int> vec) {
    TODO();
}

// Return true if `value` is found in `vec` using std::ranges::find.
inline bool find_value(const std::vector<int>& vec, int value) {
    TODO();
}

// Sort the vector in descending order using std::ranges::sort
// with std::greater<>{} as the comparator.
// Return the sorted vector.
inline std::vector<int> sort_descending(std::vector<int> vec) {
    TODO();
}
