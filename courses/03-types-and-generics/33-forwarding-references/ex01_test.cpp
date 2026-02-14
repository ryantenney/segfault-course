// Exercise 01 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex01.h"

static testkit::TestRunner runner("03-33-ex01: Forwarding Reference vs Rvalue Reference");

TEST(runner, "is_forwarding_ref_call passes an lvalue to identify()") {
    ASSERT_EQ(is_forwarding_ref_call(), std::string("lvalue"));
}

TEST(runner, "takes_rvalue_only calls consume with std::move") {
    ASSERT_EQ(takes_rvalue_only("hello"), std::string("consumed: hello"));
}

TEST(runner, "classify_argument detects lvalue") {
    std::string s = "test";
    ASSERT_EQ(classify_argument(s), std::string("lvalue"));
}

TEST(runner, "classify_argument detects rvalue") {
    ASSERT_EQ(classify_argument(std::string("temp")), std::string("rvalue"));
}

TEST(runner, "classify_argument detects int lvalue") {
    int x = 5;
    ASSERT_EQ(classify_argument(x), std::string("lvalue"));
}

TEST(runner, "classify_argument detects int rvalue") {
    ASSERT_EQ(classify_argument(42), std::string("rvalue"));
}

TESTKIT_MAIN(runner)
