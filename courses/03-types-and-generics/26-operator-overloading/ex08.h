// Exercise 08: Function Call Operator
//
// operator() makes an object callable like a function. Objects that
// implement operator() are called "functors" or "function objects."
//
// Unlike lambdas, functors can have named state, be inspected, and be
// reused across different call sites. They are the foundation that lambdas
// are built on — the compiler turns every lambda into an anonymous class
// with an operator().
//
// Functors are widely used with STL algorithms: std::sort, std::transform,
// std::find_if, etc.
//
// TODO:
//   1. Implement operator() for Multiplier. It returns its argument
//      multiplied by the stored factor.
//   2. Implement operator() for Counter. It takes no arguments and returns
//      the current count, then increments the internal counter.
//   3. Implement operator() for InRange. It takes a value and returns
//      true if the value is between low and high (inclusive).

#pragma once

#include <testkit/testkit.h>

// A functor that multiplies its argument by a fixed factor.
class Multiplier {
    int factor_;

public:
    explicit Multiplier(int factor) : factor_(factor) {}

    // Return value * factor_.
    int operator()(int value) const {
        TODO();
    }
};

// A functor that counts how many times it has been called.
class Counter {
    int count_ = 0;

public:
    // Return the current count, then increment it.
    int operator()() {
        TODO();
    }

    // Return the current count without incrementing.
    int current() const {
        TODO();
    }
};

// A predicate functor that checks if a value is within [low, high].
class InRange {
    int low_;
    int high_;

public:
    InRange(int low, int high) : low_(low), high_(high) {}

    // Return true if `value` is between low_ and high_ (inclusive).
    bool operator()(int value) const {
        TODO();
    }
};
