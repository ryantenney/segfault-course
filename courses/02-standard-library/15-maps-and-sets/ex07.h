// Exercise 07: Multimap
//
// std::multimap allows multiple values per key. Unlike std::map where
// each key maps to exactly one value, a multimap can store several
// values under the same key.
//
// Key operations:
//   - insert({key, value}): always inserts (never overwrites)
//   - equal_range(key): returns a pair of iterators [begin, end) for
//     all entries with that key
//   - count(key): returns how many entries have that key
//
// This is ideal for one-to-many relationships like tags -> items.
//
// TODO:
//   Implement the three functions below using std::multimap.

#pragma once

#include <testkit/testkit.h>
#include <map>
#include <vector>
#include <string>
#include <set>
#include <utility>

// Build a multimap from a list of (tag, item) pairs.
// Each tag can map to multiple items.
inline std::multimap<std::string, std::string> build_tag_index(
        const std::vector<std::pair<std::string, std::string>>& entries) {
    TODO();
}

// Return a vector of all items associated with the given tag.
// The items should appear in the order they were inserted.
// If the tag doesn't exist, return an empty vector.
// Hint: use equal_range().
inline std::vector<std::string> items_for_tag(
        const std::multimap<std::string, std::string>& index,
        const std::string& tag) {
    TODO();
}

// Return a sorted, deduplicated vector of all tags in the multimap.
// Hint: iterate over the multimap and collect keys into a set.
inline std::vector<std::string> all_tags(
        const std::multimap<std::string, std::string>& index) {
    TODO();
}
