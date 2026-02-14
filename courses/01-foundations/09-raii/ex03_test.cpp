// Exercise 03 — Tests (read-only)
//
// Verifies the ScopedLock RAII wrapper and SafeCounter.

#include <mutex>
#include <thread>
#include <testkit/testkit.h>
#include "ex03.h"

static testkit::TestRunner runner("01-09-ex03: Scoped Lock (Manual)");

TEST(runner, "ScopedLock locks and unlocks") {
    std::mutex mtx;
    {
        ScopedLock lock(mtx);
        // If we're here, the mutex is locked.
        // try_lock should fail because it's already locked.
        ASSERT_FALSE(mtx.try_lock());
    }
    // After scope exit, mutex should be unlocked.
    // try_lock should succeed.
    ASSERT_TRUE(mtx.try_lock());
    mtx.unlock();
}

TEST(runner, "SafeCounter starts at zero") {
    SafeCounter counter;
    ASSERT_EQ(counter.get(), 0);
}

TEST(runner, "SafeCounter increments correctly") {
    SafeCounter counter;
    counter.increment();
    counter.increment();
    counter.increment();
    ASSERT_EQ(counter.get(), 3);
}

TEST(runner, "SafeCounter is thread-safe") {
    SafeCounter counter;
    counter.get(); // gates on TODO() — skips if not yet implemented
    constexpr int iterations = 1000;
    constexpr int num_threads = 4;

    auto worker = [&]() {
        for (int i = 0; i < iterations; ++i) {
            counter.increment();
        }
    };

    std::thread threads[num_threads];
    for (auto& t : threads) {
        t = std::thread(worker);
    }
    for (auto& t : threads) {
        t.join();
    }

    ASSERT_EQ(counter.get(), num_threads * iterations);
}

TESTKIT_MAIN(runner)
