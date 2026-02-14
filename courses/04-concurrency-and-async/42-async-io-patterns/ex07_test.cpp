// Exercise 07 — Tests (read-only)
//
// These tests verify that:
//   1. Operations complete in tick order, not submission order.
//   2. pending_count() tracks submitted vs completed.
//   3. Multiple operations at the same tick complete in submission order.

#include <testkit/testkit.h>
#include <vector>
#include <string>
#include "ex07.h"

static testkit::TestRunner runner("04-42-ex07: Multiple Pending Operations");

TEST(runner, "single operation completes") {
    TimerEventLoop loop;
    OperationTracker tracker;
    tracker.submit("read", 1, loop);
    loop.run();
    ASSERT_EQ(tracker.completed().size(), 1u);
    ASSERT_EQ(tracker.completed()[0], "read");
}

TEST(runner, "operations complete in tick order") {
    TimerEventLoop loop;
    OperationTracker tracker;
    tracker.submit("slow", 10, loop);
    tracker.submit("fast", 1, loop);
    tracker.submit("medium", 5, loop);
    loop.run();
    auto& done = tracker.completed();
    ASSERT_EQ(done.size(), 3u);
    ASSERT_EQ(done[0], "fast");
    ASSERT_EQ(done[1], "medium");
    ASSERT_EQ(done[2], "slow");
}

TEST(runner, "pending_count tracks progress") {
    TimerEventLoop loop;
    OperationTracker tracker;
    tracker.submit("a", 1, loop);
    tracker.submit("b", 2, loop);
    ASSERT_EQ(tracker.pending_count(), 2);
    loop.run();
    ASSERT_EQ(tracker.pending_count(), 0);
}

TEST(runner, "same-tick operations complete in submission order") {
    TimerEventLoop loop;
    OperationTracker tracker;
    tracker.submit("first", 5, loop);
    tracker.submit("second", 5, loop);
    tracker.submit("third", 5, loop);
    loop.run();
    auto& done = tracker.completed();
    ASSERT_EQ(done.size(), 3u);
    ASSERT_EQ(done[0], "first");
    ASSERT_EQ(done[1], "second");
    ASSERT_EQ(done[2], "third");
}

TEST(runner, "immediate operations complete first") {
    TimerEventLoop loop;
    OperationTracker tracker;
    tracker.submit("delayed", 5, loop);
    tracker.submit("immediate", 0, loop);
    loop.run();
    auto& done = tracker.completed();
    ASSERT_EQ(done.size(), 2u);
    ASSERT_EQ(done[0], "immediate");
    ASSERT_EQ(done[1], "delayed");
}

TESTKIT_MAIN(runner)
