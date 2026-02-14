// Exercise 07: consteval (Immediate Functions)
//
// `consteval` was introduced in C++20. A consteval function MUST be evaluated
// at compile time -- it cannot be called at runtime. If you try to call it
// with non-constant arguments, you get a compile error.
//
// Use consteval when you want to guarantee that a computation happens at
// compile time. Unlike constexpr (which allows runtime evaluation), consteval
// enforces compile-time evaluation.
//
// IMPORTANT: Do NOT put TODO() inside a consteval function -- it throws,
// which is not a valid constant expression, so it won't compile at all.
//
// TODO:
//   1. Implement compile_time_square(n): return n * n.
//   2. Implement compile_time_abs(n): return the absolute value of n.
//   3. Implement compile_time_gcd(a, b): return the GCD using the Euclidean
//      algorithm (while b != 0: t = b, b = a % b, a = t; return a).

#pragma once

#include <testkit/testkit.h>

// Gate function -- tests call this first so TODO() causes "skipped"
// while the student hasn't implemented the consteval functions below.
inline void ex07_gate() {
    TODO();
}

// Return n * n. Must be evaluated at compile time.
consteval int compile_time_square(int n) {
    return 0; // Replace with: return n * n;
}

// Return the absolute value of n. Must be evaluated at compile time.
consteval int compile_time_abs(int n) {
    return 0; // Replace with correct implementation
}

// Return the GCD of a and b using the Euclidean algorithm.
// Must be evaluated at compile time.
consteval int compile_time_gcd(int a, int b) {
    return 0; // Replace with correct implementation
}
