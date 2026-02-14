// Exercise 06 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex06.h"

static testkit::TestRunner runner("01-04-ex06: String Comparison");

TEST(runner, "to_lower converts all characters to lowercase") {
    ASSERT_EQ(to_lower("Hello World"), std::string("hello world"));
    ASSERT_EQ(to_lower("ALLCAPS"), std::string("allcaps"));
    ASSERT_EQ(to_lower("already"), std::string("already"));
    ASSERT_EQ(to_lower("Mixed123"), std::string("mixed123"));
    ASSERT_EQ(to_lower(""), std::string(""));
}

TEST(runner, "iequals compares strings case-insensitively") {
    ASSERT_TRUE(iequals("Hello", "hello"));
    ASSERT_TRUE(iequals("HELLO", "hello"));
    ASSERT_TRUE(iequals("hello", "hello"));
    ASSERT_TRUE(iequals("", ""));
    ASSERT_FALSE(iequals("hello", "world"));
    ASSERT_FALSE(iequals("hello", "hell"));
    ASSERT_FALSE(iequals("hi", "hello"));
}

TEST(runner, "istarts_with checks prefix case-insensitively") {
    ASSERT_TRUE(istarts_with("Hello World", "hello"));
    ASSERT_TRUE(istarts_with("HTTP/1.1", "http"));
    ASSERT_TRUE(istarts_with("anything", ""));
    ASSERT_FALSE(istarts_with("Hello", "world"));
    ASSERT_FALSE(istarts_with("Hi", "Hello"));
}

TESTKIT_MAIN(runner)
