// Exercise 05 — Tests (read-only)
//
// These tests verify that:
//   1. post() queues callbacks.
//   2. run() executes them in FIFO order.
//   3. run() returns the number of callbacks executed.

#include <testkit/testkit.h>
#include <vector>
#include "ex05.h"

static testkit::TestRunner runner("04-42-ex05: Simulated Event Loop");

TEST(runner, "post and run executes callback") {
    EventLoop loop;
    int value = 0;
    loop.post([&value] { value = 42; });
    int executed = loop.run();
    ASSERT_EQ(value, 42);
    ASSERT_EQ(executed, 1);
}

TEST(runner, "callbacks execute in FIFO order") {
    EventLoop loop;
    std::vector<int> order;
    loop.post([&order] { order.push_back(1); });
    loop.post([&order] { order.push_back(2); });
    loop.post([&order] { order.push_back(3); });
    loop.run();
    ASSERT_EQ(order.size(), 3u);
    ASSERT_EQ(order[0], 1);
    ASSERT_EQ(order[1], 2);
    ASSERT_EQ(order[2], 3);
}

TEST(runner, "run returns count of executed callbacks") {
    EventLoop loop;
    loop.post([] {});
    loop.post([] {});
    loop.post([] {});
    ASSERT_EQ(loop.run(), 3);
}

TEST(runner, "run on empty loop returns 0") {
    EventLoop loop;
    ASSERT_EQ(loop.run(), 0);
}

TEST(runner, "pending reports number of queued callbacks") {
    EventLoop loop;
    ASSERT_EQ(loop.pending(), 0u);
    loop.post([] {});
    loop.post([] {});
    ASSERT_EQ(loop.pending(), 2u);
    loop.run();
    ASSERT_EQ(loop.pending(), 0u);
}

TEST(runner, "callbacks can post more callbacks") {
    EventLoop loop;
    int value = 0;
    loop.post([&loop, &value] {
        value = 1;
        loop.post([&value] { value = 2; });
    });
    int executed = loop.run();
    ASSERT_EQ(value, 2);
    ASSERT_EQ(executed, 2);
}

TESTKIT_MAIN(runner)
