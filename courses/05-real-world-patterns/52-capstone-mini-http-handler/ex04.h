// Exercise 04: Middleware Integration
//
// Middleware wraps a handler to add cross-cutting behavior (logging,
// auth, timing, etc.). A middleware takes a Handler and returns a new
// Handler that decorates the original.
//
// The Router stores a list of middleware and applies them in order
// before calling the final handler.
//
// TODO:
//   1. Implement add_route()      — store the handler.
//   2. Implement use()            — add a middleware to the chain.
//   3. Implement dispatch()       — wrap the handler through all
//      middleware, then call it. Return 404 if no route matches.

#pragma once

#include <testkit/testkit.h>
#include <functional>
#include <map>
#include <string>
#include <vector>

struct Request {
    std::string method;
    std::string path;
    std::string body;
    std::map<std::string, std::string> headers;
};

struct Response {
    int status = 200;
    std::string body;
    std::map<std::string, std::string> headers;
};

using Handler = std::function<Response(const Request&)>;
using Middleware = std::function<Handler(Handler)>;

class Router {
    std::map<std::string, Handler> routes_;
    std::vector<Middleware> middleware_;

    static std::string make_key(const std::string& method, const std::string& path) {
        return method + " " + path;
    }

public:
    void add_route(const std::string& method, const std::string& path,
                   Handler handler) {
        TODO();
    }

    // Add a middleware. Middleware are applied in the order added:
    // the first middleware added is the outermost wrapper.
    void use(Middleware mw) {
        TODO();
    }

    // Dispatch the request. Apply all middleware around the handler.
    // Return 404 with "Not Found" if no route matches.
    Response dispatch(const Request& req) {
        TODO();
    }
};
