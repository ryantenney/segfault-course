// Exercise 01: Path Construction
//
// C++17 introduced std::filesystem::path for portable path manipulation.
// Paths can be constructed from strings and joined using the / operator:
//
//   namespace fs = std::filesystem;
//   fs::path dir = "/usr/local";
//   fs::path file = dir / "bin" / "app";  // "/usr/local/bin/app"
//
// The / operator automatically inserts the platform-correct separator
// (/ on Unix, \ on Windows).
//
// You can also construct paths from strings:
//   fs::path p("some/path");
//   fs::path p = "some/path";
//
// path::string() returns the path as a std::string.
//
// TODO:
//   1. Implement join_paths() -- join two path components using the / operator.
//   2. Implement build_filepath() -- construct a file path from a directory,
//      a filename stem, and an extension (e.g., dir/"name.ext").
//   3. Implement append_subdirectory() -- given a base path and a list of
//      subdirectory names, build the full path by appending each one.

#pragma once

#include <filesystem>
#include <string>
#include <vector>
#include <testkit/testkit.h>

namespace fs = std::filesystem;

// Join two path components and return the result as a string.
inline std::string join_paths(const std::string& a, const std::string& b) {
    TODO();
}

// Build a file path: directory / (stem + extension).
// For example: build_filepath("/home/user", "readme", ".md")
// should return "/home/user/readme.md".
inline std::string build_filepath(const std::string& directory,
                                   const std::string& stem,
                                   const std::string& extension) {
    TODO();
}

// Starting from base, append each subdirectory name in order.
// Return the resulting path as a string.
// Example: append_subdirs("/home", {"user", "docs", "notes"})
//   -> "/home/user/docs/notes"
inline std::string append_subdirs(const std::string& base,
                                   const std::vector<std::string>& subdirs) {
    TODO();
}
