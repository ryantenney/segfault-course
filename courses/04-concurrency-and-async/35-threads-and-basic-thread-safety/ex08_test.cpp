// Exercise 08 — Tests (read-only)
//
// These tests verify that:
//   1. parallel_sum computes the correct total.
//   2. parallel_sum works with various thread counts.

#include <testkit/testkit.h>
#include <numeric>
#include <vector>
#include "ex08.h"

static testkit::TestRunner runner("04-35-ex08: Launch N Threads");

TEST(runner, "parallel_sum with single thread") {
    std::vector<int> data = {1, 2, 3, 4, 5};
    long long result = parallel_sum(data, 1);  // gates on TODO()
    ASSERT_EQ(result, 15LL);
}

TEST(runner, "parallel_sum with multiple threads") {
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8};
    long long result = parallel_sum(data, 4);  // gates on TODO()
    ASSERT_EQ(result, 36LL);
}

TEST(runner, "parallel_sum with empty vector") {
    std::vector<int> data;
    long long result = parallel_sum(data, 2);  // gates on TODO()
    ASSERT_EQ(result, 0LL);
}

TEST(runner, "parallel_sum with more threads than elements") {
    std::vector<int> data = {10, 20, 30};
    long long result = parallel_sum(data, 8);  // gates on TODO()
    ASSERT_EQ(result, 60LL);
}

TEST(runner, "parallel_sum with large dataset") {
    std::vector<int> data(10000);
    std::iota(data.begin(), data.end(), 1);  // 1, 2, ..., 10000
    long long expected = static_cast<long long>(10000) * 10001 / 2;

    long long result = parallel_sum(data, 4);  // gates on TODO()
    ASSERT_EQ(result, expected);
}

TESTKIT_MAIN(runner)
