// Exercise 02: Numeric Casts
//
// PROBLEM:
//   static_cast is the workhorse for numeric conversions: int to double,
//   double to int, int to enum, and enum to int. It also serves as a
//   clear signal that you intentionally accept narrowing.
//
// TODO:
//   Implement each function using static_cast. The enum Color is
//   provided below with explicit underlying values.
//
// WHY:
//   Implicit conversions between numeric types can hide bugs. Using
//   static_cast makes every conversion deliberate and visible.

#pragma once
#include <testkit/testkit.h>

enum class Color : int {
    Red   = 0,
    Green = 1,
    Blue  = 2
};

// Convert a double to int using static_cast (truncation).
inline int truncate(double value) {
    TODO();
}

// Safely compute an integer ratio as a double.
// E.g., safe_divide(7, 2) should return 3.5, not 3.
inline double safe_divide(int numerator, int denominator) {
    TODO();
}

// Convert an enum to its underlying int value.
inline int color_to_int(Color c) {
    TODO();
}

// Convert an int to a Color enum value.
inline Color int_to_color(int value) {
    TODO();
}

// Demonstrate narrowing: convert a large double to a short.
// This is intentional narrowing — static_cast documents the intent.
inline short narrow_to_short(double value) {
    TODO();
}
