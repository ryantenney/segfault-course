// Exercise 02: Formatted Output
//
// Real log messages often include structured key-value context:
//   "[INFO] request completed | status=200 duration=15ms"
//
// This exercise builds a LogMessage that collects fields and formats
// them into a single string using std::ostringstream.
//
// TODO:
//   1. Implement field(key, value) -- add a key-value pair, return *this.
//   2. Implement str() -- return the formatted string.
//      Format: "[LEVEL] message | key1=val1 key2=val2"
//      If no fields, just "[LEVEL] message" (no trailing " | ").

#pragma once

#include <testkit/testkit.h>
#include <sstream>
#include <string>
#include <vector>
#include <utility>

enum class Level {
    Debug = 0,
    Info = 1,
    Warn = 2,
    Error = 3
};

inline std::string level_str(Level l) {
    switch (l) {
        case Level::Debug: return "DEBUG";
        case Level::Info:  return "INFO";
        case Level::Warn:  return "WARN";
        case Level::Error: return "ERROR";
    }
    return "UNKNOWN";
}

class LogMessage {
    Level level_;
    std::string message_;
    std::vector<std::pair<std::string, std::string>> fields_;

public:
    LogMessage(Level level, const std::string& message)
        : level_(level), message_(message) {}

    // Add a key-value field. Returns *this for chaining.
    LogMessage& field(const std::string& key, const std::string& value) {
        TODO();
    }

    // Format the complete log string.
    // "[LEVEL] message" if no fields.
    // "[LEVEL] message | key1=val1 key2=val2" if fields present.
    std::string str() const {
        TODO();
    }
};
