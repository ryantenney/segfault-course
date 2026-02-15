// Exercise 02: Router Dispatch
//
// dispatch() takes a Request, finds the matching handler, calls it,
// and returns the Response. If no route matches, return 404.
//
// TODO:
//   1. Implement add_route() — store the handler.
//   2. Implement dispatch()  — find and call the handler, or return 404.

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
    void add_route(const std::string& method, const std::string& path,
                   Handler handler) {
        TODO();
    }

    // Dispatch the request to the matching handler.
    // Return 404 with body "Not Found" if no route matches.
    Response dispatch(const Request& req) {
        TODO();
    }
};
