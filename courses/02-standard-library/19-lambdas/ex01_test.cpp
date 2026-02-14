// Exercise 01 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex01.h"

static testkit::TestRunner runner("02-19-ex01: Basic Lambda Predicate");

TEST(runner, "sort_ascending sorts in ascending order") {
    auto result = sort_ascending({5, 3, 1, 4, 2});
    std::vector<int> expected = {1, 2, 3, 4, 5};
    ASSERT_EQ(result.size(), expected.size());
    for (std::size_t i = 0; i < expected.size(); ++i) {
        ASSERT_EQ(result[i], expected[i]);
    }
}

TEST(runner, "sort_ascending handles already sorted") {
    auto result = sort_ascending({1, 2, 3});
    ASSERT_EQ(result[0], 1);
    ASSERT_EQ(result[2], 3);
}

TEST(runner, "sort_ascending handles single element") {
    auto result = sort_ascending({42});
    ASSERT_EQ(result.size(), 1u);
    ASSERT_EQ(result[0], 42);
}

TEST(runner, "sort_by_absolute sorts by absolute value") {
    auto result = sort_by_absolute({-5, 3, -1, 4, -2});
    // by absolute value: 1, 2, 3, 4, 5
    ASSERT_EQ(std::abs(result[0]), 1);
    ASSERT_EQ(std::abs(result[1]), 2);
    ASSERT_EQ(std::abs(result[2]), 3);
    ASSERT_EQ(std::abs(result[3]), 4);
    ASSERT_EQ(std::abs(result[4]), 5);
}

TEST(runner, "sort_by_absolute handles all positive") {
    auto result = sort_by_absolute({10, 1, 5});
    ASSERT_EQ(result[0], 1);
    ASSERT_EQ(result[1], 5);
    ASSERT_EQ(result[2], 10);
}

TEST(runner, "sort_strings_by_length sorts by length") {
    auto result = sort_strings_by_length({"hello", "hi", "hey", "a"});
    ASSERT_EQ(result[0], std::string("a"));
    ASSERT_EQ(result[1], std::string("hi"));
}

TEST(runner, "sort_strings_by_length breaks ties alphabetically") {
    auto result = sort_strings_by_length({"cat", "bat", "ant"});
    // all length 3, should be alphabetical
    ASSERT_EQ(result[0], std::string("ant"));
    ASSERT_EQ(result[1], std::string("bat"));
    ASSERT_EQ(result[2], std::string("cat"));
}

TEST(runner, "sort_strings_by_length combined behavior") {
    auto result = sort_strings_by_length({"bb", "a", "cc", "aaa"});
    ASSERT_EQ(result[0], std::string("a"));
    // "bb" and "cc" both length 2
    ASSERT_EQ(result[1], std::string("bb"));
    ASSERT_EQ(result[2], std::string("cc"));
    ASSERT_EQ(result[3], std::string("aaa"));
}

TESTKIT_MAIN(runner)
