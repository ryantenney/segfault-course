// Exercise 04 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex04.h"

static testkit::TestRunner runner("03-33-ex04: Forward to Constructor");

TEST(runner, "construct_in_place creates a Widget") {
    auto w = construct_in_place<Widget>("test", 42);
    ASSERT_EQ(w.name, std::string("test"));
    ASSERT_EQ(w.value, 42);
}

TEST(runner, "construct_in_place creates a string") {
    auto s = construct_in_place<std::string>(5, 'x');
    ASSERT_EQ(s, std::string("xxxxx"));
}

TEST(runner, "construct_in_place forwards rvalue args (no extra copies)") {
    std::string name = "widget";
    auto w = construct_in_place<Widget>(std::move(name), 10);
    ASSERT_EQ(w.name, std::string("widget"));
    ASSERT_EQ(w.value, 10);
    // name was moved from
    ASSERT_TRUE(name.empty() || name == "(moved)");
}

TEST(runner, "construct_pair with string literals") {
    auto p = construct_pair("hello", "world");
    ASSERT_EQ(p.first, std::string("hello"));
    ASSERT_EQ(p.second, std::string("world"));
}

TEST(runner, "construct_pair forwards rvalue strings") {
    std::string a = "first";
    std::string b = "second";
    auto p = construct_pair(std::move(a), std::move(b));
    ASSERT_EQ(p.first, std::string("first"));
    ASSERT_EQ(p.second, std::string("second"));
}

TEST(runner, "construct_pair with mixed lvalue and rvalue") {
    std::string a = "left";
    auto p = construct_pair(a, std::string("right"));
    ASSERT_EQ(p.first, std::string("left"));
    ASSERT_EQ(p.second, std::string("right"));
    // a was passed as lvalue, so it should be unchanged
    ASSERT_EQ(a, std::string("left"));
}

TESTKIT_MAIN(runner)
