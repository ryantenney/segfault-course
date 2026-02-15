// Exercise 01: Basic Logger
//
// A logger filters messages by severity level. Messages below the
// configured level are silently discarded. This is the foundation
// of every logging system.
//
// TODO:
//   1. Implement set_level(level) -- set the minimum log level.
//   2. Implement log(level, message) -- if level >= current level,
//      append the formatted message to the output vector.
//      Format: "[LEVEL] message"
//   3. Implement messages() -- return the vector of logged messages.
//
// Levels (lowest to highest): Debug, Info, Warn, Error

#pragma once

#include <testkit/testkit.h>
#include <string>
#include <vector>

enum class LogLevel {
    Debug = 0,
    Info = 1,
    Warn = 2,
    Error = 3
};

inline std::string level_to_string(LogLevel level) {
    switch (level) {
        case LogLevel::Debug: return "DEBUG";
        case LogLevel::Info:  return "INFO";
        case LogLevel::Warn:  return "WARN";
        case LogLevel::Error: return "ERROR";
    }
    return "UNKNOWN";
}

class BasicLogger {
    LogLevel current_level_ = LogLevel::Debug;
    std::vector<std::string> messages_;

public:
    // Set the minimum log level.
    void set_level(LogLevel level) {
        TODO();
    }

    // Log a message if its level >= the current level.
    // Format: "[LEVEL] message"
    void log(LogLevel level, const std::string& message) {
        TODO();
    }

    // Return all logged messages.
    const std::vector<std::string>& messages() const {
        TODO();
    }
};
