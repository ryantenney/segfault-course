// Exercise 08 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex08.h"

static testkit::TestRunner runner("02-18-ex08: Split and Join");

TEST(runner, "split_by_comma splits CSV values") {
    auto result = split_by_comma("apple,banana,cherry");
    ASSERT_EQ(result.size(), 3u);
    ASSERT_EQ(result[0], std::string("apple"));
    ASSERT_EQ(result[1], std::string("banana"));
    ASSERT_EQ(result[2], std::string("cherry"));
}

TEST(runner, "split_by_comma handles single value") {
    auto result = split_by_comma("only");
    ASSERT_EQ(result.size(), 1u);
    ASSERT_EQ(result[0], std::string("only"));
}

TEST(runner, "split_by_comma handles empty parts") {
    auto result = split_by_comma("a,,b");
    ASSERT_EQ(result.size(), 3u);
    ASSERT_EQ(result[0], std::string("a"));
    ASSERT_EQ(result[1], std::string(""));
    ASSERT_EQ(result[2], std::string("b"));
}

TEST(runner, "split_by_char splits by colon") {
    auto result = split_by_char("key:value:extra", ':');
    ASSERT_EQ(result.size(), 3u);
    ASSERT_EQ(result[0], std::string("key"));
    ASSERT_EQ(result[1], std::string("value"));
    ASSERT_EQ(result[2], std::string("extra"));
}

TEST(runner, "split_by_char splits by dash") {
    auto result = split_by_char("2024-01-15", '-');
    ASSERT_EQ(result.size(), 3u);
    ASSERT_EQ(result[0], std::string("2024"));
    ASSERT_EQ(result[1], std::string("01"));
    ASSERT_EQ(result[2], std::string("15"));
}

TEST(runner, "split_by_char handles no delimiter present") {
    auto result = split_by_char("nodash", '-');
    ASSERT_EQ(result.size(), 1u);
    ASSERT_EQ(result[0], std::string("nodash"));
}

TEST(runner, "count_words counts space-separated words") {
    ASSERT_EQ(count_words("hello world foo"), 3u);
}

TEST(runner, "count_words handles single word") {
    ASSERT_EQ(count_words("hello"), 1u);
}

TEST(runner, "count_words handles multiple spaces") {
    // Note: split will produce empty parts between consecutive spaces;
    // count_words should only count non-empty parts.
    ASSERT_EQ(count_words("hello  world"), 2u);
}

TEST(runner, "count_words handles empty input") {
    ASSERT_EQ(count_words(""), 0u);
}

TESTKIT_MAIN(runner)
