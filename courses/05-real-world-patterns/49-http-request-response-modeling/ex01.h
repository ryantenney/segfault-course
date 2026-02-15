// Exercise 01: HTTP Method Enum
//
// HTTP defines a small set of request methods (verbs). Modeling them as
// an enum class gives us type safety -- you can't accidentally pass an
// integer or a string where a method is expected.
//
// TODO:
//   1. Implement to_string(Method) -- return the uppercase string form
//      (e.g., Method::GET -> "GET", Method::DELETE_ -> "DELETE").
//   2. Implement method_from_string(str) -- return the matching Method.
//      Throw std::invalid_argument for unrecognized strings.
//
// NOTE: DELETE is a macro on some platforms, so the enumerator is DELETE_.

#pragma once

#include <testkit/testkit.h>
#include <stdexcept>
#include <string>

enum class Method {
    GET,
    POST,
    PUT,
    DELETE_,
    PATCH,
    HEAD,
    OPTIONS
};

// Convert a Method to its string representation.
// DELETE_ maps to "DELETE".
inline std::string to_string(Method m) {
    TODO();
}

// Convert a string to a Method.
// "DELETE" maps to Method::DELETE_.
// Throws std::invalid_argument for unknown strings.
inline Method method_from_string(const std::string& s) {
    TODO();
}
