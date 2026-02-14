// Exercise 02: Capture by Reference
//
// A lambda can capture variables from its enclosing scope. Capture by
// reference lets the lambda modify the original variable:
//
//   int count = 0;
//   auto inc = [&count]() { ++count; };
//   inc();   // count is now 1
//
// You can also capture everything by reference with [&], though
// explicit captures are generally preferred for clarity.
//
// Common use: a counting lambda passed to std::for_each or
// std::count_if that accumulates a result in a local variable.
//
// TODO:
//   1. Implement count_if_positive() -- use std::for_each with a lambda
//      that captures a counter by reference and increments it for each
//      positive element. Return the count.
//   2. Implement sum_elements() -- use std::for_each with a lambda that
//      captures a running sum by reference. Return the sum.
//   3. Implement apply_to_each() -- use std::for_each with a lambda
//      that captures a results vector by reference and pushes each
//      element multiplied by `factor`. Return the results vector.

#pragma once

#include <algorithm>
#include <vector>
#include <testkit/testkit.h>

// Count positive elements using for_each with a lambda that captures
// a counter by reference.
inline int count_if_positive(const std::vector<int>& nums) {
    TODO();
}

// Sum all elements using for_each with a lambda that captures a
// running total by reference.
inline int sum_elements(const std::vector<int>& nums) {
    TODO();
}

// Multiply each element by `factor` and collect the results in a vector.
// Use for_each with a lambda that captures the results vector by reference.
inline std::vector<int> apply_to_each(const std::vector<int>& nums, int factor) {
    TODO();
}
