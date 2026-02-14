// Exercise 06: Overload vs Specialization
//
// PROBLEM:
//   In C++, a non-template function overload is preferred over a template
//   specialization during overload resolution. This matters because:
//
//     template<typename T> void print(T val);        // primary template
//     template<> void print<int>(int val);            // specialization
//     void print(int val);                            // overload (wins!)
//
//   When you call print(42), the non-template overload wins. The
//   specialization is only considered if the primary template is selected.
//
//   Best practice: prefer overloads over specializations for functions.
//   (Class templates don't have this issue because classes can't be overloaded.)
//
// TODO:
//   1. Implement the primary template format_value<T>: return
//      "value: " + std::to_string(val).
//   2. Implement the non-template overload for const char*:
//      return "text: " + std::string(val).
//   3. Implement the non-template overload for std::string:
//      return "text: " + val.
//
// WHY:
//   Understanding overload resolution with templates prevents surprises.
//   If you specialize a template but someone adds a plain overload, the
//   overload wins. Prefer overloads for functions; use specialization
//   for class templates.

#pragma once

#include <string>
#include <testkit/testkit.h>

// Primary template: format any numeric value.
template<typename T>
std::string format_value(T val) {
    TODO();
}

// Non-template overload for C strings.
// This is preferred over the template when called with a const char*.
inline std::string format_value(const char* val) {
    TODO();
}

// Non-template overload for std::string.
inline std::string format_value(const std::string& val) {
    TODO();
}
