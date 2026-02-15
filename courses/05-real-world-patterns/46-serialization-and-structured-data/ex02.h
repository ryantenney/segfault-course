// Exercise 02: Dynamic Value Type
//
// Structured data (JSON, config files, etc.) can hold values of different
// types. std::variant lets us create a sum type that can be exactly one of
// several alternatives at any time.
//
// We define a Value that can hold: string, int, double, bool, or "null"
// (represented by std::monostate).
//
// TODO:
//   1. Implement is_string(), is_int(), is_double(), is_bool(), is_null()
//      — return true if the Value currently holds that type.
//   2. Implement type_name() — return a string describing the current type:
//      "string", "int", "double", "bool", or "null".

#pragma once

#include <testkit/testkit.h>
#include <string>
#include <variant>

// A dynamic value that can hold one of several types.
using ValueBase = std::variant<std::monostate, std::string, int, double, bool>;

struct Value : ValueBase {
    // Inherit constructors from variant.
    using ValueBase::ValueBase;

    // Default-construct as null (monostate).
    Value() : ValueBase(std::monostate{}) {}

    inline bool is_string() const { TODO(); }
    inline bool is_int() const { TODO(); }
    inline bool is_double() const { TODO(); }
    inline bool is_bool() const { TODO(); }
    inline bool is_null() const { TODO(); }

    // Return "string", "int", "double", "bool", or "null".
    inline std::string type_name() const { TODO(); }
};
