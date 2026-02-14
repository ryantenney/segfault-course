// Exercise 03: auto in range-for
//
// PROBLEM:
//   Range-for loops are a natural fit for auto. Choosing the right
//   form of auto controls whether you copy, reference, or move elements:
//
//   - for (auto x : v)         → copies each element
//   - for (auto& x : v)        → mutable reference (can modify)
//   - for (const auto& x : v)  → read-only reference (no copy)
//   - for (auto&& x : v)       → forwarding reference (works everywhere)
//
// TODO:
//   Implement each function using the appropriate form of auto.

#pragma once

#include <testkit/testkit.h>
#include <string>
#include <vector>

// Return the sum of all elements. Use const auto& to avoid copies.
inline int sum(const std::vector<int>& v) {
    TODO();
}

// Negate every element in-place. Use auto& to modify.
inline void negate_all(std::vector<int>& v) {
    TODO();
}

// Build a comma-separated string: "1,2,3" (no trailing comma).
// Use const auto& to avoid copying ints (though ints are cheap,
// this teaches the habit for expensive types).
inline std::string join(const std::vector<int>& v) {
    TODO();
}

// Append "!" to every string in-place. Use auto& to modify.
inline void exclaim_all(std::vector<std::string>& v) {
    TODO();
}

// Return true if any string in the vector equals the target.
// Use const auto& since we only need to read.
inline bool contains(const std::vector<std::string>& v, const std::string& target) {
    TODO();
}
