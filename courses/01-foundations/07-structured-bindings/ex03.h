// Exercise 03: Unpack a struct
//
// PROBLEM:
//   Structured bindings can decompose any aggregate (struct/class with
//   all public members):
//
//     struct Point { double x; double y; };
//     Point p = {3.0, 4.0};
//     auto [x, y] = p;  // x = 3.0, y = 4.0
//
//   The bindings are created in declaration order of the members.
//
// TODO:
//   Implement functions that return structs, then use structured
//   bindings in the test file to verify the results.

#pragma once

#include <testkit/testkit.h>
#include <cmath>
#include <string>

struct Point {
    double x;
    double y;
};

struct Rect {
    double x;
    double y;
    double width;
    double height;
};

struct Person {
    std::string name;
    int age;
};

// Return a Point at the given coordinates.
inline Point make_point(double x, double y) {
    TODO();
}

// Return the distance from the origin (0, 0) to the point.
// Hint: std::sqrt(p.x * p.x + p.y * p.y)
inline double distance_from_origin(Point p) {
    TODO();
}

// Return a Rect with the given position and size.
inline Rect make_rect(double x, double y, double w, double h) {
    TODO();
}

// Return the area of the rectangle (width * height).
inline double rect_area(Rect r) {
    TODO();
}

// Return a Person with the given name and age.
inline Person make_person(const std::string& name, int age) {
    TODO();
}

// Return a greeting like "Hello, Alice (age 30)!"
inline std::string greet(Person p) {
    TODO();
}
