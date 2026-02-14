// Exercise 05 — Tests (read-only)
//
// These tests verify that:
//   1. async_transform returns futures for each input element.
//   2. Each future resolves to the square of its input.

#include <testkit/testkit.h>
#include <future>
#include <vector>
#include "ex05.h"

static testkit::TestRunner runner("04-39-ex05: Multiple Futures");

TEST(runner, "async_transform returns correct number of futures") {
    std::vector<int> input = {1, 2, 3, 4, 5};
    auto futures = async_transform(input);
    ASSERT_EQ(futures.size(), static_cast<std::size_t>(5));
    // Consume all futures to avoid potential issues.
    for (auto& f : futures) { f.get(); }
}

TEST(runner, "each future resolves to the square of its input") {
    std::vector<int> input = {2, 3, 4};
    auto futures = async_transform(input);
    ASSERT_EQ(futures[0].get(), 4);
    ASSERT_EQ(futures[1].get(), 9);
    ASSERT_EQ(futures[2].get(), 16);
}

TEST(runner, "empty input produces empty output") {
    std::vector<int> input = {};
    auto futures = async_transform(input);
    ASSERT_EQ(futures.size(), static_cast<std::size_t>(0));
}

TEST(runner, "works with negative values") {
    std::vector<int> input = {-3, -5};
    auto futures = async_transform(input);
    ASSERT_EQ(futures[0].get(), 9);
    ASSERT_EQ(futures[1].get(), 25);
}

TESTKIT_MAIN(runner)
