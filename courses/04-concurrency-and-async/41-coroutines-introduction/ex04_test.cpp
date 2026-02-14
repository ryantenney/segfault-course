// Exercise 04 — Tests (read-only)
//
// These tests verify that:
//   1. double_value(n) returns n * 2.
//   2. double_and_add(n, m) awaits double_value and adds m.

#include <testkit/testkit.h>
#include "ex04.h"

static testkit::TestRunner runner("04-41-ex04: Chained Coroutines");

TEST(runner, "double_value(5) returns 10") {
    ex04_gate();
    auto task = double_value(5);
    ASSERT_EQ(task.result(), 10);
}

TEST(runner, "double_value(-3) returns -6") {
    ex04_gate();
    auto task = double_value(-3);
    ASSERT_EQ(task.result(), -6);
}

TEST(runner, "double_and_add(5, 3) returns 13") {
    ex04_gate();
    auto task = double_and_add(5, 3);
    ASSERT_EQ(task.result(), 13);
}

TEST(runner, "double_and_add(0, 0) returns 0") {
    ex04_gate();
    auto task = double_and_add(0, 0);
    ASSERT_EQ(task.result(), 0);
}

TEST(runner, "double_and_add(10, -5) returns 15") {
    ex04_gate();
    auto task = double_and_add(10, -5);
    ASSERT_EQ(task.result(), 15);
}

TESTKIT_MAIN(runner)
