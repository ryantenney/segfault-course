// Exercise 03: Erase While Iterating
//
// A common bug is erasing elements from a container while iterating with
// a for loop. In most containers, erasing invalidates the current iterator.
// The correct pattern uses the return value of erase(), which gives you
// a valid iterator to the next element:
//
//   for (auto it = m.begin(); it != m.end(); /* no increment here */) {
//       if (should_remove(*it)) {
//           it = m.erase(it);   // erase returns iterator to next element
//       } else {
//           ++it;               // only advance if we didn't erase
//       }
//   }
//
// TODO:
//   1. Implement remove_negative_values() — erase all entries from a
//      std::map<std::string, int> whose value is negative.
//   2. Implement remove_long_keys() — erase all entries from a
//      std::map<std::string, int> whose key length exceeds `max_len`.
//   3. Implement remove_if_map() — erase entries from a map where
//      the predicate returns true. This is a generic version.

#pragma once

#include <functional>
#include <map>
#include <string>
#include <testkit/testkit.h>

// Remove all entries whose value is negative.
// Return the number of entries removed.
inline int remove_negative_values(std::map<std::string, int>& m) {
    TODO();
}

// Remove all entries whose key is longer than max_len characters.
// Return the number of entries removed.
inline int remove_long_keys(std::map<std::string, int>& m, std::size_t max_len) {
    TODO();
}

// Remove all entries for which predicate(key, value) returns true.
// Return the number of entries removed.
inline int remove_if_map(std::map<std::string, int>& m,
                         std::function<bool(const std::string&, int)> predicate) {
    TODO();
}
