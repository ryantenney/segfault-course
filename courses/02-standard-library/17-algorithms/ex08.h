// Exercise 08: Predicate Composition
//
// The "any/all/none_of" family tests whether elements in a range satisfy
// a predicate:
//
//   std::any_of(begin, end, pred)   — true if at least one matches
//   std::all_of(begin, end, pred)   — true if every element matches
//   std::none_of(begin, end, pred)  — true if no element matches
//
// These are useful for expressing complex queries concisely. For example:
//
//   bool has_negative = std::any_of(v.begin(), v.end(),
//       [](int x) { return x < 0; });
//
// Note: all three return true for an empty range by convention (vacuous truth
// for all_of and none_of; false for any_of since nothing can match).
//
// TODO:
//   1. Implement has_negative() — return true if any element is negative.
//   2. Implement all_positive() — return true if every element is positive (> 0).
//   3. Implement none_empty() — return true if no string in the vector is empty.
//   4. Implement classify_numbers() — return a string describing the vector:
//      "all positive", "all negative", "mixed", or "empty".

#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include <testkit/testkit.h>

// Return true if any element in the vector is negative.
inline bool has_negative(const std::vector<int>& vec) {
    TODO();
}

// Return true if every element in the vector is positive (> 0).
// An empty vector returns true (vacuous truth).
inline bool all_positive(const std::vector<int>& vec) {
    TODO();
}

// Return true if no string in the vector is empty.
inline bool none_empty(const std::vector<std::string>& vec) {
    TODO();
}

// Classify a vector of numbers:
//   - "empty"        if the vector is empty
//   - "all positive" if every element is > 0
//   - "all negative" if every element is < 0
//   - "mixed"        otherwise (has both positive and negative, or zeros)
inline std::string classify_numbers(const std::vector<int>& vec) {
    TODO();
}
