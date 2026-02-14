// Exercise 08: View Lifetime Traps
//
// string_view is powerful but comes with lifetime pitfalls. Each function
// below has a comment saying whether it is SAFE or BUGGY.
//
// TODO:
//   1. For each SAFE function: implement it correctly.
//   2. For each BUGGY function: the return type needs to change from
//      std::string_view to std::string. Fix the return type and implement.
//
// Guiding principle:
//   A string_view is safe to return if the data it points to outlives the
//   returned view. It is NOT safe if it points to a local or temporary.

#pragma once

#include <string>
#include <string_view>
#include <testkit/testkit.h>

// SAFE: The input string_view points to caller-owned data.
// Returning a sub-view is fine — it still points into the caller's data.
//
// Implement: return the string_view without its first and last characters.
// If sv.size() < 2, return an empty view.
inline std::string_view strip_quotes(std::string_view sv) {
    TODO();
}

// BUGGY return type! Concatenation creates a NEW std::string. Returning a
// string_view into a local string is a dangling reference.
//
// Example of the bug:
//   std::string result = std::string(a) + std::string(b);
//   return result;  // dangling! result is destroyed on return
//
// FIX: Change the return type to std::string.
// Then implement: return std::string(a) + std::string(b).
inline std::string concat(std::string_view a, std::string_view b) {
    TODO();
}

// SAFE: We only read from the view to compute a result value (bool).
// No reference to the view's data escapes the function.
//
// Implement: return true if every character is a digit ('0'-'9').
// An empty string should return false.
inline bool is_all_digits(std::string_view sv) {
    TODO();
}

// BUGGY return type! std::to_string creates a temporary std::string.
// Returning a string_view into a temporary is a dangling reference.
//
// Example of the bug:
//   return std::to_string(value);  // dangling! temporary destroyed
//
// FIX: Change the return type to std::string.
// Then implement: return std::to_string(value).
inline std::string int_to_str(int value) {
    TODO();
}

// SAFE: string_view::find returns a position (size_t), not a reference.
// Returning a size_t is always safe — no lifetime concern.
//
// Implement: return the position of `needle` in `haystack`, or npos.
inline std::size_t find_pos(std::string_view haystack, std::string_view needle) {
    TODO();
}
