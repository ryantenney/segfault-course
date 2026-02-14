// Exercise 04: Exception Safety with RAII
//
// When an exception is thrown, the stack unwinds: local variables in each
// frame are destroyed in reverse order. If you allocate memory with `new`
// and an exception is thrown before `delete`, you have a memory leak.
//
// RAII (Resource Acquisition Is Initialization) fixes this: wrap every
// resource in an object whose destructor releases it. When the stack
// unwinds, destructors run automatically.
//
// In this exercise, the buggy version uses raw new/delete. If the processing
// step throws, the delete never runs. Your job is to fix it with RAII.
//
// TODO:
//   1. Implement process_data_unsafe() — this is the BUGGY version that
//      leaks on exception. Allocate an int array with new[], set each
//      element to (i * factor), compute the sum, delete[], and return.
//      If factor is 0, throw std::runtime_error("zero factor") AFTER
//      the allocation (simulating a mid-function error).
//
//   2. Implement process_data_safe() — the FIXED version using
//      std::unique_ptr<int[]> instead of raw new/delete. Same logic,
//      but no leak on exception.

#pragma once

#include <memory>
#include <stdexcept>
#include <testkit/testkit.h>

// BUGGY: Allocates with new[], may leak if exception is thrown.
// Allocate an array of `count` ints, set arr[i] = i * factor.
// If factor == 0, throw std::runtime_error("zero factor").
// Otherwise compute and return the sum of all elements.
inline int process_data_unsafe(int count, int factor) {
    TODO();
}

// SAFE: Same logic as above, but uses std::unique_ptr<int[]> so the
// memory is freed automatically even if an exception is thrown.
inline int process_data_safe(int count, int factor) {
    TODO();
}
