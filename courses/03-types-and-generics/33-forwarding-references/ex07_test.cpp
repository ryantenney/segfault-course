// Exercise 07 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex07.h"
#include <vector>

static testkit::TestRunner runner("03-33-ex07: Variadic Forwarding");

TEST(runner, "apply_to_each calls f for each argument") {
    std::vector<int> collected;
    auto collector = [&](int x) { collected.push_back(x); };
    apply_to_each(collector, 1, 2, 3);
    ASSERT_EQ(collected.size(), 3u);
    ASSERT_EQ(collected[0], 1);
    ASSERT_EQ(collected[1], 2);
    ASSERT_EQ(collected[2], 3);
}

TEST(runner, "apply_to_each with single argument") {
    int count = 0;
    auto counter = [&](int) { ++count; };
    apply_to_each(counter, 42);
    ASSERT_EQ(count, 1);
}

TEST(runner, "apply_to_each forwards lvalue by reference") {
    std::string s = "hello";
    auto appender = [](std::string& str) { str += "!"; };
    apply_to_each(appender, s);
    ASSERT_EQ(s, std::string("hello!"));
}

TEST(runner, "forward_to passes all args to target") {
    auto sum3 = [](int a, int b, int c) { return a + b + c; };
    auto result = forward_to(sum3, 10, 20, 30);
    ASSERT_EQ(result, 60);
}

TEST(runner, "forward_to preserves lvalue references") {
    std::string s = "original";
    auto modify = [](std::string& str, const std::string& suffix) {
        str += suffix;
    };
    forward_to(modify, s, std::string("_added"));
    ASSERT_EQ(s, std::string("original_added"));
}

TEST(runner, "count_args returns 0 for no args") {
    ASSERT_EQ(count_args(), 0u);
}

TEST(runner, "count_args returns correct count") {
    ASSERT_EQ(count_args(1), 1u);
    ASSERT_EQ(count_args(1, 2, 3), 3u);
    ASSERT_EQ(count_args("a", "b", "c", "d"), 4u);
}

TESTKIT_MAIN(runner)
