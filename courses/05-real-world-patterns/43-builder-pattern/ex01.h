// Exercise 01: Basic Builder
//
// The builder pattern separates the construction of a complex object from
// its representation. A builder accumulates configuration step by step,
// then produces the final object.
//
// Here you'll build a simple RequestBuilder that stores method, url, and
// body as separate setter calls.
//
// TODO:
//   1. Implement set_method() -- stores the given HTTP method string.
//   2. Implement set_url()    -- stores the given URL string.
//   3. Implement set_body()   -- stores the given body string.
//   4. Implement get_method(), get_url(), get_body() -- return the stored values.

#pragma once

#include <testkit/testkit.h>
#include <string>

class RequestBuilder {
    std::string method_;
    std::string url_;
    std::string body_;

public:
    void set_method(const std::string& method) {
        TODO();
    }

    void set_url(const std::string& url) {
        TODO();
    }

    void set_body(const std::string& body) {
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
