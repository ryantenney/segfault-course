// Exercise 06 — Tests (read-only)
//
// These tests verify that:
//   1. post_delayed() schedules callbacks at the correct tick.
//   2. Callbacks execute in tick order.
//   3. Same-tick callbacks execute in insertion order.

#include <testkit/testkit.h>
#include <vector>
#include "ex06.h"

static testkit::TestRunner runner("04-42-ex06: Timer in Event Loop");

TEST(runner, "post executes callback immediately (tick 0)") {
    TimerEventLoop loop;
    int value = 0;
    loop.post([&value] { value = 42; });
    loop.run();
    ASSERT_EQ(value, 42);
}

TEST(runner, "post_delayed executes after delay") {
    TimerEventLoop loop;
    std::vector<int> order;
    loop.post_delayed(2, [&order] { order.push_back(2); });
    loop.post_delayed(1, [&order] { order.push_back(1); });
    loop.post([&order] { order.push_back(0); });
    loop.run();
    ASSERT_EQ(order.size(), 3u);
    ASSERT_EQ(order[0], 0);
    ASSERT_EQ(order[1], 1);
    ASSERT_EQ(order[2], 2);
}

TEST(runner, "same-tick callbacks execute in insertion order") {
    TimerEventLoop loop;
    std::vector<int> order;
    loop.post_delayed(1, [&order] { order.push_back(1); });
    loop.post_delayed(1, [&order] { order.push_back(2); });
    loop.post_delayed(1, [&order] { order.push_back(3); });
    loop.run();
    ASSERT_EQ(order.size(), 3u);
    ASSERT_EQ(order[0], 1);
    ASSERT_EQ(order[1], 2);
    ASSERT_EQ(order[2], 3);
}

TEST(runner, "run returns count of executed callbacks") {
    TimerEventLoop loop;
    loop.post([] {});
    loop.post_delayed(5, [] {});
    loop.post_delayed(3, [] {});
    ASSERT_EQ(loop.run(), 3);
}

TEST(runner, "current_tick advances to last executed callback") {
    TimerEventLoop loop;
    loop.post_delayed(10, [] {});
    loop.run();
    ASSERT_EQ(loop.current_tick(), 10);
}

TEST(runner, "run on empty loop returns 0") {
    TimerEventLoop loop;
    ASSERT_EQ(loop.run(), 0);
}

TESTKIT_MAIN(runner)
