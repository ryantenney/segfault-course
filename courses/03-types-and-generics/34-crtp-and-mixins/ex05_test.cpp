// Exercise 05 -- Tests (read-only)
//
// Verifies composable policy-based design.

#include <testkit/testkit.h>
#include "ex05.h"

static testkit::TestRunner runner("03-34-ex05: Composable Policies");

// --- FixedStorage tests ---

TEST(runner, "FixedBuffer capacity is 64") {
    FixedBuffer buf;
    buf.put(0, 0);  // gate
    ASSERT_EQ(buf.capacity(), 64u);
}

TEST(runner, "FixedBuffer stores and retrieves values") {
    FixedBuffer buf;
    buf.put(0, 42);
    buf.put(10, 99);
    ASSERT_EQ(buf.read(0), 42);
    ASSERT_EQ(buf.read(10), 99);
}

TEST(runner, "FixedBuffer initializes to zero") {
    FixedBuffer buf;
    buf.put(0, 0);  // gate
    ASSERT_EQ(buf.read(5), 0);
    ASSERT_EQ(buf.read(63), 0);
}

// --- DynamicStorage tests ---

TEST(runner, "DynamicBuffer starts with zero capacity") {
    DynamicBuffer buf;
    buf.put(0, 1);  // gate -- triggers resize
    // After storing at index 0, capacity should be at least 1.
    ASSERT_TRUE(buf.capacity() >= 1u);
}

TEST(runner, "DynamicBuffer auto-resizes on store") {
    DynamicBuffer buf;
    buf.put(9, 100);
    ASSERT_TRUE(buf.capacity() >= 10u);
    ASSERT_EQ(buf.read(9), 100);
}

TEST(runner, "DynamicBuffer fills new slots with zero") {
    DynamicBuffer buf;
    buf.put(5, 42);
    ASSERT_EQ(buf.read(0), 0);
    ASSERT_EQ(buf.read(4), 0);
    ASSERT_EQ(buf.read(5), 42);
}

TEST(runner, "DynamicBuffer overwrites existing values") {
    DynamicBuffer buf;
    buf.put(3, 10);
    buf.put(3, 20);
    ASSERT_EQ(buf.read(3), 20);
}

// --- ThreadSafe variants compile and work ---

TEST(runner, "ThreadSafeFixedBuffer stores and retrieves") {
    ThreadSafeFixedBuffer buf;
    buf.put(0, 7);
    ASSERT_EQ(buf.read(0), 7);
}

TEST(runner, "ThreadSafeDynamicBuffer stores and retrieves") {
    ThreadSafeDynamicBuffer buf;
    buf.put(2, 55);
    ASSERT_EQ(buf.read(2), 55);
}

TESTKIT_MAIN(runner)
