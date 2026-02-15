// Exercise 04 -- Tests (read-only)

#include <testkit/testkit.h>
#include <thread>
#include <vector>

#include "ex04.h"

static testkit::TestRunner runner("05-47-ex04: Thread-safe Pool");

TEST(runner, "acquire returns an object from the pool") {
    ThreadSafePool<int> pool(std::vector<int>{10, 20, 30});
    int obj = pool.acquire();
    ASSERT_TRUE(obj == 10 || obj == 20 || obj == 30);
    ASSERT_EQ(pool.available(), std::size_t(2));
}

TEST(runner, "release puts an object back") {
    ThreadSafePool<int> pool(std::vector<int>{5});
    int obj = pool.acquire();
    ASSERT_EQ(pool.available(), std::size_t(0));
    pool.release(obj);
    ASSERT_EQ(pool.available(), std::size_t(1));
}

TEST(runner, "acquire all then release all round-trips") {
    ThreadSafePool<int> pool(std::vector<int>{1, 2, 3});
    int a = pool.acquire();
    int b = pool.acquire();
    int c = pool.acquire();
    ASSERT_EQ(pool.available(), std::size_t(0));
    pool.release(a);
    pool.release(b);
    pool.release(c);
    ASSERT_EQ(pool.available(), std::size_t(3));
}

TEST(runner, "acquire blocks until release from another thread") {
    ThreadSafePool<int> pool(std::vector<int>{1});

    // Gate: verify basic acquire/release works single-threaded
    int gate = pool.acquire();
    pool.release(gate);

    // Now test blocking behavior
    int obj = pool.acquire();  // pool is now empty
    ASSERT_EQ(pool.available(), std::size_t(0));

    std::thread releaser([&pool, obj] {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        pool.release(obj);
    });

    int acquired = pool.acquire();  // should block until releaser runs
    ASSERT_EQ(acquired, 1);
    releaser.join();
}

TEST(runner, "concurrent acquire and release does not corrupt pool") {
    ThreadSafePool<int> pool(std::vector<int>{1, 2, 3, 4, 5});

    // Gate: verify basic acquire/release works first
    {
        int g = pool.acquire();
        pool.release(g);
    }

    constexpr int iterations = 100;
    auto worker = [&pool] {
        for (int i = 0; i < iterations; ++i) {
            int obj = pool.acquire();
            std::this_thread::yield();
            pool.release(obj);
        }
    };

    std::thread t1(worker);
    std::thread t2(worker);
    std::thread t3(worker);

    t1.join();
    t2.join();
    t3.join();

    // All objects should be back in the pool
    ASSERT_EQ(pool.available(), std::size_t(5));
}

TESTKIT_MAIN(runner)
