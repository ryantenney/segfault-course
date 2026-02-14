// Exercise 04 — Tests (read-only)

#include <testkit/testkit.h>
#include <string>
#include <vector>

#include "ex04.h"

static testkit::TestRunner runner("01-02-ex04: Fix using-namespace Pollution");

TEST(runner, "repeat_string repeats a string N times") {
    ASSERT_EQ(formatting::repeat_string("ab", 3), std::string("ababab"));
    ASSERT_EQ(formatting::repeat_string("x", 1), std::string("x"));
    ASSERT_EQ(formatting::repeat_string("hi", 0), std::string(""));
}

TEST(runner, "join concatenates with separator") {
    std::vector<std::string> words = {"hello", "world"};
    ASSERT_EQ(formatting::join(words, " "), std::string("hello world"));

    std::vector<std::string> nums = {"1", "2", "3"};
    ASSERT_EQ(formatting::join(nums, ", "), std::string("1, 2, 3"));

    std::vector<std::string> single = {"alone"};
    ASSERT_EQ(formatting::join(single, "-"), std::string("alone"));

    std::vector<std::string> empty = {};
    ASSERT_EQ(formatting::join(empty, ","), std::string(""));
}

TEST(runner, "describe_size returns a description of vector size") {
    std::vector<int> v3 = {1, 2, 3};
    ASSERT_EQ(formatting::describe_size(v3), std::string("size: 3"));

    std::vector<int> v0 = {};
    ASSERT_EQ(formatting::describe_size(v0), std::string("size: 0"));
}

TESTKIT_MAIN(runner)
