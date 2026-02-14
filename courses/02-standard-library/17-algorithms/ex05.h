// Exercise 05: Copy_if
//
// std::copy_if copies elements from a source range to a destination, but
// only those that satisfy a predicate. It's the functional "filter"
// operation.
//
//   std::copy_if(src.begin(), src.end(), std::back_inserter(dst), pred);
//
// Unlike remove_if (which modifies in place), copy_if creates a new
// collection without touching the original.
//
// TODO:
//   1. Implement filter_evens() — copy only even numbers to a new vector.
//   2. Implement filter_by_prefix() — copy strings that start with a
//      given prefix to a new vector.
//   3. Implement filter_in_range() — copy numbers that fall within
//      [low, high] (inclusive) to a new vector.

#pragma once

#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <testkit/testkit.h>

// Return a new vector containing only the even numbers from `vec`.
inline std::vector<int> filter_evens(const std::vector<int>& vec) {
    TODO();
}

// Return a new vector containing only strings that start with `prefix`.
// A string starts with a prefix if it begins with the prefix substring.
// Use std::string::find(prefix) == 0 or std::string::substr.
inline std::vector<std::string> filter_by_prefix(
    const std::vector<std::string>& vec,
    const std::string& prefix) {
    TODO();
}

// Return a new vector containing only numbers in [low, high] (inclusive).
inline std::vector<int> filter_in_range(const std::vector<int>& vec,
                                        int low, int high) {
    TODO();
}
