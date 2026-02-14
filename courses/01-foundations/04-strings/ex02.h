// Exercise 02: Fix String Copies with string_view
//
// std::string_view is a non-owning, lightweight reference to a contiguous
// sequence of characters. It avoids copying when you only need to read.
//
// These functions currently take `const std::string&`, which forces the
// caller to own a std::string. If the caller has a string literal or a
// substring, the compiler must create a temporary std::string just to
// bind to the reference — an unnecessary heap allocation.
//
// TODO:
//   1. Change each parameter from `const std::string&` to `std::string_view`.
//   2. Implement the function bodies.
//
// IMPORTANT: You will also need to add #include <string_view> to this file.

#pragma once

#include <string>
#include <testkit/testkit.h>

// Return true if the string starts with the given prefix.
inline bool starts_with(const std::string& text, const std::string& prefix) {
    TODO();
}

// Return true if the string ends with the given suffix.
inline bool ends_with(const std::string& text, const std::string& suffix) {
    TODO();
}

// Return true if the string contains the given substring.
inline bool contains(const std::string& text, const std::string& substring) {
    TODO();
}
