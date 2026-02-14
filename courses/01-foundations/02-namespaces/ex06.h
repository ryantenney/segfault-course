// Exercise 06: Namespace Alias
//
// PROBLEM:
//   The fully-qualified names in the functions below are long and
//   repetitive: `engine::physics::units::meters_to_feet(...)`.
//   This hurts readability, especially when the same namespace
//   is referenced multiple times in a function.
//
// TODO:
//   1. Inside each function, create a namespace alias:
//        namespace units = engine::physics::units;
//   2. Use the alias to call the conversion functions.
//   3. Implement each function body.
//
// WHY:
//   Namespace aliases let you shorten deeply nested namespaces
//   without polluting the enclosing scope. Unlike `using namespace`,
//   an alias is explicit about what it refers to.

#pragma once

#include <testkit/testkit.h>
#include <string>

namespace engine::physics::units {

inline double km_to_miles(double km) {
    return km * 0.621371;
}

inline double miles_to_km(double miles) {
    return miles / 0.621371;
}

inline double kg_to_pounds(double kg) {
    return kg * 2.20462;
}

} // namespace engine::physics::units

namespace converter {

// TODO: Create a namespace alias and use it to call km_to_miles.
inline double convert_km_to_miles(double km) {
    TODO();
}

// TODO: Create a namespace alias and use it to call miles_to_km.
inline double convert_miles_to_km(double miles) {
    TODO();
}

// TODO: Create a namespace alias and use it to call kg_to_pounds.
inline double convert_kg_to_pounds(double kg) {
    TODO();
}

} // namespace converter
