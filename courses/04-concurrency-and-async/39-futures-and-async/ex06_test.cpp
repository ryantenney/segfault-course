// Exercise 06 — Tests (read-only)
//
// These tests verify that:
//   1. slow_compute returns the correct result.
//   2. wait_for can be used to poll a future's readiness.

#include <testkit/testkit.h>
#include <future>
#include <chrono>
#include "ex06.h"

static testkit::TestRunner runner("04-39-ex06: wait_for with Timeout");

TEST(runner, "slow_compute(5) returns 10") {
    auto f = slow_compute(5);
    ASSERT_EQ(f.get(), 10);
}

TEST(runner, "slow_compute(0) returns 0") {
    auto f = slow_compute(0);
    ASSERT_EQ(f.get(), 0);
}

TEST(runner, "slow_compute(-3) returns -6") {
    auto f = slow_compute(-3);
    ASSERT_EQ(f.get(), -6);
}

TEST(runner, "wait_for eventually returns ready") {
    auto f = slow_compute(7);
    // Wait a generous amount — the computation should finish quickly.
    auto status = f.wait_for(std::chrono::seconds(5));
    ASSERT_TRUE(status == std::future_status::ready);
    ASSERT_EQ(f.get(), 14);
}

TESTKIT_MAIN(runner)
