// Exercise 03: Getter Methods
//
// PROBLEM:
//   The Color class stores private RGB values. External code needs
//   read-only access to these values without being able to modify them.
//
// TODO:
//   Implement the const getter methods:
//   1. red()   — returns the red component
//   2. green() — returns the green component
//   3. blue()  — returns the blue component
//   4. luminance() — returns perceived brightness using the formula:
//        0.2126 * red + 0.7152 * green + 0.0722 * blue
//   5. is_grayscale() — returns true if r == g == b
//
// WHY:
//   Getters provide controlled read access to private data. Making them
//   `const` means they can be called on const objects and through
//   const references — essential for writing correct C++.

#pragma once

#include <testkit/testkit.h>

class Color {
private:
    int r_;
    int g_;
    int b_;

public:
    Color(int r, int g, int b) : r_(r), g_(g), b_(b) {}

    // Returns the red component (0-255).
    int red() const {
        TODO();
    }

    // Returns the green component (0-255).
    int green() const {
        TODO();
    }

    // Returns the blue component (0-255).
    int blue() const {
        TODO();
    }

    // Returns the perceived luminance as a double.
    // Formula: 0.2126 * r_ + 0.7152 * g_ + 0.0722 * b_
    double luminance() const {
        TODO();
    }

    // Returns true if the color is grayscale (all components equal).
    bool is_grayscale() const {
        TODO();
    }
};

// Free function: returns true if the color is considered "bright"
// (luminance > 128.0). Takes a const reference.
inline bool is_bright(const Color& c) {
    TODO();
}
