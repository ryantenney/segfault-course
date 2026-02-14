// Exercise 04: Exception Propagation
//
// PROBLEM:
//   Implement async_divide to perform integer division. If the divisor is
//   zero, throw std::invalid_argument. Use std::async so the exception
//   propagates through the future.
//
// TODO:
//   Implement async_divide() using std::async. Throw on divide-by-zero.
//
// WHY:
//   When an async task throws an exception, std::future captures it.
//   Calling .get() on the future re-throws the stored exception, making
//   error handling in async code feel natural.

#pragma once
#include <testkit/testkit.h>
#include <future>
#include <stdexcept>

// Returns a future that resolves to a / b.
// Throws std::invalid_argument if b is 0.
inline std::future<int> async_divide(int a, int b) {
    TODO();
}
