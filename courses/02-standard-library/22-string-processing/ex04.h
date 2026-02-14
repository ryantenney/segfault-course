// Exercise 04: Format Strings
//
// C++20 introduced std::format, a type-safe, extensible alternative to
// printf and string concatenation with ostringstream. It uses Python-style
// replacement fields:
//
//   std::format("Hello, {}!", "world")          -> "Hello, world!"
//   std::format("{} + {} = {}", 1, 2, 3)        -> "1 + 2 = 3"
//   std::format("{:.2f}", 3.14159)              -> "3.14"
//   std::format("{:>10}", "hi")                 -> "        hi"
//   std::format("{:0>5}", 42)                   -> "00042"
//
// Positional arguments (0-indexed) allow reordering:
//   std::format("{1} before {0}", "second", "first")  -> "first before second"
//
// Common format specifiers:
//   {:d}   - decimal integer (default for int)
//   {:x}   - hexadecimal
//   {:o}   - octal
//   {:b}   - binary
//   {:f}   - fixed-point float
//   {:e}   - scientific notation
//   {:.Nf} - N decimal places
//   {:>W}  - right-align in width W
//   {:<W}  - left-align in width W
//   {:^W}  - center in width W
//   {:0W}  - zero-pad to width W
//
// TODO:
//   1. Implement greet() -- format a greeting using a name and age.
//   2. Implement format_price() -- format a price to 2 decimal places
//      with a dollar sign.
//   3. Implement format_table_row() -- format a row with fixed-width
//      columns: name (left-aligned, 20 chars) and score (right-aligned, 5 chars).

#pragma once

#include <format>
#include <string>
#include <testkit/testkit.h>

// Return "Hello, <name>! You are <age> years old."
inline std::string greet(const std::string& name, int age) {
    TODO();
}

// Return a string like "$12.50" -- dollar sign followed by the amount
// formatted to exactly 2 decimal places.
inline std::string format_price(double amount) {
    TODO();
}

// Format a table row: name left-aligned in 20 characters, followed by a
// space, followed by score right-aligned in 5 characters.
// Example: "Alice               100" (20 chars for name, space, 5 for score)
inline std::string format_table_row(const std::string& name, int score) {
    TODO();
}
