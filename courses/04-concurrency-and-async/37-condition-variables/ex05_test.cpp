// Exercise 05 -- Tests (read-only)

#include <testkit/testkit.h>
#include <atomic>
#include <thread>

#include "ex05.h"

static testkit::TestRunner runner("04-37-ex05: One-shot Event");

TEST(runner, "event starts unsignaled") {
    Event e;
    // Gate: call signal to test TODO
    e.signal();
    Event fresh;
    ASSERT_FALSE(fresh.is_signaled());
}

TEST(runner, "signal sets the signaled flag") {
    Event e;
    e.signal();
    ASSERT_TRUE(e.is_signaled());
}

TEST(runner, "signal is idempotent") {
    Event e;
    e.signal();
    e.signal();  // should not crash or change state
    ASSERT_TRUE(e.is_signaled());
}

TEST(runner, "wait returns immediately if already signaled") {
    Event e;
    e.signal();
    e.wait();  // should not block
    ASSERT_TRUE(e.is_signaled());
}

TEST(runner, "wait blocks until signal from another thread") {
    Event e;
    // Gate
    {
        Event gate;
        gate.signal();
    }

    std::thread t([&e] {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        e.signal();
    });

    e.wait();
    ASSERT_TRUE(e.is_signaled());
    t.join();
}

TEST(runner, "multiple waiters all unblock on signal") {
    Event e;
    // Gate
    {
        Event gate;
        gate.signal();
    }

    std::atomic<int> count{0};

    std::thread t1([&] { e.wait(); count.fetch_add(1); });
    std::thread t2([&] { e.wait(); count.fetch_add(1); });
    std::thread t3([&] { e.wait(); count.fetch_add(1); });

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    e.signal();

    t1.join();
    t2.join();
    t3.join();

    ASSERT_EQ(count.load(), 3);
}

TESTKIT_MAIN(runner)
