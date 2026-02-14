// Exercise 04 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex04.h"

static testkit::TestRunner runner("01-04-ex04: Build a String");

TEST(runner, "make_greeting builds Hello, <name>!") {
    ASSERT_EQ(make_greeting("Alice"), std::string("Hello, Alice!"));
    ASSERT_EQ(make_greeting("World"), std::string("Hello, World!"));
    ASSERT_EQ(make_greeting(""), std::string("Hello, !"));
}

TEST(runner, "make_tag wraps label in brackets") {
    ASSERT_EQ(make_tag("ERROR"), std::string("[ERROR]"));
    ASSERT_EQ(make_tag("INFO"), std::string("[INFO]"));
    ASSERT_EQ(make_tag(""), std::string("[]"));
}

TEST(runner, "make_pair joins key and value with equals sign") {
    ASSERT_EQ(make_pair("host", "localhost"), std::string("host=localhost"));
    ASSERT_EQ(make_pair("port", "8080"), std::string("port=8080"));
    ASSERT_EQ(make_pair("key", ""), std::string("key="));
}

TEST(runner, "join_path joins three segments with slashes") {
    ASSERT_EQ(join_path("usr", "local", "bin"), std::string("usr/local/bin"));
    ASSERT_EQ(join_path("home", "user", "docs"), std::string("home/user/docs"));
    ASSERT_EQ(join_path("a", "b", "c"), std::string("a/b/c"));
}

TESTKIT_MAIN(runner)
