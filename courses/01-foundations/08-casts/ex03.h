// Exercise 03: Safe Downcasting (Pointer)
//
// PROBLEM:
//   Given a base class pointer, you need to determine at runtime whether
//   the actual object is a specific derived type. dynamic_cast<Derived*>
//   returns nullptr if the cast fails, so you can check safely.
//
// TODO:
//   Implement try_get_area() to dynamic_cast the Shape* to a Circle*.
//   If the cast succeeds, return the circle's area. If it fails, return -1.
//
// WHY:
//   dynamic_cast is the safe way to downcast in a polymorphic hierarchy.
//   Unlike static_cast (which trusts you blindly), dynamic_cast checks
//   the actual runtime type using RTTI.

#pragma once
#include <testkit/testkit.h>

class Shape {
public:
    virtual ~Shape() = default;
    virtual const char* name() const = 0;
};

class Circle : public Shape {
    double radius_;
public:
    explicit Circle(double r) : radius_(r) {}
    const char* name() const override { return "Circle"; }
    double area() const { return 3.14159265358979 * radius_ * radius_; }
    double radius() const { return radius_; }
};

class Rectangle : public Shape {
    double w_, h_;
public:
    Rectangle(double w, double h) : w_(w), h_(h) {}
    const char* name() const override { return "Rectangle"; }
    double area() const { return w_ * h_; }
};

// Use dynamic_cast<Circle*> to attempt a downcast.
// If the shape is a Circle, return its area.
// If the shape is NOT a Circle, return -1.0.
inline double try_get_circle_area(Shape* shape) {
    TODO();
}

// Use dynamic_cast<Rectangle*> to attempt a downcast.
// If the shape is a Rectangle, return its area.
// If the shape is NOT a Rectangle, return -1.0.
inline double try_get_rectangle_area(Shape* shape) {
    TODO();
}
