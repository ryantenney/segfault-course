// Exercise 08 — Tests (read-only)
//
// Verifies understanding of initializer_list ambiguity.

#include <testkit/testkit.h>
#include <vector>
#include <string>
#include "ex08.h"

static testkit::TestRunner runner("03-25-ex08: initializer_list Ambiguity");

TEST(runner, "vector<int>(10, 3) has 10 elements") {
    ASSERT_EQ(paren_count_value_size(), 10);
}

TEST(runner, "vector<int>(10, 3) first element is 3") {
    ASSERT_EQ(paren_count_value_first(), 3);
}

TEST(runner, "vector<int>{10, 3} has 2 elements") {
    ASSERT_EQ(brace_two_ints_size(), 2);
}

TEST(runner, "vector<int>{10, 3} first element is 10") {
    ASSERT_EQ(brace_two_ints_first(), 10);
}

TEST(runner, "vector<int>{10, 3} second element is 3") {
    ASSERT_EQ(brace_two_ints_second(), 3);
}

TEST(runner, "vector<string>(3) has 3 elements") {
    ASSERT_EQ(string_vec_paren_size(), 3);
}

TEST(runner, "vector<string>{a, b, c} has 3 elements") {
    ASSERT_EQ(string_vec_brace_size(), 3);
}

TEST(runner, "make_filled_vector has 5 elements all equal to 42") {
    auto v = make_filled_vector();
    ASSERT_EQ(static_cast<int>(v.size()), 5);
    for (int x : v) {
        ASSERT_EQ(x, 42);
    }
}

TEST(runner, "make_literal_vector has exactly {5, 42}") {
    auto v = make_literal_vector();
    ASSERT_EQ(static_cast<int>(v.size()), 2);
    ASSERT_EQ(v[0], 5);
    ASSERT_EQ(v[1], 42);
}

TESTKIT_MAIN(runner)
