// Exercise 01: struct vs class
//
// PROBLEM:
//   In C++, `struct` and `class` are almost identical. The only difference
//   is the default access level:
//     - struct: members are public by default
//     - class:  members are private by default
//
//   Below is a `struct Point` with all members publicly accessible.
//   The tests expect it to be a `class` with explicit public access.
//
// TODO:
//   1. Change the `struct` keyword to `class`.
//   2. Add `public:` before the members so they remain accessible.
//   3. Implement the `distance_to` method.
//
// WHY:
//   Understanding this distinction is the first step toward encapsulation.
//   By convention, `struct` is used for plain data aggregates and `class`
//   for types with invariants or behavior. The choice signals intent.

#pragma once

#include <testkit/testkit.h>
#include <cmath>

struct Point {
    double x;
    double y;

    // Returns the Euclidean distance from this point to another.
    double distance_to(const Point& other) const {
        TODO();
    }
};

// Returns true if the given type is a class (not a struct).
// Hint: std::is_class_v is true for BOTH struct and class, so we can't
// distinguish them that way. But we CAN check default accessibility:
// a class with no explicit access specifier has private members.
// The test uses a different approach — see the test file.

// Free function: compute the midpoint of two Points.
inline Point midpoint(const Point& a, const Point& b) {
    TODO();
}
