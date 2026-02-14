// Exercise 01: Callback-based API
//
// PROBLEM:
//   Implement a simulated async read that calls a callback with the result.
//   This is the most basic async pattern: you pass a function (callback)
//   that gets invoked when the "operation" completes.
//
// TODO:
//   Implement async_read(callback) so that it calls the callback with the
//   string "hello, world".
//
// WHY:
//   Callback-based APIs are the foundation of async I/O. Before futures,
//   promises, and coroutines, callbacks were the only way to handle async
//   results. Understanding them is essential because higher-level patterns
//   (futures, coroutine awaitables) are built on top of callbacks.

#pragma once
#include <testkit/testkit.h>
#include <functional>
#include <string>

// Simulates an async read operation. Calls callback with the result "hello, world".
// In real code, the callback would be invoked later (e.g., by an event loop or I/O
// completion). Here we call it synchronously to simulate the pattern.
inline void async_read(std::function<void(const std::string&)> callback) {
    TODO();
    // Hint: callback("hello, world");
}
