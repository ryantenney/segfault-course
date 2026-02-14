// Exercise 02 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex02.h"

static testkit::TestRunner runner("02-14-ex02: Reserve and Capacity");

TEST(runner, "reserved_push returns correct elements") {
    auto v = reserved_push(5);
    ASSERT_EQ(v.size(), 5u);
    ASSERT_EQ(v[0], 0);
    ASSERT_EQ(v[1], 1);
    ASSERT_EQ(v[4], 4);
}

TEST(runner, "reserved_push does not reallocate") {
    auto v = reserved_push(100);
    // After reserving 100 and pushing 100, capacity should still be 100
    // (no reallocation happened).
    ASSERT_EQ(v.size(), 100u);
    ASSERT_EQ(v.capacity(), 100u);
}

TEST(runner, "capacity_after_reserve returns at least n") {
    ASSERT_TRUE(capacity_after_reserve(50) >= 50u);
    ASSERT_TRUE(capacity_after_reserve(1000) >= 1000u);
}

TEST(runner, "capacity_after_reserve on empty vector starts at 0 size") {
    // reserve doesn't change size, just capacity
    ASSERT_TRUE(capacity_after_reserve(10) >= 10u);
}

TEST(runner, "grow_and_report counts capacity changes") {
    // An empty vector pushing 0 elements should have 0 capacity changes
    ASSERT_EQ(grow_and_report(0), 0);

    // Pushing 1 element: capacity goes from 0 to 1 (1 change)
    ASSERT_EQ(grow_and_report(1), 1);

    // Pushing many elements should trigger multiple reallocations
    int changes = grow_and_report(100);
    ASSERT_TRUE(changes > 1);
    ASSERT_TRUE(changes < 100);  // far fewer than 100 changes
}

TESTKIT_MAIN(runner)
