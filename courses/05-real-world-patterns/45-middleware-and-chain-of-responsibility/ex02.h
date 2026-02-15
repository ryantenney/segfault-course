// Exercise 02: Request/Response Context
//
// Real middleware operates on a structured context, not a plain string.
// A Context object carries the request data, response data, and arbitrary
// metadata that middleware can read and write as the request flows through
// the chain.
//
// TODO:
//   1. Implement Context::set_metadata() — store a key-value pair.
//   2. Implement Context::get_metadata() — retrieve a value by key,
//      returning std::optional<std::string>. Return std::nullopt if not found.
//
// The request and response fields are public strings — no TODO needed there.

#pragma once

#include <testkit/testkit.h>
#include <map>
#include <optional>
#include <string>

struct Context {
    std::string request;
    std::string response;

    // Store a metadata key-value pair.
    inline void set_metadata(const std::string& key, const std::string& value) {
        TODO();
    }

    // Retrieve metadata by key. Return std::nullopt if the key does not exist.
    inline std::optional<std::string> get_metadata(const std::string& key) const {
        TODO();
    }

private:
    std::map<std::string, std::string> metadata_;
};
