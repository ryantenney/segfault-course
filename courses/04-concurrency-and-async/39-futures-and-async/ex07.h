// Exercise 07: Shared Future
//
// PROBLEM:
//   Return a shared_future<int> that resolves to n * 10. Unlike a regular
//   future, a shared_future can be .get()-ed multiple times and copied.
//
// TODO:
//   Implement make_shared_result() returning a std::shared_future<int>.
//   Hint: std::async returns a std::future. Call .share() on it to get
//   a std::shared_future.
//
// WHY:
//   A regular future is move-only and can be .get()-ed exactly once. When
//   multiple consumers need the same result, you need a shared_future.
//   It's copyable, and every copy can call .get() independently.

#pragma once
#include <testkit/testkit.h>
#include <future>

// Returns a shared future that resolves to n * 10.
inline std::shared_future<int> make_shared_result(int n) {
    TODO();
}
