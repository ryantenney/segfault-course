// Exercise 02 — Tests (read-only)
//
// These tests verify that:
//   1. deferred_compute returns a valid future.
//   2. The future resolves to n * n + 1.
//   3. The future uses deferred execution.

#include <testkit/testkit.h>
#include <future>
#include "ex02.h"

static testkit::TestRunner runner("04-39-ex02: Launch Policies");

TEST(runner, "deferred_compute(5) returns 26") {
    auto f = deferred_compute(5);
    ASSERT_EQ(f.get(), 26);
}

TEST(runner, "deferred_compute(0) returns 1") {
    auto f = deferred_compute(0);
    ASSERT_EQ(f.get(), 1);
}

TEST(runner, "deferred_compute(-3) returns 10") {
    auto f = deferred_compute(-3);
    ASSERT_EQ(f.get(), 10);
}

TEST(runner, "deferred future reports deferred status before get") {
    auto f = deferred_compute(7);
    // A deferred future reports deferred status when checked with zero timeout.
    auto status = f.wait_for(std::chrono::milliseconds(0));
    ASSERT_TRUE(status == std::future_status::deferred);
    ASSERT_EQ(f.get(), 50);
}

TESTKIT_MAIN(runner)
