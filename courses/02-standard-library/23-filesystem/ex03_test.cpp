// Exercise 03 -- Tests (read-only)

#include <fstream>
#include <testkit/testkit.h>

#include "ex03.h"

namespace {

// Helper: create a unique temp directory for each test run.
struct TempDir {
    fs::path path;

    TempDir() {
        path = fs::temp_directory_path() / "segfault-02-23-ex03";
        fs::remove_all(path);
        fs::create_directories(path);
    }

    ~TempDir() {
        std::error_code ec;
        fs::remove_all(path, ec);
    }
};

} // namespace

static testkit::TestRunner runner("02-23-ex03: Existence and Type Checks");

TEST(runner, "path_status returns file for regular file") {
    TempDir tmp;
    auto file = tmp.path / "test.txt";
    std::ofstream(file) << "hello";
    ASSERT_EQ(path_status(file), std::string("file"));
}

TEST(runner, "path_status returns directory for directory") {
    TempDir tmp;
    auto dir = tmp.path / "subdir";
    fs::create_directory(dir);
    ASSERT_EQ(path_status(dir), std::string("directory"));
}

TEST(runner, "path_status returns not found for missing path") {
    TempDir tmp;
    ASSERT_EQ(path_status(tmp.path / "nonexistent"), std::string("not found"));
}

TEST(runner, "count_entries counts files in directory") {
    TempDir tmp;
    std::ofstream(tmp.path / "a.txt") << "a";
    std::ofstream(tmp.path / "b.txt") << "b";
    std::ofstream(tmp.path / "c.txt") << "c";
    ASSERT_EQ(count_entries(tmp.path), 3);
}

TEST(runner, "count_entries returns 0 for empty directory") {
    TempDir tmp;
    auto empty = tmp.path / "empty";
    fs::create_directory(empty);
    ASSERT_EQ(count_entries(empty), 0);
}

TEST(runner, "count_entries returns 0 for nonexistent path") {
    TempDir tmp;
    ASSERT_EQ(count_entries(tmp.path / "nope"), 0);
}

TEST(runner, "count_entries counts subdirectories too") {
    TempDir tmp;
    std::ofstream(tmp.path / "file.txt") << "data";
    fs::create_directory(tmp.path / "subdir");
    ASSERT_EQ(count_entries(tmp.path), 2);
}

TEST(runner, "path_exists_safe returns true for existing file") {
    TempDir tmp;
    auto file = tmp.path / "exists.txt";
    std::ofstream(file) << "yes";
    ASSERT_TRUE(path_exists_safe(file));
}

TEST(runner, "path_exists_safe returns false for missing path") {
    TempDir tmp;
    ASSERT_FALSE(path_exists_safe(tmp.path / "missing"));
}

TESTKIT_MAIN(runner)
