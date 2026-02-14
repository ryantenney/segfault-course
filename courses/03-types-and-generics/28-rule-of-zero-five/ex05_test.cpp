// Exercise 05 -- Tests (read-only)
//
// Verifies all five special members of DynamicBuffer.

#include <testkit/testkit.h>
#include "ex05.h"

static testkit::TestRunner runner("03-28-ex05: Rule of Five");

TEST(runner, "constructor creates zero-initialized buffer") {
    DynamicBuffer buf(4);
    ASSERT_EQ(buf.size(), 4u);
    ASSERT_EQ(buf[0], 0);
    ASSERT_EQ(buf[1], 0);
    ASSERT_EQ(buf[2], 0);
    ASSERT_EQ(buf[3], 0);
}

TEST(runner, "copy constructor creates deep copy") {
    DynamicBuffer a(3);
    a[0] = 10;
    a[1] = 20;
    a[2] = 30;

    DynamicBuffer b(a);

    ASSERT_EQ(b.size(), 3u);
    ASSERT_EQ(b[0], 10);
    ASSERT_EQ(b[1], 20);
    ASSERT_EQ(b[2], 30);
    ASSERT_TRUE(a.data() != b.data());
}

TEST(runner, "copy constructor: modifying original does not affect copy") {
    DynamicBuffer a(2);
    a[0] = 5;
    a[1] = 6;

    DynamicBuffer b(a);
    a[0] = 999;

    ASSERT_EQ(b[0], 5);
}

TEST(runner, "move constructor steals resources") {
    DynamicBuffer a(3);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;
    const int* original_data = a.data();

    DynamicBuffer b(std::move(a));

    ASSERT_EQ(b.size(), 3u);
    ASSERT_EQ(b[0], 1);
    ASSERT_EQ(b[1], 2);
    ASSERT_EQ(b[2], 3);
    ASSERT_TRUE(b.data() == original_data);

    // Source should be in a null/empty state
    ASSERT_TRUE(a.data() == nullptr);
    ASSERT_EQ(a.size(), 0u);
}

TEST(runner, "copy assignment creates deep copy") {
    DynamicBuffer a(3);
    a[0] = 10;
    a[1] = 20;
    a[2] = 30;

    DynamicBuffer b(1);
    b = a;

    ASSERT_EQ(b.size(), 3u);
    ASSERT_EQ(b[0], 10);
    ASSERT_EQ(b[1], 20);
    ASSERT_EQ(b[2], 30);
    ASSERT_TRUE(a.data() != b.data());
}

TEST(runner, "copy assignment: self-assignment is safe") {
    DynamicBuffer a(3);
    a[0] = 42;
    a[1] = 43;
    a[2] = 44;

    a = a;

    ASSERT_EQ(a.size(), 3u);
    ASSERT_EQ(a[0], 42);
}

TEST(runner, "move assignment steals resources") {
    DynamicBuffer a(2);
    a[0] = 7;
    a[1] = 8;
    const int* original_data = a.data();

    DynamicBuffer b(1);
    b = std::move(a);

    ASSERT_EQ(b.size(), 2u);
    ASSERT_EQ(b[0], 7);
    ASSERT_EQ(b[1], 8);
    ASSERT_TRUE(b.data() == original_data);

    ASSERT_TRUE(a.data() == nullptr);
    ASSERT_EQ(a.size(), 0u);
}

TEST(runner, "move assignment: self-assignment is safe") {
    DynamicBuffer a(3);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;

    a = std::move(a);

    // After self-move, the object should still be in a valid state.
    // We just check that size and data are consistent (not crashed).
    ASSERT_TRUE(a.size() == 3u || a.size() == 0u);
}

TESTKIT_MAIN(runner)
