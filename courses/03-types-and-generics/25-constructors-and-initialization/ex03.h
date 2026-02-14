// Exercise 03: Delegating Constructors
//
// PROBLEM:
//   The LogEntry class has several constructors with duplicated
//   initialization logic. C++11 allows one constructor to delegate
//   to another, eliminating the duplication.
//
// TODO:
//   1. Implement the "primary" constructor that takes all four parameters.
//   2. Implement the three convenience constructors by delegating to
//      the primary constructor using the member initializer list syntax:
//        LogEntry(...) : LogEntry(all, four, params, here) {}
//   3. Implement the getter methods.
//
// WHY:
//   Before C++11, constructors couldn't call each other. Common init
//   logic had to be duplicated or factored into a private init() method
//   (which can't initialize const members or references). Delegating
//   constructors solve this cleanly.

#pragma once

#include <testkit/testkit.h>
#include <string>

class LogEntry {
private:
    std::string message_;
    std::string level_;
    std::string source_;
    int timestamp_;

public:
    // Primary constructor: takes all four parameters.
    LogEntry(std::string message, std::string level,
             std::string source, int timestamp) {
        TODO();
    }

    // Convenience: message + level, source defaults to "app", timestamp to 0.
    // Delegate to the primary constructor.
    LogEntry(std::string message, std::string level) {
        TODO();
    }

    // Convenience: message only, level defaults to "INFO",
    // source to "app", timestamp to 0.
    // Delegate to the primary constructor.
    LogEntry(std::string message) {
        TODO();
    }

    // Convenience: default constructor, all defaults.
    // message = "", level = "DEBUG", source = "app", timestamp = 0.
    // Delegate to the primary constructor.
    LogEntry() {
        TODO();
    }

    std::string message() const {
        TODO();
    }

    std::string level() const {
        TODO();
    }

    std::string source() const {
        TODO();
    }

    int timestamp() const {
        TODO();
    }
};
