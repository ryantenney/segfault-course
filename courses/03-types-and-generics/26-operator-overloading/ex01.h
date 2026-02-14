// Exercise 01: Equality Operator
//
// The most fundamental operator to overload is operator==. Without it, you
// cannot compare two objects for logical equality — the compiler has no idea
// what "equal" means for your custom type.
//
// operator== can be defined as a member function or as a free (non-member)
// function. Either way, defining operator== also gives you operator!= for
// free in C++20 (the compiler rewrites a != b as !(a == b)).
//
// TODO:
//   1. Implement operator== for Point as a member function.
//      Two points are equal when both x and y match.
//   2. Implement operator== for Color as a free function.
//      Two colors are equal when r, g, and b all match.

#pragma once

#include <testkit/testkit.h>

struct Point {
    double x;
    double y;

    // Return true if this point has the same x and y as `other`.
    bool operator==(const Point& other) const {
        TODO();
    }
};

struct Color {
    int r;
    int g;
    int b;
};

// Return true if `a` and `b` have the same r, g, and b values.
inline bool operator==(const Color& a, const Color& b) {
    TODO();
}
