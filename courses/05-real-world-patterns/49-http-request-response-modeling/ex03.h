// Exercise 03: Headers Class
//
// HTTP headers are key-value pairs, but the keys are case-insensitive
// per the HTTP spec ("Content-Type" and "content-type" are the same).
//
// TODO:
//   1. Implement set(key, value) -- store a single value for the key.
//   2. Implement get(key) -- return the value as optional<string>.
//      Return std::nullopt if the key is not present.
//   3. Implement has(key) -- return true if the key is present.
//   4. Implement remove(key) -- remove the key and its value.
//
// HINT: To make lookups case-insensitive, convert keys to lowercase
//       before storing/looking them up.

#pragma once

#include <testkit/testkit.h>
#include <algorithm>
#include <map>
#include <optional>
#include <string>

class Headers {
    std::map<std::string, std::string> headers_;

    // Helper: convert a string to lowercase.
    static std::string to_lower(std::string s) {
        std::transform(s.begin(), s.end(), s.begin(),
                       [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
        return s;
    }

public:
    // Store a value for the given key (case-insensitive).
    void set(const std::string& key, const std::string& value) {
        TODO();
    }

    // Retrieve the value for the given key, or std::nullopt.
    std::optional<std::string> get(const std::string& key) const {
        TODO();
    }

    // Return true if the key exists.
    bool has(const std::string& key) const {
        TODO();
    }

    // Remove the key and its value.
    void remove(const std::string& key) {
        TODO();
    }
};
