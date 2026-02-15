// Exercise 03: Build Method
//
// A builder accumulates state, then a build() method produces the
// final immutable product. This separates the mutable construction
// phase from the immutable result.
//
// TODO:
//   1. Implement the Request struct with method, url, and body fields.
//      (Already provided below.)
//   2. Implement set_method(), set_url(), set_body() returning *this.
//   3. Implement build() -- returns a Request struct with the stored values.

#pragma once

#include <testkit/testkit.h>
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

    Request build() const {
        TODO();
    }
};
