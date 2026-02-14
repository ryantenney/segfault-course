// Exercise 04: Directory Listing
//
// std::filesystem::directory_iterator lets you iterate over the entries
// in a single directory (non-recursively):
//
//   for (const auto& entry : fs::directory_iterator(dir)) {
//       std::cout << entry.path() << "\n";
//   }
//
// Each entry is a fs::directory_entry with useful methods:
//   entry.path()              -- the full path
//   entry.is_regular_file()   -- true if it is a regular file
//   entry.is_directory()      -- true if it is a directory
//   entry.path().extension()  -- the file extension
//   entry.path().filename()   -- the file name component
//
// TODO:
//   1. Implement list_files() -- return the filenames (not full paths) of
//      all regular files in a directory, sorted alphabetically.
//   2. Implement list_by_extension() -- return the filenames of all
//      regular files with a specific extension, sorted alphabetically.
//   3. Implement count_files_and_dirs() -- return a pair where first is
//      the count of regular files and second is the count of subdirectories.

#pragma once

#include <algorithm>
#include <filesystem>
#include <string>
#include <utility>
#include <vector>
#include <testkit/testkit.h>

namespace fs = std::filesystem;

// Return the filenames (just the name, not full path) of all regular files
// in the directory, sorted alphabetically.
inline std::vector<std::string> list_files(const fs::path& dir) {
    TODO();
}

// Return the filenames of all regular files with the given extension,
// sorted alphabetically. The extension includes the dot (e.g., ".txt").
inline std::vector<std::string> list_by_extension(const fs::path& dir,
                                                    const std::string& ext) {
    TODO();
}

// Count the number of regular files and subdirectories in a directory.
// Return {file_count, dir_count}.
inline std::pair<int, int> count_files_and_dirs(const fs::path& dir) {
    TODO();
}
