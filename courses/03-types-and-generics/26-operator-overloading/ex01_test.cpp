// Exercise 01 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex01.h"

static testkit::TestRunner runner("03-26-ex01: Equality Operator");

TEST(runner, "identical Points are equal") {
    Point a{1.0, 2.0};
    Point b{1.0, 2.0};
    ASSERT_TRUE(a == b);
}

TEST(runner, "Points with different x are not equal") {
    Point a{1.0, 2.0};
    Point b{3.0, 2.0};
    ASSERT_FALSE(a == b);
}

TEST(runner, "Points with different y are not equal") {
    Point a{1.0, 2.0};
    Point b{1.0, 5.0};
    ASSERT_FALSE(a == b);
}

TEST(runner, "Point operator!= works via rewrite") {
    Point a{1.0, 2.0};
    Point b{3.0, 4.0};
    ASSERT_TRUE(a != b);
    ASSERT_FALSE(a != a);
}

TEST(runner, "identical Colors are equal") {
    Color a{255, 128, 0};
    Color b{255, 128, 0};
    ASSERT_TRUE(a == b);
}

TEST(runner, "Colors with any different channel are not equal") {
    Color base{100, 200, 50};
    Color diff_r{101, 200, 50};
    Color diff_g{100, 201, 50};
    Color diff_b{100, 200, 51};
    ASSERT_FALSE(base == diff_r);
    ASSERT_FALSE(base == diff_g);
    ASSERT_FALSE(base == diff_b);
}

TEST(runner, "Color operator!= works via rewrite") {
    Color a{10, 20, 30};
    Color b{10, 20, 31};
    ASSERT_TRUE(a != b);
    ASSERT_FALSE(a != a);
}

TESTKIT_MAIN(runner)
