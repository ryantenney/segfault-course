// Exercise 02: Custom Exception Class
//
// You can define your own exception types by inheriting from std::runtime_error
// (or std::exception). Custom exceptions let catch blocks distinguish between
// different error categories.
//
// A custom exception should:
//   - Inherit from std::runtime_error (or another standard exception)
//   - Pass the error message to the base class constructor
//   - Optionally carry extra data (error codes, context, etc.)
//
// Below is a ParseError class that inherits from std::runtime_error and
// stores a line number. Study how it's built:
//   - The constructor forwards the message to the base class
//   - An extra data member (line_) carries context about the error
//   - An accessor (line()) exposes the extra data
//
// TODO:
//   Implement parse_config_line() — parse a "key=value" string.
//   Throw ParseError if the line doesn't contain '='.

#pragma once

#include <stdexcept>
#include <string>
#include <testkit/testkit.h>

// A custom exception that carries a line number for error context.
class ParseError : public std::runtime_error {
    int line_;

public:
    ParseError(const std::string& message, int line_number)
        : std::runtime_error(message), line_(line_number) {}

    int line() const { return line_; }
};

// A simple key-value pair.
struct KeyValue {
    std::string key;
    std::string value;
};

// Parse a "key=value" string. Return a KeyValue with the parts.
// If the line doesn't contain '=', throw ParseError with message
// "missing '=' in config line" and the given line_number.
// The key is everything before the first '=', value is everything after.
inline KeyValue parse_config_line(const std::string& line, int line_number) {
    TODO();
}
