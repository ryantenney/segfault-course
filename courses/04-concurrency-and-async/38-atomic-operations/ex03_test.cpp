// Exercise 03 -- Tests (read-only)

#include <testkit/testkit.h>
#include <thread>
#include <vector>

#include "ex03.h"

static testkit::TestRunner runner("04-38-ex03: Atomic Flag Spinlock");

TEST(runner, "lock and unlock do not deadlock") {
    Spinlock sl;
    sl.lock();
    sl.unlock();
    // If we reach here, basic lock/unlock works
    ASSERT_TRUE(true);
}

TEST(runner, "lock can be acquired after unlock") {
    Spinlock sl;
    sl.lock();
    sl.unlock();
    sl.lock();
    sl.unlock();
    ASSERT_TRUE(true);
}

TEST(runner, "spinlock protects a critical section") {
    Spinlock sl;
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

TESTKIT_MAIN(runner)
