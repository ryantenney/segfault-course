// Exercise 01: Return optional from Lookup
//
// A common antipattern in C and C++ is returning a sentinel value (-1, nullptr,
// empty string) to indicate "not found." The caller must remember to check for
// the sentinel, and the compiler won't help if they forget.
//
// std::optional<T> makes the "might not have a value" case explicit in the type
// system. An optional either holds a T or is empty (std::nullopt).
//
// TODO:
//   Rewrite find_user_age() to return std::optional<int> instead of int.
//   Return std::nullopt when the user is not found, and the age when found.
//
//   The lookup table is:
//     "Alice" -> 30, "Bob" -> 25, "Charlie" -> 35

#pragma once

#include <optional>
#include <string>
#include <testkit/testkit.h>

// Look up a user's age by name.
// Return the age wrapped in optional, or std::nullopt if not found.
inline std::optional<int> find_user_age(const std::string& name) {
    TODO();
}
