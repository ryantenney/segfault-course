// Exercise 06: Case Conversion
//
// C++ does not have built-in to_lower/to_upper for strings. You can
// build them using std::transform with the character-level functions
// from <cctype>:
//
//   std::tolower(ch) -- convert a single char to lowercase
//   std::toupper(ch) -- convert a single char to uppercase
//
// std::transform applies a function to each element in a range and
// writes the result to an output range:
//
//   std::string s = "Hello";
//   std::string lower;
//   lower.resize(s.size());
//   std::transform(s.begin(), s.end(), lower.begin(),
//                  [](unsigned char c) { return std::tolower(c); });
//   // lower == "hello"
//
// Note: We cast to unsigned char because std::tolower/toupper have
// undefined behavior if the argument is negative (signed char values
// above 127). The lambda parameter type `unsigned char` handles this.
//
// These functions only handle ASCII characters. For full Unicode case
// conversion, you would need a library like ICU.
//
// TODO:
//   1. Implement to_lower() -- convert all ASCII letters to lowercase.
//   2. Implement to_upper() -- convert all ASCII letters to uppercase.
//   3. Implement is_equal_ignore_case() -- compare two strings case-insensitively
//      (for ASCII characters only).

#pragma once

#include <algorithm>
#include <cctype>
#include <string>
#include <testkit/testkit.h>

// Return a copy of `s` with all ASCII uppercase letters converted to lowercase.
inline std::string to_lower(std::string s) {
    TODO();
}

// Return a copy of `s` with all ASCII lowercase letters converted to uppercase.
inline std::string to_upper(std::string s) {
    TODO();
}

// Return true if the two strings are equal when compared case-insensitively
// (ASCII only).
inline bool is_equal_ignore_case(const std::string& a, const std::string& b) {
    TODO();
}
