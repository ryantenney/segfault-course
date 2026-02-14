// Exercise 02 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex02.h"

static testkit::TestRunner runner("02-18-ex02: Filter View");

TEST(runner, "filter_positives keeps only positive values") {
    auto result = filter_positives({-3, -1, 0, 2, 5, -7, 8});
    std::vector<int> expected = {2, 5, 8};
    ASSERT_EQ(result.size(), expected.size());
    for (std::size_t i = 0; i < expected.size(); ++i) {
        ASSERT_EQ(result[i], expected[i]);
    }
}

TEST(runner, "filter_positives returns empty for all non-positive") {
    auto result = filter_positives({-3, -1, 0});
    ASSERT_EQ(result.size(), 0u);
}

TEST(runner, "filter_positives handles empty input") {
    auto result = filter_positives({});
    ASSERT_EQ(result.size(), 0u);
}

TEST(runner, "filter_long_strings keeps strings longer than min_length") {
    auto result = filter_long_strings({"hi", "hello", "hey", "greetings"}, 3);
    std::vector<std::string> expected = {"hello", "greetings"};
    ASSERT_EQ(result.size(), expected.size());
    for (std::size_t i = 0; i < expected.size(); ++i) {
        ASSERT_EQ(result[i], expected[i]);
    }
}

TEST(runner, "filter_long_strings with zero min_length keeps all") {
    auto result = filter_long_strings({"a", "bb", "ccc"}, 0);
    ASSERT_EQ(result.size(), 3u);
}

TEST(runner, "count_matching counts even numbers") {
    auto result = count_matching({1, 2, 3, 4, 5, 6}, [](int x) { return x % 2 == 0; });
    ASSERT_EQ(result, 3u);
}

TEST(runner, "count_matching returns zero when none match") {
    auto result = count_matching({1, 3, 5}, [](int x) { return x % 2 == 0; });
    ASSERT_EQ(result, 0u);
}

TEST(runner, "count_matching handles empty input") {
    auto result = count_matching({}, [](int x) { return x > 0; });
    ASSERT_EQ(result, 0u);
}

TESTKIT_MAIN(runner)
