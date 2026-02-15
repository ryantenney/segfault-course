// Exercise 07 -- Tests (read-only)

#include <testkit/testkit.h>
#include <chrono>
#include <thread>
#include <vector>

#include "ex07.h"

static testkit::TestRunner runner("05-47-ex07: Pool with Timeout");

using ms = std::chrono::milliseconds;

TEST(runner, "try_acquire returns object when pool is non-empty") {
    TimeoutPool<int> pool(std::vector<int>{42});
    auto result = pool.try_acquire(ms(100));
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(result.value(), 42);
}

TEST(runner, "try_acquire returns nullopt on empty pool after timeout") {
    TimeoutPool<int> pool(std::vector<int>{});
    auto start = std::chrono::steady_clock::now();
    auto result = pool.try_acquire(ms(50));
    auto elapsed = std::chrono::steady_clock::now() - start;
    ASSERT_FALSE(result.has_value());
    // Should have waited at least ~30ms (generous margin)
    auto elapsed_ms = std::chrono::duration_cast<ms>(elapsed).count();
    ASSERT_TRUE(elapsed_ms >= 30);
}

TEST(runner, "release makes object available") {
    TimeoutPool<int> pool(std::vector<int>{5});
    auto obj = pool.try_acquire(ms(100));
    ASSERT_TRUE(obj.has_value());
    ASSERT_EQ(pool.available(), std::size_t(0));
    pool.release(obj.value());
    ASSERT_EQ(pool.available(), std::size_t(1));
}

TEST(runner, "try_acquire succeeds when release happens before timeout") {
    TimeoutPool<int> pool(std::vector<int>{});

    // Gate: ensure release works
    pool.release(99);
    auto gate = pool.try_acquire(ms(100));
    ASSERT_TRUE(gate.has_value());

    // Now test: pool is empty, release from another thread before timeout
    std::thread releaser([&pool] {
        std::this_thread::sleep_for(ms(30));
        pool.release(77);
    });

    auto result = pool.try_acquire(ms(500));
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(result.value(), 77);
    releaser.join();
}

TEST(runner, "try_acquire times out when no release happens") {
    TimeoutPool<int> pool(std::vector<int>{});

    // Gate: ensure basic functionality works
    pool.release(1);
    auto gate = pool.try_acquire(ms(100));
    ASSERT_TRUE(gate.has_value());

    // Pool is now empty; no one will release
    auto result = pool.try_acquire(ms(50));
    ASSERT_FALSE(result.has_value());
}

TESTKIT_MAIN(runner)
