// Exercise 03: Function Pointer
//
// Before std::function and lambdas, C++ (and C) used plain function pointers
// for callbacks. A function pointer stores the address of a free function and
// can be called through that pointer.
//
// Syntax:
//   int (*fp)(int, int) = &add;   // pointer to a function taking two ints
//   fp(3, 4);                      // call through the pointer: returns 7
//
// Using a typedef or type alias makes the syntax cleaner:
//   using BinaryOp = int(*)(int, int);
//   BinaryOp fp = &add;
//
// Function pointers are lightweight (just an address), have no overhead, and
// interop with C APIs. However, they cannot capture state — for that you
// need std::function or a template parameter.
//
// TODO:
//   1. Implement apply() — call the given function pointer with the two args.
//   2. Implement select_operation() — return a function pointer to add_ints
//      or multiply_ints based on the op character ('+' or '*').
//   3. Implement compute() — use select_operation and apply to compute a result.

#pragma once

#include <testkit/testkit.h>

// Two plain functions for use as targets.
inline int add_ints(int a, int b) { return a + b; }
inline int multiply_ints(int a, int b) { return a * b; }

// Type alias for a binary integer operation.
using BinaryOp = int(*)(int, int);

// Call the function pointer `op` with arguments `a` and `b`, and return
// the result.
inline int apply(BinaryOp op, int a, int b) {
    TODO();
}

// Return a function pointer: &add_ints if `op` is '+', &multiply_ints
// if `op` is '*'. For any other character, return nullptr.
inline BinaryOp select_operation(char op) {
    TODO();
}

// Use select_operation to pick the right function, then call apply.
// If the operation character is invalid (select_operation returns nullptr),
// return 0.
inline int compute(char op, int a, int b) {
    TODO();
}
