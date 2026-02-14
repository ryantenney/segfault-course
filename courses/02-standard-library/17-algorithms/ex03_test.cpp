// Exercise 03 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex03.h"

static testkit::TestRunner runner("02-17-ex03: Transform Elements");

TEST(runner, "to_uppercase converts all strings") {
    std::vector<std::string> vec = {"hello", "world"};
    auto result = to_uppercase(vec);
    ASSERT_EQ(result.size(), 2u);
    ASSERT_EQ(result[0], std::string("HELLO"));
    ASSERT_EQ(result[1], std::string("WORLD"));
}

TEST(runner, "to_uppercase with mixed case") {
    std::vector<std::string> vec = {"HeLLo", "WoRlD"};
    auto result = to_uppercase(vec);
    ASSERT_EQ(result[0], std::string("HELLO"));
    ASSERT_EQ(result[1], std::string("WORLD"));
}

TEST(runner, "to_uppercase with empty vector") {
    std::vector<std::string> vec;
    auto result = to_uppercase(vec);
    ASSERT_TRUE(result.empty());
}

TEST(runner, "square_all squares each element") {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    auto result = square_all(vec);
    ASSERT_EQ(result.size(), 5u);
    ASSERT_EQ(result[0], 1);
    ASSERT_EQ(result[1], 4);
    ASSERT_EQ(result[2], 9);
    ASSERT_EQ(result[3], 16);
    ASSERT_EQ(result[4], 25);
}

TEST(runner, "square_all handles negatives") {
    std::vector<int> vec = {-3, 0, 2};
    auto result = square_all(vec);
    ASSERT_EQ(result[0], 9);
    ASSERT_EQ(result[1], 0);
    ASSERT_EQ(result[2], 4);
}

TEST(runner, "pairwise_sum adds corresponding elements") {
    std::vector<int> a = {1, 2, 3};
    std::vector<int> b = {10, 20, 30};
    auto result = pairwise_sum(a, b);
    ASSERT_EQ(result.size(), 3u);
    ASSERT_EQ(result[0], 11);
    ASSERT_EQ(result[1], 22);
    ASSERT_EQ(result[2], 33);
}

TEST(runner, "pairwise_sum with zeros") {
    std::vector<int> a = {5, 10};
    std::vector<int> b = {0, 0};
    auto result = pairwise_sum(a, b);
    ASSERT_EQ(result[0], 5);
    ASSERT_EQ(result[1], 10);
}

TEST(runner, "pairwise_sum with empty vectors") {
    std::vector<int> a;
    std::vector<int> b;
    auto result = pairwise_sum(a, b);
    ASSERT_TRUE(result.empty());
}

TESTKIT_MAIN(runner)
