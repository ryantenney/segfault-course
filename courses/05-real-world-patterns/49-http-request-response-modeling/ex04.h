// Exercise 04: Multi-value Headers
//
// Some HTTP headers (like Set-Cookie, Accept) can appear multiple times.
// This exercise extends the header concept to support multiple values
// per key.
//
// TODO:
//   1. Implement add(key, value) -- append a value (do not replace).
//   2. Implement get_all(key) -- return all values as a vector<string>.
//      Return an empty vector if the key is not present.
//   3. Implement get_first(key) -- return the first value, or nullopt.
//   4. Implement remove(key) -- remove all values for the key.

#pragma once

#include <testkit/testkit.h>
#include <algorithm>
#include <map>
#include <optional>
#include <string>
#include <vector>

class MultiHeaders {
    std::map<std::string, std::vector<std::string>> headers_;

    static std::string to_lower(std::string s) {
        std::transform(s.begin(), s.end(), s.begin(),
                       [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
        return s;
    }

public:
    // Append a value for the given key (case-insensitive).
    void add(const std::string& key, const std::string& value) {
        TODO();
    }

    // Return all values for the key, or an empty vector.
    std::vector<std::string> get_all(const std::string& key) const {
        TODO();
    }

    // Return the first value for the key, or std::nullopt.
    std::optional<std::string> get_first(const std::string& key) const {
        TODO();
    }

    // Remove all values for the key.
    void remove(const std::string& key) {
        TODO();
    }
};
