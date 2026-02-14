// Exercise 06: Return a Const Reference
//
// PROBLEM:
//   When you have a container and want to provide access to an element
//   without copying it, you return a const reference. This avoids a
//   potentially expensive copy (especially for large objects like strings)
//   while preventing modification of the container's internals.
//
// TODO:
//   1. Implement `max_element(v)` to return a const reference to the
//      largest element in the vector.
//   2. Implement `longest_string(v)` to return a const reference to
//      the longest string in the vector.
//
// IMPORTANT: The vector must not be empty. The tests guarantee this.
//
// WHY:
//   Returning by const reference is a core pattern in C++. It shows up
//   in std::vector::front(), std::map::at(), and countless other APIs.
//   It gives the caller read access without copying.

#pragma once

#include <testkit/testkit.h>
#include <vector>
#include <string>

// Return a const reference to the largest element.
// Precondition: v is not empty.
inline const int& max_element(const std::vector<int>& v) {
    TODO();
}

// Return a const reference to the longest string.
// If there's a tie, return the first one found.
// Precondition: v is not empty.
inline const std::string& longest_string(const std::vector<std::string>& v) {
    TODO();
}
