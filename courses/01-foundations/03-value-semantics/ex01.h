// Exercise 01: Prove Value Semantics
//
// PROBLEM:
//   In C++, assignment copies the value — the two variables are
//   completely independent afterward. This is different from Java
//   or Python, where assigning an object gives you a second reference
//   to the same data.
//
// TODO:
//   1. Implement `make_point(x, y)` to return a Point with the given
//      coordinates.
//   2. Implement `offset_point(p, dx, dy)` which takes a Point BY VALUE,
//      modifies it, and returns the modified copy.
//      The original must not change — that's what value semantics means.
//
// WHY:
//   Value semantics is the default in C++. Understanding that assignment
//   and pass-by-value create independent copies is foundational.

#pragma once

#include <testkit/testkit.h>

struct Point {
    int x;
    int y;
};

// Create a Point with the given coordinates
inline Point make_point(int x, int y) {
    TODO();
}

// Return a NEW point offset by (dx, dy).
// `p` is passed by value — it's already a copy.
inline Point offset_point(Point p, int dx, int dy) {
    TODO();
}
