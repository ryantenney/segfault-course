// Exercise 08 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex08.h"

static testkit::TestRunner runner("03-33-ex08: decltype(auto) Return");

TEST(runner, "forward_result returns value from value-returning function") {
    auto add = [](int a, int b) { return a + b; };
    auto result = forward_result(add, 3, 7);
    ASSERT_EQ(result, 10);
}

TEST(runner, "forward_result preserves reference return") {
    int x = 42;
    auto get_ref = [&x]() -> int& { return x; };
    decltype(auto) ref = forward_result(get_ref);
    // ref should be a reference to x
    ref = 100;
    ASSERT_EQ(x, 100);
}

TEST(runner, "forward_result preserves const reference return") {
    const std::string s = "hello";
    auto get_cref = [&s]() -> const std::string& { return s; };
    decltype(auto) ref = forward_result(get_cref);
    ASSERT_EQ(ref, std::string("hello"));
    // ref should be const std::string&, pointing to s
    ASSERT_TRUE(&ref == &s);
}

TEST(runner, "forward_result forwards arguments correctly") {
    std::string s = "base";
    auto append = [](std::string& str, const char* suffix) -> std::string& {
        str += suffix;
        return str;
    };
    decltype(auto) ref = forward_result(append, s, "_ext");
    ASSERT_EQ(s, std::string("base_ext"));
    ASSERT_TRUE(&ref == &s);
}

TEST(runner, "get_or_default returns pointed-to value when non-null") {
    int x = 42;
    const int& result = get_or_default(&x, 0);
    ASSERT_EQ(result, 42);
    ASSERT_TRUE(&result == &x);
}

TEST(runner, "get_or_default returns default when null") {
    int fallback = 99;
    const int& result = get_or_default<int>(nullptr, fallback);
    ASSERT_EQ(result, 99);
    ASSERT_TRUE(&result == &fallback);
}

TEST(runner, "get_or_default works with strings") {
    std::string s = "found";
    std::string def = "default";
    const std::string& result = get_or_default(&s, def);
    ASSERT_EQ(result, std::string("found"));
    ASSERT_TRUE(&result == &s);
}

TEST(runner, "get_or_default returns default string when null") {
    std::string def = "fallback";
    const std::string& result = get_or_default<std::string>(nullptr, def);
    ASSERT_EQ(result, std::string("fallback"));
    ASSERT_TRUE(&result == &def);
}

TESTKIT_MAIN(runner)
