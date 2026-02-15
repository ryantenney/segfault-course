// Exercise 06 -- Tests (read-only)

#include <testkit/testkit.h>
#include <string>
#include <vector>

#include "ex06.h"

static testkit::TestRunner runner("05-47-ex06: Pool Statistics");

TEST(runner, "initial counts are correct") {
    StatsPool<int> pool(std::vector<int>{1, 2, 3});
    ASSERT_EQ(pool.idle_count(), std::size_t(3));
    ASSERT_EQ(pool.active_count(), std::size_t(0));
    ASSERT_EQ(pool.total_created(), std::size_t(3));
}

TEST(runner, "acquire increments active and decrements idle") {
    StatsPool<int> pool(std::vector<int>{10, 20});
    pool.acquire();
    ASSERT_EQ(pool.active_count(), std::size_t(1));
    ASSERT_EQ(pool.idle_count(), std::size_t(1));
}

TEST(runner, "release decrements active and increments idle") {
    StatsPool<int> pool(std::vector<int>{10, 20});
    int obj = pool.acquire();
    pool.release(obj);
    ASSERT_EQ(pool.active_count(), std::size_t(0));
    ASSERT_EQ(pool.idle_count(), std::size_t(2));
}

TEST(runner, "total_created does not change on acquire/release") {
    StatsPool<int> pool(std::vector<int>{1, 2, 3});
    int a = pool.acquire();
    int b = pool.acquire();
    pool.release(a);
    pool.release(b);
    ASSERT_EQ(pool.total_created(), std::size_t(3));
}

TEST(runner, "acquire all then release all tracks correctly") {
    StatsPool<std::string> pool(
        std::vector<std::string>{"x", "y", "z"});
    std::string s1 = pool.acquire();
    std::string s2 = pool.acquire();
    std::string s3 = pool.acquire();
    ASSERT_EQ(pool.active_count(), std::size_t(3));
    ASSERT_EQ(pool.idle_count(), std::size_t(0));
    pool.release(std::move(s1));
    pool.release(std::move(s2));
    pool.release(std::move(s3));
    ASSERT_EQ(pool.active_count(), std::size_t(0));
    ASSERT_EQ(pool.idle_count(), std::size_t(3));
}

TEST(runner, "acquire on empty pool throws") {
    StatsPool<int> pool(std::vector<int>{});
    ASSERT_THROWS(pool.acquire(), std::runtime_error);
}

TESTKIT_MAIN(runner)
