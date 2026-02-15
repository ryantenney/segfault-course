// Exercise 07: Log Context/Scope
//
// In request-handling code, you often want to automatically prefix
// every log message with context like "request_id=abc". A scope-based
// approach pushes context on construction and pops it on destruction
// (RAII), so nested scopes build up a context chain.
//
// TODO:
//   1. Implement ContextLogger::push(context) -- push a context string.
//   2. Implement ContextLogger::pop() -- remove the most recent context.
//   3. Implement ContextLogger::log(message) -- format the message
//      with all active contexts prepended.
//      Format: "[ctx1] [ctx2] message"
//      If no context, just "message".
//   4. Implement LogScope so that construction pushes context and
//      destruction pops it (RAII).

#pragma once

#include <testkit/testkit.h>
#include <string>
#include <vector>

class ContextLogger {
    std::vector<std::string> contexts_;
    std::vector<std::string> messages_;

public:
    // Push a context string onto the stack.
    void push(const std::string& context) {
        TODO();
    }

    // Pop the most recent context string.
    void pop() {
        TODO();
    }

    // Log a message with all active contexts prepended.
    // Format: "[ctx1] [ctx2] message" or just "message" if no contexts.
    void log(const std::string& message) {
        TODO();
    }

    // Return all logged messages.
    const std::vector<std::string>& messages() const {
        TODO();
    }
};

// RAII scope that pushes context on construction, pops on destruction.
// NOTE: The destructor must NOT contain TODO(). It must work even
// before the student implements push/pop.
class LogScope {
    ContextLogger& logger_;

public:
    LogScope(ContextLogger& logger, const std::string& context)
        : logger_(logger) {
        TODO();
    }

    ~LogScope() {
        logger_.pop();
    }

    // Non-copyable, non-movable.
    LogScope(const LogScope&) = delete;
    LogScope& operator=(const LogScope&) = delete;
};
