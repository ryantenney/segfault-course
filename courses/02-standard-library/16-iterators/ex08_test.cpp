// Exercise 08 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex08.h"

static testkit::TestRunner runner("02-16-ex08: Custom Iterator");

TEST(runner, "IntRange iterator dereferences correctly") {
    IntRange::Iterator it(42);
    ASSERT_EQ(*it, 42);
}

TEST(runner, "IntRange iterator increments") {
    IntRange::Iterator it(10);
    ++it;
    ASSERT_EQ(*it, 11);
}

TEST(runner, "IntRange iterator inequality") {
    IntRange::Iterator a(1);
    IntRange::Iterator b(2);
    IntRange::Iterator c(1);
    ASSERT_TRUE(a != b);
    ASSERT_FALSE(a != c);
}

TEST(runner, "IntRange begin and end produce correct range") {
    IntRange r(0, 3);
    auto it = r.begin();
    auto e = r.end();
    ASSERT_EQ(*it, 0);
    ++it;
    ASSERT_EQ(*it, 1);
    ++it;
    ASSERT_EQ(*it, 2);
    ++it;
    ASSERT_TRUE(!(it != e));
}

TEST(runner, "IntRange works with range-for loop") {
    IntRange r(1, 4);
    std::vector<int> values;
    for (int v : r) {
        values.push_back(v);
    }
    ASSERT_EQ(values.size(), 3u);
    ASSERT_EQ(values[0], 1);
    ASSERT_EQ(values[1], 2);
    ASSERT_EQ(values[2], 3);
}

TEST(runner, "IntRange with empty range") {
    IntRange r(5, 5);
    int count = 0;
    for ([[maybe_unused]] int v : r) {
        ++count;
    }
    ASSERT_EQ(count, 0);
}

TEST(runner, "range_sum sums all values in range") {
    ASSERT_EQ(range_sum(1, 6), 15);   // 1+2+3+4+5
    ASSERT_EQ(range_sum(0, 1), 0);    // just 0
    ASSERT_EQ(range_sum(5, 5), 0);    // empty range
}

TEST(runner, "collect_range collects values into a vector") {
    auto vec = collect_range(3, 7);
    ASSERT_EQ(vec.size(), 4u);
    ASSERT_EQ(vec[0], 3);
    ASSERT_EQ(vec[1], 4);
    ASSERT_EQ(vec[2], 5);
    ASSERT_EQ(vec[3], 6);
}

TESTKIT_MAIN(runner)
