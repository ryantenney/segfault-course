// Exercise 08: auto Return Type
//
// PROBLEM:
//   In C++14 and later, you can let the compiler deduce a function's
//   return type using `auto`:
//
//     auto square(int x) { return x * x; }  // deduced as int
//
//   The compiler examines the return statement(s) and deduces the type.
//   All return statements must yield the same type.
//
//   This is especially useful for:
//   - Lambda-like short functions where the type is obvious
//   - Template code where spelling the type would be complex
//
// RULES:
//   - If there are multiple return statements, they must all deduce
//     to the same type.
//   - The function body must be visible (can't separate into .cpp).
//   - auto never deduces to a reference; use auto& or decltype(auto)
//     if you need one.
//
// TODO:
//   1. Change each function's return type from the explicit type to
//      `auto`.
//   2. Implement the function body with a return statement.
//   The compiler will deduce the return type from your return statement.

#pragma once

#include <testkit/testkit.h>
#include <string>
#include <vector>

// TODO: Change return type to auto, then implement.
// Return the absolute value of x.
inline int absolute(int x) {
    TODO();
}

// TODO: Change return type to auto, then implement.
// Return the larger of two values.
inline int max_of(int a, int b) {
    TODO();
}

// TODO: Change return type to auto, then implement.
// Return true if the string is a palindrome, false otherwise.
inline bool is_palindrome(const std::string& s) {
    TODO();
    // Hint: compare s with std::string(s.rbegin(), s.rend())
}

// TODO: Change return type to auto, then implement.
// Return a vector containing n copies of the given value.
inline std::vector<int> repeat(int value, int n) {
    TODO();
    // Hint: return std::vector<int>(n, value);
}

// TODO: Change return type to auto, then implement.
// Return the element at index `i`, or a fallback if out of range.
inline int safe_get(const std::vector<int>& v, int i, int fallback) {
    TODO();
}
