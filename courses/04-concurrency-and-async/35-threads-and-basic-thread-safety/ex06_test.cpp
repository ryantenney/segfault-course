// Exercise 06 — Tests (read-only)
//
// These tests verify that:
//   1. ThreadSafeCounter starts at 0.
//   2. increment() and get() work correctly.
//   3. The counter is safe under concurrent access.

#include <testkit/testkit.h>
#include <thread>
#include <vector>
#include "ex06.h"

static testkit::TestRunner runner("04-35-ex06: Fix the Data Race");

TEST(runner, "counter starts at 0") {
    ThreadSafeCounter c;
    ASSERT_EQ(c.get(), 0);  // gates on TODO() in get()
}

TEST(runner, "increment increases the counter") {
    ThreadSafeCounter c;
    c.increment();  // gates on TODO() in increment()
    ASSERT_EQ(c.get(), 1);
}

TEST(runner, "multiple increments work") {
    ThreadSafeCounter c;
    c.increment();  // gate
    c.increment();
    c.increment();
    ASSERT_EQ(c.get(), 3);
}

TEST(runner, "counter is correct under concurrent access") {
    ThreadSafeCounter c;
    c.increment();  // gate
    // Reset by creating a new counter
    ThreadSafeCounter counter;

    constexpr int num_threads = 8;
    constexpr int increments_per_thread = 10000;

    std::vector<std::thread> threads;
    threads.reserve(num_threads);
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&counter] {
            for (int j = 0; j < increments_per_thread; ++j) {
                counter.increment();
            }
        });
    }
    for (auto& t : threads) {
        t.join();
    }
    ASSERT_EQ(counter.get(), num_threads * increments_per_thread);
}

TESTKIT_MAIN(runner)
