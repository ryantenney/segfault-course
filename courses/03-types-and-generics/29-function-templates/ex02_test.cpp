// Exercise 02 -- Tests (read-only)
//
// Verifies templates with multiple type parameters.

#include <string>
#include <testkit/testkit.h>
#include "ex02.h"

static testkit::TestRunner runner("03-29-ex02: Multiple Type Parameters");

TEST(runner, "convert int to double") {
    double result = convert<double>(42);
    ASSERT_TRUE(result > 41.9 && result < 42.1);
}

TEST(runner, "convert double to int truncates") {
    int result = convert<int>(3.99);
    ASSERT_EQ(result, 3);
}

TEST(runner, "convert int to char") {
    char result = convert<char>(65);
    ASSERT_EQ(result, 'A');
}

TEST(runner, "convert char to int") {
    int result = convert<int>('A');
    ASSERT_EQ(result, 65);
}

TEST(runner, "make_pair_of with same types") {
    auto p = make_pair_of(1, 2);
    ASSERT_EQ(p.first, 1);
    ASSERT_EQ(p.second, 2);
}

TEST(runner, "make_pair_of with different types") {
    auto p = make_pair_of(std::string("hello"), 42);
    ASSERT_EQ(p.first, std::string("hello"));
    ASSERT_EQ(p.second, 42);
}

TEST(runner, "make_pair_of with double and int") {
    auto p = make_pair_of(3.14, 7);
    ASSERT_TRUE(p.first > 3.13 && p.first < 3.15);
    ASSERT_EQ(p.second, 7);
}

TESTKIT_MAIN(runner)
