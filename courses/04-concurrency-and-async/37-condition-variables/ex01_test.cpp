// Exercise 01 -- Tests (read-only)

#include <testkit/testkit.h>
#include <thread>

#include "ex01.h"

static testkit::TestRunner runner("04-37-ex01: Basic Wait/Notify");

TEST(runner, "notifier starts not ready") {
    Notifier n;
    // Gate: calling notify will throw TODO() if not implemented
    n.notify();
    // If we get here, notify is implemented; check initial state via is_ready
    // (After notify, ready should be true, so create a fresh one to check default)
    Notifier fresh;
    ASSERT_FALSE(fresh.is_ready());
}

TEST(runner, "notify sets the ready flag") {
    Notifier n;
    n.notify();
    ASSERT_TRUE(n.is_ready());
}

TEST(runner, "wait returns immediately if already notified") {
    Notifier n;
    n.notify();
    // Should not block because ready is already true
    n.wait();
    ASSERT_TRUE(n.is_ready());
}

TEST(runner, "wait blocks until notify is called from another thread") {
    Notifier n;
    // Gate: ensure notify works first
    {
        Notifier gate;
        gate.notify();
    }

    std::thread t([&n] {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        n.notify();
    });

    n.wait();
    ASSERT_TRUE(n.is_ready());
    t.join();
}

TESTKIT_MAIN(runner)
