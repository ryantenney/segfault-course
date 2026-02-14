// Exercise 06 -- Tests (read-only)

#include <chrono>
#include <fstream>
#include <thread>
#include <testkit/testkit.h>

#include "ex06.h"

namespace {

struct TempDir {
    fs::path path;

    TempDir() {
        path = fs::temp_directory_path() / "segfault-02-23-ex06";
        fs::remove_all(path);
        fs::create_directories(path);
    }

    ~TempDir() {
        std::error_code ec;
        fs::remove_all(path, ec);
    }
};

} // namespace

static testkit::TestRunner runner("02-23-ex06: File Size and Timestamps");

TEST(runner, "get_file_size returns correct size") {
    TempDir tmp;
    auto file = tmp.path / "data.txt";
    {
        std::ofstream ofs(file);
        ofs << "hello";  // 5 bytes
    }
    ASSERT_EQ(get_file_size(file), static_cast<std::uintmax_t>(5));
}

TEST(runner, "get_file_size returns 0 for empty file") {
    TempDir tmp;
    auto file = tmp.path / "empty.txt";
    { std::ofstream ofs(file); }  // create empty file
    ASSERT_EQ(get_file_size(file), static_cast<std::uintmax_t>(0));
}

TEST(runner, "get_file_size returns 0 for nonexistent file") {
    TempDir tmp;
    ASSERT_EQ(get_file_size(tmp.path / "nope.txt"), static_cast<std::uintmax_t>(0));
}

TEST(runner, "get_file_size returns 0 for directory") {
    TempDir tmp;
    ASSERT_EQ(get_file_size(tmp.path), static_cast<std::uintmax_t>(0));
}

TEST(runner, "is_newer_than detects newer file") {
    TempDir tmp;
    auto older = tmp.path / "older.txt";
    auto newer = tmp.path / "newer.txt";

    // Create the older file, then set its modification time to the past.
    std::ofstream(older) << "old";
    auto old_time = fs::last_write_time(older);
    fs::last_write_time(older, old_time - std::chrono::seconds(10));

    // Create the newer file -- it gets the current time.
    std::ofstream(newer) << "new";

    ASSERT_TRUE(is_newer_than(newer, older));
    ASSERT_FALSE(is_newer_than(older, newer));
}

TEST(runner, "find_largest_file finds the biggest file") {
    TempDir tmp;
    std::ofstream(tmp.path / "small.txt") << "ab";
    std::ofstream(tmp.path / "large.txt") << "abcdefghij";
    std::ofstream(tmp.path / "medium.txt") << "abcde";

    ASSERT_EQ(find_largest_file(tmp.path), std::string("large.txt"));
}

TEST(runner, "find_largest_file returns empty for empty directory") {
    TempDir tmp;
    ASSERT_EQ(find_largest_file(tmp.path), std::string(""));
}

TEST(runner, "find_largest_file ignores subdirectories") {
    TempDir tmp;
    std::ofstream(tmp.path / "file.txt") << "content";
    fs::create_directory(tmp.path / "subdir");

    ASSERT_EQ(find_largest_file(tmp.path), std::string("file.txt"));
}

TESTKIT_MAIN(runner)
