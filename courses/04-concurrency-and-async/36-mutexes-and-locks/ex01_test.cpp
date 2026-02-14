// Exercise 01 — Tests (read-only)
//
// These tests verify that:
//   1. GuardedCounter operations work correctly.
//   2. The counter is thread-safe.

#include <testkit/testkit.h>
#include <thread>
#include <vector>
#include "ex01.h"

static testkit::TestRunner runner("04-36-ex01: Protect Shared Data");

TEST(runner, "counter starts at 0") {
    GuardedCounter c;
    ASSERT_EQ(c.get(), 0);  // gates on TODO() in get()
}

TEST(runner, "increment increases the counter") {
    GuardedCounter c;
    c.increment();  // gates on TODO() in increment()
    ASSERT_EQ(c.get(), 1);
}

TEST(runner, "decrement decreases the counter") {
    GuardedCounter c;
    c.increment();  // gate
    c.decrement();  // gates on TODO() in decrement()
    ASSERT_EQ(c.get(), 0);
}

TEST(runner, "mixed operations produce correct result") {
    GuardedCounter c;
    c.increment();  // gate
    c.increment();
    c.increment();
    c.decrement();
    ASSERT_EQ(c.get(), 2);
}

TEST(runner, "counter is thread-safe") {
    GuardedCounter c;
    c.increment();  // gate

    GuardedCounter counter;
    constexpr int num_threads = 8;
    constexpr int ops_per_thread = 10000;

    std::vector<std::thread> threads;
    threads.reserve(num_threads);
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&counter] {
            for (int j = 0; j < ops_per_thread; ++j) {
                counter.increment();
            }
        });
    }
    for (auto& t : threads) {
        t.join();
    }
    ASSERT_EQ(counter.get(), num_threads * ops_per_thread);
}

TESTKIT_MAIN(runner)
