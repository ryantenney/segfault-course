// Exercise 03: Duration Arithmetic
//
// Chrono durations support arithmetic operations:
//
//   auto a = std::chrono::seconds(10);
//   auto b = std::chrono::seconds(3);
//   auto sum = a + b;        // seconds(13)
//   auto diff = a - b;       // seconds(7)
//   auto scaled = a * 2;     // seconds(20)
//
// When you mix different units, the result type is the finer unit:
//   auto result = std::chrono::seconds(1) + std::chrono::milliseconds(500);
//   // result is milliseconds(1500)
//
// To convert back to a coarser unit, use duration_cast:
//   auto s = std::chrono::duration_cast<std::chrono::seconds>(result);
//   // s is seconds(1) — truncated
//
// TODO:
//   1. Implement add_durations() — add two millisecond durations, return count.
//   2. Implement subtract_durations() — subtract, return count.
//   3. Implement mixed_add() — add seconds and milliseconds, return ms count.
//   4. Implement scale_duration() — multiply a duration by a factor, return count.
//   5. Implement remaining_ms() — given a total in seconds and elapsed in ms,
//      return remaining milliseconds.

#pragma once

#include <testkit/testkit.h>
#include <chrono>

// Add two millisecond durations and return the result count.
inline long long add_durations(
    std::chrono::milliseconds a,
    std::chrono::milliseconds b)
{
    TODO();
}

// Subtract b from a (millisecond durations) and return the result count.
inline long long subtract_durations(
    std::chrono::milliseconds a,
    std::chrono::milliseconds b)
{
    TODO();
}

// Add a duration in seconds to a duration in milliseconds.
// Return the total in milliseconds count.
inline long long mixed_add(
    std::chrono::seconds s,
    std::chrono::milliseconds ms)
{
    TODO();
}

// Multiply a millisecond duration by `factor` and return the result count.
inline long long scale_duration(
    std::chrono::milliseconds d,
    int factor)
{
    TODO();
}

// Given a total time in seconds and elapsed time in milliseconds,
// return the remaining time in milliseconds count.
// If elapsed exceeds total, return 0 (not negative).
inline long long remaining_ms(
    std::chrono::seconds total,
    std::chrono::milliseconds elapsed)
{
    TODO();
}
