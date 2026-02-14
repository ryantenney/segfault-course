// Exercise 06 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex06.h"

#include <stdexcept>

static testkit::TestRunner runner("02-14-ex06: Fixed-Size with std::array");

TEST(runner, "make_zeros returns an array of five zeros") {
    auto arr = make_zeros();
    ASSERT_EQ(arr.size(), 5u);
    for (std::size_t i = 0; i < arr.size(); ++i) {
        ASSERT_EQ(arr[i], 0);
    }
}

TEST(runner, "array_sum returns the sum of all elements") {
    std::array<int, 5> a = {1, 2, 3, 4, 5};
    ASSERT_EQ(array_sum(a), 15);
}

TEST(runner, "array_sum of zeros is zero") {
    std::array<int, 5> a = {0, 0, 0, 0, 0};
    ASSERT_EQ(array_sum(a), 0);
}

TEST(runner, "array_sum with negative numbers") {
    std::array<int, 5> a = {-1, -2, 3, 4, -5};
    ASSERT_EQ(array_sum(a), -1);
}

TEST(runner, "safe_array_access returns the correct element") {
    std::array<int, 5> a = {10, 20, 30, 40, 50};
    ASSERT_EQ(safe_array_access(a, 0), 10);
    ASSERT_EQ(safe_array_access(a, 4), 50);
}

TEST(runner, "safe_array_access throws on out-of-range index") {
    std::array<int, 5> a = {10, 20, 30, 40, 50};
    ASSERT_THROWS(safe_array_access(a, 5), std::out_of_range);
    ASSERT_THROWS(safe_array_access(a, 100), std::out_of_range);
}

TEST(runner, "reverse_array reverses the elements") {
    std::array<int, 5> a = {1, 2, 3, 4, 5};
    auto r = reverse_array(a);
    ASSERT_EQ(r[0], 5);
    ASSERT_EQ(r[1], 4);
    ASSERT_EQ(r[2], 3);
    ASSERT_EQ(r[3], 2);
    ASSERT_EQ(r[4], 1);
}

TEST(runner, "reverse_array does not modify the original") {
    std::array<int, 5> a = {1, 2, 3, 4, 5};
    reverse_array(a);
    ASSERT_EQ(a[0], 1);
    ASSERT_EQ(a[4], 5);
}

TESTKIT_MAIN(runner)
