// Exercise 07 — Tests (read-only)
//
// These tests verify that:
//   1. resize() can grow the pool.
//   2. resize() can shrink the pool.
//   3. Tasks still execute correctly after resize.

#include <testkit/testkit.h>
#include <chrono>
#include <thread>
#include "ex07.h"

static testkit::TestRunner runner("04-40-ex07: Pool Resize");

TEST(runner, "initial size is correct") {
    ResizablePool pool(2);
    ASSERT_EQ(pool.size(), static_cast<std::size_t>(2));
}

TEST(runner, "resize grows the pool") {
    ResizablePool pool(2);
    pool.resize(6);
    ASSERT_EQ(pool.size(), static_cast<std::size_t>(6));
}

TEST(runner, "resize shrinks the pool") {
    ResizablePool pool(4);
    pool.resize(2);
    // Give threads time to stop.
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    ASSERT_EQ(pool.size(), static_cast<std::size_t>(2));
}

TEST(runner, "tasks work after growing") {
    ResizablePool pool(1);
    pool.resize(4);
    auto f = pool.submit([] { return 42; });
    ASSERT_EQ(f.get(), 42);
}

TEST(runner, "tasks work after shrinking") {
    ResizablePool pool(4);
    pool.resize(1);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    auto f = pool.submit([] { return 99; });
    ASSERT_EQ(f.get(), 99);
}

TEST(runner, "resize to same size is a no-op") {
    ResizablePool pool(3);
    pool.resize(3);
    ASSERT_EQ(pool.size(), static_cast<std::size_t>(3));
    auto f = pool.submit([] { return 7; });
    ASSERT_EQ(f.get(), 7);
}

TESTKIT_MAIN(runner)
