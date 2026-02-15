// Exercise 05: Middleware Composition
//
// A Pipeline class encapsulates an ordered list of middleware and provides
// a clean API: add middleware with use(), then execute() with a context and
// final handler. Internally it chains them with the next-function pattern.
//
// TODO:
//   1. Implement Pipeline::use() — append a middleware to the internal list.
//   2. Implement Pipeline::execute() — run all middleware in order, then
//      the handler. Use the same next-chaining pattern as ex03/ex04.

#pragma once

#include <testkit/testkit.h>
#include <functional>
#include <string>
#include <vector>

using Middleware05 = std::function<void(std::string& context, std::function<void()> next)>;

class Pipeline {
    std::vector<Middleware05> middleware_;

public:
    // Append a middleware to the pipeline.
    inline void use(Middleware05 mw) {
        TODO();
    }

    // Execute all middleware in order, then call handler.
    inline void execute(std::string& context, std::function<void()> handler) const {
        TODO();
    }
};
