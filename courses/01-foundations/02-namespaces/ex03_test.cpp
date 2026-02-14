// Exercise 03 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex03.h"

static testkit::TestRunner runner("01-02-ex03: Using Declarations");

TEST(runner, "build_and_sum adds three numbers via vector") {
    ASSERT_EQ(test_helpers::build_and_sum(1, 2, 3), 6);
    ASSERT_EQ(test_helpers::build_and_sum(10, 20, 30), 60);
    ASSERT_EQ(test_helpers::build_and_sum(-1, 0, 1), 0);
}

TEST(runner, "build_and_product multiplies three numbers via vector") {
    ASSERT_EQ(test_helpers::build_and_product(2, 3, 4), 24);
    ASSERT_EQ(test_helpers::build_and_product(1, 1, 1), 1);
    ASSERT_EQ(test_helpers::build_and_product(5, 0, 10), 0);
}

TESTKIT_MAIN(runner)
