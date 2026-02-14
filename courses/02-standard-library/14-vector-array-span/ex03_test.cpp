// Exercise 03 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex03.h"

#include <stdexcept>

static testkit::TestRunner runner("02-14-ex03: Bounds-Safe Access");

TEST(runner, "safe_element returns the correct element") {
    std::vector<int> v = {10, 20, 30, 40, 50};
    ASSERT_EQ(safe_element(v, 0), 10);
    ASSERT_EQ(safe_element(v, 2), 30);
    ASSERT_EQ(safe_element(v, 4), 50);
}

TEST(runner, "safe_element throws on out-of-range index") {
    std::vector<int> v = {10, 20, 30};
    ASSERT_THROWS(safe_element(v, 5), std::out_of_range);
    ASSERT_THROWS(safe_element(v, 100), std::out_of_range);
}

TEST(runner, "safe_sum sums a range of indices") {
    std::vector<int> v = {1, 2, 3, 4, 5};
    ASSERT_EQ(safe_sum(v, 0, 4), 15);
    ASSERT_EQ(safe_sum(v, 1, 3), 9);
    ASSERT_EQ(safe_sum(v, 2, 2), 3);
}

TEST(runner, "safe_sum throws on invalid range") {
    std::vector<int> v = {1, 2, 3};
    ASSERT_THROWS(safe_sum(v, 0, 5), std::out_of_range);
}

TEST(runner, "get_or_default returns element when index is valid") {
    std::vector<int> v = {100, 200, 300};
    ASSERT_EQ(get_or_default(v, 0, -1), 100);
    ASSERT_EQ(get_or_default(v, 2, -1), 300);
}

TEST(runner, "get_or_default returns default when index is invalid") {
    std::vector<int> v = {100, 200, 300};
    ASSERT_EQ(get_or_default(v, 10, -1), -1);
    ASSERT_EQ(get_or_default(v, 999, 42), 42);
}

TESTKIT_MAIN(runner)
