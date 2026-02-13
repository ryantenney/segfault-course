// Exercise 02: Pragma Once — Combined header
//
// TODO: Add `#pragma once` to the top of this file.
//
// This header pulls in both the Point and Color headers.
// All three files need `#pragma once` for safe inclusion.
//
// WHY #pragma once?
//   It's a simpler alternative to the #ifndef / #define / #endif
//   pattern from Exercise 01.  One line at the top of the file is
//   all you need — the preprocessor tracks which files it has already
//   included and skips duplicates automatically.

#include "ex02_point.h"
#include "ex02_color.h"

struct ColoredPoint {
    Point2D position;
    Color color;
};
