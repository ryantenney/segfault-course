// Exercise 05: Request Type
//
// An HTTP request has a method, a path, headers, and an optional body.
// This exercise models the Request as a struct with named fields and
// provides a convenience constructor.
//
// TODO:
//   1. Implement the make_request() free function that constructs a
//      Request from the given parameters.
//   2. Implement has_body() that returns true if the body is non-empty.
//   3. Implement full_path() that returns path + "?" + query if query
//      is non-empty, otherwise just the path.

#pragma once

#include <testkit/testkit.h>
#include <map>
#include <optional>
#include <string>

struct Request {
    std::string method;
    std::string path;
    std::string query;
    std::map<std::string, std::string> headers;
    std::optional<std::string> body;
};

// Create a Request from the given parameters.
inline Request make_request(const std::string& method,
                            const std::string& path,
                            const std::string& query,
                            const std::map<std::string, std::string>& headers,
                            const std::optional<std::string>& body) {
    TODO();
}

// Return true if the request has a non-empty body.
inline bool has_body(const Request& req) {
    TODO();
}

// Return the full path including query string if present.
// e.g., path="/api" query="" => "/api"
//       path="/api" query="key=val" => "/api?key=val"
inline std::string full_path(const Request& req) {
    TODO();
}
