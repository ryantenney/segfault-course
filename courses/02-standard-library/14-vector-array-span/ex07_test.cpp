// Exercise 07 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex07.h"

#include <vector>
#include <array>
#include <span>

static testkit::TestRunner runner("02-14-ex07: Accept a Span Parameter");

TEST(runner, "span_sum sums elements from a vector") {
    std::vector<int> v = {1, 2, 3, 4, 5};
    ASSERT_EQ(span_sum(v), 15);
}

TEST(runner, "span_sum sums elements from a std::array") {
    std::array<int, 4> a = {10, 20, 30, 40};
    ASSERT_EQ(span_sum(a), 100);
}

TEST(runner, "span_sum sums elements from a C array") {
    int c[] = {5, 10, 15};
    ASSERT_EQ(span_sum(c), 30);
}

TEST(runner, "span_sum of empty span is zero") {
    std::vector<int> empty;
    ASSERT_EQ(span_sum(empty), 0);
}

TEST(runner, "span_contains finds existing value") {
    std::vector<int> v = {3, 7, 11, 15};
    ASSERT_TRUE(span_contains(v, 7));
    ASSERT_TRUE(span_contains(v, 3));
    ASSERT_TRUE(span_contains(v, 15));
}

TEST(runner, "span_contains returns false for missing value") {
    std::vector<int> v = {3, 7, 11, 15};
    ASSERT_FALSE(span_contains(v, 4));
    ASSERT_FALSE(span_contains(v, 0));
}

TEST(runner, "span_min_max finds min and max") {
    std::vector<int> v = {5, 3, 8, 1, 7};
    auto [mn, mx] = span_min_max(v);
    ASSERT_EQ(mn, 1);
    ASSERT_EQ(mx, 8);
}

TEST(runner, "span_min_max works with single element") {
    std::array<int, 1> a = {42};
    auto [mn, mx] = span_min_max(a);
    ASSERT_EQ(mn, 42);
    ASSERT_EQ(mx, 42);
}

TEST(runner, "span_min_max works with negative numbers") {
    int c[] = {-10, -3, -7, -1};
    auto [mn, mx] = span_min_max(c);
    ASSERT_EQ(mn, -10);
    ASSERT_EQ(mx, -1);
}

TESTKIT_MAIN(runner)
