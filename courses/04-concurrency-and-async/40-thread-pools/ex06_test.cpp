// Exercise 06 — Tests (read-only)
//
// These tests verify that:
//   1. completed_count increases as tasks finish.
//   2. pending_count reflects queued tasks.
//   3. active_count reflects running tasks.

#include <testkit/testkit.h>
#include <atomic>
#include <chrono>
#include <thread>
#include "ex06.h"

static testkit::TestRunner runner("04-40-ex06: Pool Statistics");

TEST(runner, "completed_count starts at zero") {
    StatsPool pool(2);
    ASSERT_EQ(pool.completed_count(), 0);
}

TEST(runner, "completed_count increments after tasks finish") {
    StatsPool pool(2);
    auto f1 = pool.submit([] { return 1; });
    auto f2 = pool.submit([] { return 2; });
    f1.get();
    f2.get();
    // Give worker threads a moment to update the counter.
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    ASSERT_TRUE(pool.completed_count() >= 2);
}

TEST(runner, "active_count reflects running tasks") {
    StatsPool pool(2);
    std::atomic<bool> hold{true};
    std::atomic<bool> started{false};
    auto f = pool.submit([&] {
        started.store(true);
        while (hold.load()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
    });
    // Wait for task to start.
    while (!started.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
    ASSERT_TRUE(pool.active_count() >= 1);
    hold.store(false);
    f.get();
}

TEST(runner, "pending_count reflects queued tasks") {
    // Use 1 worker to control scheduling.
    StatsPool pool(1);
    std::atomic<bool> hold{true};
    std::atomic<bool> started{false};
    // Block the single worker.
    pool.submit([&] {
        started.store(true);
        while (hold.load()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
    });
    while (!started.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
    // Now the worker is busy; submit more tasks that will queue up.
    auto f1 = pool.submit([] { return 1; });
    auto f2 = pool.submit([] { return 2; });
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    ASSERT_TRUE(pool.pending_count() >= 2);
    hold.store(false);
    f1.get();
    f2.get();
}

TESTKIT_MAIN(runner)
