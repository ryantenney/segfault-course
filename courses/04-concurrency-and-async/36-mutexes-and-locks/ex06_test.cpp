// Exercise 06 — Tests (read-only)
//
// These tests verify that:
//   1. ReadWriteMap basic operations work.
//   2. Concurrent reads don't block each other.

#include <testkit/testkit.h>
#include <thread>
#include <vector>
#include <atomic>
#include "ex06.h"

static testkit::TestRunner runner("04-36-ex06: Shared Mutex for Readers");

TEST(runner, "get returns -1 for missing key") {
    ReadWriteMap m;
    ASSERT_EQ(m.get("missing"), -1);  // gates on TODO() in get()
}

TEST(runner, "put and get work") {
    ReadWriteMap m;
    m.put("x", 42);  // gates on TODO() in put()
    ASSERT_EQ(m.get("x"), 42);
}

TEST(runner, "contains returns false for missing key") {
    ReadWriteMap m;
    ASSERT_FALSE(m.contains("missing"));  // gates on TODO() in contains()
}

TEST(runner, "contains returns true for existing key") {
    ReadWriteMap m;
    m.put("x", 1);  // gate
    ASSERT_TRUE(m.contains("x"));
}

TEST(runner, "put overwrites existing value") {
    ReadWriteMap m;
    m.put("x", 10);  // gate
    m.put("x", 20);
    ASSERT_EQ(m.get("x"), 20);
}

TEST(runner, "concurrent reads and writes are safe") {
    ReadWriteMap m;
    m.put("counter", 0);  // gate

    constexpr int num_writers = 2;
    constexpr int num_readers = 4;
    constexpr int writes_per_thread = 1000;

    std::atomic<bool> done{false};
    std::vector<std::thread> threads;

    // Writers
    for (int w = 0; w < num_writers; ++w) {
        threads.emplace_back([&m, w] {
            for (int i = 0; i < writes_per_thread; ++i) {
                m.put("key" + std::to_string(w) + "_" + std::to_string(i), i);
            }
        });
    }

    // Readers
    for (int r = 0; r < num_readers; ++r) {
        threads.emplace_back([&m, &done] {
            while (!done.load()) {
                m.get("counter");
                m.contains("counter");
            }
        });
    }

    // Wait for writers to finish
    for (int i = 0; i < num_writers; ++i) {
        threads[i].join();
    }
    done.store(true);

    // Wait for readers to finish
    for (int i = num_writers; i < static_cast<int>(threads.size()); ++i) {
        threads[i].join();
    }

    // Verify some writes
    ASSERT_EQ(m.get("key0_999"), 999);
    ASSERT_EQ(m.get("key1_999"), 999);
}

TESTKIT_MAIN(runner)
