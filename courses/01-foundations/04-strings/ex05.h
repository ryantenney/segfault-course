// Exercise 05: Find and Extract
//
// std::string provides find(), rfind(), and substr() for searching and
// extracting substrings. These are essential for parsing delimited data.
//
//   find(str)  — returns the position of the first occurrence, or npos
//   rfind(str) — returns the position of the last occurrence, or npos
//   substr(pos, count) — returns a new string starting at pos
//
// TODO:
//   Implement each function using find/rfind and substr.

#pragma once

#include <string>
#include <testkit/testkit.h>

// Given a string like "key:value", extract and return the part before ':'.
// If no ':' is found, return the entire string.
inline std::string extract_key(const std::string& kv) {
    TODO();
}

// Given a string like "key:value", extract and return the part after ':'.
// If no ':' is found, return an empty string.
inline std::string extract_value(const std::string& kv) {
    TODO();
}

// Given a file path like "/home/user/docs/report.txt", extract the filename
// (the part after the last '/'). If no '/' is found, return the entire string.
inline std::string extract_filename(const std::string& path) {
    TODO();
}

// Given a filename like "photo.backup.jpg", extract the extension
// (the part after the LAST '.'). If no '.' is found, return an empty string.
inline std::string extract_extension(const std::string& filename) {
    TODO();
}
