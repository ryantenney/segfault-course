// Exercise 06 -- Tests (read-only)

#include <testkit/testkit.h>
#include <thread>
#include <vector>

#include "ex06.h"

static testkit::TestRunner runner("04-38-ex06: Spinlock with Backoff");

TEST(runner, "lock and unlock do not deadlock") {
    BackoffSpinlock sl;
    sl.lock();
    sl.unlock();
    ASSERT_TRUE(true);
}

TEST(runner, "lock can be reacquired after unlock") {
    BackoffSpinlock sl;
    sl.lock();
    sl.unlock();
    sl.lock();
    sl.unlock();
    ASSERT_TRUE(true);
}

TEST(runner, "spinlock protects a critical section") {
    BackoffSpinlock sl;
    // Gate: ensure lock/unlock works
    sl.lock();
    sl.unlock();

    int counter = 0;
    constexpr int threads = 4;
    constexpr int per_thread = 1000;
    std::vector<std::thread> tv;

    for (int i = 0; i < threads; ++i) {
        tv.emplace_back([&] {
            for (int j = 0; j < per_thread; ++j) {
                sl.lock();
                ++counter;
                sl.unlock();
            }
        });
    }

    for (auto& t : tv) {
        t.join();
    }

    ASSERT_EQ(counter, threads * per_thread);
}

TEST(runner, "multiple lock-unlock cycles work correctly") {
    BackoffSpinlock sl;
    for (int i = 0; i < 100; ++i) {
        sl.lock();
        sl.unlock();
    }
    ASSERT_TRUE(true);
}

TESTKIT_MAIN(runner)
