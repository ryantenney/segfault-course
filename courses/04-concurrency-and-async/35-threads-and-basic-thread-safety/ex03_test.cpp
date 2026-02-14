// Exercise 03 — Tests (read-only)
//
// These tests verify that:
//   1. fill_vector pushes the correct values.
//   2. fill_vector works from a jthread (auto-join).

#include <testkit/testkit.h>
#include <thread>
#include <vector>
#include "ex03.h"

static testkit::TestRunner runner("04-35-ex03: jthread Basics");

TEST(runner, "fill_vector pushes 0..count-1") {
    std::vector<int> v;
    fill_vector(v, 5);  // gates on TODO()
    ASSERT_EQ(v.size(), 5u);
    ASSERT_EQ(v[0], 0);
    ASSERT_EQ(v[1], 1);
    ASSERT_EQ(v[4], 4);
}

TEST(runner, "fill_vector with count 0 leaves vector empty") {
    std::vector<int> v;
    fill_vector(v, 0);  // gates on TODO()
    ASSERT_EQ(v.size(), 0u);
}

TEST(runner, "fill_vector works from a jthread") {
    std::vector<int> v;
    fill_vector(v, 1);  // gate
    v.clear();           // reset

    {
        std::jthread jt([&v] { fill_vector(v, 10); });
        // jthread joins automatically at end of scope
    }
    ASSERT_EQ(v.size(), 10u);
    ASSERT_EQ(v[0], 0);
    ASSERT_EQ(v[9], 9);
}

TESTKIT_MAIN(runner)
