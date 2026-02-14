// Exercise 07 -- Tests (read-only)

#include <testkit/testkit.h>
#include <thread>

#include "ex07.h"

static testkit::TestRunner runner("04-37-ex07: Timed Wait");

TEST(runner, "event starts unsignaled") {
    TimedEvent te;
    // Gate on signal
    te.signal();
    TimedEvent fresh;
    ASSERT_FALSE(fresh.is_signaled());
}

TEST(runner, "signal sets the flag") {
    TimedEvent te;
    te.signal();
    ASSERT_TRUE(te.is_signaled());
}

TEST(runner, "wait_for_ms returns true immediately if already signaled") {
    TimedEvent te;
    te.signal();
    bool result = te.wait_for_ms(1000);
    ASSERT_TRUE(result);
}

TEST(runner, "wait_for_ms returns false on timeout") {
    TimedEvent te;
    // Gate: ensure signal works
    {
        TimedEvent gate;
        gate.signal();
    }

    // Wait for a short time on an unsignaled event
    bool result = te.wait_for_ms(10);
    ASSERT_FALSE(result);
    ASSERT_FALSE(te.is_signaled());
}

TEST(runner, "wait_for_ms returns true when signaled before timeout") {
    TimedEvent te;
    // Gate
    {
        TimedEvent gate;
        gate.signal();
    }

    std::thread t([&te] {
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        te.signal();
    });

    // Wait long enough for the signal to arrive
    bool result = te.wait_for_ms(2000);
    ASSERT_TRUE(result);
    ASSERT_TRUE(te.is_signaled());
    t.join();
}

TEST(runner, "wait_for_ms with zero timeout returns current state") {
    TimedEvent te;
    // Gate
    {
        TimedEvent gate;
        gate.signal();
    }

    ASSERT_FALSE(te.wait_for_ms(0));
    te.signal();
    ASSERT_TRUE(te.wait_for_ms(0));
}

TESTKIT_MAIN(runner)
