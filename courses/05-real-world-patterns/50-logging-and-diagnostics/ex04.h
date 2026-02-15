// Exercise 04: Structured Log Entry
//
// A structured log entry carries metadata alongside the message:
// timestamp, level, message text, and a map of extra fields.
// This makes logs machine-parseable and easy to filter.
//
// TODO:
//   1. Implement make_entry() to construct a LogEntry with the given
//      level, message, and fields. The timestamp should be set to
//      the current time using std::chrono::system_clock::now().
//   2. Implement format_entry() to produce a human-readable string.
//      Format: "YYYY-MM-DDTHH:MM:SS [LEVEL] message | key=val ..."
//      (If no fields, omit the " | ..." part.)
//
// HINT: Use std::time_t + std::localtime + std::strftime for formatting.

#pragma once

#include <testkit/testkit.h>
#include <chrono>
#include <ctime>
#include <map>
#include <sstream>
#include <string>

enum class EntryLevel {
    Debug = 0,
    Info = 1,
    Warn = 2,
    Error = 3
};

inline std::string entry_level_str(EntryLevel l) {
    switch (l) {
        case EntryLevel::Debug: return "DEBUG";
        case EntryLevel::Info:  return "INFO";
        case EntryLevel::Warn:  return "WARN";
        case EntryLevel::Error: return "ERROR";
    }
    return "UNKNOWN";
}

struct LogEntry {
    std::chrono::system_clock::time_point timestamp;
    EntryLevel level;
    std::string message;
    std::map<std::string, std::string> fields;
};

// Create a LogEntry with the current timestamp.
inline LogEntry make_entry(EntryLevel level,
                           const std::string& message,
                           const std::map<std::string, std::string>& fields = {}) {
    TODO();
}

// Format a LogEntry into a human-readable string.
// Format: "YYYY-MM-DDTHH:MM:SS [LEVEL] message"
//   or:   "YYYY-MM-DDTHH:MM:SS [LEVEL] message | key=val key2=val2"
inline std::string format_entry(const LogEntry& entry) {
    TODO();
}
