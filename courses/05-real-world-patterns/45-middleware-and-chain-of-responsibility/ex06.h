// Exercise 06: Error-handling Middleware
//
// In a real middleware pipeline, exceptions can be thrown by any handler.
// An error-handling middleware sits at the front of the chain, wraps the
// call to next() in a try/catch, and converts exceptions into an error
// response on the context instead of letting them propagate.
//
// TODO:
//   1. Implement make_error_handler() — returns a middleware that:
//      - Calls next() inside a try block.
//      - Catches std::exception and sets context to "500: " + e.what().
//      - Re-throws testkit::not_implemented (so TODO() still works).
//   2. Implement execute_with_error_handling() — same chain logic as before.

#pragma once

#include <testkit/testkit.h>
#include <functional>
#include <stdexcept>
#include <string>
#include <vector>

using Middleware06 = std::function<void(std::string& context, std::function<void()> next)>;

// Return an error-handling middleware.
// It calls next() in a try block. If a std::exception is caught
// (but NOT testkit::not_implemented), set context to "500: " + e.what().
inline Middleware06 make_error_handler() {
    TODO();
}

// Run all middleware in order, then call handler.
inline void execute_with_error_handling(const std::vector<Middleware06>& middleware,
                                        std::string& context,
                                        std::function<void()> handler) {
    TODO();
}
