// Exercise 02: Fix a Parameter Type
//
// PROBLEM:
//   The `greet()` function takes a std::string by value. Every call
//   copies the entire string — wasteful when the function only needs
//   to read it.
//
// TODO:
//   1. Change the parameter from `std::string name` to
//      `const std::string& name` (const reference).
//   2. Implement the function to return "Hello, <name>!".
//
// WHY:
//   Passing by const reference avoids copying while still preventing
//   modification. This is the default choice for any type larger than
//   a pointer that you don't need to modify.

#pragma once

#include <testkit/testkit.h>
#include <string>

// TODO: Change `std::string name` to `const std::string& name`
inline std::string greet(std::string name) {
    TODO();
}

// TODO: Change `std::string first` and `std::string last` to const references
inline std::string full_greeting(std::string first, std::string last) {
    TODO();
}
