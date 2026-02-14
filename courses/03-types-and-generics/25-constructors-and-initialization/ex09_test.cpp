// Exercise 09 — Tests (read-only)
//
// Verifies understanding and fixes for the most vexing parse.

#include <testkit/testkit.h>
#include <string>
#include "ex09.h"

static testkit::TestRunner runner("03-25-ex09: Most Vexing Parse");

TEST(runner, "default_counter_value returns 0") {
    ASSERT_EQ(default_counter_value(), 0);
}

TEST(runner, "incremented_counter returns 13") {
    ASSERT_EQ(incremented_counter(), 13);
}

TEST(runner, "five_x_chars returns xxxxx") {
    ASSERT_EQ(five_x_chars(), std::string("xxxxx"));
}

TEST(runner, "five_x_chars has length 5") {
    ASSERT_EQ(static_cast<int>(five_x_chars().size()), 5);
}

TEST(runner, "empty_string_length returns 0") {
    ASSERT_EQ(empty_string_length(), 0);
}

TESTKIT_MAIN(runner)
