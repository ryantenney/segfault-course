// Exercise 08: Multi-TU Build — Format implementations
//
// TODO: Implement each function declared in ex08_format.h.
//
// Hints:
//   format_signed(5)        → "+5"
//   format_signed(-3)       → "-3"
//   format_signed(0)        → "+0"
//
//   format_range(10, 3, 0, 8) → "3..8"
//     (clamp 10 → 8, clamp 3 → 3, then sort so smaller is first)

#include "ex08_format.h"

#include <testkit/testkit.h>

std::string format_signed(int value) {
    TODO();
}

std::string format_range(int a, int b, int min, int max) {
    TODO();
}
