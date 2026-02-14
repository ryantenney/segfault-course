// Exercise 05 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex05.h"

static testkit::TestRunner runner("02-14-ex05: Erase Elements");

TEST(runner, "remove_value removes all occurrences") {
    std::vector<int> v = {1, 2, 3, 2, 4, 2, 5};
    remove_value(v, 2);
    ASSERT_EQ(v.size(), 4u);
    ASSERT_EQ(v[0], 1);
    ASSERT_EQ(v[1], 3);
    ASSERT_EQ(v[2], 4);
    ASSERT_EQ(v[3], 5);
}

TEST(runner, "remove_value with no matches leaves vector unchanged") {
    std::vector<int> v = {1, 2, 3};
    remove_value(v, 99);
    ASSERT_EQ(v.size(), 3u);
}

TEST(runner, "remove_negatives removes all negative numbers") {
    std::vector<int> v = {-3, 1, -1, 4, -2, 0, 5};
    remove_negatives(v);
    ASSERT_EQ(v.size(), 4u);
    ASSERT_EQ(v[0], 1);
    ASSERT_EQ(v[1], 4);
    ASSERT_EQ(v[2], 0);
    ASSERT_EQ(v[3], 5);
}

TEST(runner, "remove_negatives on all-positive vector leaves it unchanged") {
    std::vector<int> v = {1, 2, 3};
    remove_negatives(v);
    ASSERT_EQ(v.size(), 3u);
}

TEST(runner, "remove_duplicates keeps first occurrence only") {
    std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    remove_duplicates(v);
    ASSERT_EQ(v.size(), 7u);
    ASSERT_EQ(v[0], 3);
    ASSERT_EQ(v[1], 1);
    ASSERT_EQ(v[2], 4);
    ASSERT_EQ(v[3], 5);
    ASSERT_EQ(v[4], 9);
    ASSERT_EQ(v[5], 2);
    ASSERT_EQ(v[6], 6);
}

TEST(runner, "remove_duplicates on unique vector leaves it unchanged") {
    std::vector<int> v = {10, 20, 30};
    remove_duplicates(v);
    ASSERT_EQ(v.size(), 3u);
    ASSERT_EQ(v[0], 10);
    ASSERT_EQ(v[1], 20);
    ASSERT_EQ(v[2], 30);
}

TESTKIT_MAIN(runner)
