// Exercise 06: Type-State Builder
//
// The type-state pattern uses the type system to enforce protocol
// constraints at compile time. Here, build() should only be callable
// when the URL has been set. We encode "has URL" vs "no URL" in a
// template bool parameter.
//
// TODO:
//   1. Implement set_method() -- stores method, returns builder with
//      same HasUrl state.
//   2. Implement set_url() -- stores url, returns TypedRequestBuilder<true>.
//   3. Implement set_body() -- stores body, returns builder with same HasUrl state.
//   4. Implement build() (only in the HasUrl=true specialization) --
//      returns a Request with the stored values.
//
// WHY:
//   With this design, calling build() on a builder where set_url()
//   was never called is a compile error -- the API is impossible to
//   misuse at runtime because the type system prevents it.

#pragma once

#include <testkit/testkit.h>
#include <string>

struct Request {
    std::string method;
    std::string url;
    std::string body;
};

template<bool HasUrl>
class TypedRequestBuilder {
    std::string method_;
    std::string url_;
    std::string body_;

    // Private constructor so set_url() can create TypedRequestBuilder<true>
    template<bool> friend class TypedRequestBuilder;

    TypedRequestBuilder(std::string method, std::string url, std::string body)
        : method_(std::move(method)), url_(std::move(url)), body_(std::move(body)) {}

public:
    TypedRequestBuilder() = default;

    TypedRequestBuilder<HasUrl> set_method(const std::string& method) {
        TODO();
    }

    TypedRequestBuilder<true> set_url(const std::string& url) {
        TODO();
    }

    TypedRequestBuilder<HasUrl> set_body(const std::string& body) {
        TODO();
    }

    // build() is only available when HasUrl is true.
    // The enable_if ensures that calling build() on TypedRequestBuilder<false>
    // is a compile error.
    template<bool U = HasUrl, typename = std::enable_if_t<U>>
    Request build() const {
        TODO();
    }
};
