// Exercise 03: Abstract Interface
//
// A class with at least one pure virtual method (= 0) is abstract and
// cannot be instantiated. It serves as an interface: a contract that
// derived classes must fulfill.
//
// This is how C++ achieves interface-based programming. The base class
// defines WHAT operations are available; derived classes define HOW
// they work.
//
// The Shape interface below defines area() and name(). You need to
// implement two concrete classes: Circle and Rectangle.
//
// TODO:
//   1. Implement Circle — stores a radius.
//      area() returns pi * radius * radius.
//      name() returns "Circle".
//   2. Implement Rectangle — stores width and height.
//      area() returns width * height.
//      name() returns "Rectangle".
//   3. Implement the factory functions make_circle() and make_rectangle().

#pragma once

#include <cmath>
#include <memory>
#include <string>
#include <testkit/testkit.h>

// Abstract interface — cannot be instantiated directly.
class Shape {
public:
    virtual ~Shape() = default;

    // Return the area of this shape.
    virtual double area() const = 0;

    // Return the name of this shape (e.g., "Circle", "Rectangle").
    virtual std::string name() const = 0;
};

// A circle with a given radius.
class Circle : public Shape {
    double radius_;

public:
    explicit Circle(double radius) : radius_(radius) {}

    // Return pi * radius_ * radius_.
    // Use M_PI or std::acos(-1.0) for pi.
    double area() const override {
        TODO();
    }

    // Return "Circle".
    std::string name() const override {
        TODO();
    }
};

// A rectangle with a given width and height.
class Rectangle : public Shape {
    double width_;
    double height_;

public:
    Rectangle(double width, double height) : width_(width), height_(height) {}

    // Return width_ * height_.
    double area() const override {
        TODO();
    }

    // Return "Rectangle".
    std::string name() const override {
        TODO();
    }
};

// Create a Circle and return it as a unique_ptr<Shape>.
inline std::unique_ptr<Shape> make_circle(double radius) {
    TODO();
}

// Create a Rectangle and return it as a unique_ptr<Shape>.
inline std::unique_ptr<Shape> make_rectangle(double width, double height) {
    TODO();
}
