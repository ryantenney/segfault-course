// Exercise 08: Variadic Template Intro
//
// PROBLEM:
//   A variadic template accepts any number of arguments of any types.
//   The syntax uses "..." (parameter pack):
//
//     template<typename... Args>
//     void func(Args... args);
//
//   To process the arguments, you typically use recursion or fold
//   expressions (C++17). This exercise uses the ostringstream approach:
//   expand the pack into a stream to concatenate all values into a string.
//
// TODO:
//   1. Implement concat_all: take any number of arguments and concatenate
//      them into a single string using std::ostringstream.
//   2. Implement count_args: return the number of arguments (use sizeof...).
//
// HINT for concat_all:
//   Use a fold expression with the comma operator and operator<<:
//     std::ostringstream oss;
//     (oss << ... << args);
//     return oss.str();
//
// WHY:
//   Variadic templates are the foundation of many C++ patterns: perfect
//   forwarding (make_unique, emplace_back), tuple, variant, and logging
//   frameworks. This exercise introduces the basic mechanics.

#pragma once

#include <cstddef>
#include <sstream>
#include <string>
#include <testkit/testkit.h>

// Concatenate all arguments into a single string.
// Each argument is written to an ostringstream using operator<<.
template<typename... Args>
std::string concat_all(Args... args) {
    TODO();
}

// Return the number of arguments passed.
template<typename... Args>
std::size_t count_args(Args... args) {
    TODO();
}
