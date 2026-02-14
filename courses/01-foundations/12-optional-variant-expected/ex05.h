// Exercise 05: std::visit
//
// std::visit applies a callable (visitor) to the currently active type in a
// variant. The visitor must handle every alternative type, and the compiler
// enforces this at compile time.
//
// Basic usage:
//   std::variant<int, std::string> v = 42;
//   std::visit([](auto& val) { /* val is int or string */ }, v);
//
// For distinct behavior per type, you can use if-constexpr or overloaded
// function objects (next exercise). Here we use a single generic lambda
// where possible, and explicit lambdas where types need different handling.
//
// TODO:
//   1. Implement setting_to_string() — visit the Setting and convert the
//      held value to a string representation.
//      int -> std::to_string(value)
//      string -> the string itself
//      bool -> "true" or "false"
//
//   2. Implement double_setting() — visit the Setting and return a new Setting:
//      int -> doubled integer
//      string -> string concatenated with itself
//      bool -> negated boolean

#pragma once

#include <string>
#include <variant>
#include <testkit/testkit.h>

using Setting = std::variant<int, std::string, bool>;

// Convert any Setting to its string representation using std::visit.
inline std::string setting_to_string(const Setting& s) {
    TODO();
}

// Return a new Setting with the value "doubled":
//   int    -> value * 2
//   string -> value + value (concatenated)
//   bool   -> !value (negated)
inline Setting double_setting(const Setting& s) {
    TODO();
}
