// Exercise 05: Anonymous Namespace
//
// PROBLEM:
//   This header declares two public functions: `compute_score_a()` and
//   `compute_score_b()`. Each is implemented in its own .cpp file, and
//   each uses a helper function called `bonus()`.
//
//   The two `bonus()` functions return different values (they model
//   different scoring rules). Because both have external linkage, the
//   linker sees two definitions of `bonus()` → ODR violation.
//
// TODO:
//   In ex05_detail.cpp:
//   1. Wrap the `bonus()` function in an anonymous namespace.
//   2. Implement `bonus()` to return 10.
//   3. Implement `compute_score_b()` to return base + bonus().
//
//   The anonymous namespace gives `bonus()` internal linkage, so it
//   won't conflict with the `bonus()` in the test file.
//
// WHY:
//   Anonymous namespaces are the idiomatic C++ way to create file-private
//   helpers. They work for functions, variables, and types.

#pragma once

namespace scoring {

// Implemented in ex05_test.cpp (has its own bonus() helper)
int compute_score_a(int base);

// Implemented in ex05_detail.cpp (has its own bonus() helper)
int compute_score_b(int base);

} // namespace scoring
