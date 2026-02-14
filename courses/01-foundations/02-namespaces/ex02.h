// Exercise 02: Nested Namespaces
//
// PROBLEM:
//   The functions below use the verbose C++03 style for nested namespaces:
//     namespace a { namespace b { namespace c { ... }}}
//   C++17 introduced a compact syntax:
//     namespace a::b::c { ... }
//
// TODO:
//   1. Convert the verbose nested namespace syntax to C++17 compact form.
//   2. Implement each function body.
//
// WHY:
//   Deeply nested namespaces are common in large codebases (e.g.,
//   company::project::module). The C++17 syntax reduces boilerplate
//   and indentation, making the code easier to read.

#pragma once

#include <testkit/testkit.h>

// TODO: convert to  namespace engine::physics::units { ... }
namespace engine {
namespace physics {
namespace units {

inline double meters_to_feet(double meters) {
    TODO();
}

inline double feet_to_meters(double feet) {
    TODO();
}

inline double celsius_to_fahrenheit(double celsius) {
    TODO();
}

} // namespace units
} // namespace physics
} // namespace engine
