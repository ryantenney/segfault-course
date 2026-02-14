// Exercise 04: Arithmetic Operators
//
// Arithmetic operators let your types participate in natural mathematical
// expressions. The canonical pattern is:
//
//   1. Implement operator+= as a member (modifies *this, returns *this by ref)
//   2. Implement operator+ as a free function in terms of operator+=
//
// This avoids code duplication and ensures a += b and a + b are consistent.
//
// TODO:
//   1. Implement operator+= for Vec2 (add other's components to this).
//   2. Implement operator+ for Vec2 (create a copy, use +=, return it).
//   3. Implement operator*= for Vec2 (multiply both components by a scalar).
//   4. Implement operator* for Vec2 (scalar multiplication, as a free function).

#pragma once

#include <testkit/testkit.h>

struct Vec2 {
    double x;
    double y;

    // Add `other` to this vector component-wise. Return *this.
    Vec2& operator+=(const Vec2& other) {
        TODO();
    }

    // Multiply both components by `scalar`. Return *this.
    Vec2& operator*=(double scalar) {
        TODO();
    }

    bool operator==(const Vec2&) const = default;
};

// Return the component-wise sum of two vectors.
// Hint: make a copy of `a`, use operator+=, return the copy.
inline Vec2 operator+(Vec2 a, const Vec2& b) {
    TODO();
}

// Return the vector scaled by `scalar`.
// Hint: make a copy of `v`, use operator*=, return the copy.
inline Vec2 operator*(Vec2 v, double scalar) {
    TODO();
}
