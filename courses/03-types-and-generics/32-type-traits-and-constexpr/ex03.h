// Exercise 03: constexpr Function
//
// A `constexpr` function CAN be evaluated at compile time when called with
// constant arguments. It can also be called at runtime with non-constant
// arguments -- it works both ways.
//
// Rules for constexpr functions:
//   - No inline assembly, goto, or non-literal local variables (relaxed in C++20)
//   - All called functions must also be constexpr
//   - In C++14+, loops and local variables are allowed
//
// TODO:
//   1. Implement constexpr_factorial(n): returns n! (factorial).
//      Use a loop or recursion. Handle n == 0 as returning 1.
//      Add the `constexpr` keyword to the function.
//   2. Implement constexpr_fibonacci(n): returns the n-th Fibonacci number.
//      fib(0) = 0, fib(1) = 1, fib(n) = fib(n-1) + fib(n-2).
//      Add the `constexpr` keyword to the function.
//   3. Implement constexpr_is_prime(n): returns true if n is prime.
//      Check divisibility from 2 up to sqrt(n). 0 and 1 are not prime.
//      Add the `constexpr` keyword to the function.
//
// IMPORTANT: The stubs are NOT marked constexpr yet because they contain
// TODO(). Once you implement the bodies, add `constexpr` to each function.

#pragma once

#include <testkit/testkit.h>

// Compute n! at compile time or runtime.
// Add `constexpr` to this function once you implement it.
inline int constexpr_factorial(int n) {
    TODO();
}

// Compute the n-th Fibonacci number at compile time or runtime.
// Add `constexpr` to this function once you implement it.
inline int constexpr_fibonacci(int n) {
    TODO();
}

// Return true if n is prime, at compile time or runtime.
// Add `constexpr` to this function once you implement it.
inline bool constexpr_is_prime(int n) {
    TODO();
}
