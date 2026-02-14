// Exercise 06: Final Keyword
//
// The `final` keyword prevents further overriding or inheritance:
//
//   - On a virtual method: no derived class can override it further.
//   - On a class: no class can inherit from it.
//
// `final` is useful for:
//   - Preventing accidental overrides in deep hierarchies
//   - Allowing the compiler to devirtualize calls (performance)
//   - Expressing design intent: "this is the last word"
//
// TODO:
//   1. Implement Logger::log() — return "LOG: " + message.
//   2. Implement TimestampLogger::log() — return "[TS] LOG: " + message.
//      Mark it `final` so no further derived class can override it.
//   3. Implement exercise_ready() gate function.
//
// NOTE: The tests verify that Logger and TimestampLogger work correctly.
// The `final` constraint is a compile-time guarantee — the test
// verifies behavior, and the comment documents the design intent.

#pragma once

#include <memory>
#include <string>
#include <testkit/testkit.h>

class Logger {
public:
    virtual ~Logger() = default;

    // Return "LOG: " + message.
    virtual std::string log(const std::string& message) const {
        TODO();
    }
};

// TimestampLogger overrides log() and marks it final.
// No class derived from TimestampLogger can override log().
class TimestampLogger : public Logger {
public:
    // Return "[TS] LOG: " + message.
    // TODO: Add `final` after `override` to prevent further overrides.
    std::string log(const std::string& message) const override {
        TODO();
    }
};

// Create a Logger and return it as a unique_ptr<Logger>.
inline std::unique_ptr<Logger> make_logger() {
    TODO();
}

// Create a TimestampLogger and return it as a unique_ptr<Logger>.
inline std::unique_ptr<Logger> make_timestamp_logger() {
    TODO();
}

// Gate function: implement this to signal that the exercise is ready.
inline bool exercise_ready() {
    TODO();
}
