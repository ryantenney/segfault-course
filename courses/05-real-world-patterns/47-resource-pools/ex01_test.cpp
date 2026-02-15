// Exercise 01 -- Tests (read-only)

#include <testkit/testkit.h>
#include <string>
#include <vector>

#include "ex01.h"

static testkit::TestRunner runner("05-47-ex01: Basic Object Pool");

TEST(runner, "pool starts with correct number of available objects") {
    Pool<int> pool(std::vector<int>{1, 2, 3});
    ASSERT_EQ(pool.available(), std::size_t(3));
}

TEST(runner, "acquire returns an object and decreases count") {
    Pool<int> pool(std::vector<int>{10, 20});
    int obj = pool.acquire();
    ASSERT_TRUE(obj == 10 || obj == 20);
    ASSERT_EQ(pool.available(), std::size_t(1));
}

TEST(runner, "release returns an object and increases count") {
    Pool<int> pool(std::vector<int>{42});
    int obj = pool.acquire();
    ASSERT_EQ(pool.available(), std::size_t(0));
    pool.release(obj);
    ASSERT_EQ(pool.available(), std::size_t(1));
}

TEST(runner, "acquire on empty pool throws runtime_error") {
    Pool<int> pool(std::vector<int>{});
    ASSERT_THROWS(pool.acquire(), std::runtime_error);
}

TEST(runner, "acquire all then release all round-trips correctly") {
    Pool<std::string> pool(std::vector<std::string>{"a", "b", "c"});
    std::string s1 = pool.acquire();
    std::string s2 = pool.acquire();
    std::string s3 = pool.acquire();
    ASSERT_EQ(pool.available(), std::size_t(0));
    pool.release(std::move(s1));
    pool.release(std::move(s2));
    pool.release(std::move(s3));
    ASSERT_EQ(pool.available(), std::size_t(3));
}

TESTKIT_MAIN(runner)
