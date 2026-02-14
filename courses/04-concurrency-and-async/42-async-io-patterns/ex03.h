// Exercise 03: Future-based Wrapper
//
// PROBLEM:
//   Wrap a callback-based API into a function that returns a std::future.
//   This bridges the callback world with the future/promise world.
//
// TODO:
//   Implement future_read() that:
//   1. Creates a std::promise<std::string>.
//   2. Calls the provided callback-based async_read_cb with a callback
//      that sets the promise value.
//   3. Returns the promise's future.
//
// WHY:
//   Futures are a higher-level abstraction than callbacks. Instead of
//   passing a callback, you get a future object that you can query for
//   the result later with .get(). This is the first step toward
//   structured concurrency — the result has a name and a lifetime.
//   Wrapping callback APIs into futures is a common real-world task.

#pragma once
#include <testkit/testkit.h>
#include <functional>
#include <future>
#include <string>

// A callback-based async read (provided — do not modify).
// Calls the callback synchronously with "future data".
inline void async_read_cb(std::function<void(const std::string&)> callback) {
    callback("future data");
}

// Wraps async_read_cb into a future-returning function.
// Returns a std::future<std::string> that will contain the read result.
inline std::future<std::string> future_read() {
    TODO();
    // Hint:
    //   auto p = std::make_shared<std::promise<std::string>>();
    //   auto f = p->get_future();
    //   async_read_cb([p](const std::string& data) { p->set_value(data); });
    //   return f;
}
