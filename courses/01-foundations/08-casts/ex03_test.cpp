// Exercise 03 — Tests (read-only)
//
// Verifies safe pointer downcasting with dynamic_cast.

#include <testkit/testkit.h>
#include "ex03.h"

static testkit::TestRunner runner("01-08-ex03: Safe Downcasting (Pointer)");

TEST(runner, "try_get_circle_area succeeds for Circle") {
    Circle c(5.0);
    double area = try_get_circle_area(&c);
    // pi * 25 = 78.5398...
    ASSERT_TRUE(area > 78.0);
    ASSERT_TRUE(area < 79.0);
}

TEST(runner, "try_get_circle_area returns -1 for Rectangle") {
    Rectangle r(3.0, 4.0);
    double area = try_get_circle_area(&r);
    ASSERT_EQ(area, -1.0);
}

TEST(runner, "try_get_rectangle_area succeeds for Rectangle") {
    Rectangle r(3.0, 4.0);
    double area = try_get_rectangle_area(&r);
    ASSERT_EQ(area, 12.0);
}

TEST(runner, "try_get_rectangle_area returns -1 for Circle") {
    Circle c(2.0);
    double area = try_get_rectangle_area(&c);
    ASSERT_EQ(area, -1.0);
}

TESTKIT_MAIN(runner)
