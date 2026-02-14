// Exercise 04 -- Tests (read-only)
//
// Verifies that Config has all five special members explicitly defaulted.

#include <type_traits>
#include <testkit/testkit.h>
#include "ex04.h"

static testkit::TestRunner runner("03-28-ex04: The = default Keyword");

TEST(runner, "constructor initializes members") {
    Config c("host", "localhost", 10);
    ASSERT_EQ(c.key(), std::string("host"));
    ASSERT_EQ(c.value(), std::string("localhost"));
    ASSERT_EQ(c.priority(), 10);
}

TEST(runner, "is copy constructible") {
    Config c("k", "v", 1);
    (void)c.key();

    ASSERT_TRUE(std::is_copy_constructible_v<Config>);
}

TEST(runner, "copy constructor works") {
    Config a("port", "8080", 5);
    Config b(a);
    ASSERT_EQ(b.key(), std::string("port"));
    ASSERT_EQ(b.value(), std::string("8080"));
    ASSERT_EQ(b.priority(), 5);
}

TEST(runner, "is copy assignable") {
    Config c("k", "v", 1);
    (void)c.key();

    ASSERT_TRUE(std::is_copy_assignable_v<Config>);
}

TEST(runner, "copy assignment works") {
    Config a("host", "example.com", 3);
    Config b("tmp", "tmp", 0);
    b = a;
    ASSERT_EQ(b.key(), std::string("host"));
    ASSERT_EQ(b.value(), std::string("example.com"));
    ASSERT_EQ(b.priority(), 3);
}

TEST(runner, "is move constructible") {
    Config c("k", "v", 1);
    (void)c.key();

    ASSERT_TRUE(std::is_move_constructible_v<Config>);
}

TEST(runner, "move constructor works") {
    Config a("host", "example.com", 3);
    Config b(std::move(a));
    ASSERT_EQ(b.key(), std::string("host"));
    ASSERT_EQ(b.value(), std::string("example.com"));
    ASSERT_EQ(b.priority(), 3);
}

TEST(runner, "is move assignable") {
    Config c("k", "v", 1);
    (void)c.key();

    ASSERT_TRUE(std::is_move_assignable_v<Config>);
}

TEST(runner, "move assignment works") {
    Config a("host", "example.com", 3);
    Config b("tmp", "tmp", 0);
    b = std::move(a);
    ASSERT_EQ(b.key(), std::string("host"));
    ASSERT_EQ(b.value(), std::string("example.com"));
    ASSERT_EQ(b.priority(), 3);
}

TEST(runner, "is destructible") {
    Config c("k", "v", 1);
    (void)c.key();

    ASSERT_TRUE(std::is_destructible_v<Config>);
}

TESTKIT_MAIN(runner)
