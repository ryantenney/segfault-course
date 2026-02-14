// Exercise 01: Move a String into a Container
//
// When you insert a local variable into a container and you know you won't
// need the local anymore, std::move avoids an unnecessary copy.
//
// Without move:  vector.push_back(str)    -- copies str into the vector
// With move:     vector.push_back(std::move(str)) -- steals str's buffer
//
// TODO:
//   Implement the functions below. Use std::move where indicated to avoid
//   copies. The "log" string records what happened so the tests can verify
//   whether a copy or move occurred.

#pragma once

#include <string>
#include <vector>
#include <testkit/testkit.h>

// A simple wrapper that logs when it's copied vs moved.
struct TrackedString {
    std::string value;
    static inline std::string log;

    explicit TrackedString(std::string v) : value(std::move(v)) {
        log += "ctor;";
    }

    TrackedString(const TrackedString& other) : value(other.value) {
        log += "copy;";
    }

    TrackedString(TrackedString&& other) noexcept : value(std::move(other.value)) {
        log += "move;";
    }

    TrackedString& operator=(const TrackedString& other) {
        value = other.value;
        log += "copy-assign;";
        return *this;
    }

    TrackedString& operator=(TrackedString&& other) noexcept {
        value = std::move(other.value);
        log += "move-assign;";
        return *this;
    }
};

// Add the string `text` to `vec` by COPYING (do not use std::move).
inline void add_by_copy(std::vector<TrackedString>& vec, TrackedString item) {
    TODO();
}

// Add the string `text` to `vec` by MOVING. Use std::move on item.
inline void add_by_move(std::vector<TrackedString>& vec, TrackedString item) {
    TODO();
}

// Build a vector of TrackedStrings from raw strings, using move for each.
inline std::vector<TrackedString> build_collection(const std::vector<std::string>& inputs) {
    TODO();
}
