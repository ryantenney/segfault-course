// Exercise 04 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex04.h"

static testkit::TestRunner runner("01-07-ex04: Tuple decomposition");

TEST(runner, "stats returns min, max, sum") {
    auto [mn, mx, total] = stats({3, 1, 4, 1, 5});
    ASSERT_EQ(mn, 1);
    ASSERT_EQ(mx, 5);
    ASSERT_EQ(total, 14);
}

TEST(runner, "stats handles single element") {
    auto [mn, mx, total] = stats({42});
    ASSERT_EQ(mn, 42);
    ASSERT_EQ(mx, 42);
    ASSERT_EQ(total, 42);
}

TEST(runner, "stats returns zeros for empty vector") {
    auto [mn, mx, total] = stats({});
    ASSERT_EQ(mn, 0);
    ASSERT_EQ(mx, 0);
    ASSERT_EQ(total, 0);
}

TEST(runner, "divmod returns quotient and remainder") {
    auto [q, r] = divmod(17, 5);
    ASSERT_EQ(q, 3);
    ASSERT_EQ(r, 2);
}

TEST(runner, "divmod with exact division") {
    auto [q, r] = divmod(10, 2);
    ASSERT_EQ(q, 5);
    ASSERT_EQ(r, 0);
}

TEST(runner, "split_name separates first and last") {
    auto [first, last] = split_name("John Doe");
    ASSERT_EQ(first, "John");
    ASSERT_EQ(last, "Doe");
}

TEST(runner, "split_name handles no space") {
    auto [first, last] = split_name("Alice");
    ASSERT_EQ(first, "Alice");
    ASSERT_EQ(last, std::string(""));
}

TEST(runner, "split_name handles multiple words (splits on first space)") {
    auto [first, last] = split_name("Mary Jane Watson");
    ASSERT_EQ(first, "Mary");
    ASSERT_EQ(last, "Jane Watson");
}

TEST(runner, "count_and_sum_positive counts and sums positive values") {
    auto [count, total] = count_and_sum_positive({-1, 2, -3, 4, 5});
    ASSERT_EQ(count, 3);
    ASSERT_EQ(total, 11);
}

TEST(runner, "count_and_sum_positive with no positives") {
    auto [count, total] = count_and_sum_positive({-1, -2, 0});
    ASSERT_EQ(count, 0);
    ASSERT_EQ(total, 0);
}

TESTKIT_MAIN(runner)
