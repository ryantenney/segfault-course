// Exercise 06: Overloaded Visitor
//
// Writing a visitor with per-type behavior often requires an if-constexpr
// chain or a struct with multiple operator() overloads. The "overloaded"
// pattern provides a concise way to combine multiple lambdas into one visitor:
//
//   template<class... Ts>
//   struct overloaded : Ts... { using Ts::operator()...; };
//
// Usage:
//   std::visit(overloaded{
//       [](int i)         { return "int"; },
//       [](const string&) { return "string"; },
//       [](bool b)        { return "bool"; },
//   }, my_variant);
//
// TODO:
//   1. Define the overloaded template (the struct above) in this file.
//   2. Implement describe_shape() using std::visit with overloaded{...}
//      to return a string description for each shape type.
//   3. Implement shape_area() using std::visit with overloaded{...}
//      to compute the area of each shape.

#pragma once

#include <cmath>
#include <string>
#include <variant>
#include <testkit/testkit.h>

// --- Shape types ---

struct Circle {
    double radius;
};

struct Rectangle {
    double width;
    double height;
};

struct Triangle {
    double base;
    double height;
};

using Shape = std::variant<Circle, Rectangle, Triangle>;

// TODO: Define the overloaded template here.
// template<class... Ts>
// struct overloaded : Ts... { using Ts::operator()...; };

// Return a description string for the shape:
//   Circle    -> "circle(r=<radius>)"    e.g. "circle(r=5)"
//   Rectangle -> "rect(<w>x<h>)"         e.g. "rect(3x4)"
//   Triangle  -> "tri(b=<b>,h=<h>)"      e.g. "tri(b=6,h=3)"
//
// Use std::to_string() to format the doubles. Don't worry about trailing zeros.
// Hint: use std::visit with overloaded{...}.
inline std::string describe_shape(const Shape& shape) {
    TODO();
}

// Return the area of the shape:
//   Circle    -> pi * r * r
//   Rectangle -> w * h
//   Triangle  -> 0.5 * b * h
//
// Use M_PI for pi or 3.14159265358979.
inline double shape_area(const Shape& shape) {
    TODO();
}
