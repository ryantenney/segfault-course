// Exercise 01: Async Computation
//
// PROBLEM:
//   Return a future<int> that resolves to n * n. Use std::async to launch
//   the computation in another thread.
//
// TODO:
//   Implement async_square() using std::async.
//
// WHY:
//   std::async is the simplest way to run a computation asynchronously and
//   retrieve the result later. It returns a std::future that you can .get()
//   to block until the result is ready.

#pragma once
#include <testkit/testkit.h>
#include <future>

// Returns a future that resolves to n * n.
inline std::future<int> async_square(int n) {
    TODO();
}
