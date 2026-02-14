// Exercise 06: Replace std::bind with Lambda
//
// std::bind was introduced in C++11 to create callables with pre-bound
// arguments. However, lambdas (also C++11) are almost always clearer, more
// efficient, and easier to debug. Modern C++ style strongly prefers lambdas.
//
// std::bind example:
//   auto bound = std::bind(add, 10, std::placeholders::_1);
//   bound(5);  // returns 15
//
// Equivalent lambda:
//   auto bound = [](int x) { return add(10, x); };
//   bound(5);  // returns 15
//
// Key reasons to prefer lambdas:
//   - Easier to read: the code is right there, not hidden behind placeholders
//   - Better compile-time checking: errors show up in your code, not in bind internals
//   - The compiler can inline lambdas more reliably
//   - Lambdas handle overloaded functions correctly; bind cannot
//
// TODO:
//   Replace each std::bind expression with an equivalent lambda.
//   The functions bind_xxx use std::bind — rewrite them as lambdas in the
//   corresponding lambda_xxx functions.

#pragma once

#include <testkit/testkit.h>
#include <functional>
#include <string>

// --- Helper functions (do not modify) ---

inline int add(int a, int b) { return a + b; }
inline int multiply(int a, int b) { return a * b; }
inline std::string greet(const std::string& greeting, const std::string& name) {
    return greeting + ", " + name + "!";
}

// --- std::bind versions (for reference — do not modify) ---

// Binds the first argument of add to 10.
inline std::function<int(int)> bind_add_10() {
    return std::bind(add, 10, std::placeholders::_1);
}

// Binds the first argument of multiply to 3.
inline std::function<int(int)> bind_triple() {
    return std::bind(multiply, 3, std::placeholders::_1);
}

// Swaps the arguments of greet using placeholders.
inline std::function<std::string(const std::string&, const std::string&)> bind_swap_greet() {
    return std::bind(greet, std::placeholders::_2, std::placeholders::_1);
}

// --- Lambda versions (implement these) ---

// Return a lambda that adds 10 to its argument.
// Equivalent to bind_add_10.
inline std::function<int(int)> lambda_add_10() {
    TODO();
}

// Return a lambda that triples its argument.
// Equivalent to bind_triple.
inline std::function<int(int)> lambda_triple() {
    TODO();
}

// Return a lambda that calls greet with swapped arguments.
// i.e., lambda_swap_greet()("Alice", "Hello") should call greet("Hello", "Alice").
// Equivalent to bind_swap_greet.
inline std::function<std::string(const std::string&, const std::string&)> lambda_swap_greet() {
    TODO();
}
