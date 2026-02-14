// Exercise 07: Return Value Optimization (RVO)
//
// The compiler can eliminate copy/move operations when returning objects
// from functions. This is called Return Value Optimization (RVO) or
// Named Return Value Optimization (NRVO).
//
// RVO applies when:
//   - Returning a prvalue (e.g., return Type{args})     -- guaranteed in C++17
//   - Returning a named local variable (NRVO)           -- permitted, not guaranteed
//
// RVO does NOT apply when:
//   - Returning a parameter (it's not a local variable)
//   - Returning via std::move on a local (inhibits NRVO!)
//   - Returning one of several possible locals (conditional NRVO is unreliable)
//
// TODO:
//   Implement the functions below. Use the Tracker class to observe which
//   operations actually occur.

#pragma once

#include <string>
#include <testkit/testkit.h>

struct Tracker {
    std::string label;
    static inline int copies = 0;
    static inline int moves = 0;

    explicit Tracker(std::string l) : label(std::move(l)) {}

    Tracker(const Tracker& other) : label(other.label) { ++copies; }
    Tracker(Tracker&& other) noexcept : label(std::move(other.label)) { ++moves; }

    Tracker& operator=(const Tracker& other) { label = other.label; ++copies; return *this; }
    Tracker& operator=(Tracker&& other) noexcept { label = std::move(other.label); ++moves; return *this; }

    static void reset() { copies = 0; moves = 0; }
};

// Case 1: Return a prvalue. This should trigger guaranteed RVO (C++17).
// No copies or moves.
inline Tracker make_tracker(const std::string& label) {
    TODO();
}

// Case 2: Return a named local. This should trigger NRVO.
// Compilers typically elide the copy/move here too.
inline Tracker make_named_tracker(const std::string& label) {
    TODO();
}

// Case 3: Return a function parameter. NRVO does NOT apply to parameters.
// This will trigger a move (not a copy, since the compiler knows the
// parameter is about to be destroyed).
inline Tracker passthrough_tracker(Tracker t) {
    TODO();
}

// Case 4: BAD -- return std::move(local). This INHIBITS NRVO because
// std::move returns an rvalue reference, not a local variable.
// The compiler will move instead of eliding.
// Implement this by creating a local Tracker and returning std::move of it.
inline Tracker move_tracker_bad(const std::string& label) {
    TODO();
}
