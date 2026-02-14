// Exercise 04: Timeout Check
//
// A common pattern in systems code is checking whether a deadline has passed:
//
//   auto deadline = start + timeout;
//   if (std::chrono::steady_clock::now() > deadline) {
//       // timed out!
//   }
//
// Rather than checking wall-clock time, which makes tests flaky, we'll work
// with time_points directly. Given a "now" time_point and a deadline, you
// determine whether the deadline has passed, how much time remains, etc.
//
// Time point comparison uses the normal relational operators:
//   tp1 < tp2   // tp1 is before tp2
//   tp1 >= tp2  // tp1 is at or after tp2
//
// TODO:
//   1. Implement is_expired() — return true if `now` is at or past `deadline`.
//   2. Implement time_remaining_ms() — return ms remaining until deadline
//      (0 if already expired).
//   3. Implement make_deadline() — compute a deadline from a start time and
//      a timeout duration.
//   4. Implement extend_deadline() — add extra time to an existing deadline.

#pragma once

#include <testkit/testkit.h>
#include <chrono>

using SteadyTimePoint = std::chrono::steady_clock::time_point;

// Return true if `now` is at or past `deadline`.
inline bool is_expired(SteadyTimePoint now, SteadyTimePoint deadline) {
    TODO();
}

// Return the number of milliseconds remaining until `deadline`.
// If `now` is at or past `deadline`, return 0.
inline long long time_remaining_ms(SteadyTimePoint now, SteadyTimePoint deadline) {
    TODO();
}

// Compute a deadline: start + timeout.
inline SteadyTimePoint make_deadline(
    SteadyTimePoint start,
    std::chrono::milliseconds timeout)
{
    TODO();
}

// Extend an existing deadline by adding `extra` time.
inline SteadyTimePoint extend_deadline(
    SteadyTimePoint deadline,
    std::chrono::milliseconds extra)
{
    TODO();
}
