// Exercise 07: RAII Survives Exceptions
//
// PROBLEM:
//   One of RAII's most important properties: destructors run during
//   stack unwinding when an exception propagates. This means RAII
//   objects clean up even on error paths — no finally blocks needed.
//
// TODO:
//   Implement the Tracker class and the functions that demonstrate
//   RAII cleanup during exception propagation.
//
// WHY:
//   In languages without destructors (Java, Python), you need
//   try/finally or "with" statements for cleanup. In C++, RAII
//   handles it automatically. This is why C++ doesn't have finally.

#pragma once
#include <stdexcept>
#include <string>
#include <testkit/testkit.h>

class Tracker {
    std::string name_;
    std::string& log_;
public:
    Tracker(const std::string& name, std::string& log)
        : name_(name), log_(log) {
        TODO();
        // HINT: append "acquire:<name> " to log
    }

    ~Tracker() {
        // TODO: append "release:<name> " to log
    }

    Tracker(const Tracker&) = delete;
    Tracker& operator=(const Tracker&) = delete;
};

// Create two trackers, throw an exception after the second.
// The exception will cause stack unwinding, running both destructors.
// Caller should catch the exception and examine the log.
inline void function_that_throws(std::string& log) {
    TODO();
    // HINT:
    //   Tracker a("resource1", log);
    //   Tracker b("resource2", log);
    //   throw std::runtime_error("something went wrong");
}

// Demonstrates that cleanup happens even when an exception propagates.
// Returns the log string showing acquire/release order.
inline std::string demonstrate_exception_safety() {
    TODO();
    // HINT:
    //   std::string log;
    //   try {
    //       function_that_throws(log);
    //   } catch (const std::runtime_error&) {
    //       log += "caught ";
    //   }
    //   return log;
}

// Return the expected output of demonstrate_exception_safety().
inline std::string predicted_exception_output() {
    TODO();
    // HINT: "acquire:resource1 acquire:resource2 release:resource2 release:resource1 caught "
}
