// Exercise 07: Simple Regex Match
//
// C++11 added <regex> for regular expression support. The main types are:
//
//   std::regex   -- a compiled regular expression pattern
//   std::smatch  -- holds match results for std::string
//
// Key functions:
//   std::regex_match(str, pattern)  -- true if the ENTIRE string matches
//   std::regex_search(str, pattern) -- true if the pattern is found ANYWHERE
//   std::regex_match(str, match, pattern)  -- match + capture groups
//
// Common regex syntax:
//   .     - any character
//   \d    - digit [0-9]    (use \\d in C++ strings)
//   \w    - word char       (use \\w in C++ strings)
//   +     - one or more
//   *     - zero or more
//   ?     - zero or one
//   {n,m} - between n and m
//   [abc] - character class
//   (...)  - capture group
//   ^, $  - start/end of string
//
// Note: In C++ string literals, backslashes must be doubled:
//   std::regex pattern("\\d+");  // matches one or more digits
// Or use raw string literals:
//   std::regex pattern(R"(\d+)"); // same, but more readable
//
// TODO:
//   1. Implement is_valid_identifier() -- return true if the string is a
//      valid C++ identifier: starts with a letter or underscore, followed
//      by zero or more letters, digits, or underscores. Use std::regex_match.
//   2. Implement contains_number() -- return true if the string contains
//      at least one sequence of digits anywhere in it. Use std::regex_search.
//   3. Implement is_valid_email_simple() -- return true if the string
//      matches a simplified email pattern: one or more word characters,
//      then '@', then one or more word characters, then '.', then 2-4
//      letters. Use std::regex_match.

#pragma once

#include <regex>
#include <string>
#include <testkit/testkit.h>

// Return true if `s` is a valid C++ identifier:
// starts with letter or underscore, followed by letters/digits/underscores.
inline bool is_valid_identifier(const std::string& s) {
    TODO();
}

// Return true if `s` contains at least one sequence of digits.
inline bool contains_number(const std::string& s) {
    TODO();
}

// Return true if `s` matches a simplified email pattern:
//   \w+@\w+\.[a-zA-Z]{2,4}
// This is NOT a production email validator -- just a learning exercise.
inline bool is_valid_email_simple(const std::string& s) {
    TODO();
}
