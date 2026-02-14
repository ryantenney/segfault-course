// Exercise 01: Replace Explicit Types with auto
//
// PROBLEM:
//   The functions below use verbose explicit types where auto would be
//   cleaner. When iterating containers with begin()/end(), the iterator
//   type name can be extremely long (e.g., std::vector<int>::iterator).
//   Using auto lets the compiler deduce the type for you.
//
// TODO:
//   1. In find_first(), replace the explicit iterator type with auto.
//   2. In sum_elements(), replace the explicit iterator type with auto.
//   3. In longest_string(), replace the explicit iterator type with auto.
//
// WHY:
//   auto reduces visual clutter without losing type safety. The compiler
//   still knows the exact type; you just don't have to spell it out.

#pragma once

#include <testkit/testkit.h>
#include <string>
#include <vector>

// Returns the first element equal to `target`, or -1 if not found.
// Replace the explicit iterator type with auto.
inline int find_first(const std::vector<int>& v, int target) {
    TODO();
    // Hint: use auto it = v.begin(); then loop with it != v.end()
}

// Returns the sum of all elements.
// Replace the explicit iterator type with auto.
inline int sum_elements(const std::vector<int>& v) {
    TODO();
    // Hint: use auto it = v.begin(); accumulate into a sum
}

// Returns the longest string in the vector, or "" if empty.
// Replace the explicit iterator type with auto.
inline std::string longest_string(const std::vector<std::string>& v) {
    TODO();
    // Hint: use auto best = v.begin(); compare lengths
}
