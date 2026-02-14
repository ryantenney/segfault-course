// Exercise 07: Reference vs Pointer Parameter
//
// CONTEXT:
//   In C-style code, you often see pointer parameters for output values:
//     void compute(int input, int* result);  // caller writes: compute(5, &result)
//
//   In C++, references are preferred when the argument is required
//   (non-nullable) and will be modified:
//     void compute(int input, int& result);  // caller writes: compute(5, result)
//
//   The functions below already use reference parameters. Notice how
//   much cleaner the syntax is — no `*` dereferences, no `&` at call sites,
//   and no need to check for null.
//
// TODO:
//   Implement each function using the reference parameters directly.
//
// THINK ABOUT:
//   References can't be null and can't be reseated to point elsewhere.
//   This makes them safer and more expressive than pointers for
//   required output parameters.

#pragma once

#include <testkit/testkit.h>

// Doubles the value in-place.
// With a pointer this would be: void double_value(int* value) { *value *= 2; }
// With a reference it's simpler:
inline void double_value(int& value) {
    TODO();
}

// Sets `area` = width * height, `perimeter` = 2 * (width + height).
// With pointers: void rectangle_stats(int w, int h, int* area, int* perimeter)
// References eliminate the dereference syntax and null checks.
inline void rectangle_stats(int width, int height, int& area, int& perimeter) {
    TODO();
}

// Ensures lo <= hi by swapping if needed.
// The caller's variables are modified directly through references.
inline void order_pair(int& lo, int& hi) {
    TODO();
}
