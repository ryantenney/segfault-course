// Exercise 02 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex02.h"

static testkit::TestRunner runner("02-17-ex02: Find and Count");

TEST(runner, "find_first_even finds the first even number") {
    std::vector<int> vec = {1, 3, 4, 6, 7};
    ASSERT_EQ(find_first_even(vec), 4);
}

TEST(runner, "find_first_even returns -1 when no even numbers") {
    std::vector<int> vec = {1, 3, 5, 7};
    ASSERT_EQ(find_first_even(vec), -1);
}

TEST(runner, "find_first_even with empty vector") {
    std::vector<int> vec;
    ASSERT_EQ(find_first_even(vec), -1);
}

TEST(runner, "find_first_even with first element even") {
    std::vector<int> vec = {2, 3, 5};
    ASSERT_EQ(find_first_even(vec), 2);
}

TEST(runner, "count_strings_starting_with counts matching strings") {
    std::vector<std::string> vec = {"apple", "banana", "avocado", "cherry", "apricot"};
    ASSERT_EQ(count_strings_starting_with(vec, 'a'), 3);
}

TEST(runner, "count_strings_starting_with returns 0 when none match") {
    std::vector<std::string> vec = {"banana", "cherry"};
    ASSERT_EQ(count_strings_starting_with(vec, 'z'), 0);
}

TEST(runner, "count_strings_starting_with with empty vector") {
    std::vector<std::string> vec;
    ASSERT_EQ(count_strings_starting_with(vec, 'a'), 0);
}

TEST(runner, "find_first_longer_than finds matching string") {
    std::vector<std::string> vec = {"hi", "hello", "hey", "wonderful"};
    ASSERT_EQ(find_first_longer_than(vec, 3), std::string("hello"));
}

TEST(runner, "find_first_longer_than returns empty when none match") {
    std::vector<std::string> vec = {"a", "bb", "ccc"};
    ASSERT_EQ(find_first_longer_than(vec, 5), std::string(""));
}

TEST(runner, "find_first_longer_than with exact boundary") {
    std::vector<std::string> vec = {"abc", "abcd", "ab"};
    // "abc" has length 3, not longer than 3; "abcd" has length 4, longer than 3
    ASSERT_EQ(find_first_longer_than(vec, 3), std::string("abcd"));
}

TESTKIT_MAIN(runner)
