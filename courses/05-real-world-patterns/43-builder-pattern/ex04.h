// Exercise 04: Required vs Optional Fields
//
// Not every request is valid. A URL is required, but body is optional.
// The build() method should validate and return std::optional<Request>:
// it returns std::nullopt when required fields are missing, or a
// fully-constructed Request when everything is present.
//
// TODO:
//   1. Implement set_method(), set_url(), set_body() returning *this.
//   2. Implement build():
//      - Return std::nullopt if url is empty.
//      - Return std::nullopt if method is empty.
//      - Otherwise return a Request with the stored values.

#pragma once

#include <testkit/testkit.h>
#include <optional>
#include <string>

struct Request {
    std::string method;
    std::string url;
    std::string body;
};

class RequestBuilder {
    std::string method_;
    std::string url_;
    std::string body_;

public:
    RequestBuilder& set_method(const std::string& method) {
        TODO();
    }

    RequestBuilder& set_url(const std::string& url) {
        TODO();
    }

    RequestBuilder& set_body(const std::string& body) {
        TODO();
    }

    std::optional<Request> build() const {
        TODO();
    }
};
