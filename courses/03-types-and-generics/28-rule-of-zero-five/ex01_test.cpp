// Exercise 01 -- Tests (read-only)
//
// Verifies that IntArray correctly implements copy operations (Rule of Three).

#include <testkit/testkit.h>
#include "ex01.h"

static testkit::TestRunner runner("03-28-ex01: Spot the Bug (Rule of Three)");

TEST(runner, "copy constructor creates independent copy") {
    IntArray a(3);
    a[0] = 10;
    a[1] = 20;
    a[2] = 30;

    IntArray b(a);

    ASSERT_EQ(b.size(), 3u);
    ASSERT_EQ(b[0], 10);
    ASSERT_EQ(b[1], 20);
    ASSERT_EQ(b[2], 30);

    // Modifying original should not affect copy
    a[0] = 999;
    ASSERT_EQ(b[0], 10);
}

TEST(runner, "copy constructor allocates separate memory") {
    IntArray a(5);
    IntArray b(a);

    // The data pointers must be different (deep copy)
    ASSERT_TRUE(a.data() != b.data());
}

TEST(runner, "copy assignment copies values") {
    IntArray a(3);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;

    IntArray b(1);
    b = a;

    ASSERT_EQ(b.size(), 3u);
    ASSERT_EQ(b[0], 1);
    ASSERT_EQ(b[1], 2);
    ASSERT_EQ(b[2], 3);
}

TEST(runner, "copy assignment allocates separate memory") {
    IntArray a(4);
    IntArray b(2);
    b = a;

    ASSERT_TRUE(a.data() != b.data());
}

TEST(runner, "self-assignment is safe") {
    IntArray a(3);
    a[0] = 42;
    a[1] = 43;
    a[2] = 44;

    a = a;

    ASSERT_EQ(a.size(), 3u);
    ASSERT_EQ(a[0], 42);
    ASSERT_EQ(a[1], 43);
    ASSERT_EQ(a[2], 44);
}

TEST(runner, "copy assignment returns *this for chaining") {
    IntArray a(2);
    a[0] = 5;
    a[1] = 6;

    IntArray b(1);
    IntArray c(1);

    c = b = a;

    ASSERT_EQ(b[0], 5);
    ASSERT_EQ(c[0], 5);
    ASSERT_EQ(b.size(), 2u);
    ASSERT_EQ(c.size(), 2u);
}

TESTKIT_MAIN(runner)
