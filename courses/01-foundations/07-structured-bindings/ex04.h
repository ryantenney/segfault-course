// Exercise 04: Tuple decomposition
//
// PROBLEM:
//   Structured bindings work with std::tuple, letting you unpack
//   multiple return values with meaningful names:
//
//     std::tuple<int, double, std::string> get_record();
//     auto [id, score, name] = get_record();
//
//   This is much better than std::get<0>(t), std::get<1>(t), etc.
//
// TODO:
//   Implement functions that return tuples, then the tests will
//   use structured bindings to unpack them.

#pragma once

#include <testkit/testkit.h>
#include <string>
#include <tuple>
#include <vector>

// Return a tuple of (min, max, sum) for the given vector.
// If the vector is empty, return {0, 0, 0}.
inline std::tuple<int, int, int> stats(const std::vector<int>& v) {
    TODO();
}

// Return a tuple of (quotient, remainder) for integer division.
inline std::tuple<int, int> divmod(int a, int b) {
    TODO();
    // Hint: return {a / b, a % b};
}

// Return a tuple of (first_name, last_name) by splitting on the
// first space. If there's no space, last_name is "".
inline std::tuple<std::string, std::string> split_name(const std::string& full) {
    TODO();
    // Hint: auto pos = full.find(' ');
}

// Return a tuple of (count, total) where count is the number of
// positive values and total is their sum.
inline std::tuple<int, int> count_and_sum_positive(const std::vector<int>& v) {
    TODO();
}
