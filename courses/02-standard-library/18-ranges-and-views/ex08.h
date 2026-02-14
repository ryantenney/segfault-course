// Exercise 08: Split and Join
//
// views::split divides a range into subranges at each occurrence of a
// delimiter. Each subrange is itself a view, so there is no allocation.
//
//   std::string_view csv = "one,two,three";
//   for (auto part : csv | std::views::split(',')) {
//       // part is a subrange of characters
//   }
//
// To collect each subrange into a std::string, construct a string from
// the subrange's begin/end iterators or use std::string(part.begin(), part.end()).
//
// A common pattern: use ranges::begin and ranges::end with the
// std::string range constructor.
//
// TODO:
//   1. Implement split_by_comma() -- split a comma-separated string_view
//      into a vector<string>.
//   2. Implement split_by_char() -- split a string_view by an arbitrary
//      delimiter character into a vector<string>.
//   3. Implement count_words() -- split a string_view by spaces and
//      return the number of non-empty parts.

#pragma once

#include <ranges>
#include <string>
#include <string_view>
#include <vector>
#include <testkit/testkit.h>

// Split a comma-separated string_view into a vector of strings.
inline std::vector<std::string> split_by_comma(std::string_view input) {
    TODO();
}

// Split a string_view by the given delimiter character.
inline std::vector<std::string> split_by_char(std::string_view input, char delim) {
    TODO();
}

// Split by spaces and count the non-empty parts.
inline std::size_t count_words(std::string_view input) {
    TODO();
}
