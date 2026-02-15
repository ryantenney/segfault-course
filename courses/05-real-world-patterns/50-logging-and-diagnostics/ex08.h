// Exercise 08: Thread-safe Logger
//
// In a multi-threaded program, a logger must protect its internal
// data structures from concurrent access. This exercise adds mutex
// protection to a logger.
//
// TODO:
//   1. Implement ThreadSafeLogger::log(message) -- acquire the mutex,
//      then append the message to the entries vector.
//   2. Implement ThreadSafeLogger::entries() -- acquire the mutex,
//      then return a copy of the entries vector.
//
// CRITICAL: Do NOT put TODO() inside a noexcept function or destructor.
//           The lock_guard pattern is safe because lock/unlock don't throw.

#pragma once

#include <testkit/testkit.h>
#include <mutex>
#include <string>
#include <vector>

class ThreadSafeLogger {
    mutable std::mutex mutex_;
    std::vector<std::string> entries_;

public:
    // Thread-safe: append a message to the log.
    void log(const std::string& message) {
        TODO();
    }

    // Thread-safe: return a snapshot of all entries.
    std::vector<std::string> entries() const {
        TODO();
    }

    // Thread-safe: return the number of entries.
    int size() const {
        TODO();
    }
};
