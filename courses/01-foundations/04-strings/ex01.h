// Exercise 01: String Basics
//
// std::string is the standard owning string type. It manages its own memory
// on the heap and supports a rich set of member functions.
//
// TODO:
//   Implement the functions below using std::string construction and
//   basic member functions: size(), empty(), clear().

#pragma once

#include <string>
#include <testkit/testkit.h>

// Return a std::string constructed from the given C-string literal.
inline std::string make_greeting(const char* name) {
    TODO();
}

// Return the number of characters in the string.
inline std::size_t string_length(const std::string& s) {
    TODO();
}

// Return true if the string is empty.
inline bool is_empty(const std::string& s) {
    TODO();
}

// Return a copy of `s` that has been cleared (i.e., an empty string).
// Hint: copy the string, call clear() on it, return it.
inline std::string cleared_copy(const std::string& s) {
    TODO();
}

// Construct a string of `count` copies of character `ch`.
// Hint: std::string has a constructor that takes (count, char).
inline std::string repeat_char(std::size_t count, char ch) {
    TODO();
}
