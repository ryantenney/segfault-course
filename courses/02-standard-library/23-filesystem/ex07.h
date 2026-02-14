// Exercise 07: Create Directory Tree
//
// std::filesystem provides functions to create directories:
//
//   fs::create_directory(path)    -- create a single directory
//   fs::create_directories(path)  -- create all missing directories in the path
//
// create_directory() fails if the parent does not exist.
// create_directories() creates all intermediate directories (like mkdir -p).
//
// Both return true if the directory was actually created, false if it
// already existed. On errors, they throw fs::filesystem_error.
//
// To handle errors without exceptions, pass a std::error_code:
//
//   std::error_code ec;
//   fs::create_directories(path, ec);
//   if (ec) { /* handle error */ }
//
// TODO:
//   1. Implement create_tree() -- given a base path and a vector of
//      relative directory paths, create all of them. Use create_directories
//      with error_code. Return true if all succeeded, false if any failed.
//   2. Implement ensure_parent_exists() -- given a file path, create its
//      parent directory if it does not exist. Return true on success.
//   3. Implement create_file_in_dir() -- create a directory if needed, then
//      create a file inside it with the given content. Return true on success.

#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <testkit/testkit.h>

namespace fs = std::filesystem;

// Create all the directories listed in `dirs` as subdirectories of `base`.
// Each entry in `dirs` is a relative path (may be nested like "a/b/c").
// Use create_directories with error_code. Return true if all succeeded.
inline bool create_tree(const fs::path& base,
                         const std::vector<std::string>& dirs) {
    TODO();
}

// Ensure that the parent directory of `filepath` exists.
// If it does not exist, create it (and any ancestors) using create_directories.
// Return true on success, false on failure.
inline bool ensure_parent_exists(const fs::path& filepath) {
    TODO();
}

// Create the directory `dir` if it does not exist, then create a file named
// `filename` inside it with the given `content`.
// Return true on success, false if the directory could not be created.
inline bool create_file_in_dir(const fs::path& dir,
                                const std::string& filename,
                                const std::string& content) {
    TODO();
}
