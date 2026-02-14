// Exercise 01: Measure Elapsed Time
//
// std::chrono provides type-safe time utilities. To measure how long something
// takes, you capture time points before and after, then subtract:
//
//   auto start = std::chrono::steady_clock::now();
//   do_work();
//   auto end = std::chrono::steady_clock::now();
//   auto elapsed = end - start;  // a duration
//
// steady_clock is the right clock for measuring intervals — it never adjusts
// (unlike system_clock which can jump due to NTP or manual changes).
//
// Subtracting two time_points gives a duration. You can convert that duration
// to specific units with duration_cast:
//
//   auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
//   ms.count();  // the numeric value
//
// NOTE: In this exercise, instead of measuring actual wall-clock time (which
// makes tests flaky), you will compute elapsed time from two given time points.
//
// TODO:
//   1. Implement elapsed_ms() — given two steady_clock time_points (start
//      and end), return the elapsed time in milliseconds as a long long.
//   2. Implement elapsed_us() — same, but return microseconds.
//   3. Implement elapsed_between() — given a start time_point and a
//      duration to add, return the end time_point.

#pragma once

#include <testkit/testkit.h>
#include <chrono>

using SteadyTimePoint = std::chrono::steady_clock::time_point;

// Return the number of milliseconds between `start` and `end`.
inline long long elapsed_ms(SteadyTimePoint start, SteadyTimePoint end) {
    TODO();
}

// Return the number of microseconds between `start` and `end`.
inline long long elapsed_us(SteadyTimePoint start, SteadyTimePoint end) {
    TODO();
}

// Given a starting time_point and a duration, return the time_point that is
// `offset` later than `start`.
inline SteadyTimePoint elapsed_between(
    SteadyTimePoint start,
    std::chrono::milliseconds offset)
{
    TODO();
}
