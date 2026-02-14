// Exercise 04: try_emplace for Lazy Init
//
// try_emplace(key, args...) inserts a new element only if the key doesn't
// exist. If the key already exists, it does nothing -- no overwrite, no
// wasted construction of the value.
//
// It returns a pair:
//   auto [it, inserted] = m.try_emplace(key, default_value);
//   - it:       iterator to the element (existing or newly inserted)
//   - inserted: true if a new element was inserted, false if key existed
//
// This is useful for "get-or-create" patterns where you want to access
// the value regardless of whether it was just inserted or already present.
//
// TODO:
//   Implement the two functions below using try_emplace.

#pragma once

#include <testkit/testkit.h>
#include <unordered_map>
#include <vector>
#include <string>

// Return a reference to the value for `key` in the map.
// If the key doesn't exist, insert it with `default_value` first.
// Use try_emplace.
inline std::string& get_or_create(
        std::unordered_map<std::string, std::string>& m,
        const std::string& key,
        const std::string& default_value) {
    TODO();
}

// Group words by their length.
// Return an unordered_map where each key is a word length and each
// value is a vector of words with that length.
// Use try_emplace to create the vector for a new length, then push_back
// the word into it.
inline std::unordered_map<std::size_t, std::vector<std::string>> group_by_length(
        const std::vector<std::string>& words) {
    TODO();
}
