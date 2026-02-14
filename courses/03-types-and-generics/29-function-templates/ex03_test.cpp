// Exercise 03 -- Tests (read-only)
//
// Verifies the FixedBuffer class template with non-type parameter.

#include <testkit/testkit.h>
#include "ex03.h"

static testkit::TestRunner runner("03-29-ex03: Non-Type Template Parameter");

TEST(runner, "default constructed buffer has correct size") {
    FixedBuffer<5> buf;
    ASSERT_EQ(buf.size(), 5u);
}

TEST(runner, "different sizes are different types") {
    FixedBuffer<3> small;
    FixedBuffer<10> large;
    // Gate call
    (void)small.size();
    (void)large.size();

    ASSERT_EQ(small.size(), 3u);
    ASSERT_EQ(large.size(), 10u);
}

TEST(runner, "elements are zero-initialized") {
    FixedBuffer<4> buf;
    ASSERT_EQ(buf[0], 0);
    ASSERT_EQ(buf[1], 0);
    ASSERT_EQ(buf[2], 0);
    ASSERT_EQ(buf[3], 0);
}

TEST(runner, "operator[] allows read and write") {
    FixedBuffer<3> buf;
    buf[0] = 10;
    buf[1] = 20;
    buf[2] = 30;
    ASSERT_EQ(buf[0], 10);
    ASSERT_EQ(buf[1], 20);
    ASSERT_EQ(buf[2], 30);
}

TEST(runner, "fill sets all elements") {
    FixedBuffer<5> buf;
    buf.fill(42);
    ASSERT_EQ(buf[0], 42);
    ASSERT_EQ(buf[1], 42);
    ASSERT_EQ(buf[2], 42);
    ASSERT_EQ(buf[3], 42);
    ASSERT_EQ(buf[4], 42);
}

TEST(runner, "sum returns total of all elements") {
    FixedBuffer<4> buf;
    buf[0] = 1;
    buf[1] = 2;
    buf[2] = 3;
    buf[3] = 4;
    ASSERT_EQ(buf.sum(), 10);
}

TEST(runner, "sum of filled buffer") {
    FixedBuffer<3> buf;
    buf.fill(7);
    ASSERT_EQ(buf.sum(), 21);
}

TEST(runner, "buffer of size 1 works") {
    FixedBuffer<1> buf;
    buf[0] = 99;
    ASSERT_EQ(buf.size(), 1u);
    ASSERT_EQ(buf.sum(), 99);
}

TESTKIT_MAIN(runner)
