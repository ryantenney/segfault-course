// Exercise 08 -- Tests (read-only)
//
// Verifies thread-safe logger. Tests run single-threaded first (gate),
// then concurrent.

#include <testkit/testkit.h>
#include <string>
#include <thread>
#include <vector>
#include "ex08.h"

static testkit::TestRunner runner("05-50-ex08: Thread-safe Logger");

TEST(runner, "log stores a message (single-threaded gate)") {
    ThreadSafeLogger logger;
    logger.log("hello");
    auto e = logger.entries();
    ASSERT_EQ(static_cast<int>(e.size()), 1);
    ASSERT_EQ(e[0], std::string("hello"));
}

TEST(runner, "size returns entry count") {
    ThreadSafeLogger logger;
    logger.log("hello");  // gate
    ASSERT_EQ(logger.size(), 1);
    logger.log("world");
    ASSERT_EQ(logger.size(), 2);
}

TEST(runner, "entries returns a snapshot copy") {
    ThreadSafeLogger logger;
    logger.log("first");  // gate
    auto snapshot = logger.entries();
    logger.log("second");
    // snapshot should not include "second"
    ASSERT_EQ(static_cast<int>(snapshot.size()), 1);
    ASSERT_EQ(static_cast<int>(logger.entries().size()), 2);
}

TEST(runner, "concurrent writes from multiple threads") {
    ThreadSafeLogger logger;
    logger.log("gate");  // gate: skip if not implemented

    // Reset for the real test: create a new logger.
    ThreadSafeLogger test_logger;
    const int num_threads = 8;

    std::vector<std::thread> threads;
    threads.reserve(num_threads);
    for (int t = 0; t < num_threads; ++t) {
        threads.emplace_back([&test_logger]() {
            for (int i = 0; i < 100; ++i) {
                test_logger.log("msg");
            }
        });
    }
    for (auto& th : threads) {
        th.join();
    }

    ASSERT_EQ(test_logger.size(), num_threads * 100);
}

TEST(runner, "concurrent reads and writes") {
    ThreadSafeLogger logger;
    logger.log("gate");  // gate

    ThreadSafeLogger test_logger;
    const int num_writers = 4;

    std::vector<std::thread> threads;
    // Writers
    for (int w = 0; w < num_writers; ++w) {
        threads.emplace_back([&test_logger]() {
            for (int i = 0; i < 50; ++i) {
                test_logger.log("w");
            }
        });
    }
    // Readers
    for (int r = 0; r < 2; ++r) {
        threads.emplace_back([&test_logger]() {
            for (int i = 0; i < 50; ++i) {
                auto snap = test_logger.entries();
                (void)snap.size();
            }
        });
    }
    for (auto& th : threads) {
        th.join();
    }

    ASSERT_EQ(test_logger.size(), num_writers * 50);
}

TESTKIT_MAIN(runner)
