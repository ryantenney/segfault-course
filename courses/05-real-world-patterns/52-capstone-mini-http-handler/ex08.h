// Exercise 08: JSON-like Body Parsing
//
// Parse a simple key-value body format into a map. The format uses
// one key=value pair per line (newline-separated). This is a
// simplified stand-in for real JSON parsing.
//
// Format: "key1=value1\nkey2=value2\n..."
//
// The handler uses parsed body data to produce responses.
//
// TODO:
//   1. Implement parse_body() — split by '\n', then by '='.
//      Skip malformed lines (no '=' sign). Trim nothing.
//   2. Implement handle_create_user() — extract "name" and "email"
//      from parsed body. Return 400 if either is missing.
//      Return 201 with body "created <name> <email>" on success.

#pragma once

#include <testkit/testkit.h>
#include <map>
#include <string>

struct Request {
    std::string method;
    std::string path;
    std::string body;
};

struct Response {
    int status = 200;
    std::string body;
};

// Parse "key1=value1\nkey2=value2" into a map.
// Skip lines without '='.
inline std::map<std::string, std::string> parse_body(const std::string& body) {
    TODO();
}

// Handle user creation.
// Expects "name" and "email" in the parsed body.
// Returns 201 "created <name> <email>" on success.
// Returns 400 "missing field: <field>" if name or email is absent.
inline Response handle_create_user(const Request& req) {
    TODO();
}
