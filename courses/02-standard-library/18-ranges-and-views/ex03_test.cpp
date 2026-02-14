// Exercise 03 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex03.h"

static testkit::TestRunner runner("02-18-ex03: Transform View");

TEST(runner, "double_values doubles each element") {
    auto result = double_values({1, 2, 3, 4, 5});
    std::vector<int> expected = {2, 4, 6, 8, 10};
    ASSERT_EQ(result.size(), expected.size());
    for (std::size_t i = 0; i < expected.size(); ++i) {
        ASSERT_EQ(result[i], expected[i]);
    }
}

TEST(runner, "double_values handles empty input") {
    auto result = double_values({});
    ASSERT_EQ(result.size(), 0u);
}

TEST(runner, "double_values handles negative numbers") {
    auto result = double_values({-1, 0, 3});
    ASSERT_EQ(result[0], -2);
    ASSERT_EQ(result[1], 0);
    ASSERT_EQ(result[2], 6);
}

TEST(runner, "extract_lengths returns string lengths") {
    auto result = extract_lengths({"hi", "hello", "a", "world!"});
    ASSERT_EQ(result.size(), 4u);
    ASSERT_EQ(result[0], 2u);
    ASSERT_EQ(result[1], 5u);
    ASSERT_EQ(result[2], 1u);
    ASSERT_EQ(result[3], 6u);
}

TEST(runner, "extract_lengths handles empty strings") {
    auto result = extract_lengths({"", "abc", ""});
    ASSERT_EQ(result[0], 0u);
    ASSERT_EQ(result[1], 3u);
    ASSERT_EQ(result[2], 0u);
}

TEST(runner, "negate_values negates each element") {
    auto result = negate_values({1, -2, 3, 0, -5});
    std::vector<int> expected = {-1, 2, -3, 0, 5};
    ASSERT_EQ(result.size(), expected.size());
    for (std::size_t i = 0; i < expected.size(); ++i) {
        ASSERT_EQ(result[i], expected[i]);
    }
}

TEST(runner, "negate_values handles empty input") {
    auto result = negate_values({});
    ASSERT_EQ(result.size(), 0u);
}

TESTKIT_MAIN(runner)
