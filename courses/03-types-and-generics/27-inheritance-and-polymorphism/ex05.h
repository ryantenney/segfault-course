// Exercise 05: Override Keyword
//
// The `override` keyword tells the compiler: "I intend this method to
// override a virtual method in the base class." If the signature doesn't
// match any base class virtual method, the compiler reports an error
// instead of silently creating a new, unrelated method.
//
// Common mistakes that `override` catches:
//   - Misspelling the method name
//   - Wrong parameter types
//   - Missing const qualifier
//   - Base method is not virtual
//
// In this exercise, the Printer base class has a virtual method
// print(const std::string&). The BrokenPrinter class tries to override
// it but has a signature mismatch. Fix it.
//
// TODO:
//   1. Fix the signature of BrokenPrinter::print() so it matches the
//      base class virtual method. Add `override` to catch future mistakes.
//   2. Implement LoudPrinter::print() — return the message in uppercase.
//      Add `override` to mark it as an override.
//   3. Implement to_upper() helper — convert a string to uppercase.

#pragma once

#include <cctype>
#include <memory>
#include <string>
#include <testkit/testkit.h>

class Printer {
public:
    virtual ~Printer() = default;

    // Format a message for printing. The base version returns it unchanged.
    virtual std::string print(const std::string& message) const {
        return message;
    }
};

// This class intends to override print(), but the signature is wrong.
// The parameter type is std::string (by value) instead of const std::string&.
// Without `override`, the compiler does not complain — it just creates a
// new method that hides the base version.
//
// TODO: Fix the parameter type to match the base class, and add `override`.
class BrokenPrinter : public Printer {
public:
    // BUG: parameter should be `const std::string& message`
    // Also add `override` at the end.
    std::string print(std::string message) const {
        TODO();
    }
};

// Convert a string to uppercase.
inline std::string to_upper(const std::string& s) {
    TODO();
}

// A printer that converts the message to uppercase.
class LoudPrinter : public Printer {
public:
    // Return the message converted to uppercase.
    // TODO: implement this and add `override`.
    std::string print(const std::string& message) const {
        TODO();
    }
};

// Create a LoudPrinter and return it as a unique_ptr<Printer>.
inline std::unique_ptr<Printer> make_loud_printer() {
    TODO();
}
