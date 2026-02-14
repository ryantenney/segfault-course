// Exercise 02 — Tests (read-only)
//
// These tests verify that:
//   1. WorkerPool executes submitted tasks.
//   2. Multiple tasks are all executed.

#include <testkit/testkit.h>
#include <atomic>
#include <chrono>
#include <thread>
#include "ex02.h"

static testkit::TestRunner runner("04-40-ex02: Worker Loop");

TEST(runner, "submitted task is executed") {
    WorkerPool pool(2);
    std::atomic<int> result{0};
    pool.submit([&result] { result.store(42); });
    // Give the worker time to execute.
    for (int i = 0; i < 100 && result.load() == 0; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    ASSERT_EQ(result.load(), 42);
}

TEST(runner, "multiple tasks are all executed") {
    WorkerPool pool(2);
    std::atomic<int> count{0};
    for (int i = 0; i < 10; ++i) {
        pool.submit([&count] { count.fetch_add(1); });
    }
    for (int i = 0; i < 200 && count.load() < 10; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    ASSERT_EQ(count.load(), 10);
}

TEST(runner, "tasks run concurrently on multiple workers") {
    WorkerPool pool(4);
    std::atomic<int> max_concurrent{0};
    std::atomic<int> current{0};

    for (int i = 0; i < 8; ++i) {
        pool.submit([&] {
            int c = current.fetch_add(1) + 1;
            // Update max if we see higher concurrency.
            int prev = max_concurrent.load();
            while (c > prev && !max_concurrent.compare_exchange_weak(prev, c)) {}
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            current.fetch_sub(1);
        });
    }
    // Wait for all tasks.
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    // With 4 workers and 8 tasks, we expect at least 2 to overlap.
    ASSERT_TRUE(max_concurrent.load() >= 2);
}

TESTKIT_MAIN(runner)
