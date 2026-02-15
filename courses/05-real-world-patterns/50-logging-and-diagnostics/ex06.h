// Exercise 06: Zero-cost Disabled Logs
//
// In performance-critical code, you want disabled log levels to produce
// zero overhead — not even a function call. C++17 `if constexpr` with
// template parameters makes this possible: the compiler eliminates the
// dead branch entirely.
//
// TODO:
//   1. Implement ZeroCostLogger::log<Level>() so that if the Level
//      template parameter is below MinLevel, the message is discarded
//      at compile time (using if constexpr).
//   2. Implement entries() to return the stored messages.
//
// CRITICAL: Do NOT put TODO() inside the if-constexpr disabled branch.
//           The branch that is "disabled" must be empty at compile time.

#pragma once

#include <testkit/testkit.h>
#include <string>
#include <vector>

enum class ZLevel {
    Debug = 0,
    Info = 1,
    Warn = 2,
    Error = 3
};

inline std::string zlevel_str(ZLevel l) {
    switch (l) {
        case ZLevel::Debug: return "DEBUG";
        case ZLevel::Info:  return "INFO";
        case ZLevel::Warn:  return "WARN";
        case ZLevel::Error: return "ERROR";
    }
    return "UNKNOWN";
}

template <ZLevel MinLevel>
class ZeroCostLogger {
    std::vector<std::string> entries_;

public:
    // Log a message if Level >= MinLevel, otherwise discard at compile time.
    // Format: "[LEVEL] message"
    template <ZLevel Level>
    void log(const std::string& message) {
        TODO();
    }

    const std::vector<std::string>& entries() const {
        TODO();
    }
};
