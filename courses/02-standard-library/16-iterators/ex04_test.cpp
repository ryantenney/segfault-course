// Exercise 04 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex04.h"

static testkit::TestRunner runner("02-16-ex04: Reverse Iteration");

TEST(runner, "reverse_copy_vec reverses the elements") {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    auto result = reverse_copy_vec(vec);
    ASSERT_EQ(result.size(), 5u);
    ASSERT_EQ(result[0], 5);
    ASSERT_EQ(result[1], 4);
    ASSERT_EQ(result[2], 3);
    ASSERT_EQ(result[3], 2);
    ASSERT_EQ(result[4], 1);
}

TEST(runner, "reverse_copy_vec with single element") {
    std::vector<int> vec = {42};
    auto result = reverse_copy_vec(vec);
    ASSERT_EQ(result.size(), 1u);
    ASSERT_EQ(result[0], 42);
}

TEST(runner, "reverse_copy_vec with empty vector") {
    std::vector<int> vec;
    auto result = reverse_copy_vec(vec);
    ASSERT_TRUE(result.empty());
}

TEST(runner, "last_n_elements returns last n in original order") {
    std::vector<int> vec = {10, 20, 30, 40, 50};
    auto result = last_n_elements(vec, 3);
    ASSERT_EQ(result.size(), 3u);
    ASSERT_EQ(result[0], 30);
    ASSERT_EQ(result[1], 40);
    ASSERT_EQ(result[2], 50);
}

TEST(runner, "last_n_elements with n >= size returns all") {
    std::vector<int> vec = {1, 2, 3};
    auto result = last_n_elements(vec, 10);
    ASSERT_EQ(result.size(), 3u);
    ASSERT_EQ(result[0], 1);
    ASSERT_EQ(result[1], 2);
    ASSERT_EQ(result[2], 3);
}

TEST(runner, "last_n_elements with n=0 returns empty") {
    std::vector<int> vec = {1, 2, 3};
    auto result = last_n_elements(vec, 0);
    ASSERT_TRUE(result.empty());
}

TEST(runner, "find_last returns index of last occurrence") {
    std::vector<int> vec = {1, 3, 5, 3, 7};
    ASSERT_EQ(find_last(vec, 3), 3);
}

TEST(runner, "find_last returns -1 when not found") {
    std::vector<int> vec = {1, 2, 3};
    ASSERT_EQ(find_last(vec, 99), -1);
}

TEST(runner, "find_last with single occurrence") {
    std::vector<int> vec = {10, 20, 30};
    ASSERT_EQ(find_last(vec, 10), 0);
}

TESTKIT_MAIN(runner)
