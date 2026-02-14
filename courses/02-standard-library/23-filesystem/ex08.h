// Exercise 08: Temp Directory with RAII
//
// A common pattern when working with temporary files is to create a
// temporary directory, do your work, and then clean it up. Forgetting
// to clean up leaves behind junk files. Exceptions can skip cleanup.
//
// RAII solves this: wrap the temp directory in a class whose destructor
// calls fs::remove_all(). The directory is cleaned up automatically
// when the object goes out of scope -- even if an exception is thrown.
//
// std::filesystem::temp_directory_path() returns the platform's
// temporary directory (e.g., /tmp on Linux/macOS).
//
// To create a unique directory name, you can append a random or
// unique suffix. A simple approach is to use a counter or the
// address of the object.
//
// TODO:
//   1. Implement the TempDirectory class:
//      - Constructor: create a unique directory inside a given base path.
//        The directory name should be the given `prefix` followed by a
//        unique suffix (use the provided make_unique_name helper).
//      - path(): return the path to the created directory.
//      - Destructor: remove the directory and all its contents.
//      - Make it non-copyable (delete copy ctor and copy assignment).
//   2. Implement create_temp_file() -- create a file inside a TempDirectory
//      and return the full path to it.

#pragma once

#include <atomic>
#include <filesystem>
#include <fstream>
#include <string>
#include <testkit/testkit.h>

namespace fs = std::filesystem;

// Helper: generate a unique directory name.
// Uses an atomic counter to ensure uniqueness within a process.
inline std::string make_unique_name(const std::string& prefix) {
    static std::atomic<int> counter{0};
    return prefix + "-" + std::to_string(counter.fetch_add(1));
}

// A RAII wrapper that creates a temporary directory on construction
// and removes it (with all contents) on destruction.
class TempDirectory {
public:
    // Create a uniquely-named directory inside `base_path`.
    // Use make_unique_name(prefix) to generate the directory name.
    // Create the directory using fs::create_directories.
    TempDirectory(const fs::path& base_path, const std::string& prefix) {
        (void)base_path;
        (void)prefix;
        TODO();
    }

    // Non-copyable.
    TempDirectory(const TempDirectory&) = delete;
    TempDirectory& operator=(const TempDirectory&) = delete;

    // Destructor: remove the directory and all its contents.
    // Use fs::remove_all with an error_code to avoid throwing from destructor.
    ~TempDirectory() {
        // Note: destructor must not throw, so use error_code overload.
        // Students: implement cleanup here after removing TODO() from constructor.
        std::error_code ec;
        fs::remove_all(dir_path_, ec);
    }

    // Return the path to the created directory.
    const fs::path& path() const { return dir_path_; }

private:
    fs::path dir_path_;
};

// Create a file named `filename` inside the TempDirectory's path,
// write `content` to it, and return the full path to the file.
inline fs::path create_temp_file(TempDirectory& tmp,
                                  const std::string& filename,
                                  const std::string& content) {
    TODO();
}
