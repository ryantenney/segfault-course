// Exercise 02: Split a String
//
// Splitting a string by a delimiter is one of the most common string
// operations, yet C++ does not provide a built-in split function.
// You can build one using std::string::find and std::string::substr
// in a loop:
//
//   std::size_t start = 0;
//   while (true) {
//       auto pos = s.find(delimiter, start);
//       tokens.push_back(s.substr(start, pos - start));
//       if (pos == std::string::npos) break;
//       start = pos + delimiter.size();
//   }
//
// TODO:
//   1. Implement split() -- split a string by a delimiter string and
//      return a vector of the resulting tokens.
//      - An empty input string should return a vector with one empty string.
//      - Consecutive delimiters produce empty strings between them.
//   2. Implement join() -- the inverse of split: combine a vector of
//      strings with a separator between each element.

#pragma once

#include <string>
#include <vector>
#include <testkit/testkit.h>

// Split `str` by `delimiter` and return the resulting tokens.
// Consecutive delimiters produce empty strings between them.
inline std::vector<std::string> split(const std::string& str,
                                       const std::string& delimiter) {
    TODO();
}

// Join a vector of strings with `separator` between each element.
// An empty vector returns an empty string.
inline std::string join(const std::vector<std::string>& parts,
                         const std::string& separator) {
    TODO();
}
