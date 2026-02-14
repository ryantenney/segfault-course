// Exercise 06: Stream Extraction
//
// operator>> is the counterpart of operator<<. It reads formatted data from
// an input stream (like std::cin or std::istringstream) and populates your
// object.
//
// The signature is:
//   std::istream& operator>>(std::istream& is, YourType& obj)
//
// It should read from `is` into `obj` and return `is` so that extraction
// can be chained: is >> a >> b >> c;
//
// When parsing structured data (e.g., "HH:MM:SS"), you typically need to
// read and discard separator characters. Use `is.get()` or read into a
// char variable to consume the separator.
//
// TODO:
//   1. Implement operator>> for Dimensions.
//      Format: "WxH" (e.g., "1920x1080"). Read width, consume 'x', read height.
//   2. Implement operator>> for DateParts.
//      Format: "YYYY-MM-DD" (e.g., "2024-03-15"). Read year, consume '-',
//      read month, consume '-', read day.

#pragma once

#include <istream>
#include <testkit/testkit.h>

struct Dimensions {
    int width;
    int height;
};

// Parse "WxH" from the stream (e.g., "1920x1080").
// Read width, consume the 'x' character, then read height.
inline std::istream& operator>>(std::istream& is, Dimensions& dim) {
    TODO();
}

struct DateParts {
    int year;
    int month;
    int day;
};

// Parse "YYYY-MM-DD" from the stream (e.g., "2024-03-15").
// Read year, consume '-', read month, consume '-', read day.
inline std::istream& operator>>(std::istream& is, DateParts& date) {
    TODO();
}
