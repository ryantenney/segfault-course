// Exercise 01 -- Tests (read-only)

#include <testkit/testkit.h>
#include <thread>
#include <vector>

#include "ex01.h"

static testkit::TestRunner runner("04-38-ex01: Atomic Counter");

TEST(runner, "counter starts at zero") {
    AtomicCounter c;
    // Gate on get()
    int val = c.get();
    ASSERT_EQ(val, 0);
}

TEST(runner, "increment increases the count") {
    AtomicCounter c;
    c.increment();
    ASSERT_EQ(c.get(), 1);
    c.increment();
    c.increment();
    ASSERT_EQ(c.get(), 3);
}

TEST(runner, "reset sets the count to zero") {
    AtomicCounter c;
    c.increment();
    c.increment();
    c.reset();
    ASSERT_EQ(c.get(), 0);
}

TEST(runner, "concurrent increments produce correct total") {
    AtomicCounter c;
    // Gate: verify single-threaded ops work
    c.increment();
    c.reset();

    constexpr int threads = 4;
    constexpr int per_thread = 1000;
    std::vector<std::thread> tv;

    for (int i = 0; i < threads; ++i) {
        tv.emplace_back([&c] {
            for (int j = 0; j < per_thread; ++j) {
                c.increment();
            }
        });
    }

    for (auto& t : tv) {
        t.join();
    }

    ASSERT_EQ(c.get(), threads * per_thread);
}

TESTKIT_MAIN(runner)
