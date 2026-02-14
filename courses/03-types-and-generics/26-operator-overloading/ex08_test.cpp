// Exercise 08 -- Tests (read-only)

#include <testkit/testkit.h>
#include <algorithm>
#include <vector>

#include "ex08.h"

static testkit::TestRunner runner("03-26-ex08: Function Call Operator");

TEST(runner, "Multiplier multiplies by the stored factor") {
    Multiplier times3(3);
    ASSERT_EQ(times3(4), 12);
    ASSERT_EQ(times3(0), 0);
    ASSERT_EQ(times3(-2), -6);
}

TEST(runner, "Multiplier with factor 1 is identity") {
    Multiplier identity(1);
    ASSERT_EQ(identity(42), 42);
    ASSERT_EQ(identity(-7), -7);
}

TEST(runner, "Counter starts at zero and increments") {
    Counter c;
    ASSERT_EQ(c(), 0);
    ASSERT_EQ(c(), 1);
    ASSERT_EQ(c(), 2);
    ASSERT_EQ(c(), 3);
}

TEST(runner, "Counter current() returns count without incrementing") {
    Counter c;
    ASSERT_EQ(c.current(), 0);
    c();
    c();
    ASSERT_EQ(c.current(), 2);
    ASSERT_EQ(c.current(), 2);  // still 2, not incremented
}

TEST(runner, "InRange returns true for values in bounds") {
    InRange check(1, 10);
    ASSERT_TRUE(check(1));
    ASSERT_TRUE(check(5));
    ASSERT_TRUE(check(10));
}

TEST(runner, "InRange returns false for values out of bounds") {
    InRange check(1, 10);
    ASSERT_FALSE(check(0));
    ASSERT_FALSE(check(11));
    ASSERT_FALSE(check(-5));
}

TEST(runner, "Multiplier works with std::transform") {
    std::vector<int> input{1, 2, 3, 4};
    std::vector<int> output(input.size());
    std::transform(input.begin(), input.end(), output.begin(), Multiplier(10));
    ASSERT_EQ(output[0], 10);
    ASSERT_EQ(output[1], 20);
    ASSERT_EQ(output[2], 30);
    ASSERT_EQ(output[3], 40);
}

TEST(runner, "InRange works with std::count_if") {
    std::vector<int> data{1, 5, 10, 15, 20, 25};
    auto count = std::count_if(data.begin(), data.end(), InRange(5, 20));
    ASSERT_EQ(count, 4L);  // 5, 10, 15, 20
}

TESTKIT_MAIN(runner)
