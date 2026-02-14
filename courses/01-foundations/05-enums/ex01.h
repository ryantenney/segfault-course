// Exercise 01: Convert a C Enum to enum class
//
// C-style enums (unscoped enums) leak their enumerators into the
// surrounding scope and implicitly convert to int. This leads to
// confusing bugs where you can accidentally mix enum values with
// integers or values from a different enum.
//
// C++11 introduced `enum class` (scoped enums) which:
//   - Require qualified names: Color::Red instead of just Red
//   - Do NOT implicitly convert to int
//   - Can have an explicit underlying type
//
// PROBLEM:
//   The enum below is an old-style C enum. The enumerators Red, Green,
//   Blue are in the global scope. Convert it to `enum class`.
//
// TODO:
//   1. Change `enum Color` to `enum class Color`.
//   2. Fix the helper functions to use qualified names (Color::Red, etc.).

#pragma once

#include <testkit/testkit.h>

enum Color {
    Red,
    Green,
    Blue
};

// Return true if the color is Red.
inline bool is_red(Color c) {
    TODO();
}

// Return the "opposite" color:
//   Red → Blue, Blue → Red, Green → Green
inline Color opposite(Color c) {
    TODO();
}

// Return true if two colors are the same.
inline bool same_color(Color a, Color b) {
    TODO();
}
