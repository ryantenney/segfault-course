// Exercise 07: Nested Builder
//
// Complex objects often contain sub-objects. A nested builder pattern
// lets you build the inner parts with their own builders, then compose
// them into the outer object.
//
// Here, an HttpRequest contains a Headers object (built by HeadersBuilder)
// and a Body object (built by BodyBuilder). The top-level RequestBuilder
// composes them.
//
// TODO:
//   1. Implement HeadersBuilder::add() -- stores a key-value pair, returns *this.
//   2. Implement HeadersBuilder::build() -- returns a Headers struct.
//   3. Implement BodyBuilder::set_content() -- stores content, returns *this.
//   4. Implement BodyBuilder::set_content_type() -- stores content type, returns *this.
//   5. Implement BodyBuilder::build() -- returns a Body struct.
//   6. Implement RequestBuilder::set_method(), set_url() returning *this.
//   7. Implement RequestBuilder::headers_builder() -- returns reference to inner
//      HeadersBuilder.
//   8. Implement RequestBuilder::body_builder() -- returns reference to inner
//      BodyBuilder.
//   9. Implement RequestBuilder::build() -- builds the HttpRequest by calling
//      build() on the sub-builders.

#pragma once

#include <testkit/testkit.h>
#include <string>
#include <utility>
#include <vector>

struct Headers {
    std::vector<std::pair<std::string, std::string>> entries;
};

struct Body {
    std::string content;
    std::string content_type;
};

struct HttpRequest {
    std::string method;
    std::string url;
    Headers headers;
    Body body;
};

class HeadersBuilder {
    std::vector<std::pair<std::string, std::string>> entries_;

public:
    HeadersBuilder& add(const std::string& key, const std::string& value) {
        TODO();
    }

    Headers build() const {
        TODO();
    }
};

class BodyBuilder {
    std::string content_;
    std::string content_type_;

public:
    BodyBuilder& set_content(const std::string& content) {
        TODO();
    }

    BodyBuilder& set_content_type(const std::string& content_type) {
        TODO();
    }

    Body build() const {
        TODO();
    }
};

class RequestBuilder {
    std::string method_;
    std::string url_;
    HeadersBuilder headers_builder_;
    BodyBuilder body_builder_;

public:
    RequestBuilder& set_method(const std::string& method) {
        TODO();
    }

    RequestBuilder& set_url(const std::string& url) {
        TODO();
    }

    HeadersBuilder& headers_builder() {
        TODO();
    }

    BodyBuilder& body_builder() {
        TODO();
    }

    HttpRequest build() const {
        TODO();
    }
};
