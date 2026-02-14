// Exercise 04 -- Tests (read-only)
//
// Each test calls ex04_gate() first. While the student hasn't removed
// TODO() from that gate, all tests show as "skipped" instead of failing.

#include <testkit/testkit.h>

#include "ex04.h"

static testkit::TestRunner runner("03-32-ex04: constexpr Variable");

TEST(runner, "squares_table[0] is 0") {
    ex04_gate();
    ASSERT_EQ(squares_table[0], 0);
}

TEST(runner, "squares_table[1] is 1") {
    ex04_gate();
    ASSERT_EQ(squares_table[1], 1);
}

TEST(runner, "squares_table[5] is 25") {
    ex04_gate();
    ASSERT_EQ(squares_table[5], 25);
}

TEST(runner, "squares_table[9] is 81") {
    ex04_gate();
    ASSERT_EQ(squares_table[9], 81);
}

TEST(runner, "is_lower['a'] is true") {
    ex04_gate();
    ASSERT_TRUE(is_lower['a']);
}

TEST(runner, "is_lower['z'] is true") {
    ex04_gate();
    ASSERT_TRUE(is_lower['z']);
}

TEST(runner, "is_lower['m'] is true") {
    ex04_gate();
    ASSERT_TRUE(is_lower['m']);
}

TEST(runner, "is_lower['A'] is false") {
    ex04_gate();
    ASSERT_FALSE(is_lower['A']);
}

TEST(runner, "is_lower['0'] is false") {
    ex04_gate();
    ASSERT_FALSE(is_lower['0']);
}

TEST(runner, "is_lower[' '] is false") {
    ex04_gate();
    ASSERT_FALSE(is_lower[' ']);
}

TESTKIT_MAIN(runner)
