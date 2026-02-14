// Exercise 07: Insert Iterator
//
// std::inserter(container, pos) creates an output iterator that calls
// container.insert(pos, value) for each written element. This is useful
// for ordered containers like std::set, where you want to insert elements
// while maintaining the sorted order.
//
// Unlike back_inserter (which only works with containers that have
// push_back), inserter works with any container that has an insert()
// method taking a position hint -- including set, map, and list.
//
//   std::set<int> s;
//   std::copy(vec.begin(), vec.end(), std::inserter(s, s.end()));
//
// TODO:
//   1. Implement vector_to_set() — copy elements from a vector into a
//      new set using std::copy and std::inserter.
//   2. Implement merge_sets() — copy elements from set `b` into set `a`
//      using std::copy and std::inserter.
//   3. Implement insert_at_front() — use std::inserter with lst.begin()
//      to insert elements at the front of a list, reversing their order.

#pragma once

#include <algorithm>
#include <iterator>
#include <list>
#include <set>
#include <vector>
#include <testkit/testkit.h>

// Copy elements from a vector into a new set.
// Use std::copy with std::inserter.
inline std::set<int> vector_to_set(const std::vector<int>& vec) {
    TODO();
}

// Insert all elements from set `b` into set `a`.
// Use std::copy with std::inserter. Modifies `a` in place.
inline void merge_sets(std::set<int>& a, const std::set<int>& b) {
    TODO();
}

// Insert elements from `src` at the front of `lst` using
// std::inserter(lst, lst.begin()). This reverses their order in the
// resulting list because each insert pushes before the current front.
inline void insert_at_front(std::list<int>& lst, const std::vector<int>& src) {
    TODO();
}
