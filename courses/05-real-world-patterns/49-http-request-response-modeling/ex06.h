// Exercise 06: Response Builder
//
// Build an HTTP Response using a fluent (method-chaining) API. Each
// setter returns a reference to the builder so calls can be chained:
//   ResponseBuilder().status(200).header("X", "Y").body("...").build()
//
// TODO:
//   1. Implement status(int code) -- store the status code, return *this.
//   2. Implement header(key, value) -- add a header, return *this.
//   3. Implement set_body(text) -- store the body, return *this.
//   4. Implement build() -- return the finished Response.

#pragma once

#include <testkit/testkit.h>
#include <map>
#include <string>

struct Response {
    int status_code = 0;
    std::map<std::string, std::string> headers;
    std::string body;
};

class ResponseBuilder {
    Response response_;

public:
    // Set the status code. Returns *this for chaining.
    ResponseBuilder& status(int code) {
        TODO();
    }

    // Add a header. Returns *this for chaining.
    ResponseBuilder& header(const std::string& key, const std::string& value) {
        TODO();
    }

    // Set the body. Returns *this for chaining.
    ResponseBuilder& set_body(const std::string& text) {
        TODO();
    }

    // Produce the finished Response.
    Response build() const {
        TODO();
    }
};
