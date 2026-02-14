// Exercise 04: Const Correctness Chain
//
// CONTEXT:
//   const propagates through the call chain. If a function receives a
//   `const T&`, it can only call `const` methods on that object. The
//   non-modifying methods below are marked const, which is what allows
//   `describe_temp()` and `warmer_celsius()` to work — they receive
//   const references and need to call celsius(), fahrenheit(), etc.
//
// TODO:
//   1. Implement celsius(), fahrenheit(), and is_freezing().
//   2. Implement describe_temp() and warmer_celsius().
//
// THINK ABOUT:
//   Notice how `adjust()` is NOT const — it modifies state. Try
//   calling t.adjust(5.0) inside describe_temp() and see the compiler
//   error. That's const correctness enforcing your intent.

#pragma once

#include <testkit/testkit.h>
#include <string>

class Temperature {
    double celsius_;

public:
    explicit Temperature(double celsius) : celsius_(celsius) {}

    // const — returns the temperature in Celsius
    double celsius() const {
        TODO();
    }

    // const — returns the temperature in Fahrenheit
    double fahrenheit() const {
        TODO();
    }

    // const — returns true if water would be frozen
    bool is_freezing() const {
        TODO();
    }

    // NOT const — this modifies state
    void adjust(double delta) {
        celsius_ += delta;
    }
};

// Takes a const reference — can only call const methods on t.
// Return "COLD" if freezing, "WARM" otherwise.
inline std::string describe_temp(const Temperature& t) {
    TODO();
}

// Return the higher of the two temperatures (in celsius).
// Takes const references — can only call const methods.
inline double warmer_celsius(const Temperature& a, const Temperature& b) {
    TODO();
}
