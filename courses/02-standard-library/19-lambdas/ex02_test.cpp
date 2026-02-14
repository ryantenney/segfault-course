// Exercise 02 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex02.h"

static testkit::TestRunner runner("02-19-ex02: Capture by Reference");

TEST(runner, "count_if_positive counts positive values") {
    ASSERT_EQ(count_if_positive({-3, -1, 0, 2, 5, -7, 8}), 3);
}

TEST(runner, "count_if_positive returns zero for no positives") {
    ASSERT_EQ(count_if_positive({-3, -1, 0}), 0);
}

TEST(runner, "count_if_positive handles empty input") {
    ASSERT_EQ(count_if_positive({}), 0);
}

TEST(runner, "sum_elements sums all values") {
    ASSERT_EQ(sum_elements({1, 2, 3, 4, 5}), 15);
}

TEST(runner, "sum_elements handles negatives") {
    ASSERT_EQ(sum_elements({-1, 2, -3, 4}), 2);
}

TEST(runner, "sum_elements returns zero for empty") {
    ASSERT_EQ(sum_elements({}), 0);
}

TEST(runner, "apply_to_each multiplies by factor") {
    auto result = apply_to_each({1, 2, 3}, 10);
    ASSERT_EQ(result.size(), 3u);
    ASSERT_EQ(result[0], 10);
    ASSERT_EQ(result[1], 20);
    ASSERT_EQ(result[2], 30);
}

TEST(runner, "apply_to_each with factor zero") {
    auto result = apply_to_each({5, 10, 15}, 0);
    ASSERT_EQ(result.size(), 3u);
    ASSERT_EQ(result[0], 0);
    ASSERT_EQ(result[1], 0);
    ASSERT_EQ(result[2], 0);
}

TEST(runner, "apply_to_each handles empty input") {
    auto result = apply_to_each({}, 5);
    ASSERT_EQ(result.size(), 0u);
}

TESTKIT_MAIN(runner)
