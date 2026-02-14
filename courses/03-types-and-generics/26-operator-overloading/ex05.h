// Exercise 05: Stream Insertion
//
// operator<< lets you print your types using std::cout, std::ostringstream,
// and any other output stream. It must be a free function (not a member)
// because the left-hand side is a std::ostream, not your type.
//
// The signature is always:
//   std::ostream& operator<<(std::ostream& os, const YourType& obj)
//
// It should write the formatted representation to `os` and return `os`
// to support chaining: std::cout << a << b << c;
//
// TODO:
//   1. Implement operator<< for Timestamp.
//      Format: "HH:MM:SS" (e.g., "09:30:00", "14:05:59")
//      Use two-digit fields with leading zeros.
//   2. Implement operator<< for Coordinate.
//      Format: "(lat, lon)" (e.g., "(40.7128, -74.006)")

#pragma once

#include <iomanip>
#include <ostream>
#include <testkit/testkit.h>

struct Timestamp {
    int hours;
    int minutes;
    int seconds;
};

// Format: "HH:MM:SS" with leading zeros (e.g., "09:05:02").
// Hint: use std::setw(2) and std::setfill('0') from <iomanip>.
inline std::ostream& operator<<(std::ostream& os, const Timestamp& ts) {
    TODO();
}

struct Coordinate {
    double latitude;
    double longitude;
};

// Format: "(lat, lon)" (e.g., "(40.7128, -74.006)").
// No special formatting for the doubles — just stream them directly.
inline std::ostream& operator<<(std::ostream& os, const Coordinate& coord) {
    TODO();
}
