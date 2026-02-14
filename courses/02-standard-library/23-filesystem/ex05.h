// Exercise 05: Recursive Listing
//
// std::filesystem::recursive_directory_iterator walks an entire directory
// tree, descending into subdirectories automatically:
//
//   for (const auto& entry : fs::recursive_directory_iterator(dir)) {
//       std::cout << entry.path() << "\n";
//   }
//
// You can filter entries as you iterate. For example, to skip hidden
// directories (those starting with '.'), you can check the filename
// and use the iterator's disable_recursion_pending() method, or simply
// filter after collecting all entries.
//
// A simpler approach: collect all matching entries and filter out
// paths that contain a hidden directory component.
//
// Useful methods on directory_entry:
//   entry.path().filename().string()[0] == '.'  // check if name starts with dot
//   entry.is_regular_file()
//   entry.is_directory()
//   entry.path().lexically_relative(base)  // path relative to base
//
// TODO:
//   1. Implement find_all_files() -- recursively find all regular files in
//      a directory tree. Return their paths relative to the base directory,
//      sorted alphabetically.
//   2. Implement find_files_by_extension() -- recursively find all regular
//      files with a given extension. Return relative paths, sorted.
//   3. Implement find_files_skip_hidden() -- recursively find all regular
//      files, but skip any file whose path contains a hidden directory
//      (a directory component starting with '.'). Return relative paths, sorted.

#pragma once

#include <algorithm>
#include <filesystem>
#include <string>
#include <vector>
#include <testkit/testkit.h>

namespace fs = std::filesystem;

// Recursively find all regular files under `dir`.
// Return their paths relative to `dir`, sorted alphabetically.
inline std::vector<std::string> find_all_files(const fs::path& dir) {
    TODO();
}

// Recursively find all regular files with the given extension under `dir`.
// Return their paths relative to `dir`, sorted alphabetically.
inline std::vector<std::string> find_files_by_extension(const fs::path& dir,
                                                          const std::string& ext) {
    TODO();
}

// Recursively find all regular files under `dir`, skipping any file
// that is inside a hidden directory (a directory whose name starts with '.').
// Return their paths relative to `dir`, sorted alphabetically.
inline std::vector<std::string> find_files_skip_hidden(const fs::path& dir) {
    TODO();
}
