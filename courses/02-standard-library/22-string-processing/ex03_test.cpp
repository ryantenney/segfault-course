// Exercise 03 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex03.h"

static testkit::TestRunner runner("02-22-ex03: Number Conversion");

TEST(runner, "int_to_string positive number") {
    ASSERT_EQ(int_to_string(42), std::string("42"));
}

TEST(runner, "int_to_string zero") {
    ASSERT_EQ(int_to_string(0), std::string("0"));
}

TEST(runner, "int_to_string negative number") {
    ASSERT_EQ(int_to_string(-17), std::string("-17"));
}

TEST(runner, "int_to_string large number") {
    ASSERT_EQ(int_to_string(1000000), std::string("1000000"));
}

TEST(runner, "string_to_int valid number") {
    ASSERT_EQ(string_to_int("123"), 123);
}

TEST(runner, "string_to_int negative number") {
    ASSERT_EQ(string_to_int("-99"), -99);
}

TEST(runner, "string_to_int zero") {
    ASSERT_EQ(string_to_int("0"), 0);
}

TEST(runner, "string_to_int invalid returns 0") {
    ASSERT_EQ(string_to_int("abc"), 0);
}

TEST(runner, "string_to_int_checked valid number") {
    auto result = string_to_int_checked("456");
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(result.value(), 456);
}

TEST(runner, "string_to_int_checked negative number") {
    auto result = string_to_int_checked("-10");
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(result.value(), -10);
}

TEST(runner, "string_to_int_checked rejects trailing characters") {
    auto result = string_to_int_checked("42abc");
    ASSERT_FALSE(result.has_value());
}

TEST(runner, "string_to_int_checked rejects non-numeric") {
    auto result = string_to_int_checked("hello");
    ASSERT_FALSE(result.has_value());
}

TEST(runner, "string_to_int_checked rejects empty string") {
    auto result = string_to_int_checked("");
    ASSERT_FALSE(result.has_value());
}

TESTKIT_MAIN(runner)
