// Exercise 05: Ordered Set Operations
//
// std::set stores unique elements in sorted order. Inserting a duplicate
// is a no-op. Iterating over a set always yields elements in ascending
// order (using operator< by default).
//
// Common uses:
//   - Deduplication: insert all elements, duplicates are ignored
//   - Sorted iteration: for (auto& x : s) visits elements in order
//   - Membership testing: s.contains(x) or s.count(x)
//
// TODO:
//   Implement the three functions below using std::set.

#pragma once

#include <testkit/testkit.h>
#include <set>
#include <vector>

// Given a vector, return a new vector containing the unique elements
// in sorted order. Use a std::set as intermediate storage.
inline std::vector<int> unique_sorted(const std::vector<int>& input) {
    TODO();
}

// Return a sorted vector of elements that appear in BOTH a and b.
// Hint: insert elements of `a` into a set, then check each element
// of `b` against it. Use a second set for the result to avoid duplicates.
inline std::vector<int> set_intersection(const std::vector<int>& a,
                                         const std::vector<int>& b) {
    TODO();
}

// Return a sorted vector of elements that appear in `a` but NOT in `b`.
// Hint: insert elements of `b` into a set, then check each element
// of `a` against it.
inline std::vector<int> set_difference(const std::vector<int>& a,
                                       const std::vector<int>& b) {
    TODO();
}
