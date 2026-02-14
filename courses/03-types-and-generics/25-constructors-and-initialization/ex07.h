// Exercise 07: Direct vs List Initialization
//
// PROBLEM:
//   C++ has two initialization syntaxes that behave differently:
//     - Direct init:  Type x(args);   — allows narrowing conversions
//     - List init:    Type x{args};   — forbids narrowing conversions
//
//   This matters: `int x(3.14)` silently truncates to 3, but `int x{3.14}`
//   is a compile error.
//
// TODO:
//   Implement each function to demonstrate your understanding of the
//   difference between () and {} initialization. Read the comments
//   carefully for what each function should return.
//
// WHY:
//   List initialization ({}) was introduced in C++11 to make
//   initialization more uniform and safer (no narrowing). But it
//   interacts with std::initializer_list in surprising ways, so
//   understanding both forms is essential.

#pragma once

#include <testkit/testkit.h>

// Returns the integer value that results from direct-initializing
// an int from 3.9 (narrowing is allowed with parentheses).
// Hint: int x(3.9); return x;
inline int direct_init_narrowing() {
    TODO();
}

// Returns the value of a double initialized from an int.
// This is a widening conversion — safe with both () and {}.
// Hint: double x{42}; return x;
inline double list_init_widening() {
    TODO();
}

// Returns the number of elements in a std::vector<int> created with
// direct initialization: std::vector<int>(5)
// (This creates a vector of 5 zeroes, not a vector containing {5}.)
inline int vector_direct_init_size() {
    TODO();
}

// Returns the number of elements in a std::vector<int> created with
// list initialization: std::vector<int>{5}
// (This creates a vector containing one element: 5.)
inline int vector_list_init_size() {
    TODO();
}

// Returns the single element in std::vector<int>{5}.
inline int vector_list_init_element() {
    TODO();
}

// Returns the value of the first element in std::vector<int>(5).
// (Default-initialized ints in a vector are 0.)
inline int vector_direct_init_element() {
    TODO();
}
