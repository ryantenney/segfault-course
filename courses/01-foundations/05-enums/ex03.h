// Exercise 03: Enum to String
//
// enum class values cannot be directly printed — std::cout << Color::Red
// won't compile. You need a conversion function.
//
// The standard pattern is a to_string function with a switch statement.
// This approach is preferred because the compiler can warn if you miss
// a case (with -Wswitch or equivalent).
//
// TODO:
//   Implement to_string for the Direction enum class.

#pragma once

#include <string_view>
#include <testkit/testkit.h>

enum class Direction {
    North,
    South,
    East,
    West
};

// Convert a Direction to its string name.
// Return "North", "South", "East", or "West".
//
// Use a switch statement. Do NOT add a default case — let the compiler
// warn you if you forget a value.
inline std::string_view to_string(Direction d) {
    TODO();
}

// Return the direction as an arrow character:
//   North → '^', South → 'v', East → '>', West → '<'
inline char to_arrow(Direction d) {
    TODO();
}
