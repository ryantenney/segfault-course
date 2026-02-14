// Exercise 06: Format a Timestamp
//
// system_clock::time_point represents a point in civil time (wall-clock time).
// To display it as a human-readable string, the traditional approach (pre-C++20)
// is to convert through std::time_t:
//
//   auto tp = std::chrono::system_clock::now();
//   std::time_t t = std::chrono::system_clock::to_time_t(tp);
//   std::tm* tm = std::gmtime(&t);   // or std::localtime(&t)
//   // Then format with std::put_time or strftime
//
// std::put_time(tm, format) works with output streams:
//   stream << std::put_time(tm, "%Y-%m-%d %H:%M:%S");
//
// Common format specifiers:
//   %Y = 4-digit year, %m = month (01-12), %d = day (01-31)
//   %H = hour (00-23), %M = minute (00-59), %S = second (00-59)
//
// NOTE: In this exercise, to avoid locale/timezone dependencies, we
// work with UTC (gmtime) and known time_t values.
//
// TODO:
//   1. Implement format_utc() — convert a system_clock time_point to a
//      string formatted as "YYYY-MM-DD HH:MM:SS" in UTC.
//   2. Implement format_date_only() — format as "YYYY-MM-DD" in UTC.
//   3. Implement to_time_t_value() — convert a time_point to time_t and
//      return the raw value (seconds since epoch).

#pragma once

#include <testkit/testkit.h>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

using SystemTimePoint = std::chrono::system_clock::time_point;

// Format a system_clock time_point as "YYYY-MM-DD HH:MM:SS" in UTC.
// Use std::chrono::system_clock::to_time_t, std::gmtime, and std::put_time.
inline std::string format_utc(SystemTimePoint tp) {
    TODO();
}

// Format a system_clock time_point as "YYYY-MM-DD" in UTC.
inline std::string format_date_only(SystemTimePoint tp) {
    TODO();
}

// Convert a system_clock time_point to std::time_t and return it.
inline std::time_t to_time_t_value(SystemTimePoint tp) {
    TODO();
}
