// Exercise 04 -- Tests (read-only)

#include <fstream>
#include <testkit/testkit.h>

#include "ex04.h"

namespace {

struct TempDir {
    fs::path path;

    TempDir() {
        path = fs::temp_directory_path() / "segfault-02-23-ex04";
        fs::remove_all(path);
        fs::create_directories(path);
    }

    ~TempDir() {
        std::error_code ec;
        fs::remove_all(path, ec);
    }
};

} // namespace

static testkit::TestRunner runner("02-23-ex04: Directory Listing");

TEST(runner, "list_files returns all regular files sorted") {
    TempDir tmp;
    std::ofstream(tmp.path / "banana.txt") << "b";
    std::ofstream(tmp.path / "apple.txt") << "a";
    std::ofstream(tmp.path / "cherry.txt") << "c";

    auto files = list_files(tmp.path);
    ASSERT_EQ(files.size(), 3u);
    ASSERT_EQ(files[0], std::string("apple.txt"));
    ASSERT_EQ(files[1], std::string("banana.txt"));
    ASSERT_EQ(files[2], std::string("cherry.txt"));
}

TEST(runner, "list_files excludes subdirectories") {
    TempDir tmp;
    std::ofstream(tmp.path / "file.txt") << "data";
    fs::create_directory(tmp.path / "subdir");

    auto files = list_files(tmp.path);
    ASSERT_EQ(files.size(), 1u);
    ASSERT_EQ(files[0], std::string("file.txt"));
}

TEST(runner, "list_files returns empty for empty directory") {
    TempDir tmp;
    auto files = list_files(tmp.path);
    ASSERT_EQ(files.size(), 0u);
}

TEST(runner, "list_by_extension filters by extension") {
    TempDir tmp;
    std::ofstream(tmp.path / "main.cpp") << "code";
    std::ofstream(tmp.path / "main.h") << "header";
    std::ofstream(tmp.path / "test.cpp") << "test";
    std::ofstream(tmp.path / "notes.txt") << "notes";

    auto cpp_files = list_by_extension(tmp.path, ".cpp");
    ASSERT_EQ(cpp_files.size(), 2u);
    ASSERT_EQ(cpp_files[0], std::string("main.cpp"));
    ASSERT_EQ(cpp_files[1], std::string("test.cpp"));
}

TEST(runner, "list_by_extension returns empty when none match") {
    TempDir tmp;
    std::ofstream(tmp.path / "data.csv") << "csv";

    auto py_files = list_by_extension(tmp.path, ".py");
    ASSERT_EQ(py_files.size(), 0u);
}

TEST(runner, "count_files_and_dirs counts correctly") {
    TempDir tmp;
    std::ofstream(tmp.path / "a.txt") << "a";
    std::ofstream(tmp.path / "b.txt") << "b";
    fs::create_directory(tmp.path / "dir1");
    fs::create_directory(tmp.path / "dir2");
    fs::create_directory(tmp.path / "dir3");

    auto [files, dirs] = count_files_and_dirs(tmp.path);
    ASSERT_EQ(files, 2);
    ASSERT_EQ(dirs, 3);
}

TEST(runner, "count_files_and_dirs handles empty directory") {
    TempDir tmp;
    auto [files, dirs] = count_files_and_dirs(tmp.path);
    ASSERT_EQ(files, 0);
    ASSERT_EQ(dirs, 0);
}

TESTKIT_MAIN(runner)
