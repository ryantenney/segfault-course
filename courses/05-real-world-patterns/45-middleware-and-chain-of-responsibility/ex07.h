// Exercise 07: Timing Middleware
//
// A timing middleware measures how long the downstream processing takes
// and records the elapsed time. This is useful for logging, metrics, and
// performance monitoring in real applications.
//
// The middleware calls next(), measures the wall-clock duration, and stores
// the elapsed time (in milliseconds) into a provided reference.
//
// TODO:
//   Implement make_timing_middleware() — returns a middleware that:
//   1. Records the start time using std::chrono::steady_clock.
//   2. Calls next().
//   3. Records the end time.
//   4. Computes the elapsed time in milliseconds and stores it in
//      the elapsed_ms reference.

#pragma once

#include <testkit/testkit.h>
#include <chrono>
#include <functional>
#include <string>
#include <thread>

using Middleware07 = std::function<void(std::string& context, std::function<void()> next)>;

// Return a middleware that measures the time spent in next() and stores the
// elapsed time (in milliseconds as a double) into `elapsed_ms`.
inline Middleware07 make_timing_middleware(double& elapsed_ms) {
    TODO();
}
