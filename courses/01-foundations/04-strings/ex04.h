// Exercise 04: Build a String
//
// std::string supports concatenation with operator+ and the append() method.
// You can also use operator+= as shorthand for append.
//
// TODO:
//   Implement each function to assemble a string from parts.

#pragma once

#include <string>
#include <testkit/testkit.h>

// Build a greeting like "Hello, Alice!" from a name.
// Use operator+ or append() to concatenate the parts.
inline std::string make_greeting(const std::string& name) {
    TODO();
}

// Build a tag like "[ERROR]" or "[INFO]" from a label.
// The format is: "[" + label + "]"
inline std::string make_tag(const std::string& label) {
    TODO();
}

// Build a key=value pair like "host=localhost" from key and value strings.
inline std::string make_pair(const std::string& key, const std::string& value) {
    TODO();
}

// Build a path by joining segments with '/'.
// For example: join_path("usr", "local", "bin") → "usr/local/bin"
inline std::string join_path(const std::string& a, const std::string& b, const std::string& c) {
    TODO();
}
