// Exercise 01 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex01.h"

static testkit::TestRunner runner("02-18-ex01: Ranges Sort and Find");

TEST(runner, "sort_ascending sorts in ascending order") {
    auto result = sort_ascending({5, 3, 1, 4, 2});
    std::vector<int> expected = {1, 2, 3, 4, 5};
    ASSERT_EQ(result.size(), expected.size());
    for (std::size_t i = 0; i < expected.size(); ++i) {
        ASSERT_EQ(result[i], expected[i]);
    }
}

TEST(runner, "sort_ascending handles empty vector") {
    auto result = sort_ascending({});
    ASSERT_EQ(result.size(), 0u);
}

TEST(runner, "sort_ascending handles already sorted") {
    auto result = sort_ascending({1, 2, 3});
    ASSERT_EQ(result[0], 1);
    ASSERT_EQ(result[2], 3);
}

TEST(runner, "find_value returns true when present") {
    ASSERT_TRUE(find_value({10, 20, 30, 40}, 30));
}

TEST(runner, "find_value returns false when absent") {
    ASSERT_FALSE(find_value({10, 20, 30, 40}, 99));
}

TEST(runner, "find_value handles empty vector") {
    ASSERT_FALSE(find_value({}, 1));
}

TEST(runner, "sort_descending sorts in descending order") {
    auto result = sort_descending({5, 3, 1, 4, 2});
    std::vector<int> expected = {5, 4, 3, 2, 1};
    ASSERT_EQ(result.size(), expected.size());
    for (std::size_t i = 0; i < expected.size(); ++i) {
        ASSERT_EQ(result[i], expected[i]);
    }
}

TEST(runner, "sort_descending handles single element") {
    auto result = sort_descending({42});
    ASSERT_EQ(result.size(), 1u);
    ASSERT_EQ(result[0], 42);
}

TESTKIT_MAIN(runner)
