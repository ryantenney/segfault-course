// Exercise 05 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex05.h"

static testkit::TestRunner runner("02-22-ex05: Trim Whitespace");

TEST(runner, "ltrim removes leading spaces") {
    ASSERT_EQ(ltrim("   hello"), std::string("hello"));
}

TEST(runner, "ltrim removes leading tabs and newlines") {
    ASSERT_EQ(ltrim("\t\n hello"), std::string("hello"));
}

TEST(runner, "ltrim leaves trailing whitespace alone") {
    ASSERT_EQ(ltrim("  hello  "), std::string("hello  "));
}

TEST(runner, "ltrim handles no leading whitespace") {
    ASSERT_EQ(ltrim("hello"), std::string("hello"));
}

TEST(runner, "ltrim returns empty for all-whitespace") {
    ASSERT_EQ(ltrim("   "), std::string(""));
}

TEST(runner, "rtrim removes trailing spaces") {
    ASSERT_EQ(rtrim("hello   "), std::string("hello"));
}

TEST(runner, "rtrim removes trailing tabs and newlines") {
    ASSERT_EQ(rtrim("hello \t\n"), std::string("hello"));
}

TEST(runner, "rtrim leaves leading whitespace alone") {
    ASSERT_EQ(rtrim("  hello  "), std::string("  hello"));
}

TEST(runner, "rtrim handles no trailing whitespace") {
    ASSERT_EQ(rtrim("hello"), std::string("hello"));
}

TEST(runner, "rtrim returns empty for all-whitespace") {
    ASSERT_EQ(rtrim("\t\t"), std::string(""));
}

TEST(runner, "trim removes both leading and trailing") {
    ASSERT_EQ(trim("  hello  "), std::string("hello"));
}

TEST(runner, "trim preserves internal whitespace") {
    ASSERT_EQ(trim("  hello world  "), std::string("hello world"));
}

TEST(runner, "trim handles empty string") {
    ASSERT_EQ(trim(""), std::string(""));
}

TEST(runner, "trim returns empty for all-whitespace") {
    ASSERT_EQ(trim("  \t\n  "), std::string(""));
}

TESTKIT_MAIN(runner)
