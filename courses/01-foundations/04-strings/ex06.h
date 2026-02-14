// Exercise 06: String Comparison
//
// std::string supports == and < for lexicographic comparison. But what if
// you need case-insensitive comparison? The standard library doesn't provide
// one directly, so you build it from std::tolower and std::equal.
//
// TODO:
//   Implement the functions below.
//
// HINT for case-insensitive comparison:
//   Use std::equal with a custom predicate that compares tolower of each char.
//   Remember that std::tolower takes and returns int, so you need a cast:
//     static_cast<unsigned char>(ch)

#pragma once

#include <algorithm>
#include <cctype>
#include <string>
#include <string_view>
#include <testkit/testkit.h>

// Return a lowercase copy of the input string.
inline std::string to_lower(std::string_view sv) {
    TODO();
}

// Return true if two strings are equal, ignoring case.
// Hint: check that sizes match first, then use std::equal with a lambda
// that compares std::tolower of each character.
inline bool iequals(std::string_view a, std::string_view b) {
    TODO();
}

// Return true if `text` starts with `prefix`, ignoring case.
inline bool istarts_with(std::string_view text, std::string_view prefix) {
    TODO();
}
