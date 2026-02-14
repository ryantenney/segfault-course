// Exercise 03: Existence and Type Checks
//
// std::filesystem provides functions to query the filesystem:
//
//   fs::exists(path)            -- true if the path exists
//   fs::is_regular_file(path)   -- true if it is a regular file
//   fs::is_directory(path)      -- true if it is a directory
//   fs::is_symlink(path)        -- true if it is a symbolic link
//   fs::is_empty(path)          -- true if file is 0 bytes or dir has no entries
//
// These functions can throw filesystem_error on permission errors. To avoid
// exceptions, pass a std::error_code as the second argument:
//
//   std::error_code ec;
//   bool result = fs::exists(path, ec);
//   if (ec) { /* handle error */ }
//
// TODO:
//   1. Implement path_status() -- return a string describing what the path is:
//      "file", "directory", "not found", or "other". Use the query functions.
//   2. Implement count_entries() -- count how many immediate entries exist in
//      a directory. Return 0 if the path is not a directory.
//   3. Implement path_exists_safe() -- return whether a path exists, using
//      the error_code overload to avoid exceptions.

#pragma once

#include <filesystem>
#include <string>
#include <testkit/testkit.h>

namespace fs = std::filesystem;

// Return "file" if the path is a regular file, "directory" if it is a
// directory, "not found" if it does not exist, or "other" for anything else.
inline std::string path_status(const fs::path& p) {
    TODO();
}

// Count the number of immediate entries in a directory.
// Return 0 if the path is not a directory or does not exist.
inline int count_entries(const fs::path& dir) {
    TODO();
}

// Return true if the path exists, using the error_code overload to
// avoid throwing exceptions. Return false on error.
inline bool path_exists_safe(const fs::path& p) {
    TODO();
}
