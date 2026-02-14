// Exercise 02 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex02.h"

static testkit::TestRunner runner("02-23-ex02: Path Decomposition");

TEST(runner, "get_extension returns .txt") {
    ASSERT_EQ(get_extension("/home/user/report.txt"), std::string(".txt"));
}

TEST(runner, "get_extension returns .cpp") {
    ASSERT_EQ(get_extension("src/main.cpp"), std::string(".cpp"));
}

TEST(runner, "get_extension returns empty for no extension") {
    ASSERT_EQ(get_extension("/usr/local/bin/app"), std::string(""));
}

TEST(runner, "get_extension returns last extension for double ext") {
    ASSERT_EQ(get_extension("archive.tar.gz"), std::string(".gz"));
}

TEST(runner, "get_stem returns filename without extension") {
    ASSERT_EQ(get_stem("/home/user/report.txt"), std::string("report"));
}

TEST(runner, "get_stem returns name when no extension") {
    ASSERT_EQ(get_stem("/usr/bin/app"), std::string("app"));
}

TEST(runner, "get_stem handles double extension") {
    ASSERT_EQ(get_stem("archive.tar.gz"), std::string("archive.tar"));
}

TEST(runner, "get_parent returns parent directory") {
    ASSERT_EQ(get_parent("/home/user/docs/file.txt"), std::string("/home/user/docs"));
}

TEST(runner, "get_parent returns root for root child") {
    ASSERT_EQ(get_parent("/file.txt"), std::string("/"));
}

TEST(runner, "get_parent handles relative path") {
    ASSERT_EQ(get_parent("src/main.cpp"), std::string("src"));
}

TEST(runner, "change_extension replaces .csv with .json") {
    ASSERT_EQ(change_extension("/data/file.csv", ".json"),
              std::string("/data/file.json"));
}

TEST(runner, "change_extension replaces .txt with .md") {
    ASSERT_EQ(change_extension("notes.txt", ".md"),
              std::string("notes.md"));
}

TEST(runner, "change_extension adds extension when none exists") {
    ASSERT_EQ(change_extension("Makefile", ".bak"),
              std::string("Makefile.bak"));
}

TESTKIT_MAIN(runner)
