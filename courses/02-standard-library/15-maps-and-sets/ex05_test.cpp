// Exercise 05 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex05.h"

static testkit::TestRunner runner("02-15-ex05: Ordered Set Operations");

TEST(runner, "unique_sorted removes duplicates and sorts") {
    auto result = unique_sorted({5, 3, 1, 3, 5, 2, 1});
    ASSERT_EQ(result.size(), 4u);
    ASSERT_EQ(result[0], 1);
    ASSERT_EQ(result[1], 2);
    ASSERT_EQ(result[2], 3);
    ASSERT_EQ(result[3], 5);
}

TEST(runner, "unique_sorted on already unique sorted input") {
    auto result = unique_sorted({1, 2, 3});
    ASSERT_EQ(result.size(), 3u);
    ASSERT_EQ(result[0], 1);
    ASSERT_EQ(result[1], 2);
    ASSERT_EQ(result[2], 3);
}

TEST(runner, "unique_sorted on empty input returns empty") {
    auto result = unique_sorted({});
    ASSERT_EQ(result.size(), 0u);
}

TEST(runner, "set_intersection finds common elements") {
    auto result = set_intersection({1, 2, 3, 4, 5}, {3, 4, 5, 6, 7});
    ASSERT_EQ(result.size(), 3u);
    ASSERT_EQ(result[0], 3);
    ASSERT_EQ(result[1], 4);
    ASSERT_EQ(result[2], 5);
}

TEST(runner, "set_intersection with no common elements") {
    auto result = set_intersection({1, 2}, {3, 4});
    ASSERT_EQ(result.size(), 0u);
}

TEST(runner, "set_intersection handles duplicates in input") {
    auto result = set_intersection({1, 1, 2, 2, 3}, {2, 2, 3, 3, 4});
    ASSERT_EQ(result.size(), 2u);
    ASSERT_EQ(result[0], 2);
    ASSERT_EQ(result[1], 3);
}

TEST(runner, "set_difference finds elements only in a") {
    auto result = set_difference({1, 2, 3, 4, 5}, {3, 4, 5, 6, 7});
    ASSERT_EQ(result.size(), 2u);
    ASSERT_EQ(result[0], 1);
    ASSERT_EQ(result[1], 2);
}

TEST(runner, "set_difference when all elements are shared") {
    auto result = set_difference({1, 2, 3}, {1, 2, 3});
    ASSERT_EQ(result.size(), 0u);
}

TEST(runner, "set_difference handles duplicates in a") {
    auto result = set_difference({1, 1, 2, 2, 3}, {2});
    ASSERT_EQ(result.size(), 2u);
    ASSERT_EQ(result[0], 1);
    ASSERT_EQ(result[1], 3);
}

TESTKIT_MAIN(runner)
