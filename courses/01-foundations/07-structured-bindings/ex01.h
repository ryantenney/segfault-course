// Exercise 01: Decompose a pair
//
// PROBLEM:
//   std::map::insert returns a std::pair<iterator, bool>. Traditionally
//   you'd access `result.first` and `result.second`, which is cryptic.
//   Structured bindings let you name both parts directly:
//
//     auto [iter, inserted] = map.insert({key, value});
//
//   This is cleaner and self-documenting.
//
// TODO:
//   Implement each function using structured bindings to unpack pairs.

#pragma once

#include <testkit/testkit.h>
#include <map>
#include <string>

// Insert `key`/`value` into the map. Return true if the insertion
// happened (key was new), false if the key already existed.
// Use a structured binding to unpack the result of map.insert().
inline bool try_insert(std::map<std::string, int>& m,
                       const std::string& key, int value) {
    TODO();
    // Hint: auto [iter, inserted] = m.insert({key, value});
    //       return inserted;
}

// Insert `key`/`value` into the map. If inserted, return the value.
// If the key already existed, return the existing value.
// Use a structured binding to unpack the result of map.insert().
inline int insert_or_get(std::map<std::string, int>& m,
                         const std::string& key, int value) {
    TODO();
    // Hint: auto [iter, inserted] = m.insert({key, value});
    //       return iter->second;
}

// Return a pair {min, max} from two integers.
// Use a structured binding at the call site to verify it works.
inline std::pair<int, int> min_max(int a, int b) {
    TODO();
    // Hint: return {std::min(a, b), std::max(a, b)};
}
