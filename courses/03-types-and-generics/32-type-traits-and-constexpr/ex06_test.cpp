// Exercise 06 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex06.h"

static testkit::TestRunner runner("03-32-ex06: enable_if (Legacy) and Concepts (Modern)");

TEST(runner, "to_int_sfinae converts long to int") {
    ASSERT_EQ(to_int_sfinae(42L), 42);
}

TEST(runner, "to_int_sfinae converts char to int") {
    ASSERT_EQ(to_int_sfinae('A'), 65);
}

TEST(runner, "to_int_concept converts long to int") {
    ASSERT_EQ(to_int_concept(42L), 42);
}

TEST(runner, "to_int_concept converts short to int") {
    short s = 7;
    ASSERT_EQ(to_int_concept(s), 7);
}

TEST(runner, "numeric_to_string_sfinae converts int") {
    ASSERT_EQ(numeric_to_string_sfinae(99), std::string("99"));
}

TEST(runner, "numeric_to_string_sfinae converts double") {
    std::string result = numeric_to_string_sfinae(2.5);
    ASSERT_TRUE(result.substr(0, 3) == "2.5");
}

TEST(runner, "numeric_to_string_concept converts int") {
    ASSERT_EQ(numeric_to_string_concept(99), std::string("99"));
}

TEST(runner, "numeric_to_string_concept converts double") {
    std::string result = numeric_to_string_concept(2.5);
    ASSERT_TRUE(result.substr(0, 3) == "2.5");
}

TESTKIT_MAIN(runner)
