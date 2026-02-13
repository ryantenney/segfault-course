// Exercise 04: Header / Source Split
//
// PROBLEM:
//   This function is defined INLINE in the header.  That works, but for
//   larger functions you typically want the body in a .cpp file so that:
//     - Changes to the body only recompile one translation unit.
//     - The header stays lightweight (just the declaration).
//
// TODO:
//   1. Remove the `inline` keyword and the function body from this header,
//      leaving only the declaration:
//        int multiply_add(int a, int b, int c);
//
//   2. Implement the function in ex04.cpp:
//        #include "ex04.h"
//        int multiply_add(int a, int b, int c) { return a * b + c; }
//
// WHY:
//   Without `inline`, a function defined in a header creates a copy of
//   its definition in EVERY translation unit that includes the header.
//   The linker then sees multiple definitions → ODR violation.
//
//   Splitting into declaration (.h) + definition (.cpp) means the body
//   exists in exactly one translation unit.  Other TUs see only the
//   declaration and the linker resolves the call.

#pragma once

#include <testkit/testkit.h>

inline int multiply_add(int a, int b, int c) {
    TODO();
}
