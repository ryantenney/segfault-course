// Exercise 04: Template Argument Deduction
//
// PROBLEM:
//   The compiler can often deduce template arguments from the function
//   arguments, so you don't have to write them explicitly:
//
//     max_of(3, 7)          // T deduced as int
//     max_of(3.0, 7.0)      // T deduced as double
//
//   But deduction fails when:
//   - The return type isn't deducible from arguments.
//   - Arguments have different types (ambiguous deduction).
//   - You want a type different from what would be deduced.
//
// TODO:
//   1. Implement clamp_value: both arguments deduce the same T.
//   2. Implement as_unsigned: return type cannot be deduced; caller must
//      specify it explicitly.
//   3. Implement add_mixed: two different type parameters From1 and From2
//      with an explicit return type To.
//
// WHY:
//   Understanding when deduction works (and when it doesn't) helps you
//   write templates that are both convenient and type-safe. Explicit
//   template arguments are needed when the compiler can't figure it out.

#pragma once

#include <cstddef>
#include <testkit/testkit.h>

// Clamp val to the range [lo, hi]. All three are the same type T.
// T is deducible from the arguments.
template<typename T>
T clamp_value(T val, T lo, T hi) {
    TODO();
}

// Convert a signed integer to its unsigned counterpart.
// The return type must be explicitly specified by the caller:
//   as_unsigned<unsigned int>(-1)
template<typename To, typename From>
To as_unsigned(From val) {
    TODO();
}

// Add two values of potentially different types and return a third type.
// The return type To must be explicitly specified:
//   add_mixed<double>(3, 4.5)
template<typename To, typename From1, typename From2>
To add_mixed(From1 a, From2 b) {
    TODO();
}
