// Exercise 04: Early Exit
//
// A key feature of middleware chains is that any middleware can short-circuit
// the chain by NOT calling next(). This lets middleware set a response
// (e.g. "401 Unauthorized") and skip all downstream processing.
//
// This exercise reuses the chain mechanism from ex03, but focuses on testing
// the short-circuit behavior: a middleware that sets a response and returns
// without calling next.
//
// TODO:
//   1. Implement make_auth_middleware() — returns a middleware that checks
//      whether the context starts with "AUTH:". If it does, strip the prefix
//      and call next(). If not, set context to "401 Unauthorized" and do NOT
//      call next.
//   2. Implement chain_with_early_exit() — same chain_execute logic as ex03:
//      run middleware in order with next-chaining.

#pragma once

#include <testkit/testkit.h>
#include <functional>
#include <string>
#include <vector>

using Middleware04 = std::function<void(std::string& context, std::function<void()> next)>;

// Return a middleware that checks if context starts with "AUTH:".
// If yes: strip the "AUTH:" prefix from context and call next().
// If no: set context to "401 Unauthorized" and do NOT call next().
inline Middleware04 make_auth_middleware() {
    TODO();
}

// Run all middleware in order, then call handler.
// Same chaining logic as ex03.
inline void chain_with_early_exit(const std::vector<Middleware04>& middleware,
                                  std::string& context,
                                  std::function<void()> handler) {
    TODO();
}
