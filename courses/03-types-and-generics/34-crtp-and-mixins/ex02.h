// Exercise 02: Static Interface via CRTP
//
// Virtual functions add a runtime cost: every call goes through a vtable
// pointer. When the set of derived types is known at compile time, CRTP
// lets you get polymorphic behavior with zero overhead.
//
// The pattern: a CRTP base calls into the derived class via static_cast:
//
//   template <typename Derived>
//   class Shape {
//   public:
//       double area() const {
//           return static_cast<const Derived*>(this)->area_impl();
//       }
//   };
//
// The derived class provides area_impl(). If it forgets to, the code
// won't compile -- enforcing the "interface" at compile time.
//
// TODO:
//   1. Implement Circle::area_impl() -- return pi * r * r.
//   2. Implement Circle::perimeter_impl() -- return 2 * pi * r.
//   3. Implement Rectangle::area_impl() -- return width * height.
//   4. Implement Rectangle::perimeter_impl() -- return 2 * (width + height).
//   5. Implement the free function print_area() that calls shape.area()
//      and returns the result as a string: "<name>: <area>".
//      Use std::ostringstream or std::to_string.
//
// WHY:
//   This is the core CRTP use case. The base class defines the public
//   API and delegates to the derived class at compile time. No vtable,
//   no indirection, full inlining potential.

#pragma once

#include <testkit/testkit.h>
#include <cmath>
#include <string>
#include <sstream>

// --- CRTP base (provided, do not modify) ---

template <typename Derived>
class Shape {
public:
    double area() const {
        return static_cast<const Derived*>(this)->area_impl();
    }

    double perimeter() const {
        return static_cast<const Derived*>(this)->perimeter_impl();
    }

    std::string name() const {
        return static_cast<const Derived*>(this)->name_impl();
    }
};

// --- Student implements below ---

class Circle : public Shape<Circle> {
    double radius_;

public:
    explicit Circle(double radius) : radius_(radius) {}
    ~Circle() = default;

    // Return pi * radius^2.  Use M_PI or std::acos(-1.0) for pi.
    double area_impl() const {
        TODO();
    }

    // Return 2 * pi * radius.
    double perimeter_impl() const {
        TODO();
    }

    std::string name_impl() const { return "Circle"; }
};

class Rectangle : public Shape<Rectangle> {
    double width_;
    double height_;

public:
    Rectangle(double width, double height) : width_(width), height_(height) {}
    ~Rectangle() = default;

    // Return width * height.
    double area_impl() const {
        TODO();
    }

    // Return 2 * (width + height).
    double perimeter_impl() const {
        TODO();
    }

    std::string name_impl() const { return "Rectangle"; }
};

// Return a string "<name>: <area>", e.g. "Circle: 78.5398"
// Use std::ostringstream for formatting.
template <typename Derived>
std::string print_area(const Shape<Derived>& shape) {
    TODO();
}
