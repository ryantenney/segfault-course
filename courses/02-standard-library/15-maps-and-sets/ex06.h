// Exercise 06: Custom Comparator
//
// std::map orders its keys using operator< by default. You can override
// this by providing a custom comparator as the third template parameter.
//
// A comparator is a type with:
//   bool operator()(const Key& a, const Key& b) const
// that defines a strict weak ordering (like <, not <=).
//
// A case-insensitive comparator compares the lowercase versions of strings
// so that "Hello" and "hello" are considered the same key.
//
// TODO:
//   1. Implement the CaseInsensitiveLess comparator.
//   2. Implement build_case_insensitive_map and lookup_case_insensitive.

#pragma once

#include <testkit/testkit.h>
#include <map>
#include <string>
#include <vector>
#include <utility>
#include <cctype>
#include <algorithm>

// A comparator that orders strings case-insensitively.
// "apple" < "Banana" should be true (a < b regardless of case).
// "Hello" and "hello" should be equivalent (neither is less than the other).
//
// Hint: convert both strings to lowercase and then compare with <.
// Use std::tolower(static_cast<unsigned char>(ch)) for each character.
struct CaseInsensitiveLess {
    bool operator()(const std::string& a, const std::string& b) const {
        TODO();
    }
};

// Type alias for convenience.
using CIMap = std::map<std::string, int, CaseInsensitiveLess>;

// Build a case-insensitive map from a vector of (string, int) pairs.
// If the same key appears multiple times (case-insensitively), the last
// value wins. Use insert_or_assign.
inline CIMap build_case_insensitive_map(
        const std::vector<std::pair<std::string, int>>& entries) {
    TODO();
}

// Look up a value in the case-insensitive map.
// Return the value if found, or -1 if not found.
inline int lookup_case_insensitive(const CIMap& m, const std::string& key) {
    TODO();
}
