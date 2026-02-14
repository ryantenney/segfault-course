// Exercise 06: If-init with binding
//
// PROBLEM:
//   C++17 added if-with-initializer, which pairs perfectly with
//   structured bindings:
//
//     if (auto [iter, ok] = map.insert({k, v}); ok) {
//         // insertion succeeded
//     } else {
//         // key already existed, iter points to existing entry
//     }
//
//   This scopes the variables tightly to the if/else block and
//   combines the check with the operation in a single statement.
//
// TODO:
//   Use if-init with structured bindings in each function.

#pragma once

#include <testkit/testkit.h>
#include <map>
#include <string>

// Try to insert key/value into the map. If successful, return
// "inserted: <key>". If the key exists, return "exists: <key>".
// Use if-init: if (auto [iter, ok] = m.insert({key, value}); ok)
inline std::string describe_insert(std::map<std::string, int>& m,
                                   const std::string& key, int value) {
    TODO();
}

// Try to find `key` in the map. If found, return its value.
// If not found, return `fallback`.
// Use if-init: if (auto it = m.find(key); it != m.end())
inline int find_or(const std::map<std::string, int>& m,
                   const std::string& key, int fallback) {
    TODO();
}

// Try to find `key` in the map. If found and the value is positive,
// return "positive". If found and non-positive, return "non-positive".
// If not found, return "missing".
// Use if-init with the find result.
inline std::string classify_value(const std::map<std::string, int>& m,
                                  const std::string& key) {
    TODO();
}
