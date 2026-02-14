// Exercise 04 — Tests (read-only)
//
// These tests verify that:
//   1. submit() works with int return type.
//   2. submit() works with std::string return type.
//   3. submit() works with void return type.

#include <testkit/testkit.h>
#include <future>
#include <string>
#include "ex04.h"

static testkit::TestRunner runner("04-40-ex04: Submit Different Types");

TEST(runner, "submit returning int") {
    TypedPool pool(2);
    auto f = pool.submit([] { return 42; });
    ASSERT_EQ(f.get(), 42);
}

TEST(runner, "submit returning string") {
    TypedPool pool(2);
    auto f = pool.submit([] { return std::string("hello"); });
    ASSERT_EQ(f.get(), std::string("hello"));
}

TEST(runner, "submit returning void") {
    TypedPool pool(2);
    std::atomic<bool> done{false};
    auto f = pool.submit([&done] { done.store(true); });
    f.get();  // wait for completion
    ASSERT_TRUE(done.load());
}

TEST(runner, "mixed types in same pool") {
    TypedPool pool(2);
    auto f_int = pool.submit([] { return 99; });
    auto f_str = pool.submit([] { return std::string("world"); });
    std::atomic<int> val{0};
    auto f_void = pool.submit([&val] { val.store(7); });
    ASSERT_EQ(f_int.get(), 99);
    ASSERT_EQ(f_str.get(), std::string("world"));
    f_void.get();
    ASSERT_EQ(val.load(), 7);
}

TESTKIT_MAIN(runner)
