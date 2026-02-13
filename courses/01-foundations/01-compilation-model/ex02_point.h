// Exercise 02: Pragma Once — Point header
//
// TODO: Add `#pragma once` to the top of this file.
//
// Without it, including this header more than once in the same
// translation unit causes a redefinition error for Point2D.

struct Point2D {
    double x;
    double y;
};

// Returns the squared distance between two points.
inline double point_distance_sq(Point2D a, Point2D b) {
    TODO();
}
