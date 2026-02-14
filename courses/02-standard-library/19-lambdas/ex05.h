// Exercise 05: Generic Lambda
//
// C++14 introduced generic lambdas, where one or more parameters use
// `auto` instead of a concrete type. The compiler generates a templated
// operator() under the hood:
//
//   auto add = [](auto a, auto b) { return a + b; };
//   add(1, 2);         // int
//   add(1.5, 2.5);     // double
//   add(std::string("a"), std::string("b")); // string
//
// This is equivalent to writing a function template, but more concise.
//
// TODO:
//   1. Implement make_adder() -- return a generic lambda (stored in
//      std::function) that adds two values. The test will call it with
//      ints and doubles.
//   2. Implement find_max() -- return a generic lambda that takes a
//      vector<T> and returns the maximum element. Use std::max_element.
//   3. Implement apply_twice() -- write a function template that takes
//      a value and a generic lambda, applies the lambda to the value
//      twice, and returns the result: fn(fn(value)).

#pragma once

#include <algorithm>
#include <functional>
#include <vector>
#include <testkit/testkit.h>

// Return a lambda that adds two ints.
// The tests call it with int arguments.
inline std::function<int(int, int)> make_int_adder() {
    TODO();
}

// Return a lambda that adds two doubles.
// The tests call it with double arguments.
inline std::function<double(double, double)> make_double_adder() {
    TODO();
}

// Write a function template that takes a value and a callable,
// applies the callable twice: fn(fn(value)), and returns the result.
template<typename T, typename Fn>
inline T apply_twice(T value, Fn fn) {
    TODO();
}

// Return a lambda that takes a vector<int> and returns the max element.
// Assume the vector is non-empty.
inline std::function<int(const std::vector<int>&)> make_max_finder() {
    TODO();
}
