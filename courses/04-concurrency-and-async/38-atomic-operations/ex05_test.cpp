// Exercise 05 -- Tests (read-only)

#include <testkit/testkit.h>
#include <thread>
#include <vector>

#include "ex05.h"

static testkit::TestRunner runner("04-38-ex05: Atomic Accumulation");

TEST(runner, "counter starts at zero") {
    StatsCounter sc;
    ASSERT_EQ(sc.get(), 0);
}

TEST(runner, "add increases the value") {
    StatsCounter sc;
    sc.add(5);
    ASSERT_EQ(sc.get(), 5);
    sc.add(3);
    ASSERT_EQ(sc.get(), 8);
}

TEST(runner, "add returns the previous value") {
    StatsCounter sc;
    int old = sc.add(10);
    ASSERT_EQ(old, 0);
    old = sc.add(5);
    ASSERT_EQ(old, 10);
}

TEST(runner, "subtract decreases the value") {
    StatsCounter sc;
    sc.add(20);
    sc.subtract(7);
    ASSERT_EQ(sc.get(), 13);
}

TEST(runner, "subtract returns the previous value") {
    StatsCounter sc;
    sc.add(100);
    int old = sc.subtract(30);
    ASSERT_EQ(old, 100);
    old = sc.subtract(20);
    ASSERT_EQ(old, 70);
}

TEST(runner, "add and subtract can go negative") {
    StatsCounter sc;
    sc.subtract(5);
    ASSERT_EQ(sc.get(), -5);
    sc.add(3);
    ASSERT_EQ(sc.get(), -2);
}

TEST(runner, "concurrent adds and subtracts produce correct net result") {
    StatsCounter sc;
    // Gate: ensure single-threaded ops work
    sc.add(0);
    sc.subtract(0);

    constexpr int threads = 4;
    constexpr int per_thread = 1000;
    std::vector<std::thread> tv;

    // Each thread adds per_thread and subtracts per_thread/2
    for (int i = 0; i < threads; ++i) {
        tv.emplace_back([&sc] {
            for (int j = 0; j < per_thread; ++j) {
                sc.add(1);
            }
            for (int j = 0; j < per_thread / 2; ++j) {
                sc.subtract(1);
            }
        });
    }

    for (auto& t : tv) {
        t.join();
    }

    ASSERT_EQ(sc.get(), threads * (per_thread - per_thread / 2));
}

TESTKIT_MAIN(runner)
