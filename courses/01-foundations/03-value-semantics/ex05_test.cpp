// Exercise 05 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex05.h"

static testkit::TestRunner runner("01-03-ex05: Swap via References");

TEST(runner, "swap_ints exchanges two values") {
    int a = 1, b = 2;
    swap_ints(a, b);
    ASSERT_EQ(a, 2);
    ASSERT_EQ(b, 1);
}

TEST(runner, "swap_ints handles equal values") {
    int a = 5, b = 5;
    swap_ints(a, b);
    ASSERT_EQ(a, 5);
    ASSERT_EQ(b, 5);
}

TEST(runner, "swap_ints handles negative values") {
    int a = -3, b = 7;
    swap_ints(a, b);
    ASSERT_EQ(a, 7);
    ASSERT_EQ(b, -3);
}

TEST(runner, "sort_three already sorted") {
    int a = 1, b = 2, c = 3;
    sort_three(a, b, c);
    ASSERT_EQ(a, 1);
    ASSERT_EQ(b, 2);
    ASSERT_EQ(c, 3);
}

TEST(runner, "sort_three reverse order") {
    int a = 9, b = 5, c = 1;
    sort_three(a, b, c);
    ASSERT_EQ(a, 1);
    ASSERT_EQ(b, 5);
    ASSERT_EQ(c, 9);
}

TEST(runner, "sort_three mixed order") {
    int a = 3, b = 1, c = 2;
    sort_three(a, b, c);
    ASSERT_EQ(a, 1);
    ASSERT_EQ(b, 2);
    ASSERT_EQ(c, 3);
}

TEST(runner, "sort_three with duplicates") {
    int a = 5, b = 3, c = 5;
    sort_three(a, b, c);
    ASSERT_EQ(a, 3);
    ASSERT_EQ(b, 5);
    ASSERT_EQ(c, 5);
}

TESTKIT_MAIN(runner)
