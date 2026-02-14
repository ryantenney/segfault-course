// Exercise 05 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex05.h"

static testkit::TestRunner runner("01-06-ex05: decltype for Expression Types");

TEST(runner, "sum_with_decltype returns the sum") {
    ASSERT_EQ(sum_with_decltype({1, 2, 3, 4}), 10);
    ASSERT_EQ(sum_with_decltype({}), 0);
    ASSERT_EQ(sum_with_decltype({-5, 5}), 0);
}

TEST(runner, "deduced_size returns the vector size") {
    std::vector<std::string> v = {"a", "b", "c"};
    ASSERT_EQ(deduced_size(v), 3u);
    ASSERT_EQ(deduced_size({}), 0u);
}

TEST(runner, "multiply_add computes a*b+c") {
    ASSERT_EQ(multiply_add(2.0, 3.0, 1.0), 7.0);
    ASSERT_EQ(multiply_add(0.0, 5.0, 10.0), 10.0);
    ASSERT_EQ(multiply_add(-1.0, 4.0, 4.0), 0.0);
}

TEST(runner, "reversed returns a reversed copy") {
    ASSERT_EQ(reversed("hello"), "olleh");
    ASSERT_EQ(reversed("a"), "a");
    ASSERT_EQ(reversed(""), std::string(""));
    ASSERT_EQ(reversed("abcde"), "edcba");
}

TESTKIT_MAIN(runner)
