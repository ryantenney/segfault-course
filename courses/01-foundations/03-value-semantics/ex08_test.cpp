// Exercise 08 — Tests (read-only)

#include <testkit/testkit.h>
#include <string>
#include <vector>

#include "ex08.h"

static testkit::TestRunner runner("01-03-ex08: Dangling Reference");

TEST(runner, "safe_max returns the longer string by value") {
    std::string a = "hi";
    std::string b = "hello";
    std::string result = safe_max(a, b);
    ASSERT_EQ(result, std::string("hello"));
}

TEST(runner, "safe_max returns first on tie") {
    std::string a = "abc";
    std::string b = "def";
    std::string result = safe_max(a, b);
    ASSERT_EQ(result, std::string("abc"));
}

TEST(runner, "safe_max_ref returns reference to the longer parameter") {
    std::string a = "short";
    std::string b = "much longer";
    const std::string& result = safe_max_ref(a, b);
    ASSERT_EQ(result, std::string("much longer"));
    // Verify it's actually a reference to b, not a copy
    ASSERT_TRUE(&result == &b);
}

TEST(runner, "safe_max_ref returns reference to first on tie") {
    std::string a = "abc";
    std::string b = "xyz";
    const std::string& result = safe_max_ref(a, b);
    ASSERT_TRUE(&result == &a);
}

TEST(runner, "first_or_default returns first element when vector is non-empty") {
    std::vector<std::string> v = {"alpha", "beta", "gamma"};
    std::string fallback = "none";
    const std::string& result = first_or_default(v, fallback);
    ASSERT_EQ(result, std::string("alpha"));
    ASSERT_TRUE(&result == &v[0]);
}

TEST(runner, "first_or_default returns fallback when vector is empty") {
    std::vector<std::string> v;
    std::string fallback = "default_value";
    const std::string& result = first_or_default(v, fallback);
    ASSERT_EQ(result, std::string("default_value"));
    ASSERT_TRUE(&result == &fallback);
}

TESTKIT_MAIN(runner)
