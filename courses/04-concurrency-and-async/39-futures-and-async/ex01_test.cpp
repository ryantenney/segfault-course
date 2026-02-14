// Exercise 01 — Tests (read-only)
//
// These tests verify that:
//   1. async_square returns a valid future.
//   2. The future resolves to n * n.
//   3. Multiple async calls can run concurrently.

#include <testkit/testkit.h>
#include <future>
#include "ex01.h"

static testkit::TestRunner runner("04-39-ex01: Async Computation");

TEST(runner, "async_square(5) returns 25") {
    auto f = async_square(5);
    ASSERT_EQ(f.get(), 25);
}

TEST(runner, "async_square(0) returns 0") {
    auto f = async_square(0);
    ASSERT_EQ(f.get(), 0);
}

TEST(runner, "async_square(-4) returns 16") {
    auto f = async_square(-4);
    ASSERT_EQ(f.get(), 16);
}

TEST(runner, "multiple async_square calls work concurrently") {
    auto f1 = async_square(3);
    auto f2 = async_square(7);
    auto f3 = async_square(10);
    ASSERT_EQ(f1.get(), 9);
    ASSERT_EQ(f2.get(), 49);
    ASSERT_EQ(f3.get(), 100);
}

TESTKIT_MAIN(runner)
