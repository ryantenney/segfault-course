// Exercise 06: noexcept Correctness
//
// The noexcept specifier promises that a function will never throw an
// exception. If it does throw anyway, std::terminate is called — the
// program crashes immediately with no stack unwinding.
//
// Why use noexcept?
//   - Enables compiler optimizations (no need for exception handling tables)
//   - Move constructors and swap should be noexcept — STL containers use
//     this to decide between move and copy (e.g., vector reallocation)
//   - Documents intent: "this function cannot fail"
//
// noexcept(expr) is also a compile-time operator that checks if an
// expression is noexcept:
//   static_assert(noexcept(add(1, 2)));  // true if add is noexcept
//
// TODO:
//   1. Implement add() as noexcept — simple addition can never throw.
//   2. Implement safe_access() as noexcept — return element at index,
//      or default_val if out of bounds. No exceptions.
//   3. Implement checked_access() WITHOUT noexcept — it throws
//      std::out_of_range if the index is invalid.
//   4. Implement swap_values() as noexcept — swap two ints.

#pragma once

#include <stdexcept>
#include <vector>
#include <testkit/testkit.h>

// Add two integers. This can never throw.
// TODO: add the noexcept specifier and implement.
inline int add(int a, int b) {
    TODO();
}

// Return vec[index] if valid, otherwise return default_val.
// This must not throw — it handles the out-of-bounds case itself.
// TODO: add the noexcept specifier and implement.
inline int safe_access(const std::vector<int>& vec, std::size_t index,
                       int default_val) {
    TODO();
}

// Return vec.at(index). This CAN throw std::out_of_range.
// Do NOT mark this noexcept.
inline int checked_access(const std::vector<int>& vec, std::size_t index) {
    TODO();
}

// Swap two integers. This should be noexcept.
// TODO: add the noexcept specifier and implement.
inline void swap_values(int& a, int& b) {
    TODO();
}
