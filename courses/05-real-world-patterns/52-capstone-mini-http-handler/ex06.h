// Exercise 06: Response Serialization
//
// Serialize a Response struct into a raw HTTP-like string. The format:
//   "HTTP/1.1 <status> <reason>\r\nHeader: value\r\n...\r\n\r\nbody"
//
// Status reasons:
//   200 -> "OK", 201 -> "Created", 400 -> "Bad Request",
//   404 -> "Not Found", 500 -> "Internal Server Error"
//   Other -> "Unknown"
//
// TODO:
//   1. Implement reason_phrase() — return the reason string for a status.
//   2. Implement serialize_response() — produce the raw string.

#pragma once

#include <testkit/testkit.h>
#include <map>
#include <sstream>
#include <string>

struct Response {
    int status = 200;
    std::map<std::string, std::string> headers;
    std::string body;
};

// Return the reason phrase for the given HTTP status code.
inline std::string reason_phrase(int status) {
    TODO();
}

// Serialize a Response to a raw HTTP-like string.
inline std::string serialize_response(const Response& resp) {
    TODO();
}
