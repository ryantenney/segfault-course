// Exercise 05: Inline Functions
//
// PROBLEM:
//   The functions below are defined in this header WITHOUT the `inline`
//   keyword.  Right now only one .cpp file includes this header, so there
//   is no linker conflict.  But ex05_helper.cpp WANTS to include this
//   header too — and can't, because two definitions of the same non-inline
//   function violate the One Definition Rule.
//
// TODO:
//   1. Add `inline` to both functions below.
//   2. Implement cube() — it should return x * x * x.
//   3. In ex05_helper.cpp: uncomment the `#include "ex05.h"` line and
//      implement compute_volume() using cube().
//
// WHY:
//   `inline` doesn't (just) mean "please inline this call."  Its primary
//   meaning in modern C++ is: "this function may be defined in multiple
//   translation units, and all definitions are identical — pick any one."
//   That's what makes it legal to put a function body in a header.

#pragma once

int square(int x) {
    return x * x;
}

int cube(int x) {
    TODO();
}
