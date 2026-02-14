// Exercise 03: Number Conversion
//
// C++17 introduced std::from_chars and std::to_chars for fast,
// locale-independent number conversion. Unlike std::stoi or std::stod,
// these functions:
//   - Do not allocate memory
//   - Do not depend on the locale (no decimal-comma surprises)
//   - Report errors via std::errc, not exceptions
//
// std::to_chars writes characters into a buffer:
//   char buf[32];
//   auto [ptr, ec] = std::to_chars(buf, buf + sizeof(buf), 42);
//   // ptr points past the last character written
//   // ec == std::errc{} on success
//   std::string result(buf, ptr);  // "42"
//
// std::from_chars parses from a string:
//   std::string_view sv = "123";
//   int value = 0;
//   auto [ptr, ec] = std::from_chars(sv.data(), sv.data() + sv.size(), value);
//   // value == 123, ec == std::errc{} on success
//
// TODO:
//   1. Implement int_to_string() -- convert an int to a string using to_chars.
//   2. Implement string_to_int() -- parse a string to int using from_chars.
//      Return 0 if parsing fails.
//   3. Implement string_to_int_checked() -- parse a string to int, returning
//      std::optional<int>. Return std::nullopt if parsing fails or if there
//      are leftover characters.

#pragma once

#include <charconv>
#include <optional>
#include <string>
#include <string_view>
#include <testkit/testkit.h>

// Convert an integer to its string representation using std::to_chars.
inline std::string int_to_string(int value) {
    TODO();
}

// Parse a string as an integer using std::from_chars.
// Return 0 if parsing fails.
inline int string_to_int(std::string_view sv) {
    TODO();
}

// Parse a string as an integer using std::from_chars.
// Return std::nullopt if parsing fails or if there are trailing characters
// (i.e., the entire string must be a valid integer).
inline std::optional<int> string_to_int_checked(std::string_view sv) {
    TODO();
}
