// Exercise 01: Function Chain
//
// A middleware is a function that wraps some inner behavior. In C++ we model
// this as a std::function that receives a context string and a "next" callback.
// Calling next() passes control to the next middleware in the chain (or to the
// final handler). Not calling next() short-circuits the rest of the chain.
//
// Signature of a single middleware:
//   std::function<void(std::string& context, std::function<void()> next)>
//
// TODO:
//   Implement run_middleware() — invoke the given middleware with the provided
//   context and next callback.
//
// WHY:
//   Middleware chains are everywhere: HTTP servers, logging pipelines, event
//   processing. Understanding how to compose functions that wrap inner behavior
//   is a key real-world pattern.

#pragma once

#include <testkit/testkit.h>
#include <functional>
#include <string>

// A middleware is a function taking a mutable context string and a next callback.
using Middleware = std::function<void(std::string& context, std::function<void()> next)>;

// Invoke `mw` with the given `context` and `next` callback.
inline void run_middleware(Middleware mw, std::string& context, std::function<void()> next) {
    TODO();
}
