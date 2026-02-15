// Exercise 03 -- Tests (read-only)

#include <testkit/testkit.h>
#include <string>

#include "ex03.h"

static testkit::TestRunner runner("05-47-ex03: Pool with Factory");

TEST(runner, "pool starts empty with zero created") {
    int counter = 0;
    FactoryPool<int> pool([&counter] { return ++counter; }, 5);
    ASSERT_EQ(pool.idle_count(), std::size_t(0));
    ASSERT_EQ(pool.total_created(), std::size_t(0));
}

TEST(runner, "acquire creates object via factory when pool is empty") {
    int counter = 0;
    FactoryPool<int> pool([&counter] { return ++counter; }, 5);
    int obj = pool.acquire();
    ASSERT_EQ(obj, 1);
    ASSERT_EQ(pool.total_created(), std::size_t(1));
}

TEST(runner, "release makes object available for reuse") {
    int counter = 0;
    FactoryPool<int> pool([&counter] { return ++counter; }, 5);
    int obj = pool.acquire();
    pool.release(obj);
    ASSERT_EQ(pool.idle_count(), std::size_t(1));
    // Next acquire should reuse, not create
    int reused = pool.acquire();
    ASSERT_EQ(pool.total_created(), std::size_t(1));
    (void)reused;
}

TEST(runner, "factory is called for each new object up to max") {
    int counter = 0;
    FactoryPool<int> pool([&counter] { return ++counter; }, 3);
    int a = pool.acquire();
    int b = pool.acquire();
    int c = pool.acquire();
    ASSERT_EQ(pool.total_created(), std::size_t(3));
    (void)a; (void)b; (void)c;
}

TEST(runner, "acquire throws when pool is at capacity") {
    int counter = 0;
    FactoryPool<int> pool([&counter] { return ++counter; }, 2);
    pool.acquire();
    pool.acquire();
    ASSERT_THROWS(pool.acquire(), std::runtime_error);
}

TEST(runner, "released objects are reused before creating new ones") {
    int counter = 0;
    FactoryPool<int> pool([&counter] { return ++counter; }, 2);
    int a = pool.acquire();   // creates #1
    pool.release(a);          // now 1 idle
    int b = pool.acquire();   // reuses, no new creation
    ASSERT_EQ(pool.total_created(), std::size_t(1));
    (void)b;
}

TESTKIT_MAIN(runner)
