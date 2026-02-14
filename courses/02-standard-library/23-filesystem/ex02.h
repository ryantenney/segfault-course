// Exercise 02: Path Decomposition
//
// std::filesystem::path provides methods to extract the parts of a path:
//
//   fs::path p = "/home/user/docs/report.txt";
//   p.parent_path()   // "/home/user/docs"
//   p.filename()      // "report.txt"
//   p.stem()          // "report"
//   p.extension()     // ".txt"
//   p.root_path()     // "/"
//   p.is_absolute()   // true
//   p.is_relative()   // false
//
// These methods work purely on the path string -- they do not check
// the filesystem. A path like "/nonexistent/file.txt" will still
// decompose correctly.
//
// Each method returns a fs::path, which you can convert to string
// with .string().
//
// TODO:
//   1. Implement get_extension() -- return the file extension (e.g., ".txt").
//   2. Implement get_stem() -- return the filename without extension.
//   3. Implement get_parent() -- return the parent directory path.
//   4. Implement change_extension() -- return a new path with the extension
//      changed. Use the .replace_extension() method on a copy of the path.

#pragma once

#include <filesystem>
#include <string>
#include <testkit/testkit.h>

namespace fs = std::filesystem;

// Return the file extension including the dot (e.g., ".txt").
// Returns empty string if there is no extension.
inline std::string get_extension(const std::string& filepath) {
    TODO();
}

// Return the filename without the extension (e.g., "report" from "report.txt").
inline std::string get_stem(const std::string& filepath) {
    TODO();
}

// Return the parent directory path (e.g., "/home/user" from "/home/user/file.txt").
inline std::string get_parent(const std::string& filepath) {
    TODO();
}

// Return a new path with the extension replaced.
// Example: change_extension("/home/user/data.csv", ".json") -> "/home/user/data.json"
inline std::string change_extension(const std::string& filepath,
                                     const std::string& new_ext) {
    TODO();
}
