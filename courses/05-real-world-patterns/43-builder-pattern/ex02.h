// Exercise 02: Method Chaining
//
// A fluent interface lets callers chain method calls:
//   builder.set_method("POST").set_url("/api").set_body("data");
//
// The trick: each setter returns a reference to *this so the next
// call can be made on the same object.
//
// TODO:
//   1. Implement set_method() -- store the method, return *this.
//   2. Implement set_url()    -- store the url, return *this.
//   3. Implement set_body()   -- store the body, return *this.
//   4. Implement get_method(), get_url(), get_body().

#pragma once

#include <testkit/testkit.h>
#include <string>

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

    std::string get_method() const {
        TODO();
    }

    std::string get_url() const {
        TODO();
    }

    std::string get_body() const {
        TODO();
    }
};
