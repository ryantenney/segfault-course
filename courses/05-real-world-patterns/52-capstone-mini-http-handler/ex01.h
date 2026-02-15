// Exercise 01: Route Registration
//
// A Router maps (method, path) pairs to handler functions. This
// exercise focuses on registering routes and looking them up.
//
// TODO:
//   1. Implement add_route() — store the handler keyed by method+path.
//   2. Implement find_handler() — return the handler for a method+path,
//      or nullptr if no route matches.

#pragma once

#include <testkit/testkit.h>
#include <functional>
#include <map>
#include <string>

struct Request {
    std::string method;
    std::string path;
    std::string body;
};

struct Response {
    int status = 200;
    std::string body;
};

using Handler = std::function<Response(const Request&)>;

class Router {
    std::map<std::string, Handler> routes_;

    static std::string make_key(const std::string& method, const std::string& path) {
        return method + " " + path;
    }

public:
    // Register a handler for the given method and path.
    void add_route(const std::string& method, const std::string& path,
                   Handler handler) {
        TODO();
    }

    // Look up a handler. Returns nullptr if not found.
    Handler find_handler(const std::string& method,
                         const std::string& path) const {
        TODO();
    }
};
