// Exercise 02 — Tests (read-only)
//
// Verifies numeric casts using static_cast.

#include <testkit/testkit.h>
#include "ex02.h"

static testkit::TestRunner runner("01-08-ex02: Numeric Casts");

TEST(runner, "truncate drops fractional part") {
    ASSERT_EQ(truncate(3.14), 3);
    ASSERT_EQ(truncate(-2.99), -2);
    ASSERT_EQ(truncate(0.5), 0);
}

TEST(runner, "safe_divide returns floating-point result") {
    ASSERT_EQ(safe_divide(7, 2), 3.5);
    ASSERT_EQ(safe_divide(10, 4), 2.5);
    ASSERT_EQ(safe_divide(1, 3), 1.0 / 3.0);
}

TEST(runner, "color_to_int returns underlying value") {
    ASSERT_EQ(color_to_int(Color::Red), 0);
    ASSERT_EQ(color_to_int(Color::Green), 1);
    ASSERT_EQ(color_to_int(Color::Blue), 2);
}

TEST(runner, "int_to_color converts back") {
    ASSERT_TRUE(int_to_color(0) == Color::Red);
    ASSERT_TRUE(int_to_color(1) == Color::Green);
    ASSERT_TRUE(int_to_color(2) == Color::Blue);
}

TEST(runner, "narrow_to_short intentionally narrows") {
    ASSERT_EQ(narrow_to_short(42.9), static_cast<short>(42));
    ASSERT_EQ(narrow_to_short(-100.1), static_cast<short>(-100));
}

TESTKIT_MAIN(runner)
