// Exercise 05: Request Parsing
//
// Parse a raw HTTP-like string into a Request struct. The format is:
//   "METHOD /path HTTP/1.1\r\nHeader: value\r\n...\r\n\r\nbody"
//
// Parsing rules:
//   - First line: method, path, and version separated by spaces.
//   - Header lines follow, each "Key: Value\r\n".
//   - A blank line ("\r\n\r\n") separates headers from body.
//   - Everything after the blank line is the body.
//
// TODO:
//   1. Implement parse_request() — parse raw string into Request.
//      Return an empty Request with status_line="" on parse failure.

#pragma once

#include <testkit/testkit.h>
#include <map>
#include <string>

struct Request {
    std::string method;
    std::string path;
    std::string version;
    std::map<std::string, std::string> headers;
    std::string body;
};

// Parse a raw HTTP-like string into a Request.
// On failure (e.g., missing request line), return a Request with
// method set to empty string.
inline Request parse_request(const std::string& raw) {
    TODO();
}
