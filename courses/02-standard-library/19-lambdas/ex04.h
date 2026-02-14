// Exercise 04: Capture by Move
//
// Move-only types like std::unique_ptr cannot be captured by value
// (which would require copying). C++14 introduced init-captures to
// move objects into a lambda:
//
//   auto ptr = std::make_unique<int>(42);
//   auto fn = [p = std::move(ptr)]() {
//       return *p;
//   };
//   // ptr is now nullptr -- ownership transferred to the lambda
//
// Init-captures can also create new variables:
//
//   auto fn = [val = expensive_computation()]() { return val; };
//
// TODO:
//   1. Implement capture_unique_ptr() -- create a unique_ptr<int>,
//      capture it into a lambda by move, and return the lambda.
//      The lambda should return the value pointed to by the unique_ptr.
//   2. Implement capture_string_by_move() -- move a string into a
//      lambda and return a function that returns the string's length.
//   3. Implement transfer_ownership() -- accept a unique_ptr by value,
//      capture it by move into a lambda, and return the lambda.
//      The lambda should dereference and return the value.

#pragma once

#include <functional>
#include <memory>
#include <string>
#include <testkit/testkit.h>

// Create a unique_ptr<int> holding `value`, capture it by move into
// a lambda, and return the lambda. The lambda returns *ptr.
inline std::function<int()> capture_unique_ptr(int value) {
    TODO();
}

// Move the string into a lambda and return a function that returns
// the string's length.
inline std::function<std::size_t()> capture_string_by_move(std::string str) {
    TODO();
}

// Accept a unique_ptr, move it into a lambda, return the lambda.
// The lambda returns the pointed-to value.
inline std::function<int()> transfer_ownership(std::unique_ptr<int> ptr) {
    TODO();
}
