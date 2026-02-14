// Exercise 02 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex02.h"

static testkit::TestRunner runner("03-33-ex02: Reference Collapsing");

TEST(runner, "collapsed_type_is_lref<int> is true") {
    ASSERT_TRUE(collapsed_type_is_lref<int>());
}

TEST(runner, "collapsed_type_is_lref<int&> is true (& + & => &)") {
    ASSERT_TRUE(collapsed_type_is_lref<int&>());
}

TEST(runner, "collapsed_type_is_lref<int&&> is true (&& + & => &)") {
    ASSERT_TRUE(collapsed_type_is_lref<int&&>());
}

TEST(runner, "deduce_and_report with lvalue deduces T=lref") {
    int x = 42;
    ASSERT_EQ(deduce_and_report(x), std::string("T=lref"));
}

TEST(runner, "deduce_and_report with rvalue deduces T=nonref") {
    ASSERT_EQ(deduce_and_report(42), std::string("T=nonref"));
}

TEST(runner, "deduce_and_report with string lvalue deduces T=lref") {
    std::string s = "hello";
    ASSERT_EQ(deduce_and_report(s), std::string("T=lref"));
}

TEST(runner, "apply_collapse<int> => rvalue_ref (int&& stays int&&)") {
    ASSERT_EQ(apply_collapse<int>(), std::string("rvalue_ref"));
}

TEST(runner, "apply_collapse<int&> => lvalue_ref (int& && collapses to int&)") {
    ASSERT_EQ(apply_collapse<int&>(), std::string("lvalue_ref"));
}

TEST(runner, "apply_collapse<int&&> => rvalue_ref (int&& && collapses to int&&)") {
    ASSERT_EQ(apply_collapse<int&&>(), std::string("rvalue_ref"));
}

TESTKIT_MAIN(runner)
