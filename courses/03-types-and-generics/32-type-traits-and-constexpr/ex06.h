// Exercise 06: enable_if (Legacy) and Concepts (Modern)
//
// Before C++20 concepts, SFINAE with std::enable_if was the primary way to
// constrain templates. enable_if<condition, T> has a member `type` equal to
// T when condition is true; when false, the type doesn't exist, which causes
// substitution failure (SFINAE) and removes the overload from consideration.
//
// C++20 concepts make this much cleaner with `requires` clauses.
//
// TODO:
//   1. Implement to_int_sfinae<T>(T value):
//      Use std::enable_if_t<std::is_integral_v<T>, int> as the return type.
//      Return static_cast<int>(value).
//
//   2. Implement to_int_concept<T>(T value):
//      Use a requires clause (or a concept) to constrain T to integral types.
//      Return static_cast<int>(value).
//
//   3. Implement numeric_to_string_sfinae<T>(T value):
//      Use enable_if to constrain T to arithmetic types.
//      Return std::to_string(value).
//
//   4. Implement numeric_to_string_concept<T>(T value):
//      Use a requires clause to constrain T to arithmetic types.
//      Return std::to_string(value).

#pragma once

#include <testkit/testkit.h>
#include <string>
#include <type_traits>

// Convert an integral value to int using SFINAE (enable_if).
// Hint: template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
int to_int_sfinae(T value) {
    TODO();
}

// Convert an integral value to int using a C++20 requires clause.
// Hint: template <typename T> requires std::integral<T>
template <typename T>
    requires std::integral<T>
int to_int_concept(T value) {
    TODO();
}

// Convert a numeric value to string using SFINAE (enable_if).
template <typename T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
std::string numeric_to_string_sfinae(T value) {
    TODO();
}

// Convert a numeric value to string using a C++20 requires clause.
template <typename T>
    requires std::is_arithmetic_v<T>
std::string numeric_to_string_concept(T value) {
    TODO();
}
