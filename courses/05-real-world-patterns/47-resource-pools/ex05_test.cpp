// Exercise 05 -- Tests (read-only)

#include <testkit/testkit.h>
#include <string>

#include "ex05.h"

static testkit::TestRunner runner("05-47-ex05: Pool with Health Check");

TEST(runner, "acquire creates object via factory on first call") {
    int counter = 0;
    HealthCheckPool<int> pool(
        [&counter] { return ++counter; },
        [](const int&) { return true; },
        5);
    int obj = pool.acquire();
    ASSERT_EQ(obj, 1);
    ASSERT_EQ(pool.total_created(), std::size_t(1));
}

TEST(runner, "healthy idle object is reused") {
    int counter = 0;
    HealthCheckPool<int> pool(
        [&counter] { return ++counter; },
        [](const int&) { return true; },  // always healthy
        5);
    int obj = pool.acquire();
    pool.release(obj);
    int reused = pool.acquire();
    ASSERT_EQ(pool.total_created(), std::size_t(1));
    (void)reused;
}

TEST(runner, "unhealthy idle object is discarded") {
    int counter = 0;
    HealthCheckPool<int> pool(
        [&counter] { return ++counter; },
        [](const int& val) { return val != 1; },  // 1 is unhealthy
        5);
    int obj = pool.acquire();  // creates 1
    ASSERT_EQ(obj, 1);
    pool.release(obj);         // put 1 back
    int next = pool.acquire(); // 1 fails check, discarded, creates 2
    ASSERT_EQ(next, 2);
    ASSERT_EQ(pool.discarded(), std::size_t(1));
    ASSERT_EQ(pool.total_created(), std::size_t(2));
}

TEST(runner, "multiple unhealthy objects are all discarded") {
    int counter = 0;
    HealthCheckPool<int> pool(
        [&counter] { return ++counter; },
        [](const int& val) { return val > 3; },  // only >3 are healthy
        10);

    // Create and release 1, 2, 3 (all will be unhealthy on reuse)
    int a = pool.acquire();
    int b = pool.acquire();
    int c = pool.acquire();
    pool.release(c);
    pool.release(b);
    pool.release(a);

    // acquire should discard all three and create 4
    int obj = pool.acquire();
    ASSERT_EQ(obj, 4);
    ASSERT_EQ(pool.discarded(), std::size_t(3));
    ASSERT_EQ(pool.total_created(), std::size_t(4));
}

TEST(runner, "throws when at capacity with no healthy objects") {
    int counter = 0;
    HealthCheckPool<int> pool(
        [&counter] { return ++counter; },
        [](const int&) { return true; },
        2);
    int a = pool.acquire();
    int b = pool.acquire();
    (void)a; (void)b;
    ASSERT_THROWS(pool.acquire(), std::runtime_error);
}

TEST(runner, "discarding frees capacity for new objects") {
    int counter = 0;
    HealthCheckPool<int> pool(
        [&counter] { return ++counter; },
        [](const int& val) { return val >= 3; },  // 1,2 unhealthy
        2);
    int a = pool.acquire();  // creates 1
    int b = pool.acquire();  // creates 2
    pool.release(a);
    pool.release(b);
    // Now at max_size=2, but both are unhealthy.
    // acquire should discard them (freeing capacity) and create 3.
    int obj = pool.acquire();
    ASSERT_EQ(obj, 3);
    ASSERT_EQ(pool.discarded(), std::size_t(2));
}

TESTKIT_MAIN(runner)
