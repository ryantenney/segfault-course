// Exercise 05: Invariant Enforcement
//
// PROBLEM:
//   A Fraction class must always be in reduced form with a positive
//   denominator. This invariant must hold after construction and after
//   every mutation. The class must never allow an invalid state.
//
// TODO:
//   1. Implement the constructor that validates and normalizes the fraction:
//      - Throw std::invalid_argument if denominator is 0
//      - Ensure denominator is always positive (flip signs if needed)
//      - Reduce to lowest terms using GCD
//   2. Implement numerator() and denominator() getters
//   3. Implement add() that returns a new Fraction (a/b + c/d = (ad+bc)/bd)
//   4. Implement multiply() that returns a new Fraction
//   5. Implement equals() to compare two fractions
//
// WHY:
//   A class invariant is a condition that is always true between method
//   calls. Good class design makes invariant violations impossible.
//   The constructor establishes the invariant; every method preserves it.

#pragma once

#include <testkit/testkit.h>
#include <stdexcept>
#include <numeric>   // for std::gcd

class Fraction {
private:
    int num_;
    int den_;

    // Helper: reduces the fraction to lowest terms with positive denominator.
    // This is provided for you — call it in the constructor and after
    // arithmetic operations.
    void normalize() {
        if (den_ < 0) {
            num_ = -num_;
            den_ = -den_;
        }
        int g = std::gcd(num_ < 0 ? -num_ : num_, den_);
        if (g > 0) {
            num_ /= g;
            den_ /= g;
        }
    }

public:
    // Constructor: create a fraction num/den.
    // Throws std::invalid_argument if den == 0.
    // After construction, the fraction must be normalized.
    Fraction(int num, int den) : num_(num), den_(den) {
        TODO();
    }

    // Returns the numerator (may be negative, zero, or positive).
    int numerator() const {
        TODO();
    }

    // Returns the denominator (always positive).
    int denominator() const {
        TODO();
    }

    // Returns a new Fraction that is the sum of this and other.
    // a/b + c/d = (a*d + c*b) / (b*d), then normalized.
    Fraction add(const Fraction& other) const {
        TODO();
    }

    // Returns a new Fraction that is the product of this and other.
    // a/b * c/d = (a*c) / (b*d), then normalized.
    Fraction multiply(const Fraction& other) const {
        TODO();
    }

    // Returns true if this fraction equals other (after normalization).
    bool equals(const Fraction& other) const {
        TODO();
    }
};
