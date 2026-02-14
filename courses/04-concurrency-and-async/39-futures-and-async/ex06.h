// Exercise 06: wait_for with Timeout
//
// PROBLEM:
//   Return a future<int> that resolves to n * 2. Use std::async with
//   std::launch::async to launch the computation.
//
// TODO:
//   Implement slow_compute() using std::async(std::launch::async, ...).
//
// WHY:
//   std::future::wait_for lets you check whether a result is ready without
//   blocking forever. It returns a std::future_status indicating whether
//   the future is ready, timed out, or deferred. This is essential for
//   building responsive systems that can't afford to block indefinitely.

#pragma once
#include <testkit/testkit.h>
#include <future>

// Returns a future that resolves to n * 2.
inline std::future<int> slow_compute(int n) {
    TODO();
}
