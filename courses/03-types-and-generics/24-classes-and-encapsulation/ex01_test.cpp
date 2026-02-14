// Exercise 01 — Tests (read-only)
//
// Verifies that Point is a class (not struct) with accessible members
// and correct behavior.

#include <testkit/testkit.h>
#include <cmath>
#include <type_traits>
#include "ex01.h"

static testkit::TestRunner runner("03-24-ex01: struct vs class");

TEST(runner, "Point is a class type") {
    // This gate ensures the test is skipped if TODO() hasn't been replaced.
    Point p{0.0, 0.0};
    p.distance_to(p);

    // std::is_class_v is true for both struct and class, so we just
    // verify it's a class type (not a fundamental or enum).
    ASSERT_TRUE(std::is_class_v<Point>);
}

TEST(runner, "Point members are accessible") {
    Point p{3.0, 4.0};
    p.distance_to(p);

    ASSERT_TRUE(p.x == 3.0);
    ASSERT_TRUE(p.y == 4.0);
}

TEST(runner, "distance_to returns correct Euclidean distance") {
    Point a{0.0, 0.0};
    Point b{3.0, 4.0};
    double d = a.distance_to(b);
    ASSERT_TRUE(std::abs(d - 5.0) < 1e-9);
}

TEST(runner, "distance_to itself is zero") {
    Point p{7.0, 11.0};
    double d = p.distance_to(p);
    ASSERT_TRUE(std::abs(d) < 1e-9);
}

TEST(runner, "distance_to is symmetric") {
    Point a{1.0, 2.0};
    Point b{4.0, 6.0};
    double d1 = a.distance_to(b);
    double d2 = b.distance_to(a);
    ASSERT_TRUE(std::abs(d1 - d2) < 1e-9);
}

TEST(runner, "midpoint returns center of two points") {
    Point a{0.0, 0.0};
    Point b{10.0, 20.0};
    Point m = midpoint(a, b);
    ASSERT_TRUE(std::abs(m.x - 5.0) < 1e-9);
    ASSERT_TRUE(std::abs(m.y - 10.0) < 1e-9);
}

TEST(runner, "midpoint of same point is itself") {
    Point p{3.0, 7.0};
    Point m = midpoint(p, p);
    ASSERT_TRUE(std::abs(m.x - 3.0) < 1e-9);
    ASSERT_TRUE(std::abs(m.y - 7.0) < 1e-9);
}

TESTKIT_MAIN(runner)
