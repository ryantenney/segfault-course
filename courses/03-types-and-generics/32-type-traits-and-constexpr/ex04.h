// Exercise 04: constexpr Variable (Compile-Time Lookup Table)
//
// A `constexpr` variable must be initialized with a compile-time constant
// expression. This is perfect for lookup tables that never change at runtime.
//
// std::array is constexpr-friendly: you can create and fill one entirely at
// compile time using a constexpr function, then declare the result as a
// constexpr variable.
//
// TODO:
//   1. Implement the constexpr helper function make_squares_table():
//      Return a std::array<int, 10> where element i holds i*i.
//   2. The constexpr variable `squares_table` is already declared below.
//      It will work once make_squares_table() is implemented.
//   3. Implement the constexpr helper function make_ascii_table():
//      Return a std::array<bool, 128> where element i is true if i
//      represents a lowercase letter ('a' through 'z').
//   4. The constexpr variable `is_lower` is already declared below.

#pragma once

#include <testkit/testkit.h>
#include <array>

// Gate function -- tests call this first so TODO() causes "skipped".
inline void ex04_gate() {
    TODO();
}

// Return a std::array<int, 10> where arr[i] = i * i.
constexpr std::array<int, 10> make_squares_table() {
    std::array<int, 10> table{};
    // Implement: fill table[i] = i * i
    return table;
}

// Compile-time lookup table: squares_table[i] == i*i for i in [0, 10).
constexpr auto squares_table = make_squares_table();

// Return a std::array<bool, 128> where arr[i] is true for lowercase letters.
constexpr std::array<bool, 128> make_ascii_table() {
    std::array<bool, 128> table{};
    // Implement: set table[c] = true for 'a' <= c <= 'z'
    return table;
}

// Compile-time lookup table: is_lower[ch] == true when ch is a-z.
constexpr auto is_lower = make_ascii_table();
