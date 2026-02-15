// Exercise 05: Builder with Defaults
//
// A well-designed builder provides sensible defaults so callers only
// need to configure what differs from the common case. Here, method
// defaults to "GET" and headers default to an empty vector.
//
// TODO:
//   1. Implement set_method(), set_url(), set_body(), add_header()
//      returning *this.
//   2. Implement build():
//      - Method defaults to "GET" if not set.
//      - Headers default to empty if none added.
//      - URL is required: return std::nullopt if empty.
//      - Otherwise return a Request.

#pragma once

#include <testkit/testkit.h>
#include <optional>
#include <string>
#include <utility>
#include <vector>

struct Request {
    std::string method;
    std::string url;
    std::string body;
    std::vector<std::pair<std::string, std::string>> headers;
};

class RequestBuilder {
    std::string method_;
    std::string url_;
    std::string body_;
    std::vector<std::pair<std::string, std::string>> headers_;

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

    RequestBuilder& add_header(const std::string& key, const std::string& value) {
        TODO();
    }

    std::optional<Request> build() const {
        TODO();
    }
};
