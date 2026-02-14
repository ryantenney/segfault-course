// Exercise 01: Basic Lambda Predicate
//
// A lambda is an anonymous function object defined inline. The basic
// syntax is:
//
//   [capture](parameters) -> return_type { body }
//
// The return type can usually be deduced, so it is often omitted:
//
//   [](int a, int b) { return a < b; }
//
// Lambdas are commonly used as predicates or comparators for STL
// algorithms like std::sort and std::find_if.
//
// TODO:
//   1. Implement sort_ascending() -- use std::sort with a lambda that
//      compares two ints in ascending order (a < b).
//   2. Implement sort_by_absolute() -- use std::sort with a lambda that
//      sorts by absolute value (ascending).
//   3. Implement sort_strings_by_length() -- use std::sort with a lambda
//      that sorts strings by length (ascending), breaking ties
//      alphabetically.

#pragma once

#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <testkit/testkit.h>

// Sort ints in ascending order using std::sort with a lambda comparator.
inline std::vector<int> sort_ascending(std::vector<int> nums) {
    TODO();
}

// Sort ints by absolute value (ascending) using a lambda comparator.
inline std::vector<int> sort_by_absolute(std::vector<int> nums) {
    TODO();
}

// Sort strings by length (ascending). If two strings have the same
// length, sort them alphabetically.
inline std::vector<std::string> sort_strings_by_length(
        std::vector<std::string> words) {
    TODO();
}
