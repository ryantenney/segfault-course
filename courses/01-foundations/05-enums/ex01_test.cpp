// Exercise 01 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex01.h"

static testkit::TestRunner runner("01-05-ex01: Convert C Enum to enum class");

TEST(runner, "Color values are scoped (Color::Red, etc.)") {
    // These lines only compile if Color is an enum class with
    // properly scoped enumerator names.
    Color r = Color::Red;
    Color g = Color::Green;
    Color b = Color::Blue;
    ASSERT_TRUE(r != g);
    ASSERT_TRUE(g != b);
    ASSERT_TRUE(r != b);
}

TEST(runner, "is_red detects red") {
    ASSERT_TRUE(is_red(Color::Red));
    ASSERT_FALSE(is_red(Color::Green));
    ASSERT_FALSE(is_red(Color::Blue));
}

TEST(runner, "opposite swaps Red and Blue") {
    ASSERT_EQ(opposite(Color::Red), Color::Blue);
    ASSERT_EQ(opposite(Color::Blue), Color::Red);
    ASSERT_EQ(opposite(Color::Green), Color::Green);
}

TEST(runner, "same_color compares two colors") {
    ASSERT_TRUE(same_color(Color::Red, Color::Red));
    ASSERT_FALSE(same_color(Color::Red, Color::Blue));
    ASSERT_TRUE(same_color(Color::Green, Color::Green));
}

TESTKIT_MAIN(runner)
