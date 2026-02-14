// Exercise 05: Explicit Specialization
//
// PROBLEM:
//   Sometimes the generic template implementation doesn't work well for
//   a specific type. You can provide an explicit specialization: a custom
//   implementation for one particular type.
//
//   The primary template defines the general behavior.
//   The specialization overrides it for one specific type.
//
// TODO:
//   1. Implement the primary template stringify<T>: convert val to a
//      string using std::to_string.
//   2. Implement the explicit specialization for std::string: return
//      the string wrapped in double quotes, e.g., "hello" becomes
//      "\"hello\"".
//   3. Implement the explicit specialization for bool: return "true"
//      or "false" (not "1" or "0" like to_string gives).
//
// WHY:
//   Specialization lets you customize generic behavior for types that
//   need different treatment, without changing the calling code. The
//   caller always writes stringify(val) regardless of the type.

#pragma once

#include <string>
#include <testkit/testkit.h>

// Primary template: convert val to string using std::to_string.
template<typename T>
std::string stringify(T val) {
    TODO();
}

// Explicit specialization for std::string: wrap in quotes.
// e.g., stringify(std::string("hello")) => "\"hello\""
template<>
inline std::string stringify<std::string>(std::string val) {
    TODO();
}

// Explicit specialization for bool: return "true" or "false".
template<>
inline std::string stringify<bool>(bool val) {
    TODO();
}
