// Exercise 08 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex08.h"

static testkit::TestRunner runner("01-04-ex08: View Lifetime Traps");

TEST(runner, "strip_quotes removes first and last characters") {
    ASSERT_EQ(strip_quotes("\"hello\""), std::string_view("hello"));
    ASSERT_EQ(strip_quotes("'x'"), std::string_view("x"));
    ASSERT_EQ(strip_quotes("ab"), std::string_view(""));
    ASSERT_EQ(strip_quotes("a"), std::string_view(""));
    ASSERT_EQ(strip_quotes(""), std::string_view(""));
}

TEST(runner, "concat returns a valid owned string") {
    auto result = concat("hello", " world");
    ASSERT_EQ(std::string(result), std::string("hello world"));
    auto result2 = concat("", "abc");
    ASSERT_EQ(std::string(result2), std::string("abc"));
}

TEST(runner, "is_all_digits detects digit-only strings") {
    ASSERT_TRUE(is_all_digits("12345"));
    ASSERT_TRUE(is_all_digits("0"));
    ASSERT_FALSE(is_all_digits(""));
    ASSERT_FALSE(is_all_digits("12a45"));
    ASSERT_FALSE(is_all_digits("hello"));
    ASSERT_FALSE(is_all_digits("-5"));
}

TEST(runner, "int_to_str returns a valid owned string") {
    auto result = int_to_str(42);
    ASSERT_EQ(std::string(result), std::string("42"));
    auto result2 = int_to_str(-7);
    ASSERT_EQ(std::string(result2), std::string("-7"));
    auto result3 = int_to_str(0);
    ASSERT_EQ(std::string(result3), std::string("0"));
}

TEST(runner, "find_pos locates a substring") {
    ASSERT_EQ(find_pos("hello world", "world"), 6u);
    ASSERT_EQ(find_pos("hello world", "hello"), 0u);
    ASSERT_EQ(find_pos("hello world", "xyz"), std::string_view::npos);
    ASSERT_EQ(find_pos("aaa", "a"), 0u);
}

TESTKIT_MAIN(runner)
