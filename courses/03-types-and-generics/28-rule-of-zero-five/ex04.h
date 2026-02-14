// Exercise 04: The = default Keyword
//
// PROBLEM:
//   Sometimes you want the compiler-generated special members, but you also
//   want to be explicit about it. The `= default` keyword says "generate the
//   default implementation for this special member."
//
//   This is useful when:
//   - You want to document that the default behavior is intentional
//   - You need to change the access level (e.g., make the copy constructor
//     protected)
//   - Adding one special member suppresses others; = default brings them back
//   - You want the compiler to generate noexcept and trivial type traits
//
// TODO:
//   1. Explicitly default all five special members (copy ctor, copy assign,
//      move ctor, move assign, destructor) using = default.
//   2. Implement the constructor and accessors.
//
// WHY:
//   Being explicit with = default communicates intent. It tells readers
//   "I considered the special members and the defaults are correct."

#pragma once

#include <string>
#include <testkit/testkit.h>

class Config {
    std::string key_;
    std::string value_;
    int priority_;

public:
    // Regular constructor.
    Config(std::string key, std::string value, int priority) {
        TODO();
    }

    // TODO: Explicitly default the destructor.
    // ~Config() = ???;

    // TODO: Explicitly default the copy constructor.
    // Config(const Config&) = ???;

    // TODO: Explicitly default the copy assignment operator.
    // Config& operator=(const Config&) = ???;

    // TODO: Explicitly default the move constructor.
    // Config(Config&&) = ???;

    // TODO: Explicitly default the move assignment operator.
    // Config& operator=(Config&&) = ???;

    const std::string& key() const { return key_; }
    const std::string& value() const { return value_; }
    int priority() const { return priority_; }
};
