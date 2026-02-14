// Exercise 05: Moved-From State
//
// After std::move, the source object is in a "valid but unspecified" state.
// This means:
//   - You CAN call operations that don't depend on the object's value
//     (e.g., size(), empty(), clear(), assignment, destruction)
//   - You SHOULD NOT assume the value is unchanged or empty
//   - The standard library guarantees moved-from containers are valid
//
// For std::string, the moved-from string is typically empty (but not
// guaranteed by the standard -- only by common implementations).
//
// TODO:
//   Implement the functions below that demonstrate moved-from state behavior.

#pragma once

#include <string>
#include <vector>
#include <testkit/testkit.h>

// Move `source` into a local string, then return whether `source` is now empty.
// This demonstrates the typical moved-from state of std::string.
inline bool move_and_check_empty(std::string& source) {
    TODO();
}

// Move `source` into a local, then assign a new value to `source`.
// Return the new value. This demonstrates that moved-from objects
// can be reused by assigning to them.
inline std::string move_and_reassign(std::string& source, const std::string& new_value) {
    TODO();
}

// Move all elements out of `source` into a new vector, then call clear()
// on `source`. Return the new vector.
// This demonstrates that moved-from containers support clear().
inline std::vector<std::string> drain_vector(std::vector<std::string>& source) {
    TODO();
}

// Move a string, then call size() on the moved-from string.
// Return the size. This demonstrates that size() is safe to call
// on a moved-from string.
inline std::size_t move_and_get_size(std::string& source) {
    TODO();
}
