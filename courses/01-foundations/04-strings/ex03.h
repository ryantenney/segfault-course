// Exercise 03: Substring Without Allocation
//
// std::string::substr() returns a NEW std::string, which allocates memory.
// std::string_view::substr() returns another string_view — just a pointer
// and a length — with zero heap allocation.
//
// When you only need to inspect a portion of a string (not modify it),
// string_view::substr is the right tool.
//
// TODO:
//   Implement each function using std::string_view::substr().
//   None of these should allocate heap memory.

#pragma once

#include <string_view>
#include <testkit/testkit.h>

// Return the first `n` characters of `sv`.
// If n > sv.size(), return the entire string_view.
inline std::string_view first_n(std::string_view sv, std::size_t n) {
    TODO();
}

// Return the last `n` characters of `sv`.
// If n > sv.size(), return the entire string_view.
inline std::string_view last_n(std::string_view sv, std::size_t n) {
    TODO();
}

// Remove the first `n` characters from `sv` and return what remains.
// If n > sv.size(), return an empty string_view.
inline std::string_view drop_first_n(std::string_view sv, std::size_t n) {
    TODO();
}

// Return the substring between positions `from` (inclusive) and `to` (exclusive).
// Clamp both values to sv.size().
inline std::string_view slice(std::string_view sv, std::size_t from, std::size_t to) {
    TODO();
}
