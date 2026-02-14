// Exercise 01 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex01.h"

static testkit::TestRunner runner("02-17-ex01: Sort and Search");

TEST(runner, "sort_ascending sorts in ascending order") {
    std::vector<int> vec = {5, 3, 8, 1, 4};
    sort_ascending(vec);
    ASSERT_EQ(vec[0], 1);
    ASSERT_EQ(vec[1], 3);
    ASSERT_EQ(vec[2], 4);
    ASSERT_EQ(vec[3], 5);
    ASSERT_EQ(vec[4], 8);
}

TEST(runner, "sort_ascending with already sorted vector") {
    std::vector<int> vec = {1, 2, 3};
    sort_ascending(vec);
    ASSERT_EQ(vec[0], 1);
    ASSERT_EQ(vec[1], 2);
    ASSERT_EQ(vec[2], 3);
}

TEST(runner, "sort_descending sorts in descending order") {
    std::vector<int> vec = {5, 3, 8, 1, 4};
    sort_descending(vec);
    ASSERT_EQ(vec[0], 8);
    ASSERT_EQ(vec[1], 5);
    ASSERT_EQ(vec[2], 4);
    ASSERT_EQ(vec[3], 3);
    ASSERT_EQ(vec[4], 1);
}

TEST(runner, "sort_descending with single element") {
    std::vector<int> vec = {42};
    sort_descending(vec);
    ASSERT_EQ(vec[0], 42);
}

TEST(runner, "binary_search_index finds an existing element") {
    std::vector<int> vec = {9, 2, 7, 4, 5};
    int idx = binary_search_index(vec, 7);
    ASSERT_EQ(idx, 3); // after sorting: {2, 4, 5, 7, 9}
}

TEST(runner, "binary_search_index returns -1 for missing element") {
    std::vector<int> vec = {3, 1, 4, 1, 5};
    int idx = binary_search_index(vec, 99);
    ASSERT_EQ(idx, -1);
}

TEST(runner, "binary_search_index finds first element") {
    std::vector<int> vec = {30, 10, 20};
    int idx = binary_search_index(vec, 10);
    ASSERT_EQ(idx, 0); // after sorting: {10, 20, 30}
}

TEST(runner, "binary_search_index with empty vector") {
    std::vector<int> vec;
    int idx = binary_search_index(vec, 5);
    ASSERT_EQ(idx, -1);
}

TESTKIT_MAIN(runner)
