// Exercise 05 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex05.h"

static testkit::TestRunner runner("02-17-ex05: Copy_if");

TEST(runner, "filter_evens returns only even numbers") {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6};
    auto result = filter_evens(vec);
    ASSERT_EQ(result.size(), 3u);
    ASSERT_EQ(result[0], 2);
    ASSERT_EQ(result[1], 4);
    ASSERT_EQ(result[2], 6);
}

TEST(runner, "filter_evens with no even numbers") {
    std::vector<int> vec = {1, 3, 5};
    auto result = filter_evens(vec);
    ASSERT_TRUE(result.empty());
}

TEST(runner, "filter_evens with empty vector") {
    std::vector<int> vec;
    auto result = filter_evens(vec);
    ASSERT_TRUE(result.empty());
}

TEST(runner, "filter_by_prefix filters matching strings") {
    std::vector<std::string> vec = {"apple", "apricot", "banana", "avocado", "appetizer"};
    auto result = filter_by_prefix(vec, "ap");
    ASSERT_EQ(result.size(), 3u);
    ASSERT_EQ(result[0], std::string("apple"));
    ASSERT_EQ(result[1], std::string("apricot"));
    ASSERT_EQ(result[2], std::string("appetizer"));
}

TEST(runner, "filter_by_prefix with no matches") {
    std::vector<std::string> vec = {"banana", "cherry"};
    auto result = filter_by_prefix(vec, "ap");
    ASSERT_TRUE(result.empty());
}

TEST(runner, "filter_by_prefix with single character prefix") {
    std::vector<std::string> vec = {"alpha", "beta", "aardvark"};
    auto result = filter_by_prefix(vec, "a");
    ASSERT_EQ(result.size(), 2u);
    ASSERT_EQ(result[0], std::string("alpha"));
    ASSERT_EQ(result[1], std::string("aardvark"));
}

TEST(runner, "filter_in_range returns elements within bounds") {
    std::vector<int> vec = {1, 5, 10, 15, 20, 25};
    auto result = filter_in_range(vec, 5, 20);
    ASSERT_EQ(result.size(), 4u);
    ASSERT_EQ(result[0], 5);
    ASSERT_EQ(result[1], 10);
    ASSERT_EQ(result[2], 15);
    ASSERT_EQ(result[3], 20);
}

TEST(runner, "filter_in_range with no matches") {
    std::vector<int> vec = {1, 2, 3};
    auto result = filter_in_range(vec, 10, 20);
    ASSERT_TRUE(result.empty());
}

TEST(runner, "filter_in_range includes boundaries") {
    std::vector<int> vec = {5, 10, 15};
    auto result = filter_in_range(vec, 5, 15);
    ASSERT_EQ(result.size(), 3u);
}

TESTKIT_MAIN(runner)
