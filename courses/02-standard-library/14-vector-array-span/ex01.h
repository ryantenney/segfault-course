// Exercise 01: Populate a Vector
//
// std::vector is the go-to dynamic array in C++. You can construct one from
// an initializer list, or build it up element by element with push_back()
// and emplace_back().
//
// - Initializer list:   std::vector<int> v = {1, 2, 3};
// - push_back(val):     copies or moves `val` into the vector
// - emplace_back(args): constructs the element in-place (avoids a copy)
//
// TODO:
//   Implement the three functions below. Each builds a vector differently.

#pragma once

#include <testkit/testkit.h>
#include <vector>
#include <string>
#include <utility>

// Return a vector<int> containing {10, 20, 30, 40, 50} using
// initializer-list construction.
inline std::vector<int> make_vector_with_list() {
    TODO();
}

// Return a vector<int> containing {1, 2, 3, 4} by starting with an
// empty vector and calling push_back for each element.
inline std::vector<int> make_vector_push_back() {
    TODO();
}

// Return a vector<pair<string, int>> containing:
//   {"alice", 90}, {"bob", 85}, {"carol", 92}
// Use emplace_back to construct each pair in-place.
inline std::vector<std::pair<std::string, int>> make_vector_emplace() {
    TODO();
}
