// Exercise 07 -- Tests (read-only)

#include <algorithm>
#include <testkit/testkit.h>

#include "ex07.h"

static testkit::TestRunner runner("02-17-ex07: Min/Max and Partition");

TEST(runner, "find_min_max returns correct min and max") {
    std::vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6};
    auto [mn, mx] = find_min_max(vec);
    ASSERT_EQ(mn, 1);
    ASSERT_EQ(mx, 9);
}

TEST(runner, "find_min_max with single element") {
    std::vector<int> vec = {42};
    auto [mn, mx] = find_min_max(vec);
    ASSERT_EQ(mn, 42);
    ASSERT_EQ(mx, 42);
}

TEST(runner, "find_min_max with negative numbers") {
    std::vector<int> vec = {-5, 3, -10, 8};
    auto [mn, mx] = find_min_max(vec);
    ASSERT_EQ(mn, -10);
    ASSERT_EQ(mx, 8);
}

TEST(runner, "partition_evens_first moves evens before odds") {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6};
    int even_count = partition_evens_first(vec);
    ASSERT_EQ(even_count, 3);
    // First 3 elements should all be even
    for (int i = 0; i < even_count; ++i) {
        ASSERT_TRUE(vec[i] % 2 == 0);
    }
    // Remaining elements should be odd
    for (std::size_t i = even_count; i < vec.size(); ++i) {
        ASSERT_TRUE(vec[i] % 2 != 0);
    }
}

TEST(runner, "partition_evens_first with all evens") {
    std::vector<int> vec = {2, 4, 6};
    int even_count = partition_evens_first(vec);
    ASSERT_EQ(even_count, 3);
}

TEST(runner, "partition_evens_first with all odds") {
    std::vector<int> vec = {1, 3, 5};
    int even_count = partition_evens_first(vec);
    ASSERT_EQ(even_count, 0);
}

TEST(runner, "partition_by_threshold splits correctly") {
    std::vector<int> vec = {1, 5, 2, 8, 3, 7};
    auto [below, at_or_above] = partition_by_threshold(vec, 5);
    // below threshold (< 5): 1, 2, 3
    ASSERT_EQ(below.size(), 3u);
    std::sort(below.begin(), below.end());
    ASSERT_EQ(below[0], 1);
    ASSERT_EQ(below[1], 2);
    ASSERT_EQ(below[2], 3);
    // at or above threshold (>= 5): 5, 8, 7
    ASSERT_EQ(at_or_above.size(), 3u);
    std::sort(at_or_above.begin(), at_or_above.end());
    ASSERT_EQ(at_or_above[0], 5);
    ASSERT_EQ(at_or_above[1], 7);
    ASSERT_EQ(at_or_above[2], 8);
}

TEST(runner, "partition_by_threshold with all below") {
    std::vector<int> vec = {1, 2, 3};
    auto [below, at_or_above] = partition_by_threshold(vec, 10);
    ASSERT_EQ(below.size(), 3u);
    ASSERT_TRUE(at_or_above.empty());
}

TEST(runner, "partition_by_threshold with all above") {
    std::vector<int> vec = {10, 20, 30};
    auto [below, at_or_above] = partition_by_threshold(vec, 5);
    ASSERT_TRUE(below.empty());
    ASSERT_EQ(at_or_above.size(), 3u);
}

TESTKIT_MAIN(runner)
