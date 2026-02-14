// Exercise 05 — Tests (read-only)
//
// These tests verify that:
//   1. Tasks submitted before shutdown complete.
//   2. submit() after shutdown throws.
//   3. shutdown() is idempotent.

#include <testkit/testkit.h>
#include <atomic>
#include <chrono>
#include <stdexcept>
#include <thread>
#include "ex05.h"

static testkit::TestRunner runner("04-40-ex05: Graceful Shutdown");

TEST(runner, "tasks complete before shutdown returns") {
    ShutdownPool pool(2);
    std::atomic<int> count{0};
    for (int i = 0; i < 5; ++i) {
        pool.submit([&count] { count.fetch_add(1); });
    }
    pool.shutdown();
    ASSERT_EQ(count.load(), 5);
}

TEST(runner, "submit after shutdown throws") {
    ShutdownPool pool(2);
    pool.shutdown();
    ASSERT_THROWS(pool.submit([] { return 1; }), std::runtime_error);
}

TEST(runner, "shutdown is idempotent") {
    ShutdownPool pool(2);
    pool.submit([] {});
    pool.shutdown();
    pool.shutdown();  // should not deadlock or throw
    ASSERT_TRUE(pool.is_shutdown());
}

TEST(runner, "future from pre-shutdown submit resolves") {
    ShutdownPool pool(2);
    auto f = pool.submit([] { return 42; });
    pool.shutdown();
    ASSERT_EQ(f.get(), 42);
}

TESTKIT_MAIN(runner)
