// Exercise 08: Multi-TU Build — Math header
//
// This header declares math utility functions.  The implementations
// live in ex08_math.cpp.
//
// TODO: Implement the functions in ex08_math.cpp.

#pragma once

// Returns the absolute value of x.
int abs_val(int x);

// Returns the larger of a and b.
int max_val(int a, int b);

// Returns a clamped to the range [lo, hi].
int clamp_val(int a, int lo, int hi);
