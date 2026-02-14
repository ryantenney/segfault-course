// Exercise 01: Parse Key-Value Pairs
//
// Strings often carry structured data. A common pattern is "key=value"
// where you need to split on the delimiter to extract both parts.
//
// std::string provides two essential tools for this:
//   - find(char) returns the index of the first occurrence, or std::string::npos
//   - substr(pos, len) returns a new string starting at pos, of length len
//
// Example:
//   std::string s = "name=Alice";
//   auto pos = s.find('=');          // pos == 4
//   auto key = s.substr(0, pos);     // "name"
//   auto val = s.substr(pos + 1);    // "Alice"
//
// TODO:
//   1. Implement parse_key() -- return the part before '=' in a "key=value" string.
//      If there is no '=', return the entire string.
//   2. Implement parse_value() -- return the part after '=' in a "key=value" string.
//      If there is no '=', return an empty string.
//   3. Implement parse_pair() -- return both key and value as a std::pair<string, string>.

#pragma once

#include <string>
#include <utility>
#include <testkit/testkit.h>

// Return the key (part before '=') from a "key=value" string.
// If no '=' is found, return the entire string.
inline std::string parse_key(const std::string& kv) {
    TODO();
}

// Return the value (part after '=') from a "key=value" string.
// If no '=' is found, return an empty string.
inline std::string parse_value(const std::string& kv) {
    TODO();
}

// Return both the key and value as a pair.
// If no '=' is found, the key is the entire string and the value is empty.
inline std::pair<std::string, std::string> parse_pair(const std::string& kv) {
    TODO();
}
