// Exercise 08: Conditional Middleware
//
// Not every middleware should run for every request. A conditional middleware
// checks whether the context matches some condition (e.g. a path prefix)
// before running its inner logic. If the condition does not match, it simply
// calls next() without doing anything.
//
// TODO:
//   Implement make_path_middleware() — returns a middleware that:
//   1. Checks if the context string starts with the given `prefix`.
//   2. If it matches: append `tag` to the context, then call next().
//   3. If it does not match: call next() without modifying the context.

#pragma once

#include <testkit/testkit.h>
#include <functional>
#include <string>

using Middleware08 = std::function<void(std::string& context, std::function<void()> next)>;

// Return a middleware that only modifies the context if it starts with `prefix`.
// When the prefix matches, append `tag` to the context and call next().
// When the prefix does not match, just call next() unchanged.
inline Middleware08 make_path_middleware(const std::string& prefix, const std::string& tag) {
    TODO();
}
