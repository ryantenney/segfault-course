// Exercise 04 — Tests (read-only)
//
// These tests verify that:
//   1. count_until_stopped increments the counter.
//   2. count_until_stopped stops when the token is triggered.

#include <testkit/testkit.h>
#include <atomic>
#include <chrono>
#include <thread>
#include "ex04.h"

static testkit::TestRunner runner("04-35-ex04: jthread and stop_token");

TEST(runner, "count_until_stopped stops immediately with pre-requested token") {
    std::atomic<int> counter{0};
    std::stop_source source;
    source.request_stop();  // request stop before calling
    count_until_stopped(source.get_token(), counter);  // gates on TODO()
    // Counter may be 0 since stop was already requested
    ASSERT_TRUE(counter.load() >= 0);
}

TEST(runner, "count_until_stopped increments counter") {
    std::atomic<int> counter{0};
    std::stop_source source;
    source.request_stop();
    count_until_stopped(source.get_token(), counter);  // gate

    // Now test with a jthread that runs briefly
    counter.store(0);
    {
        std::jthread jt([&counter](std::stop_token token) {
            count_until_stopped(token, counter);
        });
        // Let it run for a short while
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        jt.request_stop();
    }
    ASSERT_TRUE(counter.load() > 0);
}

TEST(runner, "count_until_stopped respects stop request") {
    std::atomic<int> counter{0};
    std::stop_source source;
    source.request_stop();
    count_until_stopped(source.get_token(), counter);  // gate

    counter.store(0);
    {
        std::jthread jt([&counter](std::stop_token token) {
            count_until_stopped(token, counter);
        });
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        jt.request_stop();
    }

    // After stop, the counter should no longer increase
    int value_after_stop = counter.load();
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    ASSERT_EQ(counter.load(), value_after_stop);
}

TESTKIT_MAIN(runner)
