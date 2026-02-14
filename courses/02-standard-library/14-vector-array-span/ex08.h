// Exercise 08: Span from Different Sources
//
// Because std::span is a non-owning view, you can create spans from any
// contiguous data source: std::vector, std::array, C arrays, or even
// a raw pointer + length.
//
// This exercise shows how one span-accepting function can be called with
// data from three different container types.
//
// TODO:
//   1. Implement compute_average() to calculate the mean of a span.
//   2. Implement the three from_*() functions that each create data
//      in a different container and pass it to compute_average().

#pragma once

#include <testkit/testkit.h>
#include <span>
#include <vector>
#include <array>

// Compute the arithmetic mean of the values in the span.
// Return 0.0 for an empty span.
inline double compute_average(std::span<const double> data) {
    TODO();
}

// Create a vector<double> containing {1.0, 2.0, 3.0, 4.0, 5.0} and
// return compute_average() of it.
inline double from_vector() {
    TODO();
}

// Create a C-style double array containing {10.0, 20.0, 30.0} and
// return compute_average() of it.
inline double from_c_array() {
    TODO();
}

// Create a std::array<double, 4> containing {2.5, 5.0, 7.5, 10.0} and
// return compute_average() of it.
inline double from_std_array() {
    TODO();
}
