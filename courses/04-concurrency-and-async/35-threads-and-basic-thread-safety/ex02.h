// Exercise 02: Thread with Arguments
//
// PROBLEM:
//   Pass arguments to a thread function — by value and by reference.
//   std::thread copies all arguments by default. To pass a reference,
//   you must wrap it with std::ref().
//
// TODO:
//   Implement add_to() so it adds `amount` to `target`.
//
// WHY:
//   Understanding argument passing to threads is essential. Passing by
//   value is safe (each thread owns its copy), but sometimes you need
//   shared state — that's where std::ref comes in. Forgetting std::ref
//   is a classic C++ threading bug: you modify a copy that gets discarded.

#pragma once
#include <testkit/testkit.h>

// Adds amount to target.
inline void add_to(int& target, int amount) {
    TODO();
}
