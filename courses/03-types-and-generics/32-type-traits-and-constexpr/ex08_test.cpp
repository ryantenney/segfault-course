// Exercise 08 -- Tests (read-only)
//
// Tests call the constexpr functions at RUNTIME via ASSERT_EQ so that
// TODO() produces "skipped" rather than a compile-time error.

#include <testkit/testkit.h>

#include "ex08.h"

static testkit::TestRunner runner("03-32-ex08: constexpr with std::array");

TEST(runner, "constexpr_iota<5> produces {0,1,2,3,4}") {
    auto arr = constexpr_iota<5>();
    ASSERT_EQ(arr[0], 0);
    ASSERT_EQ(arr[1], 1);
    ASSERT_EQ(arr[4], 4);
}

TEST(runner, "constexpr_iota<1> produces {0}") {
    auto arr = constexpr_iota<1>();
    ASSERT_EQ(arr[0], 0);
}

TEST(runner, "constexpr_sum of {1,2,3,4,5}") {
    std::array<int, 5> arr = {1, 2, 3, 4, 5};
    ASSERT_EQ(constexpr_sum(arr), 15);
}

TEST(runner, "constexpr_sum of empty array is 0") {
    std::array<int, 0> arr = {};
    ASSERT_EQ(constexpr_sum(arr), 0);
}

TEST(runner, "constexpr_sum of single element") {
    std::array<int, 1> arr = {42};
    ASSERT_EQ(constexpr_sum(arr), 42);
}

TEST(runner, "constexpr_reverse of {1,2,3} is {3,2,1}") {
    std::array<int, 3> arr = {1, 2, 3};
    auto rev = constexpr_reverse(arr);
    ASSERT_EQ(rev[0], 3);
    ASSERT_EQ(rev[1], 2);
    ASSERT_EQ(rev[2], 1);
}

TEST(runner, "constexpr_reverse of single element") {
    std::array<int, 1> arr = {99};
    auto rev = constexpr_reverse(arr);
    ASSERT_EQ(rev[0], 99);
}

TEST(runner, "constexpr_contains finds existing value") {
    std::array<int, 4> arr = {10, 20, 30, 40};
    ASSERT_TRUE(constexpr_contains(arr, 30));
}

TEST(runner, "constexpr_contains returns false for missing value") {
    std::array<int, 4> arr = {10, 20, 30, 40};
    ASSERT_FALSE(constexpr_contains(arr, 25));
}

TEST(runner, "constexpr_contains on empty array returns false") {
    std::array<int, 0> arr = {};
    ASSERT_FALSE(constexpr_contains(arr, 1));
}

TESTKIT_MAIN(runner)
