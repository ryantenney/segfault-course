// Exercise 03: Next Function
//
// A middleware chain runs multiple middleware in order. Each middleware
// receives a "next" callback that, when called, invokes the next middleware
// in the list (and so on recursively until the final handler runs).
//
// This exercise builds the call-next mechanism: given a vector of middleware
// functions and a final handler, compose them so they execute in order.
//
// TODO:
//   Implement chain_execute() — run all middleware in order, then the handler.
//   Build a recursive next-function: the first middleware's "next" calls the
//   second middleware, whose "next" calls the third, etc. The last middleware's
//   "next" calls the final handler.
//
// HINT:
//   Use a recursive helper or a shared index. At each step, create a next
//   callback that advances to the next middleware.

#pragma once

#include <testkit/testkit.h>
#include <functional>
#include <string>
#include <vector>

// A middleware takes a mutable context and a next callback.
using Middleware03 = std::function<void(std::string& context, std::function<void()> next)>;

// Run all middleware in order, then call handler at the end.
// Each middleware's "next" invokes the next middleware in the list.
// The last middleware's "next" invokes `handler`.
inline void chain_execute(const std::vector<Middleware03>& middleware,
                          std::string& context,
                          std::function<void()> handler) {
    TODO();
}
