// Exercise 03: Path Parameters
//
// Support route patterns like "/users/:id" where :id is a path
// parameter. When a request matches, extract the parameter values
// into the request's params map.
//
// Matching rules:
//   - Split both the pattern and the request path by '/'.
//   - Segments must have equal count.
//   - A pattern segment starting with ':' matches any value and
//     captures it by name (without the ':').
//   - A literal segment must match exactly.
//
// TODO:
//   1. Implement add_route()    — store the pattern and handler.
//   2. Implement dispatch()     — match request path against patterns,
//      extract params, call handler. Return 404 if no match.

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
    std::map<std::string, std::string> params;
};

struct Response {
    int status = 200;
    std::string body;
};

using Handler = std::function<Response(const Request&)>;

// Split a string by a delimiter character.
inline std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> parts;
    std::string current;
    for (char c : s) {
        if (c == delim) {
            if (!current.empty()) parts.push_back(current);
            current.clear();
        } else {
            current += c;
        }
    }
    if (!current.empty()) parts.push_back(current);
    return parts;
}

struct RouteEntry {
    std::string method;
    std::string pattern;
    Handler handler;
};

class Router {
    std::vector<RouteEntry> routes_;

public:
    void add_route(const std::string& method, const std::string& pattern,
                   Handler handler) {
        TODO();
    }

    // Match request against registered patterns.
    // Populate req.params with extracted path parameters.
    // Return 404 with "Not Found" if no route matches.
    Response dispatch(Request req) {
        TODO();
    }
};
