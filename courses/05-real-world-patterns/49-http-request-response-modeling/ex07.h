// Exercise 07: Content-Type Parsing
//
// The Content-Type header looks like: "text/html; charset=utf-8"
// It has a type ("text"), a subtype ("html"), and optional parameters
// (key=value pairs separated by semicolons).
//
// TODO:
//   1. Implement parse_content_type(str) to split the string into its
//      components. Store type, subtype, and a map of parameters.
//   2. Implement media_type() to return "type/subtype".

#pragma once

#include <testkit/testkit.h>
#include <map>
#include <string>

struct ContentType {
    std::string type;       // e.g., "text"
    std::string subtype;    // e.g., "html"
    std::map<std::string, std::string> params;  // e.g., {"charset": "utf-8"}

    // Return "type/subtype".
    std::string media_type() const {
        TODO();
    }
};

// Parse a Content-Type string into its components.
//
// Examples:
//   "text/html"                       -> type="text", subtype="html", params={}
//   "text/html; charset=utf-8"        -> type="text", subtype="html", params={charset: utf-8}
//   "application/json"                -> type="application", subtype="json"
//   "multipart/form-data; boundary=X" -> params={boundary: X}
//
// Whitespace around semicolons and around '=' should be trimmed.
inline ContentType parse_content_type(const std::string& str) {
    TODO();
}
