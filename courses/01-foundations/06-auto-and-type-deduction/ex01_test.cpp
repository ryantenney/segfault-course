// Exercise 01 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex01.h"

static testkit::TestRunner runner("01-06-ex01: Replace Explicit Types with auto");

TEST(runner, "find_first returns the matching element") {
    std::vector<int> v = {10, 20, 30, 40, 50};
    ASSERT_EQ(find_first(v, 30), 30);
    ASSERT_EQ(find_first(v, 10), 10);
}

TEST(runner, "find_first returns -1 when not found") {
    std::vector<int> v = {10, 20, 30};
    ASSERT_EQ(find_first(v, 99), -1);
}

TEST(runner, "find_first handles empty vector") {
    std::vector<int> v;
    ASSERT_EQ(find_first(v, 1), -1);
}

TEST(runner, "sum_elements returns the total") {
    std::vector<int> v = {1, 2, 3, 4, 5};
    ASSERT_EQ(sum_elements(v), 15);
}

TEST(runner, "sum_elements handles empty vector") {
    std::vector<int> v;
    ASSERT_EQ(sum_elements(v), 0);
}

TEST(runner, "longest_string returns the longest") {
    std::vector<std::string> v = {"hi", "hello", "hey"};
    ASSERT_EQ(longest_string(v), "hello");
}

TEST(runner, "longest_string returns empty for empty vector") {
    std::vector<std::string> v;
    ASSERT_EQ(longest_string(v), std::string(""));
}

TESTKIT_MAIN(runner)
