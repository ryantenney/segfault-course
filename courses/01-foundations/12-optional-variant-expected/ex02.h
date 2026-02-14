// Exercise 02: Optional with value_or
//
// When you have an optional, you often want to use its value if present, or
// fall back to a default. The value_or() member function does exactly this:
//
//   std::optional<int> opt = ...;
//   int val = opt.value_or(42);  // 42 if opt is empty
//
// This is cleaner than writing an if/else every time.
//
// TODO:
//   1. Implement get_config_value() to look up a key in a small config table.
//      Return the value as optional<string>, or nullopt if the key is missing.
//   2. Implement get_config_or_default() using value_or() to return either
//      the looked-up value or the provided default string.
//
//   Config table:
//     "host" -> "localhost", "port" -> "8080", "mode" -> "debug"

#pragma once

#include <optional>
#include <string>
#include <testkit/testkit.h>

// Look up a config key. Return the value or nullopt.
inline std::optional<std::string> get_config_value(const std::string& key) {
    TODO();
}

// Look up a config key. Return the value if found, otherwise return default_val.
// Hint: call get_config_value() and use .value_or().
inline std::string get_config_or_default(const std::string& key,
                                         const std::string& default_val) {
    TODO();
}
