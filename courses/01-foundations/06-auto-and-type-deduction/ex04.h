// Exercise 04: Trailing Return Types
//
// PROBLEM:
//   C++ normally puts the return type before the function name:
//
//       int add(int a, int b);
//
//   The trailing return type syntax moves it after the parameter list:
//
//       auto add(int a, int b) -> int;
//
//   This is required in some template contexts where the return type
//   depends on the parameters. It's also a style choice that aligns
//   function names vertically.
//
// TODO:
//   Convert each function to use trailing return type syntax and
//   implement the body.

#pragma once

#include <testkit/testkit.h>
#include <string>
#include <vector>

// Convert to: auto add(int a, int b) -> int
inline int add(int a, int b) {
    TODO();
}

// Convert to: auto multiply(double a, double b) -> double
inline double multiply(double a, double b) {
    TODO();
}

// Convert to: auto make_greeting(const std::string& name) -> std::string
inline std::string make_greeting(const std::string& name) {
    TODO();
    // Return "Hello, " + name + "!"
}

// Convert to: auto clamp(int val, int lo, int hi) -> int
inline int clamp(int val, int lo, int hi) {
    TODO();
    // Return val clamped to [lo, hi]
}
