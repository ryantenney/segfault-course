// Exercise 07: Static Factory Method
//
// PROBLEM:
//   Constructors in C++ have no name — you can't distinguish between
//   different ways to create an object. Static factory methods provide
//   named alternatives that make the intent clear and can enforce
//   additional constraints.
//
// TODO:
//   1. Implement Temperature::from_celsius(c) — stores internally as Celsius
//   2. Implement Temperature::from_fahrenheit(f) — convert to Celsius:
//        celsius = (f - 32) * 5.0 / 9.0
//   3. Implement Temperature::from_kelvin(k) — convert to Celsius:
//        celsius = k - 273.15
//      Throw std::invalid_argument if k < 0 (below absolute zero)
//   4. Implement the getter methods: celsius(), fahrenheit(), kelvin()
//
// WHY:
//   Static factory methods are a classic OOP pattern. They provide:
//   - Named construction (clearer than overloaded constructors)
//   - Validation before object creation
//   - The ability to return cached objects or subtypes

#pragma once

#include <testkit/testkit.h>
#include <stdexcept>

class Temperature {
private:
    double celsius_;

    // Private constructor: only factory methods can create instances.
    explicit Temperature(double celsius) : celsius_(celsius) {}

public:
    // Factory: create from Celsius value.
    static Temperature from_celsius(double c) {
        TODO();
    }

    // Factory: create from Fahrenheit value.
    // Formula: celsius = (f - 32) * 5.0 / 9.0
    static Temperature from_fahrenheit(double f) {
        TODO();
    }

    // Factory: create from Kelvin value.
    // Formula: celsius = k - 273.15
    // Throws std::invalid_argument if k < 0.
    static Temperature from_kelvin(double k) {
        TODO();
    }

    // Returns the temperature in Celsius.
    double celsius() const {
        TODO();
    }

    // Returns the temperature in Fahrenheit.
    // Formula: f = celsius * 9.0 / 5.0 + 32
    double fahrenheit() const {
        TODO();
    }

    // Returns the temperature in Kelvin.
    // Formula: k = celsius + 273.15
    double kelvin() const {
        TODO();
    }
};
