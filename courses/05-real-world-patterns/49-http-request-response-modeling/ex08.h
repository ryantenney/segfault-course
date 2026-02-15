// Exercise 08: Query String Parsing
//
// URLs often carry a query string: "?key=val&k2=v2". Parsing it means
// splitting on '&', then splitting each part on '='.
//
// Edge cases to handle:
//   - URL-encoded values: '+' means space, %XX means hex byte.
//   - Keys with no '=' get an empty-string value.
//   - Keys with '=' but no value: "key=" -> value is "".
//   - Leading '?' should be stripped if present.
//
// TODO:
//   1. Implement url_decode(str) to decode %XX sequences and '+'.
//   2. Implement parse_query(str) to split into key-value pairs.

#pragma once

#include <testkit/testkit.h>
#include <map>
#include <string>

// Decode a URL-encoded string.
// '+' becomes ' '. "%XX" becomes the byte with hex value XX.
inline std::string url_decode(const std::string& str) {
    TODO();
}

// Parse a query string into key-value pairs.
// If the string starts with '?', strip it first.
// Split on '&'. For each part, split on the first '=' only.
// Keys without '=' get value "".
// Both keys and values should be URL-decoded.
inline std::map<std::string, std::string> parse_query(const std::string& query) {
    TODO();
}
