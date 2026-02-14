// Exercise 05: Multiple Futures
//
// PROBLEM:
//   Given a vector of ints, launch an async computation for each element
//   that squares it. Return a vector of futures holding the results.
//
// TODO:
//   Implement async_transform() using std::async for each element.
//
// WHY:
//   Real workloads often involve launching many async tasks and collecting
//   results. Building a vector of futures is a common pattern for fan-out
//   parallelism.

#pragma once
#include <testkit/testkit.h>
#include <future>
#include <vector>

// Returns a vector of futures, each resolving to the square of the
// corresponding input element.
inline std::vector<std::future<int>> async_transform(const std::vector<int>& v) {
    TODO();
}
