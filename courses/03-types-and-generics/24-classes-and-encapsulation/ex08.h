// Exercise 08: Friend Function
//
// PROBLEM:
//   You want to print a Rect object using std::cout << rect.
//   The operator<< must be a non-member function (because the left
//   operand is std::ostream, not Rect), but it needs access to
//   Rect's private members. The `friend` keyword grants that access.
//
// TODO:
//   1. Implement the width() and height() getters
//   2. Implement area() and perimeter()
//   3. Implement the friend operator<< to output the Rect in the format:
//        Rect(w x h)
//      For example: Rect(10 x 5)
//
// WHY:
//   `friend` breaks encapsulation in a controlled way: the class
//   explicitly declares which outside functions can access its
//   private members. operator<< is the canonical example, because
//   the stream insertion operator must be a free function.

#pragma once

#include <testkit/testkit.h>
#include <ostream>

class Rect {
private:
    double width_;
    double height_;

public:
    Rect(double w, double h) : width_(w), height_(h) {}

    // Returns the width.
    double width() const {
        TODO();
    }

    // Returns the height.
    double height() const {
        TODO();
    }

    // Returns the area (width * height).
    double area() const {
        TODO();
    }

    // Returns the perimeter (2 * (width + height)).
    double perimeter() const {
        TODO();
    }

    // Friend declaration: allows operator<< to access private members.
    // Output format: "Rect(W x H)" where W and H are the dimensions.
    friend std::ostream& operator<<(std::ostream& os, const Rect& r);
};

// Implement operator<< as an inline free function.
// Output format: "Rect(W x H)"
// Example: Rect(10 x 5)
inline std::ostream& operator<<(std::ostream& os, const Rect& r) {
    TODO();
}
