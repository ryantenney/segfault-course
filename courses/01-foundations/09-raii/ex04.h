// Exercise 04: Prove Cleanup Order
//
// PROBLEM:
//   When multiple RAII objects exist in the same scope, they are
//   destroyed in the reverse order of their construction. This is
//   guaranteed by the C++ standard and is critical for correctness
//   when resources have dependencies.
//
// TODO:
//   Implement the Logger class and fill in the expected output string
//   in the predicted_output() function.
//
// WHY:
//   Understanding destruction order is essential for reasoning about
//   RAII correctness. If resource B depends on resource A, A must be
//   constructed first (and destroyed last).

#pragma once
#include <string>
#include <testkit/testkit.h>

class Logger {
    std::string name_;
    std::string& log_;
public:
    // Append "ctor:<name> " to the log.
    Logger(const std::string& name, std::string& log) : name_(name), log_(log) {
        TODO();
    }

    // Append "dtor:<name> " to the log.
    ~Logger() {
        // TODO: append "dtor:<name_> " to log_
    }
};

// This function creates three Logger objects in a specific order.
// Return the log string after they are all destroyed.
inline std::string observe_destruction_order() {
    std::string log;
    {
        Logger a("A", log);
        Logger b("B", log);
        Logger c("C", log);
        // All three exist here. What order are they destroyed in?
    }
    return log;
}

// Return the expected output of observe_destruction_order().
// Fill in the string with the correct construction/destruction sequence.
inline std::string predicted_output() {
    TODO();
    // HINT: Construction order is A, B, C.
    //       Destruction order is C, B, A (reverse).
    //       Format: "ctor:A ctor:B ctor:C dtor:C dtor:B dtor:A "
}

// This function creates nested scopes with Logger objects.
// Return the log string showing interleaved construction/destruction.
inline std::string observe_nested_scopes() {
    std::string log;
    {
        Logger outer("outer", log);
        {
            Logger inner("inner", log);
        }
        // inner is destroyed here, but outer is still alive
        Logger late("late", log);
    }
    return log;
}

// Return the expected output of observe_nested_scopes().
inline std::string predicted_nested_output() {
    TODO();
    // HINT: "ctor:outer ctor:inner dtor:inner ctor:late dtor:late dtor:outer "
}
