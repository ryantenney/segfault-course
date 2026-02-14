// Exercise 03: Insert or Update
//
// insert_or_assign(key, value) is the cleanest way to "upsert":
//   - If the key doesn't exist, it inserts the key-value pair.
//   - If the key already exists, it overwrites the value.
//
// Unlike operator[], insert_or_assign works with non-default-constructible
// value types and makes the insert-or-update intent explicit.
//
// TODO:
//   Implement the two functions below using insert_or_assign.

#pragma once

#include <testkit/testkit.h>
#include <unordered_map>
#include <vector>
#include <string>
#include <utility>

// Build a config map from a list of key-value pairs.
// If a key appears multiple times, the last value wins.
// Use insert_or_assign for each pair.
inline std::unordered_map<std::string, std::string> build_config(
        const std::vector<std::pair<std::string, std::string>>& entries) {
    TODO();
}

// Update a single setting in the config map.
// If the key exists, overwrite its value. If not, insert it.
// Use insert_or_assign.
inline void update_setting(std::unordered_map<std::string, std::string>& config,
                           const std::string& key,
                           const std::string& value) {
    TODO();
}
