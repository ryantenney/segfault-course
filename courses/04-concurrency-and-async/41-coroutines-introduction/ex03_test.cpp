// Exercise 03 — Tests (read-only)
//
// These tests verify that:
//   1. compute_task(n) returns n * n.
//   2. The task completes eagerly (result available immediately).

#include <testkit/testkit.h>
#include "ex03.h"

static testkit::TestRunner runner("04-41-ex03: Simple Coroutine Task");

TEST(runner, "compute_task(5) returns 25") {
    ex03_gate();
    auto task = compute_task(5);
    ASSERT_TRUE(task.done());
    ASSERT_EQ(task.result(), 25);
}

TEST(runner, "compute_task(0) returns 0") {
    ex03_gate();
    auto task = compute_task(0);
    ASSERT_EQ(task.result(), 0);
}

TEST(runner, "compute_task(-3) returns 9") {
    ex03_gate();
    auto task = compute_task(-3);
    ASSERT_EQ(task.result(), 9);
}

TEST(runner, "compute_task(1) returns 1") {
    ex03_gate();
    auto task = compute_task(1);
    ASSERT_EQ(task.result(), 1);
}

TESTKIT_MAIN(runner)
