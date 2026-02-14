// Exercise 04: Explicit Constructors
//
// PROBLEM:
//   A single-argument constructor acts as an implicit conversion from
//   the argument type to the class type. This can cause surprising bugs:
//
//     void process(Meters m);
//     process(42);  // Compiles! Implicitly converts int -> Meters
//
//   The `explicit` keyword prevents this implicit conversion.
//
// TODO:
//   1. Add `explicit` to the Meters and Kilograms constructors to
//      prevent implicit conversions.
//   2. Implement the getter methods and the free functions.
//   3. The add_distances and add_weights functions should work with
//      explicit types — callers must construct them explicitly.
//
// WHY:
//   Implicit conversions from a single constructor argument are a
//   common source of bugs. The C++ Core Guidelines recommend making
//   single-argument constructors explicit unless implicit conversion
//   is genuinely desired (e.g., std::string from const char*).

#pragma once

#include <testkit/testkit.h>

class Meters {
private:
    double value_;

public:
    // TODO: Add `explicit` keyword to prevent implicit conversion.
    Meters(double v) : value_(v) {}

    double value() const {
        TODO();
    }
};

class Kilograms {
private:
    double value_;

public:
    // TODO: Add `explicit` keyword to prevent implicit conversion.
    Kilograms(double v) : value_(v) {}

    double value() const {
        TODO();
    }
};

// Returns the sum of two distances.
inline Meters add_distances(Meters a, Meters b) {
    TODO();
}

// Returns the sum of two weights.
inline Kilograms add_weights(Kilograms a, Kilograms b) {
    TODO();
}

// Returns true if the given distance is "tall" (> 1.8 meters).
inline bool is_tall(Meters m) {
    TODO();
}
