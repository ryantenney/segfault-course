// Exercise 04: jthread and stop_token
//
// PROBLEM:
//   std::jthread supports cooperative cancellation via stop_token.
//   The thread periodically checks whether a stop has been requested,
//   and exits its loop when it has.
//
// TODO:
//   Implement count_until_stopped() so that it increments counter in a
//   loop, checking token.stop_requested() each iteration. When stop is
//   requested, the function should return.
//
// HINT:
//   while (!token.stop_requested()) {
//       counter.fetch_add(1);
//   }
//
// WHY:
//   Threads often run long-lived loops. You need a way to ask them to
//   stop gracefully. jthread pairs with stop_token for this: calling
//   jthread::request_stop() sets the token, and the thread checks it.

#pragma once
#include <testkit/testkit.h>
#include <atomic>
#include <stop_token>

// Increments counter in a loop until stop is requested via token.
inline void count_until_stopped(std::stop_token token, std::atomic<int>& counter) {
    TODO();
}
