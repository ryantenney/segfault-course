// Exercise 04 -- Tests (read-only)
//
// Verifies CTAD deduction guide for Pair.

#include <testkit/testkit.h>
#include <string>
#include <type_traits>
#include "ex04.h"

static testkit::TestRunner runner("03-30-ex04: CTAD Guide");

TEST(runner, "create_pair creates a Pair with explicit types") {
    auto p = create_pair(42, std::string("hello"));
    ASSERT_EQ(p.key(), 42);
    ASSERT_EQ(p.value(), std::string("hello"));
}

TEST(runner, "Pair with explicit template arguments works") {
    // Gate: create_pair must work first
    create_pair(1, std::string("test"));

    Pair<int, std::string> p(1, std::string("hello"));
    ASSERT_EQ(p.key(), 1);
    ASSERT_EQ(p.value(), std::string("hello"));
}

TEST(runner, "CTAD deduces Pair<int, int> from two ints") {
    // Gate: create_pair must work first
    create_pair(1, std::string("test"));

    Pair p{10, 20};
    ASSERT_EQ(p.key(), 10);
    ASSERT_EQ(p.value(), 20);
    ASSERT_TRUE((std::is_same_v<decltype(p), Pair<int, int>>));
}

TEST(runner, "CTAD guide deduces std::string from const char*") {
    // Gate: create_pair must work first
    create_pair(1, std::string("test"));

    // Without the deduction guide, this creates Pair<int, const char*>.
    // With the guide, it creates Pair<int, std::string>.
    Pair p{1, "hello"};
    ASSERT_TRUE((std::is_same_v<decltype(p), Pair<int, std::string>>));
    ASSERT_EQ(p.key(), 1);
    ASSERT_EQ(p.value(), std::string("hello"));
}

TEST(runner, "CTAD guide works with different key types") {
    // Gate: create_pair must work first
    create_pair(1, std::string("test"));

    Pair p{std::string("key"), "value"};
    ASSERT_TRUE((std::is_same_v<decltype(p), Pair<std::string, std::string>>));
    ASSERT_EQ(p.key(), std::string("key"));
    ASSERT_EQ(p.value(), std::string("value"));
}

TEST(runner, "CTAD without guide keeps non-pointer types") {
    // Gate: create_pair must work first
    create_pair(1, std::string("test"));

    Pair p{3.14, 42};
    ASSERT_TRUE((std::is_same_v<decltype(p), Pair<double, int>>));
}

TESTKIT_MAIN(runner)
