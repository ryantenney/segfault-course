// Exercise 06: Cast in a Class Hierarchy
//
// PROBLEM:
//   In a class hierarchy, upcasts (Derived* -> Base*) are implicit and
//   always safe. Downcasts (Base* -> Derived*) need a cast. The question
//   is: static_cast or dynamic_cast?
//
//   - static_cast: Fast, no runtime check. If wrong, undefined behavior.
//   - dynamic_cast: Slower, but checks at runtime. Returns null on failure.
//
// TODO:
//   Implement each function using the appropriate cast. Upcasts should
//   use static_cast (explicit is better than implicit for learning).
//   Downcasts of unknown types should use dynamic_cast.
//
// WHY:
//   Understanding when to use static_cast vs dynamic_cast is essential
//   for working with inheritance hierarchies safely and efficiently.

#pragma once
#include <string>
#include <testkit/testkit.h>

class Vehicle {
public:
    virtual ~Vehicle() = default;
    virtual std::string describe() const { return "Vehicle"; }
};

class Car : public Vehicle {
    int doors_;
public:
    explicit Car(int doors) : doors_(doors) {}
    std::string describe() const override { return "Car"; }
    int doors() const { return doors_; }
};

class Truck : public Vehicle {
    double payload_tons_;
public:
    explicit Truck(double tons) : payload_tons_(tons) {}
    std::string describe() const override { return "Truck"; }
    double payload() const { return payload_tons_; }
};

// Upcast a Car* to a Vehicle*.
// Use static_cast — upcasts are always safe.
inline Vehicle* car_to_vehicle(Car* car) {
    TODO();
}

// Downcast a Vehicle* to a Car*, checking at runtime.
// Use dynamic_cast — returns nullptr if the vehicle isn't actually a Car.
inline Car* vehicle_to_car(Vehicle* vehicle) {
    TODO();
}

// Given a Vehicle*, return the number of doors if it's a Car,
// or -1 if it's not a Car. Use dynamic_cast.
inline int get_doors(Vehicle* vehicle) {
    TODO();
}

// Given a Vehicle*, return the payload if it's a Truck,
// or -1.0 if it's not a Truck. Use dynamic_cast.
inline double get_payload(Vehicle* vehicle) {
    TODO();
}
