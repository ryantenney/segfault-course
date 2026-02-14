// Exercise 06 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex06.h"

#include <string>

static testkit::TestRunner runner("02-20-ex06: Replace std::bind with Lambda");

TEST(runner, "lambda_add_10 matches bind_add_10") {
    auto bind_fn = bind_add_10();
    auto lambda_fn = lambda_add_10();
    ASSERT_EQ(lambda_fn(5), bind_fn(5));
    ASSERT_EQ(lambda_fn(0), bind_fn(0));
    ASSERT_EQ(lambda_fn(-3), bind_fn(-3));
}

TEST(runner, "lambda_add_10 adds 10 to argument") {
    auto fn = lambda_add_10();
    ASSERT_EQ(fn(5), 15);
    ASSERT_EQ(fn(0), 10);
    ASSERT_EQ(fn(100), 110);
}

TEST(runner, "lambda_triple matches bind_triple") {
    auto bind_fn = bind_triple();
    auto lambda_fn = lambda_triple();
    ASSERT_EQ(lambda_fn(7), bind_fn(7));
    ASSERT_EQ(lambda_fn(0), bind_fn(0));
    ASSERT_EQ(lambda_fn(-2), bind_fn(-2));
}

TEST(runner, "lambda_triple triples the argument") {
    auto fn = lambda_triple();
    ASSERT_EQ(fn(4), 12);
    ASSERT_EQ(fn(0), 0);
    ASSERT_EQ(fn(10), 30);
}

TEST(runner, "lambda_swap_greet matches bind_swap_greet") {
    auto bind_fn = bind_swap_greet();
    auto lambda_fn = lambda_swap_greet();
    ASSERT_EQ(lambda_fn("Alice", "Hello"), bind_fn("Alice", "Hello"));
    ASSERT_EQ(lambda_fn("World", "Goodbye"), bind_fn("World", "Goodbye"));
}

TEST(runner, "lambda_swap_greet swaps its arguments") {
    auto fn = lambda_swap_greet();
    // fn("Alice", "Hello") should call greet("Hello", "Alice")
    ASSERT_EQ(fn("Alice", "Hello"), std::string("Hello, Alice!"));
    ASSERT_EQ(fn("World", "Hi"), std::string("Hi, World!"));
}

TESTKIT_MAIN(runner)
