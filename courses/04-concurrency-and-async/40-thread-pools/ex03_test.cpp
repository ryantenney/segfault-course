// Exercise 03 — Tests (read-only)
//
// These tests verify that:
//   1. submit() returns a future that resolves to the correct value.
//   2. Multiple submissions produce correct results.

#include <testkit/testkit.h>
#include <future>
#include "ex03.h"

static testkit::TestRunner runner("04-40-ex03: Submit with Future");

TEST(runner, "submit returns future with correct result") {
    FuturePool pool(2);
    auto f = pool.submit([] { return 42; });
    ASSERT_EQ(f.get(), 42);
}

TEST(runner, "submit captures arguments via lambda") {
    FuturePool pool(2);
    int x = 7;
    auto f = pool.submit([x] { return x * x; });
    ASSERT_EQ(f.get(), 49);
}

TEST(runner, "multiple submissions produce correct results") {
    FuturePool pool(4);
    auto f1 = pool.submit([] { return 10; });
    auto f2 = pool.submit([] { return 20; });
    auto f3 = pool.submit([] { return 30; });
    ASSERT_EQ(f1.get(), 10);
    ASSERT_EQ(f2.get(), 20);
    ASSERT_EQ(f3.get(), 30);
}

TEST(runner, "submit with computation") {
    FuturePool pool(2);
    auto f = pool.submit([] {
        int sum = 0;
        for (int i = 1; i <= 100; ++i) sum += i;
        return sum;
    });
    ASSERT_EQ(f.get(), 5050);
}

TESTKIT_MAIN(runner)
