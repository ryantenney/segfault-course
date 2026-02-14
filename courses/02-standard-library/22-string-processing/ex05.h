// Exercise 05: Trim Whitespace
//
// Trimming leading and trailing whitespace from strings is a fundamental
// operation that C++ does not provide out of the box. You can build it
// using std::string's search methods:
//
//   find_first_not_of(chars) - index of the first char NOT in `chars`
//   find_last_not_of(chars)  - index of the last char NOT in `chars`
//
// Both return std::string::npos if all characters match (i.e., the string
// is entirely whitespace or empty).
//
// The standard whitespace characters are: " \t\n\r\f\v"
//
// Example:
//   std::string s = "  hello  ";
//   auto start = s.find_first_not_of(" \t\n\r\f\v");  // 2
//   auto end   = s.find_last_not_of(" \t\n\r\f\v");   // 6
//   auto trimmed = s.substr(start, end - start + 1);   // "hello"
//
// TODO:
//   1. Implement ltrim() -- remove leading whitespace.
//   2. Implement rtrim() -- remove trailing whitespace.
//   3. Implement trim()  -- remove both leading and trailing whitespace.

#pragma once

#include <string>
#include <testkit/testkit.h>

// Remove leading whitespace characters (space, tab, newline, etc.)
// Return an empty string if the input is all whitespace.
inline std::string ltrim(const std::string& s) {
    TODO();
}

// Remove trailing whitespace characters.
// Return an empty string if the input is all whitespace.
inline std::string rtrim(const std::string& s) {
    TODO();
}

// Remove both leading and trailing whitespace characters.
// Return an empty string if the input is all whitespace.
inline std::string trim(const std::string& s) {
    TODO();
}
