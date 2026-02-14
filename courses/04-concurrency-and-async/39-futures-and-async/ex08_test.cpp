// Exercise 08 — Tests (read-only)
//
// These tests verify that:
//   1. make_task returns a valid packaged_task.
//   2. The task produces the correct result when invoked.
//   3. The associated future receives the result.

#include <testkit/testkit.h>
#include <future>
#include "ex08.h"

static testkit::TestRunner runner("04-39-ex08: Packaged Task");

TEST(runner, "make_task(5) produces 30 (5*5 + 5)") {
    auto task = make_task(5);
    auto f = task.get_future();
    task();
    ASSERT_EQ(f.get(), 30);
}

TEST(runner, "make_task(0) produces 0") {
    auto task = make_task(0);
    auto f = task.get_future();
    task();
    ASSERT_EQ(f.get(), 0);
}

TEST(runner, "make_task(3) produces 12 (3*3 + 3)") {
    auto task = make_task(3);
    auto f = task.get_future();
    task();
    ASSERT_EQ(f.get(), 12);
}

TEST(runner, "future is not ready before task is invoked") {
    auto task = make_task(7);
    auto f = task.get_future();
    auto status = f.wait_for(std::chrono::milliseconds(0));
    ASSERT_TRUE(status == std::future_status::timeout);
    task();
    ASSERT_EQ(f.get(), 56);  // 7*7 + 7
}

TESTKIT_MAIN(runner)
