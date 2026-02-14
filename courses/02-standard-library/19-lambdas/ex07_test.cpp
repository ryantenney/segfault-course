// Exercise 07 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex07.h"

static testkit::TestRunner runner("02-19-ex07: IIFE for Initialization");

TEST(runner, "classify_number returns negative") {
    ASSERT_EQ(classify_number(-5), std::string("negative"));
    ASSERT_EQ(classify_number(-1), std::string("negative"));
}

TEST(runner, "classify_number returns zero") {
    ASSERT_EQ(classify_number(0), std::string("zero"));
}

TEST(runner, "classify_number returns positive") {
    ASSERT_EQ(classify_number(1), std::string("positive"));
    ASSERT_EQ(classify_number(100), std::string("positive"));
}

TEST(runner, "build_greeting formal") {
    ASSERT_EQ(build_greeting("Alice", true), std::string("Dear Alice,"));
    ASSERT_EQ(build_greeting("Bob", true), std::string("Dear Bob,"));
}

TEST(runner, "build_greeting informal") {
    ASSERT_EQ(build_greeting("Alice", false), std::string("Hey Alice!"));
    ASSERT_EQ(build_greeting("Bob", false), std::string("Hey Bob!"));
}

TEST(runner, "first_n_squares returns correct squares") {
    auto result = first_n_squares(5);
    ASSERT_EQ(result.size(), 5u);
    ASSERT_EQ(result[0], 1);
    ASSERT_EQ(result[1], 4);
    ASSERT_EQ(result[2], 9);
    ASSERT_EQ(result[3], 16);
    ASSERT_EQ(result[4], 25);
}

TEST(runner, "first_n_squares with n = 1") {
    auto result = first_n_squares(1);
    ASSERT_EQ(result.size(), 1u);
    ASSERT_EQ(result[0], 1);
}

TEST(runner, "first_n_squares with n = 0") {
    auto result = first_n_squares(0);
    ASSERT_EQ(result.size(), 0u);
}

TEST(runner, "first_n_squares with larger n") {
    auto result = first_n_squares(3);
    ASSERT_EQ(result[0], 1);
    ASSERT_EQ(result[1], 4);
    ASSERT_EQ(result[2], 9);
}

TESTKIT_MAIN(runner)
