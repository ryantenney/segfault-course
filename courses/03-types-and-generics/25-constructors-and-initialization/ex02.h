// Exercise 02: In-Class Member Initializers (NSDMIs)
//
// PROBLEM:
//   C++11 allows you to provide default values for members directly
//   in the class definition. These are called Non-Static Data Member
//   Initializers (NSDMIs). They apply when a constructor doesn't
//   explicitly initialize that member.
//
// TODO:
//   1. Add in-class default values to the Config members:
//      - max_retries = 3
//      - timeout_ms = 5000
//      - verbose = false
//      - endpoint = "http://localhost:8080"
//   2. Implement the default constructor (should have an empty body —
//      all defaults come from the NSDMIs).
//   3. Implement the parameterized constructor that overrides specific
//      values via the initializer list.
//   4. Implement the getter methods.
//
// WHY:
//   NSDMIs reduce duplication across multiple constructors. Instead of
//   repeating the same defaults in every constructor, you state the
//   defaults once in the class definition. A constructor only needs to
//   list the members it wants to override.

#pragma once

#include <testkit/testkit.h>
#include <string>

class Config {
private:
    // TODO: Add in-class default values (NSDMIs) to these members.
    int max_retries;
    int timeout_ms;
    bool verbose;
    std::string endpoint;

public:
    // Default constructor: all members use their in-class defaults.
    // The body should be empty — the NSDMIs do the work.
    Config() {
        TODO();
    }

    // Constructor that overrides specific values.
    // max_retries and timeout_ms are provided; verbose and endpoint
    // keep their in-class defaults.
    Config(int retries, int timeout) {
        TODO();
    }

    // Full constructor: overrides all values.
    Config(int retries, int timeout, bool verb, std::string ep) {
        TODO();
    }

    int get_max_retries() const {
        TODO();
    }

    int get_timeout_ms() const {
        TODO();
    }

    bool get_verbose() const {
        TODO();
    }

    std::string get_endpoint() const {
        TODO();
    }
};
