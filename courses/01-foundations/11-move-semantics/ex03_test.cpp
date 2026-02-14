// Exercise 03 -- Tests (read-only)

#include <testkit/testkit.h>
#include <utility>

#include "ex03.h"

static testkit::TestRunner runner("01-11-ex03: Write a Move Constructor");

TEST(runner, "normal constructor creates a buffer with the right size") {
    Buffer buf(10);
    ASSERT_EQ(buf.size(), 10u);
    ASSERT_TRUE(buf.has_data());
    ASSERT_FALSE(buf.empty());
}

TEST(runner, "move constructor transfers data") {
    Buffer original(5);
    original[0] = 42;
    original[3] = 99;

    Buffer moved(std::move(original));
    ASSERT_EQ(moved.size(), 5u);
    ASSERT_TRUE(moved.has_data());
    ASSERT_EQ(moved[0], 42);
    ASSERT_EQ(moved[3], 99);
}

TEST(runner, "move constructor leaves source empty") {
    Buffer original(3);
    Buffer moved(std::move(original));
    ASSERT_TRUE(original.empty());
    ASSERT_EQ(original.size(), 0u);
    ASSERT_FALSE(original.has_data());
}

TEST(runner, "moved-into buffer is fully usable") {
    Buffer a(4);
    a[0] = 10;
    a[1] = 20;
    a[2] = 30;
    a[3] = 40;

    Buffer b(std::move(a));
    ASSERT_EQ(b[0], 10);
    ASSERT_EQ(b[1], 20);
    ASSERT_EQ(b[2], 30);
    ASSERT_EQ(b[3], 40);
}

TESTKIT_MAIN(runner)
