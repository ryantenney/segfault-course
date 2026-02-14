// Exercise 01: Replace C-Style Casts
//
// PROBLEM:
//   The functions below use C-style casts — (Type)expr — which are
//   inherited from C. C-style casts are dangerous because they silently
//   perform whichever cast happens to compile: static_cast, const_cast,
//   reinterpret_cast, or even combinations. The compiler won't warn you
//   if the cast is doing something unexpected.
//
// TODO:
//   Replace each C-style cast with the appropriate C++ named cast.
//   Use static_cast for numeric conversions and pointer upcasts.
//   Use reinterpret_cast for the pointer-to-integer round-trip.
//
// WHY:
//   C++ named casts make your intent explicit and searchable. A grep
//   for "reinterpret_cast" instantly highlights dangerous conversions,
//   while C-style casts hide among parenthesized expressions.

#pragma once
#include <cstdint>
#include <testkit/testkit.h>

// Convert a double to int, truncating the fractional part.
// Replace the C-style cast with the correct C++ cast.
inline int double_to_int(double value) {
    TODO();
    // SOLUTION HINT: return static_cast<int>(value);
    // CURRENT (broken C-style): return (int)value;
}

// Convert an int to double.
// Replace the C-style cast with the correct C++ cast.
inline double int_to_double(int value) {
    TODO();
    // SOLUTION HINT: return static_cast<double>(value);
}

// Convert a pointer to a uintptr_t integer representation.
// Replace the C-style cast with the correct C++ cast.
inline std::uintptr_t ptr_to_int(const int* ptr) {
    TODO();
    // SOLUTION HINT: return reinterpret_cast<std::uintptr_t>(ptr);
}

// Convert a uintptr_t back to a pointer.
// Replace the C-style cast with the correct C++ cast.
inline const int* int_to_ptr(std::uintptr_t addr) {
    TODO();
    // SOLUTION HINT: return reinterpret_cast<const int*>(addr);
}
