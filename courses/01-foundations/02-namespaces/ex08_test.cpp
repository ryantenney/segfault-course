// Exercise 08 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex08.h"

static testkit::TestRunner runner("01-02-ex08: ADL-Friendly Swap");

TEST(runner, "Pair::swap exchanges contents") {
    container::Pair a{1, 2};
    container::Pair b{3, 4};
    a.swap(b);
    ASSERT_EQ(a.first, 3);
    ASSERT_EQ(a.second, 4);
    ASSERT_EQ(b.first, 1);
    ASSERT_EQ(b.second, 2);
}

TEST(runner, "free swap via ADL exchanges two Pairs") {
    container::Pair a{10, 20};
    container::Pair b{30, 40};
    // Unqualified call — ADL finds container::swap
    generic_swap_pairs(a, b);
    ASSERT_EQ(a.first, 30);
    ASSERT_EQ(a.second, 40);
    ASSERT_EQ(b.first, 10);
    ASSERT_EQ(b.second, 20);
}

TEST(runner, "sort_pair puts smaller value in first") {
    container::Pair p{5, 2};
    sort_pair(p);
    ASSERT_EQ(p.first, 2);
    ASSERT_EQ(p.second, 5);
}

TEST(runner, "sort_pair leaves already-sorted pair unchanged") {
    container::Pair p{1, 9};
    sort_pair(p);
    ASSERT_EQ(p.first, 1);
    ASSERT_EQ(p.second, 9);
}

TEST(runner, "sort_pair handles equal values") {
    container::Pair p{7, 7};
    sort_pair(p);
    ASSERT_EQ(p.first, 7);
    ASSERT_EQ(p.second, 7);
}

TESTKIT_MAIN(runner)
