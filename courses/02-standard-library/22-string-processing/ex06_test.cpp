// Exercise 06 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex06.h"

static testkit::TestRunner runner("02-22-ex06: Case Conversion");

TEST(runner, "to_lower converts uppercase letters") {
    ASSERT_EQ(to_lower("HELLO"), std::string("hello"));
}

TEST(runner, "to_lower preserves non-letter characters") {
    ASSERT_EQ(to_lower("Hello, World! 123"), std::string("hello, world! 123"));
}

TEST(runner, "to_lower handles already lowercase") {
    ASSERT_EQ(to_lower("already lower"), std::string("already lower"));
}

TEST(runner, "to_lower handles empty string") {
    ASSERT_EQ(to_lower(""), std::string(""));
}

TEST(runner, "to_upper converts lowercase letters") {
    ASSERT_EQ(to_upper("hello"), std::string("HELLO"));
}

TEST(runner, "to_upper preserves non-letter characters") {
    ASSERT_EQ(to_upper("Hello, World! 123"), std::string("HELLO, WORLD! 123"));
}

TEST(runner, "to_upper handles already uppercase") {
    ASSERT_EQ(to_upper("ALREADY UPPER"), std::string("ALREADY UPPER"));
}

TEST(runner, "to_upper handles empty string") {
    ASSERT_EQ(to_upper(""), std::string(""));
}

TEST(runner, "is_equal_ignore_case same case") {
    ASSERT_TRUE(is_equal_ignore_case("hello", "hello"));
}

TEST(runner, "is_equal_ignore_case different case") {
    ASSERT_TRUE(is_equal_ignore_case("Hello", "hELLO"));
}

TEST(runner, "is_equal_ignore_case not equal") {
    ASSERT_FALSE(is_equal_ignore_case("hello", "world"));
}

TEST(runner, "is_equal_ignore_case different lengths") {
    ASSERT_FALSE(is_equal_ignore_case("hello", "hell"));
}

TEST(runner, "is_equal_ignore_case empty strings") {
    ASSERT_TRUE(is_equal_ignore_case("", ""));
}

TESTKIT_MAIN(runner)
