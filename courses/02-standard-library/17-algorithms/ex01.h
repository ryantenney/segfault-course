// Exercise 01: Sort and Search
//
// std::sort arranges elements in ascending order (by default). Once a range
// is sorted, you can use binary search algorithms for O(log n) lookups:
//
//   std::sort(v.begin(), v.end());
//   auto it = std::lower_bound(v.begin(), v.end(), value);
//
// std::lower_bound returns an iterator to the first element >= value.
// If the element at that position equals value, you found it.
//
// You can also pass a custom comparator to sort in different orders:
//   std::sort(v.begin(), v.end(), std::greater<int>());  // descending
//
// TODO:
//   1. Implement sort_ascending() — sort a vector in ascending order.
//   2. Implement sort_descending() — sort a vector in descending order.
//   3. Implement binary_search_index() — sort the vector, then use
//      std::lower_bound to find the value. Return its index, or -1.

#pragma once

#include <algorithm>
#include <functional>
#include <vector>
#include <testkit/testkit.h>

// Sort the vector in ascending order (in place).
inline void sort_ascending(std::vector<int>& vec) {
    TODO();
}

// Sort the vector in descending order (in place).
// Use std::greater<int>() as the comparator.
inline void sort_descending(std::vector<int>& vec) {
    TODO();
}

// Sort the vector, then use std::lower_bound to find `target`.
// Return the index of the target, or -1 if not found.
// Note: lower_bound returns the first position where target could be
// inserted without breaking the sort order, so you must check if the
// element at that position actually equals target.
inline int binary_search_index(std::vector<int>& vec, int target) {
    TODO();
}
