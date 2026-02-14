// Exercise 02: Duration Types
//
// std::chrono::duration represents a time span. The library provides
// predefined duration types for common units:
//
//   std::chrono::nanoseconds   — 1/1,000,000,000 second
//   std::chrono::microseconds  — 1/1,000,000 second
//   std::chrono::milliseconds  — 1/1,000 second
//   std::chrono::seconds       — 1 second
//   std::chrono::minutes       — 60 seconds
//   std::chrono::hours         — 3600 seconds
//
// Each is a typedef for duration<Rep, Period>, where Rep is the arithmetic
// type and Period is a std::ratio specifying the tick period.
//
// You can get the raw numeric value with .count():
//   std::chrono::seconds(5).count()  // 5
//
// Implicit conversions from coarser to finer units are allowed (no data loss):
//   std::chrono::milliseconds ms = std::chrono::seconds(2);  // 2000ms
//
// Conversions from finer to coarser require explicit duration_cast (lossy):
//   auto s = std::chrono::duration_cast<std::chrono::seconds>(ms);
//
// TODO:
//   1. Implement to_milliseconds() — convert seconds to milliseconds.
//   2. Implement to_seconds() — convert milliseconds to seconds (truncating).
//   3. Implement to_minutes() — convert seconds to minutes (truncating).
//   4. Implement total_ms() — given hours, minutes, seconds, return total ms.

#pragma once

#include <testkit/testkit.h>
#include <chrono>

// Convert a duration in seconds to milliseconds. Return the count.
inline long long to_milliseconds(std::chrono::seconds s) {
    TODO();
}

// Convert a duration in milliseconds to seconds (truncates). Return the count.
inline long long to_seconds(std::chrono::milliseconds ms) {
    TODO();
}

// Convert a duration in seconds to minutes (truncates). Return the count.
inline long long to_minutes(std::chrono::seconds s) {
    TODO();
}

// Given hours, minutes, and seconds, return the total as milliseconds count.
inline long long total_ms(
    std::chrono::hours h,
    std::chrono::minutes m,
    std::chrono::seconds s)
{
    TODO();
}
