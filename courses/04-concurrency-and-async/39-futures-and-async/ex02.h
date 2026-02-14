// Exercise 02: Launch Policies
//
// PROBLEM:
//   Return a future<int> that resolves to n * n + 1, using the deferred
//   launch policy. The computation should only execute when .get() or
//   .wait() is called on the future.
//
// TODO:
//   Implement deferred_compute() using std::async with std::launch::deferred.
//
// WHY:
//   std::launch::deferred creates a lazy future — the callable is stored
//   but not executed until the result is explicitly requested. This is
//   useful when you want to defer expensive work that may never be needed.

#pragma once
#include <testkit/testkit.h>
#include <future>

// Returns a deferred future that resolves to n * n + 1.
inline std::future<int> deferred_compute(int n) {
    TODO();
}
