// Exercise 04 — Tests (read-only)
//
// Verifies setter validation on the User class.

#include <testkit/testkit.h>
#include <stdexcept>
#include <string>
#include "ex04.h"

static testkit::TestRunner runner("03-24-ex04: Setter with Validation");

TEST(runner, "getters return initial values") {
    User u("Alice", 30, "alice@example.com");
    ASSERT_EQ(u.name(), std::string("Alice"));
    ASSERT_EQ(u.age(), 30);
    ASSERT_EQ(u.email(), std::string("alice@example.com"));
}

TEST(runner, "set_name updates the name") {
    User u("Alice", 30, "alice@example.com");
    u.set_name("Bob");
    ASSERT_EQ(u.name(), std::string("Bob"));
}

TEST(runner, "set_name rejects empty string") {
    User u("Alice", 30, "alice@example.com");
    ASSERT_THROWS(u.set_name(""), std::invalid_argument);
    // Name should be unchanged after failed set
    ASSERT_EQ(u.name(), std::string("Alice"));
}

TEST(runner, "set_age updates the age") {
    User u("Alice", 30, "alice@example.com");
    u.set_age(25);
    ASSERT_EQ(u.age(), 25);
}

TEST(runner, "set_age accepts boundary values") {
    User u("Alice", 30, "alice@example.com");
    u.set_age(0);
    ASSERT_EQ(u.age(), 0);
    u.set_age(150);
    ASSERT_EQ(u.age(), 150);
}

TEST(runner, "set_age rejects negative age") {
    User u("Alice", 30, "alice@example.com");
    ASSERT_THROWS(u.set_age(-1), std::invalid_argument);
    ASSERT_EQ(u.age(), 30);
}

TEST(runner, "set_age rejects age over 150") {
    User u("Alice", 30, "alice@example.com");
    ASSERT_THROWS(u.set_age(151), std::invalid_argument);
    ASSERT_EQ(u.age(), 30);
}

TEST(runner, "set_email updates the email") {
    User u("Alice", 30, "alice@example.com");
    u.set_email("alice@other.com");
    ASSERT_EQ(u.email(), std::string("alice@other.com"));
}

TEST(runner, "set_email rejects email without @") {
    User u("Alice", 30, "alice@example.com");
    ASSERT_THROWS(u.set_email("invalid-email"), std::invalid_argument);
    ASSERT_EQ(u.email(), std::string("alice@example.com"));
}

TEST(runner, "set_email rejects empty email") {
    User u("Alice", 30, "alice@example.com");
    ASSERT_THROWS(u.set_email(""), std::invalid_argument);
    ASSERT_EQ(u.email(), std::string("alice@example.com"));
}

TESTKIT_MAIN(runner)
