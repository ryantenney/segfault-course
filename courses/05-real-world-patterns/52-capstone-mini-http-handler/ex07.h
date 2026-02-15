// Exercise 07: Error Handling
//
// The router must handle three kinds of errors gracefully:
//   400 Bad Request    — the request is malformed (empty method/path).
//   404 Not Found      — no route matches.
//   500 Internal Error — the handler throws an exception.
//
// TODO:
//   1. Implement add_route() — store the handler.
//   2. Implement dispatch()  — validate request, find handler, call it
//      with exception safety. Return proper error responses.

#pragma once

#include <testkit/testkit.h>
#include <functional>
#include <map>
#include <stdexcept>
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
    void add_route(const std::string& method, const std::string& path,
                   Handler handler) {
        TODO();
    }

    // Dispatch with error handling:
    //   - If method or path is empty, return 400 "Bad Request".
    //   - If no route matches, return 404 "Not Found".
    //   - If the handler throws std::exception, return 500 with the
    //     exception message as the body.
    //   - If the handler throws something else, return 500
    //     "Internal Server Error".
    Response dispatch(const Request& req) {
        TODO();
    }
};
