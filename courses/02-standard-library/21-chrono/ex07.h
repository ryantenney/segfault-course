// Exercise 07: Sleep with Chrono
//
// std::this_thread::sleep_for(duration) suspends the current thread for at
// least the specified duration:
//
//   std::this_thread::sleep_for(std::chrono::milliseconds(100));
//
// std::this_thread::sleep_until(time_point) suspends until at least the
// specified time point:
//
//   auto wake = std::chrono::steady_clock::now() + std::chrono::seconds(1);
//   std::this_thread::sleep_until(wake);
//
// These functions accept chrono types directly — no manual conversion needed.
//
// NOTE: Actual sleeping makes tests slow and flaky, so in this exercise you
// will build helper functions that *compute* the chrono values that would be
// passed to sleep_for/sleep_until, without actually sleeping. The tests verify
// the computed values are correct.
//
// TODO:
//   1. Implement make_sleep_duration() — convert an integer number of
//      milliseconds to a std::chrono::milliseconds duration.
//   2. Implement compute_wake_time() — given "now" and a sleep duration in
//      ms, return the time_point when the thread would wake up.
//   3. Implement sleep_durations() — given a list of millisecond values,
//      return a vector of chrono::milliseconds durations.
//   4. Implement total_sleep_ms() — given a vector of millisecond sleep
//      durations, return the total sleep time in ms.

#pragma once

#include <testkit/testkit.h>
#include <chrono>
#include <vector>

using SteadyTimePoint = std::chrono::steady_clock::time_point;

// Convert an integer millisecond count to a std::chrono::milliseconds duration.
inline std::chrono::milliseconds make_sleep_duration(int ms) {
    TODO();
}

// Given the current time and a sleep duration in milliseconds, return the
// time_point at which the thread would wake up.
inline SteadyTimePoint compute_wake_time(
    SteadyTimePoint now,
    std::chrono::milliseconds sleep_duration)
{
    TODO();
}

// Convert a vector of integer ms values to a vector of chrono::milliseconds.
inline std::vector<std::chrono::milliseconds> sleep_durations(
    const std::vector<int>& ms_values)
{
    TODO();
}

// Sum all durations and return the total in milliseconds count.
inline long long total_sleep_ms(
    const std::vector<std::chrono::milliseconds>& durations)
{
    TODO();
}
