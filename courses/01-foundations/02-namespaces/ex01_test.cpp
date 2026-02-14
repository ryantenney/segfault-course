// Exercise 01 — Tests (read-only)
//
// These tests call the functions using their fully-qualified names
// (math::add, math::subtract, math::multiply).

#include <testkit/testkit.h>

#include "ex01.h"

static testkit::TestRunner runner("01-02-ex01: Wrap in a Namespace");

TEST(runner, "math::add returns the sum") {
    ASSERT_EQ(math::add(2, 3), 5);
    ASSERT_EQ(math::add(-1, 1), 0);
    ASSERT_EQ(math::add(0, 0), 0);
}

TEST(runner, "math::subtract returns the difference") {
    ASSERT_EQ(math::subtract(10, 3), 7);
    ASSERT_EQ(math::subtract(5, 5), 0);
    ASSERT_EQ(math::subtract(0, 4), -4);
}

TEST(runner, "math::multiply returns the product") {
    ASSERT_EQ(math::multiply(3, 4), 12);
    ASSERT_EQ(math::multiply(-2, 5), -10);
    ASSERT_EQ(math::multiply(0, 99), 0);
}

TESTKIT_MAIN(runner)
