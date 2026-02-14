// Exercise 01 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex01.h"

static testkit::TestRunner runner("02-23-ex01: Path Construction");

TEST(runner, "join_paths joins two components") {
    auto result = join_paths("/usr/local", "bin");
    ASSERT_EQ(result, std::string("/usr/local/bin"));
}

TEST(runner, "join_paths handles trailing slash") {
    auto result = join_paths("/usr/local/", "bin");
    ASSERT_EQ(result, std::string("/usr/local/bin"));
}

TEST(runner, "join_paths joins relative paths") {
    auto result = join_paths("src", "main.cpp");
    ASSERT_EQ(result, std::string("src/main.cpp"));
}

TEST(runner, "build_filepath constructs full path") {
    auto result = build_filepath("/home/user", "readme", ".md");
    ASSERT_EQ(result, std::string("/home/user/readme.md"));
}

TEST(runner, "build_filepath with different extension") {
    auto result = build_filepath("src", "main", ".cpp");
    ASSERT_EQ(result, std::string("src/main.cpp"));
}

TEST(runner, "build_filepath with no directory prefix") {
    auto result = build_filepath(".", "test", ".h");
    ASSERT_EQ(result, std::string("./test.h"));
}

TEST(runner, "append_subdirs builds deep path") {
    auto result = append_subdirs("/home", {"user", "docs", "notes"});
    ASSERT_EQ(result, std::string("/home/user/docs/notes"));
}

TEST(runner, "append_subdirs with single subdir") {
    auto result = append_subdirs("/var", {"log"});
    ASSERT_EQ(result, std::string("/var/log"));
}

TEST(runner, "append_subdirs with empty list returns base") {
    auto result = append_subdirs("/home", {});
    ASSERT_EQ(result, std::string("/home"));
}

TESTKIT_MAIN(runner)
