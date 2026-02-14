// Exercise 02: Functor Class
//
// A functor is any class that overloads operator(). This lets instances of the
// class be called like functions. Unlike plain functions, functors can carry
// state between invocations.
//
// Example:
//   struct Counter {
//       int count = 0;
//       int operator()(int x) {
//           count += x;
//           return count;
//       }
//   };
//   Counter c;
//   c(5);   // returns 5, c.count == 5
//   c(3);   // returns 8, c.count == 8
//
// Functors are the foundation of many standard library interfaces — they
// predate lambdas and are still used when you need a named, reusable callable
// with persistent state.
//
// TODO:
//   1. Implement RunningAverage — a functor that tracks a running average.
//      operator()(double value) adds a value and returns the current average.
//   2. Implement count() — returns how many values have been added.
//   3. Implement average() — returns the current average (0.0 if no values).

#pragma once

#include <testkit/testkit.h>

class RunningAverage {
    double sum_ = 0.0;
    int count_ = 0;

public:
    // Add a value and return the current running average.
    inline double operator()(double value) {
        TODO();
    }

    // Return the number of values added so far.
    inline int count() const {
        TODO();
    }

    // Return the current average, or 0.0 if no values have been added.
    inline double average() const {
        TODO();
    }
};
