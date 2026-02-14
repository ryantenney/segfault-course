// Exercise 05 -- Tests (read-only)

#include <fstream>
#include <testkit/testkit.h>

#include "ex05.h"

namespace {

struct TempDir {
    fs::path path;

    TempDir() {
        path = fs::temp_directory_path() / "segfault-02-23-ex05";
        fs::remove_all(path);
        fs::create_directories(path);
    }

    ~TempDir() {
        std::error_code ec;
        fs::remove_all(path, ec);
    }
};

void create_tree(const fs::path& base) {
    // base/
    //   a.txt
    //   sub1/
    //     b.txt
    //     c.cpp
    //   sub2/
    //     d.txt
    //     deep/
    //       e.txt
    //   .hidden/
    //     secret.txt
    std::ofstream(base / "a.txt") << "a";
    fs::create_directory(base / "sub1");
    std::ofstream(base / "sub1" / "b.txt") << "b";
    std::ofstream(base / "sub1" / "c.cpp") << "c";
    fs::create_directory(base / "sub2");
    std::ofstream(base / "sub2" / "d.txt") << "d";
    fs::create_directories(base / "sub2" / "deep");
    std::ofstream(base / "sub2" / "deep" / "e.txt") << "e";
    fs::create_directories(base / ".hidden");
    std::ofstream(base / ".hidden" / "secret.txt") << "s";
}

} // namespace

static testkit::TestRunner runner("02-23-ex05: Recursive Listing");

TEST(runner, "find_all_files finds all files recursively") {
    TempDir tmp;
    create_tree(tmp.path);

    auto files = find_all_files(tmp.path);
    ASSERT_EQ(files.size(), 6u);
    // Should include files from .hidden too (not skipping hidden here)
}

TEST(runner, "find_all_files returns sorted relative paths") {
    TempDir tmp;
    create_tree(tmp.path);

    auto files = find_all_files(tmp.path);
    // Verify sorted order
    for (std::size_t i = 1; i < files.size(); ++i) {
        ASSERT_TRUE(files[i - 1] <= files[i]);
    }
}

TEST(runner, "find_all_files returns empty for empty directory") {
    TempDir tmp;
    auto files = find_all_files(tmp.path);
    ASSERT_EQ(files.size(), 0u);
}

TEST(runner, "find_files_by_extension filters by .txt") {
    TempDir tmp;
    create_tree(tmp.path);

    auto txt_files = find_files_by_extension(tmp.path, ".txt");
    ASSERT_EQ(txt_files.size(), 5u);
}

TEST(runner, "find_files_by_extension filters by .cpp") {
    TempDir tmp;
    create_tree(tmp.path);

    auto cpp_files = find_files_by_extension(tmp.path, ".cpp");
    ASSERT_EQ(cpp_files.size(), 1u);
    ASSERT_EQ(cpp_files[0], std::string("sub1/c.cpp"));
}

TEST(runner, "find_files_by_extension returns empty for unmatched extension") {
    TempDir tmp;
    create_tree(tmp.path);

    auto py_files = find_files_by_extension(tmp.path, ".py");
    ASSERT_EQ(py_files.size(), 0u);
}

TEST(runner, "find_files_skip_hidden excludes hidden directory contents") {
    TempDir tmp;
    create_tree(tmp.path);

    auto files = find_files_skip_hidden(tmp.path);
    ASSERT_EQ(files.size(), 5u);
    // Verify that none of the returned paths contain ".hidden"
    for (const auto& f : files) {
        ASSERT_TRUE(f.find(".hidden") == std::string::npos);
    }
}

TEST(runner, "find_files_skip_hidden returns sorted paths") {
    TempDir tmp;
    create_tree(tmp.path);

    auto files = find_files_skip_hidden(tmp.path);
    for (std::size_t i = 1; i < files.size(); ++i) {
        ASSERT_TRUE(files[i - 1] <= files[i]);
    }
}

TESTKIT_MAIN(runner)
