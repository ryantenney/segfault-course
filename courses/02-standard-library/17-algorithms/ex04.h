// Exercise 04: Filter with Remove-Erase
//
// std::remove_if does NOT actually remove elements from a container. It
// moves the elements that don't match the predicate to the front, and
// returns an iterator to the new "logical end." The container still has
// the same size -- the elements past the returned iterator are in an
// unspecified state.
//
// To actually shrink the container, combine it with erase():
//
//   auto new_end = std::remove_if(v.begin(), v.end(), pred);
//   v.erase(new_end, v.end());
//
// This is called the "erase-remove idiom." In C++20 you can use
// std::erase_if(v, pred) which does both steps at once.
//
// TODO:
//   1. Implement remove_odds() — remove all odd numbers from a vector
//      using the erase-remove idiom.
//   2. Implement remove_empty_strings() — remove all empty strings
//      from a vector using the erase-remove idiom.
//   3. Implement remove_duplicates() — sort the vector, then use
//      std::unique + erase to remove consecutive duplicates.

#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include <testkit/testkit.h>

// Remove all odd numbers from the vector (in place).
// Use std::remove_if + erase.
inline void remove_odds(std::vector<int>& vec) {
    TODO();
}

// Remove all empty strings from the vector (in place).
// Use std::remove_if + erase.
inline void remove_empty_strings(std::vector<std::string>& vec) {
    TODO();
}

// Remove duplicate values from the vector (in place).
// Sort the vector first, then use std::unique + erase.
// After this function, the vector contains each value at most once, in
// sorted order.
inline void remove_duplicates(std::vector<int>& vec) {
    TODO();
}
