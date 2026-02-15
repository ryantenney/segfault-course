// Exercise 09: End-to-End
//
// This capstone exercise ties everything together. A raw HTTP string
// goes through: parse -> route -> middleware -> handler -> serialize.
//
// All the types and helpers are provided. You implement the glue.
//
// TODO:
//   1. Implement parse_request()      — parse raw string into Request.
//   2. Implement serialize_response() — serialize Response to string.
//   3. Implement Router::add_route()  — register a handler.
//   4. Implement Router::use()        — add middleware.
//   5. Implement Router::dispatch()   — route + middleware + error handling.
//   6. Implement handle_raw()         — full pipeline from raw string
//      to raw response string.

#pragma once

#include <testkit/testkit.h>
#include <functional>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// ---------------------------------------------------------------------------
// Types
// ---------------------------------------------------------------------------

struct Request {
    std::string method;
    std::string path;
    std::string version;
    std::map<std::string, std::string> headers;
    std::string body;
};

struct Response {
    int status = 200;
    std::map<std::string, std::string> headers;
    std::string body;
};

using Handler = std::function<Response(const Request&)>;
using Middleware = std::function<Handler(Handler)>;

// ---------------------------------------------------------------------------
// Helpers (provided)
// ---------------------------------------------------------------------------

inline std::string reason_phrase(int status) {
    switch (status) {
        case 200: return "OK";
        case 201: return "Created";
        case 400: return "Bad Request";
        case 404: return "Not Found";
        case 500: return "Internal Server Error";
        default:  return "Unknown";
    }
}

// ---------------------------------------------------------------------------
// Parse + Serialize — implement these.
// ---------------------------------------------------------------------------

// Parse raw HTTP string. On failure, return Request with empty method.
inline Request parse_request(const std::string& raw) {
    TODO();
}

// Serialize a Response to raw HTTP string.
inline std::string serialize_response(const Response& resp) {
    TODO();
}

// ---------------------------------------------------------------------------
// Router — implement these.
// ---------------------------------------------------------------------------

class Router {
    std::map<std::string, Handler> routes_;
    std::vector<Middleware> middleware_;

    static std::string make_key(const std::string& method,
                                const std::string& path) {
        return method + " " + path;
    }

public:
    void add_route(const std::string& method, const std::string& path,
                   Handler handler) {
        TODO();
    }

    void use(Middleware mw) {
        TODO();
    }

    // Dispatch with full error handling:
    //   - Empty method or path -> 400.
    //   - No matching route -> 404.
    //   - Handler throws std::exception -> 500 with e.what().
    //   - Handler throws other -> 500 "Internal Server Error".
    //   - Middleware wraps the handler in order.
    Response dispatch(const Request& req) {
        TODO();
    }
};

// ---------------------------------------------------------------------------
// Full pipeline — implement this.
// ---------------------------------------------------------------------------

// Process a raw HTTP request string through the router and return
// a raw HTTP response string. If parsing fails, return a 400 response.
inline std::string handle_raw(Router& router, const std::string& raw) {
    TODO();
}
