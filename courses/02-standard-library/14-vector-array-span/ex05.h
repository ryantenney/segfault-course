// Exercise 05: Erase Elements
//
// Removing elements from a vector can be done with C++20's std::erase and
// std::erase_if, which are free functions in <vector>:
//
//   std::erase(vec, value);           // remove all elements equal to value
//   std::erase_if(vec, predicate);    // remove all elements matching predicate
//
// For removing duplicates, you'll need a different strategy: iterate through
// the vector and track which values you've already seen.
//
// TODO:
//   Implement the three functions below.

#pragma once

#include <testkit/testkit.h>
#include <vector>
#include <unordered_set>

// Remove all occurrences of `value` from `vec`.
// Modify the vector in place.
// Hint: use std::erase(vec, value).
inline void remove_value(std::vector<int>& vec, int value) {
    TODO();
}

// Remove all negative numbers from `vec`.
// Modify the vector in place.
// Hint: use std::erase_if(vec, predicate).
inline void remove_negatives(std::vector<int>& vec) {
    TODO();
}

// Remove duplicate values from `vec`, keeping only the first occurrence
// of each value. The relative order of remaining elements must be preserved.
// Modify the vector in place.
// Hint: iterate with an index, use an unordered_set to track seen values,
// and build the result by erasing or by using erase_if with a stateful
// predicate.
inline void remove_duplicates(std::vector<int>& vec) {
    TODO();
}
