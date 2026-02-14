// Exercise 01 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex01.h"

static testkit::TestRunner runner("01-04-ex01: String Basics");

TEST(runner, "make_greeting constructs a string from a C-string") {
    ASSERT_EQ(make_greeting("Alice"), std::string("Alice"));
    ASSERT_EQ(make_greeting(""), std::string(""));
}

TEST(runner, "string_length returns the number of characters") {
    ASSERT_EQ(string_length("hello"), 5u);
    ASSERT_EQ(string_length(""), 0u);
    ASSERT_EQ(string_length("a"), 1u);
}

TEST(runner, "is_empty returns true for empty strings") {
    ASSERT_TRUE(is_empty(""));
    ASSERT_FALSE(is_empty("x"));
    ASSERT_FALSE(is_empty("hello world"));
}

TEST(runner, "cleared_copy returns an empty string") {
    std::string original = "not empty";
    std::string result = cleared_copy(original);
    ASSERT_TRUE(result.empty());
    // Original is unchanged (we copied it)
    ASSERT_EQ(original, std::string("not empty"));
}

TEST(runner, "repeat_char builds a string of repeated characters") {
    ASSERT_EQ(repeat_char(5, 'x'), std::string("xxxxx"));
    ASSERT_EQ(repeat_char(0, 'a'), std::string(""));
    ASSERT_EQ(repeat_char(3, '-'), std::string("---"));
}

TESTKIT_MAIN(runner)
