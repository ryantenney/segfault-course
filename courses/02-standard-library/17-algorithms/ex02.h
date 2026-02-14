// Exercise 02: Find and Count
//
// std::find_if searches a range for the first element matching a predicate.
// std::count_if counts how many elements satisfy a predicate.
//
//   auto it = std::find_if(v.begin(), v.end(), pred);
//   int n   = std::count_if(v.begin(), v.end(), pred);
//
// A predicate is any callable that takes an element and returns bool.
// Lambdas are the most common way to write predicates inline:
//
//   auto is_even = [](int x) { return x % 2 == 0; };
//
// TODO:
//   1. Implement find_first_even() — use std::find_if with a lambda to
//      find the first even number. Return its value, or -1 if none.
//   2. Implement count_strings_starting_with() — use std::count_if to
//      count strings that begin with a given character.
//   3. Implement find_first_longer_than() — use std::find_if to find the
//      first string longer than `n` characters.

#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include <testkit/testkit.h>

// Find the first even number in the vector.
// Return its value, or -1 if there are no even numbers.
inline int find_first_even(const std::vector<int>& vec) {
    TODO();
}

// Count how many strings in the vector start with the given character.
inline int count_strings_starting_with(const std::vector<std::string>& vec,
                                       char ch) {
    TODO();
}

// Find the first string longer than `n` characters.
// Return it, or return "" if none is found.
inline std::string find_first_longer_than(const std::vector<std::string>& vec,
                                          std::size_t n) {
    TODO();
}
