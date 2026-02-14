// Exercise 08 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex08.h"

static testkit::TestRunner runner("02-17-ex08: Predicate Composition");

TEST(runner, "has_negative returns true when negatives exist") {
    std::vector<int> vec = {1, -2, 3};
    ASSERT_TRUE(has_negative(vec));
}

TEST(runner, "has_negative returns false when no negatives") {
    std::vector<int> vec = {1, 0, 3};
    ASSERT_FALSE(has_negative(vec));
}

TEST(runner, "has_negative returns false for empty vector") {
    std::vector<int> vec;
    ASSERT_FALSE(has_negative(vec));
}

TEST(runner, "all_positive returns true when all positive") {
    std::vector<int> vec = {1, 2, 3};
    ASSERT_TRUE(all_positive(vec));
}

TEST(runner, "all_positive returns false when zero present") {
    std::vector<int> vec = {1, 0, 3};
    ASSERT_FALSE(all_positive(vec));
}

TEST(runner, "all_positive returns false when negative present") {
    std::vector<int> vec = {1, -1, 3};
    ASSERT_FALSE(all_positive(vec));
}

TEST(runner, "all_positive returns true for empty vector") {
    std::vector<int> vec;
    ASSERT_TRUE(all_positive(vec));
}

TEST(runner, "none_empty returns true when no strings are empty") {
    std::vector<std::string> vec = {"hello", "world"};
    ASSERT_TRUE(none_empty(vec));
}

TEST(runner, "none_empty returns false when empty string present") {
    std::vector<std::string> vec = {"hello", "", "world"};
    ASSERT_FALSE(none_empty(vec));
}

TEST(runner, "none_empty returns true for empty vector") {
    std::vector<std::string> vec;
    ASSERT_TRUE(none_empty(vec));
}

TEST(runner, "classify_numbers returns empty for empty vector") {
    std::vector<int> vec;
    ASSERT_EQ(classify_numbers(vec), std::string("empty"));
}

TEST(runner, "classify_numbers returns all positive") {
    std::vector<int> vec = {1, 2, 3};
    ASSERT_EQ(classify_numbers(vec), std::string("all positive"));
}

TEST(runner, "classify_numbers returns all negative") {
    std::vector<int> vec = {-1, -2, -3};
    ASSERT_EQ(classify_numbers(vec), std::string("all negative"));
}

TEST(runner, "classify_numbers returns mixed for positive and negative") {
    std::vector<int> vec = {1, -2, 3};
    ASSERT_EQ(classify_numbers(vec), std::string("mixed"));
}

TEST(runner, "classify_numbers returns mixed when zero present") {
    std::vector<int> vec = {0, 1, 2};
    ASSERT_EQ(classify_numbers(vec), std::string("mixed"));
}

TEST(runner, "classify_numbers returns mixed for only zeros") {
    std::vector<int> vec = {0, 0, 0};
    ASSERT_EQ(classify_numbers(vec), std::string("mixed"));
}

TESTKIT_MAIN(runner)
