// Exercise 04: String to Enum
//
// The reverse of to_string: parse a string into an enum value.
// Since the string might not match any known value, the return type
// should be std::optional<Enum> — returning std::nullopt for unknown inputs.
//
// TODO:
//   Implement from_string for the Season enum class.
//   Return std::nullopt if the input doesn't match any season name.

#pragma once

#include <optional>
#include <string_view>
#include <testkit/testkit.h>

enum class Season {
    Spring,
    Summer,
    Autumn,
    Winter
};

// Convert a string to a Season.
// Valid inputs: "Spring", "Summer", "Autumn", "Winter" (case-sensitive).
// Return std::nullopt for anything else.
inline std::optional<Season> from_string(std::string_view name) {
    TODO();
}

// Return true if the given string is a valid season name.
inline bool is_valid_season(std::string_view name) {
    TODO();
}
