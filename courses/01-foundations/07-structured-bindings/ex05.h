// Exercise 05: Binding with const/reference
//
// PROBLEM:
//   Like auto variables, structured bindings can be qualified:
//
//     auto [a, b] = pair;         // copies
//     auto& [a, b] = pair;        // mutable references
//     const auto& [a, b] = pair;  // const references (no copy)
//
//   Choosing the right form matters:
//   - const auto& avoids copies and prevents accidental mutation
//   - auto& lets you modify the original through the bindings
//
// TODO:
//   Implement each function, choosing the correct binding form.

#pragma once

#include <testkit/testkit.h>
#include <map>
#include <string>

// Swap the values of two entries in the map.
// If either key is missing, do nothing.
// Use auto& structured bindings via iterators, or find + modify.
inline void swap_values(std::map<std::string, int>& m,
                        const std::string& key1,
                        const std::string& key2) {
    TODO();
    // Hint: use m.find() for each key, check != m.end(),
    //       then swap iter1->second and iter2->second.
}

// Increment every value in the map by `amount`.
// Use auto& [key, value] in a range-for to modify values.
inline void increment_all(std::map<std::string, int>& m, int amount) {
    TODO();
}

// Return a string summarizing the map: "key1:val1 key2:val2 ..."
// Use const auto& [key, value] since we only read.
inline std::string summarize(const std::map<std::string, int>& m) {
    TODO();
    // Hint: build a string, separate entries with " "
}

// Return true if any value in the map exceeds `threshold`.
// Use const auto& [key, value] to avoid copies.
inline bool any_exceeds(const std::map<std::string, int>& m, int threshold) {
    TODO();
}
