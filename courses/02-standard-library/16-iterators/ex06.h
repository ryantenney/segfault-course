// Exercise 06: Back-Inserter
//
// Many algorithms write their output to a destination range, but they
// expect the destination to already have enough space. If the destination
// is empty, writing past its end is undefined behavior.
//
// std::back_inserter(container) creates an output iterator that calls
// push_back() on the container each time a value is assigned to it.
// This lets algorithms grow the destination automatically:
//
//   std::vector<int> src = {1, 2, 3};
//   std::vector<int> dst;
//   std::copy(src.begin(), src.end(), std::back_inserter(dst));
//   // dst is now {1, 2, 3}
//
// TODO:
//   1. Implement copy_to_vector() — use std::copy with std::back_inserter
//      to copy elements from a list into a new vector.
//   2. Implement transform_to_vector() — use std::transform with
//      std::back_inserter to apply a function to each element.
//   3. Implement merge_vectors() — use std::copy with std::back_inserter
//      to append all elements of `b` to the end of `a`.

#pragma once

#include <algorithm>
#include <functional>
#include <iterator>
#include <list>
#include <string>
#include <vector>
#include <testkit/testkit.h>

// Copy all elements from a list into a new vector using
// std::copy and std::back_inserter.
inline std::vector<int> copy_to_vector(const std::list<int>& lst) {
    TODO();
}

// Apply `func` to every element of `src` and push the results into a
// new vector using std::transform and std::back_inserter.
inline std::vector<int> transform_to_vector(const std::vector<int>& src,
                                            std::function<int(int)> func) {
    TODO();
}

// Append all elements of `b` to the end of `a` using std::copy and
// std::back_inserter. Modifies `a` in place.
inline void merge_vectors(std::vector<std::string>& a,
                          const std::vector<std::string>& b) {
    TODO();
}
