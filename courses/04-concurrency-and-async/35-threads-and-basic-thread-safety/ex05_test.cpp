// Exercise 05 — Tests (read-only)
//
// These tests verify that:
//   1. safe_increment increments by 1.
//   2. safe_increment is safe under concurrent access.

#include <testkit/testkit.h>
#include <atomic>
#include <thread>
#include <vector>
#include "ex05.h"

static testkit::TestRunner runner("04-35-ex05: Identify a Data Race");

TEST(runner, "safe_increment increments by 1") {
    std::atomic<int> counter{0};
    safe_increment(counter);  // gates on TODO()
    ASSERT_EQ(counter.load(), 1);
}

TEST(runner, "safe_increment increments multiple times") {
    std::atomic<int> counter{0};
    safe_increment(counter);  // gate
    safe_increment(counter);
    safe_increment(counter);
    ASSERT_EQ(counter.load(), 3);
}

TEST(runner, "safe_increment is correct under concurrent access") {
    std::atomic<int> counter{0};
    safe_increment(counter);  // gate
    counter.store(0);         // reset

    constexpr int num_threads = 8;
    constexpr int increments_per_thread = 10000;

    std::vector<std::thread> threads;
    threads.reserve(num_threads);
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&counter] {
            for (int j = 0; j < increments_per_thread; ++j) {
                safe_increment(counter);
            }
        });
    }
    for (auto& t : threads) {
        t.join();
    }
    ASSERT_EQ(counter.load(), num_threads * increments_per_thread);
}

TESTKIT_MAIN(runner)
