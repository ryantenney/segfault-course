// Exercise 03 -- Tests (read-only)
//
// Verifies Pair<K, V> construction, accessors, and comparison operators.

#include <testkit/testkit.h>
#include <string>
#include "ex03.h"

static testkit::TestRunner runner("03-30-ex03: Key-Value Pair");

TEST(runner, "construct and access key/value") {
    Pair<int, std::string> p(1, "hello");
    ASSERT_EQ(p.key(), 1);
    ASSERT_EQ(p.value(), std::string("hello"));
}

TEST(runner, "works with different types") {
    Pair<std::string, double> p("pi", 3.14);
    ASSERT_EQ(p.key(), std::string("pi"));
    ASSERT_TRUE(p.value() == 3.14);
}

TEST(runner, "equality -- same key and value") {
    Pair<int, int> a(1, 2);
    Pair<int, int> b(1, 2);
    ASSERT_TRUE(a == b);
    ASSERT_FALSE(a != b);
}

TEST(runner, "inequality -- different keys") {
    Pair<int, int> a(1, 2);
    Pair<int, int> b(3, 2);
    ASSERT_FALSE(a == b);
    ASSERT_TRUE(a != b);
}

TEST(runner, "inequality -- different values") {
    Pair<int, int> a(1, 2);
    Pair<int, int> b(1, 5);
    ASSERT_FALSE(a == b);
    ASSERT_TRUE(a != b);
}

TEST(runner, "less-than compares by key first") {
    Pair<int, int> a(1, 100);
    Pair<int, int> b(2, 1);
    ASSERT_TRUE(a < b);
    ASSERT_FALSE(b < a);
}

TEST(runner, "less-than compares by value when keys equal") {
    Pair<int, int> a(1, 2);
    Pair<int, int> b(1, 5);
    ASSERT_TRUE(a < b);
    ASSERT_FALSE(b < a);
}

TEST(runner, "less-than is false for equal pairs") {
    Pair<int, int> a(3, 3);
    Pair<int, int> b(3, 3);
    ASSERT_FALSE(a < b);
    ASSERT_FALSE(b < a);
}

TESTKIT_MAIN(runner)
