// Exercise 02: Iterate a map
//
// PROBLEM:
//   When iterating a std::map, each element is a std::pair<const Key, Value>.
//   Without structured bindings:
//
//     for (const auto& entry : m) {
//         std::cout << entry.first << ": " << entry.second;
//     }
//
//   With structured bindings:
//
//     for (const auto& [key, value] : m) {
//         std::cout << key << ": " << value;
//     }
//
//   Much clearer.
//
// TODO:
//   Use structured bindings in range-for loops over maps.

#pragma once

#include <testkit/testkit.h>
#include <map>
#include <string>
#include <vector>

// Return a vector of all keys in the map (in sorted order, which
// std::map guarantees).
inline std::vector<std::string> get_keys(const std::map<std::string, int>& m) {
    TODO();
    // Hint: for (const auto& [key, value] : m) { keys.push_back(key); }
}

// Return the sum of all values in the map.
inline int sum_values(const std::map<std::string, int>& m) {
    TODO();
}

// Return the key associated with the largest value.
// If the map is empty, return "".
inline std::string key_of_max(const std::map<std::string, int>& m) {
    TODO();
}

// Build a single string in the format "key1=val1,key2=val2,..."
// Keys are already sorted by std::map. No trailing comma.
inline std::string format_map(const std::map<std::string, int>& m) {
    TODO();
}
