// Exercise 01 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex01.h"

static testkit::TestRunner runner("02-20-ex01: Callback Registration");

TEST(runner, "has_callback returns false before registration") {
    CallbackHolder holder;
    holder.has_callback();  // gate: triggers TODO()
    ASSERT_FALSE(holder.has_callback());
}

TEST(runner, "has_callback returns true after registration") {
    CallbackHolder holder;
    holder.register_callback([](int) {});
    ASSERT_TRUE(holder.has_callback());
}

TEST(runner, "fire invokes the stored callback") {
    CallbackHolder holder;
    int received = 0;
    holder.register_callback([&received](int v) { received = v; });
    holder.fire(42);
    ASSERT_EQ(received, 42);
}

TEST(runner, "fire with no callback does nothing") {
    CallbackHolder holder;
    holder.register_callback([](int) {});  // register first so has_callback works
    CallbackHolder empty;
    // Should not throw or crash
    ASSERT_NO_THROW(empty.fire(99));
}

TEST(runner, "registering a new callback replaces the old one") {
    CallbackHolder holder;
    int count_a = 0, count_b = 0;
    holder.register_callback([&count_a](int) { ++count_a; });
    holder.fire(1);
    holder.register_callback([&count_b](int) { ++count_b; });
    holder.fire(2);
    ASSERT_EQ(count_a, 1);
    ASSERT_EQ(count_b, 1);
}

TESTKIT_MAIN(runner)
