// Exercise 07 — Tests (read-only)
//
// These tests pass variables by reference. Notice the clean call syntax
// compared to the C-style pointer approach (no & at call sites).

#include <testkit/testkit.h>

#include "ex07.h"

static testkit::TestRunner runner("01-03-ex07: Reference vs Pointer Parameter");

TEST(runner, "double_value doubles in place") {
    int x = 5;
    double_value(x);
    ASSERT_EQ(x, 10);
}

TEST(runner, "double_value with zero") {
    int x = 0;
    double_value(x);
    ASSERT_EQ(x, 0);
}

TEST(runner, "double_value with negative") {
    int x = -3;
    double_value(x);
    ASSERT_EQ(x, -6);
}

TEST(runner, "rectangle_stats computes area and perimeter") {
    int area = 0, perimeter = 0;
    rectangle_stats(3, 4, area, perimeter);
    ASSERT_EQ(area, 12);
    ASSERT_EQ(perimeter, 14);
}

TEST(runner, "rectangle_stats with square") {
    int area = 0, perimeter = 0;
    rectangle_stats(5, 5, area, perimeter);
    ASSERT_EQ(area, 25);
    ASSERT_EQ(perimeter, 20);
}

TEST(runner, "order_pair swaps if out of order") {
    int lo = 10, hi = 3;
    order_pair(lo, hi);
    ASSERT_EQ(lo, 3);
    ASSERT_EQ(hi, 10);
}

TEST(runner, "order_pair leaves sorted pair alone") {
    int lo = 1, hi = 9;
    order_pair(lo, hi);
    ASSERT_EQ(lo, 1);
    ASSERT_EQ(hi, 9);
}

TEST(runner, "order_pair handles equal values") {
    int lo = 4, hi = 4;
    order_pair(lo, hi);
    ASSERT_EQ(lo, 4);
    ASSERT_EQ(hi, 4);
}

TESTKIT_MAIN(runner)
