// Exercise 06: File Size and Timestamps
//
// std::filesystem provides functions to query file metadata:
//
//   fs::file_size(path)         -- returns file size in bytes (uintmax_t)
//   fs::last_write_time(path)   -- returns a fs::file_time_type
//
// file_time_type is a time point from the filesystem clock. You can compare
// two file_time_types directly:
//
//   auto t1 = fs::last_write_time(file1);
//   auto t2 = fs::last_write_time(file2);
//   if (t1 > t2) { /* file1 was modified more recently */ }
//
// You can also set the last write time:
//   fs::last_write_time(path, new_time);
//
// Note: file_size() only works on regular files. Calling it on a directory
// has implementation-defined behavior.
//
// TODO:
//   1. Implement get_file_size() -- return the size of a file in bytes.
//      Return 0 if the file does not exist or is not a regular file.
//   2. Implement is_newer_than() -- return true if file `a` was modified
//      more recently than file `b`.
//   3. Implement find_largest_file() -- given a directory, find the largest
//      regular file and return its filename. Return an empty string if the
//      directory is empty or has no regular files.

#pragma once

#include <filesystem>
#include <string>
#include <testkit/testkit.h>

namespace fs = std::filesystem;

// Return the size of the file at `path` in bytes.
// Return 0 if the path does not exist or is not a regular file.
inline std::uintmax_t get_file_size(const fs::path& path) {
    TODO();
}

// Return true if file `a` was modified more recently than file `b`.
// Both files must exist.
inline bool is_newer_than(const fs::path& a, const fs::path& b) {
    TODO();
}

// Find the largest regular file in the directory (non-recursive).
// Return its filename (not the full path).
// Return an empty string if no regular files exist.
inline std::string find_largest_file(const fs::path& dir) {
    TODO();
}
