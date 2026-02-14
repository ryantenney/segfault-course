// Exercise 05: Iterator Arithmetic
//
// Not all iterators support pointer-like arithmetic (it + n). Random access
// iterators (vector, deque, array) do, but bidirectional iterators (list,
// map, set) only support ++ and --. The <iterator> header provides generic
// utilities that work with any iterator category:
//
//   std::next(it, n)      — returns an iterator n positions ahead (default 1)
//   std::prev(it, n)      — returns an iterator n positions back (default 1)
//   std::advance(it, n)   — moves it forward by n positions (modifies in place)
//   std::distance(a, b)   — returns the number of increments from a to b
//
// These functions use the most efficient method available for the iterator
// category: O(1) for random access, O(n) for bidirectional/forward.
//
// TODO:
//   1. Implement get_nth() — return the nth element of a list using std::next.
//   2. Implement distance_between() — return the distance between two values
//      in a list (find both, then use std::distance).
//   3. Implement advance_and_read() — advance an iterator by `steps` positions
//      using std::advance, then return the element at that position.
//   4. Implement get_middle() — return the element at the middle index of a
//      vector using std::next with distance/2.

#pragma once

#include <iterator>
#include <list>
#include <string>
#include <vector>
#include <testkit/testkit.h>

// Return the element at index `n` (0-based) in the list.
// Precondition: n < lst.size().
// Use std::next to advance from begin().
inline int get_nth(const std::list<int>& lst, std::size_t n) {
    TODO();
}

// Find `from` and `to` in the list, then return std::distance between their
// iterators. If either is not found, return -1.
inline int distance_between(const std::list<std::string>& lst,
                            const std::string& from,
                            const std::string& to) {
    TODO();
}

// Starting from lst.begin(), advance by `steps` positions and return the
// element at that position.
// Precondition: steps < lst.size().
inline std::string advance_and_read(const std::list<std::string>& lst,
                                    std::size_t steps) {
    TODO();
}

// Return the element at the middle index of the vector.
// Middle index = vec.size() / 2.
// Precondition: vec is not empty.
inline int get_middle(const std::vector<int>& vec) {
    TODO();
}
