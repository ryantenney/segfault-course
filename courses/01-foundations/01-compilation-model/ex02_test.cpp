// Exercise 02 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex02.h"

static testkit::TestRunner runner("01-01-ex02: Pragma Once");

TEST(runner, "make_color constructs a Color") {
    Color c = make_color(255, 128, 0);
    ASSERT_EQ(c.r, 255);
    ASSERT_EQ(c.g, 128);
    ASSERT_EQ(c.b, 0);
}

TEST(runner, "point_distance_sq computes squared distance") {
    ASSERT_EQ(point_distance_sq({0, 0}, {3, 4}), 25.0);
    ASSERT_EQ(point_distance_sq({1, 1}, {1, 1}), 0.0);
}

TEST(runner, "ColoredPoint can be constructed") {
    ColoredPoint cp{{1.0, 2.0}, {255, 0, 0}};
    ASSERT_EQ(cp.position.x, 1.0);
    ASSERT_EQ(cp.color.r, 255);
}

TESTKIT_MAIN(runner)
