// Exercise 02 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex02.h"

static testkit::TestRunner runner("02-22-ex02: Split a String");

TEST(runner, "split basic comma-separated") {
    auto result = split("a,b,c", ",");
    ASSERT_EQ(result.size(), 3u);
    ASSERT_EQ(result[0], std::string("a"));
    ASSERT_EQ(result[1], std::string("b"));
    ASSERT_EQ(result[2], std::string("c"));
}

TEST(runner, "split with multi-char delimiter") {
    auto result = split("one::two::three", "::");
    ASSERT_EQ(result.size(), 3u);
    ASSERT_EQ(result[0], std::string("one"));
    ASSERT_EQ(result[1], std::string("two"));
    ASSERT_EQ(result[2], std::string("three"));
}

TEST(runner, "split with no delimiter present") {
    auto result = split("hello", ",");
    ASSERT_EQ(result.size(), 1u);
    ASSERT_EQ(result[0], std::string("hello"));
}

TEST(runner, "split empty string returns one empty token") {
    auto result = split("", ",");
    ASSERT_EQ(result.size(), 1u);
    ASSERT_EQ(result[0], std::string(""));
}

TEST(runner, "split consecutive delimiters produce empty strings") {
    auto result = split("a,,b", ",");
    ASSERT_EQ(result.size(), 3u);
    ASSERT_EQ(result[0], std::string("a"));
    ASSERT_EQ(result[1], std::string(""));
    ASSERT_EQ(result[2], std::string("b"));
}

TEST(runner, "split trailing delimiter") {
    auto result = split("x,y,", ",");
    ASSERT_EQ(result.size(), 3u);
    ASSERT_EQ(result[2], std::string(""));
}

TEST(runner, "join basic") {
    std::vector<std::string> parts = {"a", "b", "c"};
    ASSERT_EQ(join(parts, ", "), std::string("a, b, c"));
}

TEST(runner, "join single element") {
    std::vector<std::string> parts = {"hello"};
    ASSERT_EQ(join(parts, ","), std::string("hello"));
}

TEST(runner, "join empty vector") {
    std::vector<std::string> parts = {};
    ASSERT_EQ(join(parts, ","), std::string(""));
}

TEST(runner, "join with empty separator") {
    std::vector<std::string> parts = {"a", "b", "c"};
    ASSERT_EQ(join(parts, ""), std::string("abc"));
}

TESTKIT_MAIN(runner)
