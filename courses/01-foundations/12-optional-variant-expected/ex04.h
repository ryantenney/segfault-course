// Exercise 04: Variant Basics
//
// std::variant<Types...> is a type-safe union. It holds exactly one of its
// alternative types at any time. Unlike a C union, variant tracks which type
// is currently active and throws std::bad_variant_access if you try to
// access the wrong one.
//
// Key operations:
//   std::get<T>(v)       — access by type; throws if wrong type is active
//   std::get<I>(v)       — access by index; throws if wrong index is active
//   std::get_if<T>(&v)   — returns pointer to T, or nullptr if wrong type
//   v.index()            — returns the zero-based index of the active type
//   std::holds_alternative<T>(v) — returns true if T is the active type
//
// TODO:
//   1. Implement make_int_setting() — return a Setting holding an int.
//   2. Implement make_string_setting() — return a Setting holding a string.
//   3. Implement make_bool_setting() — return a Setting holding a bool.
//   4. Implement setting_type_name() — return "int", "string", or "bool"
//      depending on which type the variant currently holds.
//   5. Implement get_int_or() — if the variant holds an int, return it;
//      otherwise return the default value.

#pragma once

#include <string>
#include <variant>
#include <testkit/testkit.h>

// A configuration setting that can be an int, string, or bool.
using Setting = std::variant<int, std::string, bool>;

inline Setting make_int_setting(int value) {
    TODO();
}

inline Setting make_string_setting(const std::string& value) {
    TODO();
}

inline Setting make_bool_setting(bool value) {
    TODO();
}

// Return "int", "string", or "bool" depending on the active type.
// Hint: use std::holds_alternative<T>() or v.index().
inline std::string setting_type_name(const Setting& s) {
    TODO();
}

// If the setting holds an int, return it. Otherwise return default_val.
// Hint: use std::get_if<int>(&s).
inline int get_int_or(const Setting& s, int default_val) {
    TODO();
}
