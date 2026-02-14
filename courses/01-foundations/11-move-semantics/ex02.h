// Exercise 02: Move a Local into a Return Value
//
// When you build a local object inside a function and want to store it in
// a struct field, std::move avoids a copy. This is common in factory
// functions and builders.
//
// Note: For returning local variables from functions, the compiler already
// applies Return Value Optimization (RVO/NRVO). But when assigning a local
// into a *member* of a struct that you're building, you need explicit move.
//
// TODO:
//   Implement the functions below. Use std::move to transfer local strings
//   into struct fields.

#pragma once

#include <string>
#include <vector>
#include <testkit/testkit.h>

struct Config {
    std::string host;
    std::string path;
    int port;
};

// Build a Config by moving the given host and path into the struct fields.
// Hint: Initialize the struct with std::move on each string parameter.
inline Config make_config(std::string host, std::string path, int port) {
    TODO();
}

struct Message {
    std::string sender;
    std::string body;
};

// Build a Message by constructing the body locally (prefix + ": " + content)
// then moving it into the struct field.
inline Message compose_message(std::string sender, const std::string& content) {
    TODO();
}

// Build a vector of Messages from parallel vectors of senders and bodies.
// Use std::move to avoid copying the composed messages.
inline std::vector<Message> build_messages(const std::vector<std::string>& senders,
                                           const std::vector<std::string>& bodies) {
    TODO();
}
