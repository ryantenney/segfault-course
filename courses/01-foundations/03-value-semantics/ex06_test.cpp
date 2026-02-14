// Exercise 06 — Tests (read-only)

#include <testkit/testkit.h>
#include <vector>
#include <string>

#include "ex06.h"

static testkit::TestRunner runner("01-03-ex06: Return a Const Reference");

TEST(runner, "max_element returns reference to largest int") {
    std::vector<int> v = {3, 7, 2, 9, 4};
    const int& result = max_element(v);
    ASSERT_EQ(result, 9);
}

TEST(runner, "max_element returns a reference, not a copy") {
    std::vector<int> v = {10, 20, 30};
    const int& result = max_element(v);
    // Check that the reference points into the vector's storage
    ASSERT_TRUE(&result == &v[2]);
}

TEST(runner, "max_element works with a single element") {
    std::vector<int> v = {42};
    ASSERT_EQ(max_element(v), 42);
}

TEST(runner, "max_element with negative numbers") {
    std::vector<int> v = {-5, -2, -8, -1};
    ASSERT_EQ(max_element(v), -1);
}

TEST(runner, "longest_string returns reference to longest") {
    std::vector<std::string> v = {"hi", "hello", "hey"};
    const std::string& result = longest_string(v);
    ASSERT_EQ(result, std::string("hello"));
}

TEST(runner, "longest_string returns a reference, not a copy") {
    std::vector<std::string> v = {"short", "longer", "longest"};
    const std::string& result = longest_string(v);
    ASSERT_TRUE(&result == &v[2]);
}

TEST(runner, "longest_string returns first on tie") {
    std::vector<std::string> v = {"abc", "def", "gh"};
    const std::string& result = longest_string(v);
    // "abc" and "def" are same length; first one wins
    ASSERT_TRUE(&result == &v[0]);
}

TESTKIT_MAIN(runner)
