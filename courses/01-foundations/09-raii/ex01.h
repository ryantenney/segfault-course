// Exercise 01: Scoped Timer
//
// PROBLEM:
//   You want to measure how long a block of code takes. The RAII pattern
//   is perfect: record the start time in the constructor, compute
//   elapsed time in the destructor.
//
// TODO:
//   Implement the ScopedTimer class:
//   - Constructor: record the current time using steady_clock::now()
//   - elapsed_ms(): return milliseconds elapsed since construction
//   - The class stores a reference to a double that gets written
//     with the elapsed time when the timer goes out of scope.
//
// WHY:
//   RAII ties resource management to object lifetime. A timer is a
//   simple example: the "resource" is the measurement itself. The
//   constructor acquires (starts timing), the destructor releases
//   (records the result). No matter how the scope exits — normal
//   return, early return, or exception — the measurement is captured.

#pragma once
#include <chrono>
#include <testkit/testkit.h>

class ScopedTimer {
    // TODO: Add member variables
    // - A reference to a double where the elapsed time will be stored
    // - The start time (use std::chrono::steady_clock::time_point)
public:
    // Constructor: store the output reference and record the start time.
    explicit ScopedTimer(double& elapsed_out) {
        TODO();
    }

    // Destructor: compute elapsed time in milliseconds and write it
    // to the referenced double.
    ~ScopedTimer() {
        // TODO: Compute elapsed time and write to the output reference.
        // Use:
        //   auto end = std::chrono::steady_clock::now();
        //   std::chrono::duration<double, std::milli> diff = end - start_;
        //   output_ = diff.count();
    }

    // Return the elapsed time so far (without stopping the timer).
    double elapsed_ms() const {
        TODO();
    }
};
