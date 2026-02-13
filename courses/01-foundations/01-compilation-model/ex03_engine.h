// Exercise 03: Forward Declarations
//
// PROBLEM:
//   This header #includes "ex03_car.h" just to use a Car*.  That's
//   unnecessary — pointers and references only need the compiler to
//   know that the type EXISTS, not what it looks like.
//
// TODO:
//   1. Replace the `#include "ex03_car.h"` below with a forward
//      declaration:  class Car;
//
//   2. Implement is_installed() — return true if car_ is not null.
//
// WHY:
//   Forward declarations reduce compile-time dependencies.  If Car's
//   header changes, this file won't need to be recompiled (because it
//   no longer includes it).  For large projects, this matters.
//
//   Rule of thumb: If you only use T* or T&, forward-declare.
//   If you call T's methods or create a T object, you need the full #include.

#pragma once

#include "ex03_car.h"

#include <string>

class Engine {
    std::string type_;
    int horsepower_;
    Car* car_ = nullptr;

public:
    Engine(std::string type, int hp)
        : type_(std::move(type)), horsepower_(hp) {}

    void set_car(Car* car) { car_ = car; }
    const std::string& type() const { return type_; }
    int horsepower() const { return horsepower_; }
    Car* car() const { return car_; }

    // TODO: Return true if this engine has been installed in a car.
    bool is_installed() const {
        TODO();
    }
};
