// Exercise 08 -- Tests (read-only)
//
// Verifies variadic template functions.

#include <string>
#include <testkit/testkit.h>
#include "ex08.h"

static testkit::TestRunner runner("03-29-ex08: Variadic Template Intro");

TEST(runner, "concat_all with single int") {
    ASSERT_EQ(concat_all(42), std::string("42"));
}

TEST(runner, "concat_all with single string") {
    ASSERT_EQ(concat_all("hello"), std::string("hello"));
}

TEST(runner, "concat_all with multiple ints") {
    ASSERT_EQ(concat_all(1, 2, 3), std::string("123"));
}

TEST(runner, "concat_all with mixed types") {
    ASSERT_EQ(concat_all("age: ", 25, " years"), std::string("age: 25 years"));
}

TEST(runner, "concat_all with many arguments") {
    ASSERT_EQ(concat_all("a", "b", "c", "d", "e"), std::string("abcde"));
}

TEST(runner, "concat_all with int and double") {
    std::string result = concat_all(3, " + ", 4, " = ", 7);
    ASSERT_EQ(result, std::string("3 + 4 = 7"));
}

TEST(runner, "count_args with zero arguments") {
    ASSERT_EQ(count_args(), 0u);
}

TEST(runner, "count_args with one argument") {
    ASSERT_EQ(count_args(42), 1u);
}

TEST(runner, "count_args with multiple arguments") {
    ASSERT_EQ(count_args(1, 2, 3), 3u);
}

TEST(runner, "count_args with mixed types") {
    ASSERT_EQ(count_args(1, "hello", 3.14, true), 4u);
}

TESTKIT_MAIN(runner)
