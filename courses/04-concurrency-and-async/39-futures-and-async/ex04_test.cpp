// Exercise 04 — Tests (read-only)
//
// These tests verify that:
//   1. async_divide returns correct results.
//   2. Division by zero propagates as std::invalid_argument through the future.

#include <testkit/testkit.h>
#include <future>
#include <stdexcept>
#include "ex04.h"

static testkit::TestRunner runner("04-39-ex04: Exception Propagation");

TEST(runner, "async_divide(10, 2) returns 5") {
    auto f = async_divide(10, 2);
    ASSERT_EQ(f.get(), 5);
}

TEST(runner, "async_divide(7, 3) returns 2 (integer division)") {
    auto f = async_divide(7, 3);
    ASSERT_EQ(f.get(), 2);
}

TEST(runner, "async_divide(-12, 4) returns -3") {
    auto f = async_divide(-12, 4);
    ASSERT_EQ(f.get(), -3);
}

TEST(runner, "async_divide by zero throws std::invalid_argument") {
    auto f = async_divide(5, 0);
    ASSERT_THROWS(f.get(), std::invalid_argument);
}

TESTKIT_MAIN(runner)
