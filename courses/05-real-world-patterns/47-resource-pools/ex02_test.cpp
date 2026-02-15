// Exercise 02 -- Tests (read-only)

#include <testkit/testkit.h>
#include <string>
#include <vector>

#include "ex02.h"

static testkit::TestRunner runner("05-47-ex02: RAII Pool Handle");

TEST(runner, "handle provides access to the held object") {
    Pool02<std::string> pool(std::vector<std::string>{"hello"});
    std::string obj = pool.acquire();
    PoolHandle<std::string> handle(std::move(obj), &pool);
    ASSERT_EQ(*handle, std::string("hello"));
}

TEST(runner, "handle auto-returns object to pool on destruction") {
    Pool02<int> pool(std::vector<int>{42});
    ASSERT_EQ(pool.available(), std::size_t(1));
    {
        int obj = pool.acquire();
        ASSERT_EQ(pool.available(), std::size_t(0));
        PoolHandle<int> handle(std::move(obj), &pool);
        ASSERT_EQ(*handle, 42);
    }
    // After handle is destroyed, the object should be back in the pool.
    ASSERT_EQ(pool.available(), std::size_t(1));
}

TEST(runner, "move constructor transfers ownership") {
    Pool02<int> pool(std::vector<int>{7});
    int obj = pool.acquire();
    PoolHandle<int> h1(std::move(obj), &pool);
    PoolHandle<int> h2(std::move(h1));
    ASSERT_EQ(*h2, 7);
    // h1 moved-from, h2 owns it now
}

TEST(runner, "moved-from handle does not double-return") {
    Pool02<int> pool(std::vector<int>{99});
    {
        int obj = pool.acquire();
        PoolHandle<int> h1(std::move(obj), &pool);
        {
            PoolHandle<int> h2(std::move(h1));
            // h2 destroyed here — returns to pool
        }
        ASSERT_EQ(pool.available(), std::size_t(1));
        // h1 destroyed here — should NOT return again
    }
    // Should still be exactly 1
    ASSERT_EQ(pool.available(), std::size_t(1));
}

TEST(runner, "arrow operator provides member access") {
    Pool02<std::string> pool(std::vector<std::string>{"test"});
    std::string obj = pool.acquire();
    PoolHandle<std::string> handle(std::move(obj), &pool);
    ASSERT_EQ(handle->size(), std::size_t(4));
}

TESTKIT_MAIN(runner)
