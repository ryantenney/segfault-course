// Exercise 07 -- Tests (read-only)
//
// Verifies composition of multiple CRTP mixin bases.

#include <testkit/testkit.h>
#include <string>
#include "ex07.h"

static testkit::TestRunner runner("03-34-ex07: Multiple Mixin Bases");

// --- Config tests ---

TEST(runner, "Config::format returns correct string") {
    Config c("port", "8080");
    ASSERT_EQ(c.format(), std::string("Config{port=8080}"));
}

TEST(runner, "Config::print via Printable mixin") {
    Config c("host", "localhost");
    ASSERT_EQ(c.print(), std::string("Config{host=localhost}"));
}

TEST(runner, "Config::clone creates an independent copy") {
    Config c("db", "postgres");
    Config copy = c.clone();
    ASSERT_EQ(copy.key(), std::string("db"));
    ASSERT_EQ(copy.value(), std::string("postgres"));
}

TEST(runner, "Config clone is independent of original") {
    Config c("key", "val");
    Config copy = c.clone();
    // They should have the same content
    ASSERT_EQ(copy.format(), c.format());
    // But be separate objects (address differs)
    ASSERT_TRUE(&copy != &c);
}

// --- Message tests ---

TEST(runner, "Message::format returns correct string") {
    Message m("Alice", "hello");
    ASSERT_EQ(m.format(), std::string("Message{Alice: hello}"));
}

TEST(runner, "Message::print via Printable mixin") {
    Message m("Bob", "world");
    ASSERT_EQ(m.print(), std::string("Message{Bob: world}"));
}

TEST(runner, "Message::clone creates an independent copy") {
    Message m("Eve", "secret");
    Message copy = m.clone();
    ASSERT_EQ(copy.sender(), std::string("Eve"));
    ASSERT_EQ(copy.text(), std::string("secret"));
}

// --- print_and_clone free function ---

TEST(runner, "print_and_clone works with Config") {
    Config c("timeout", "30");
    auto [str, cloned] = print_and_clone(c);
    ASSERT_EQ(str, std::string("Config{timeout=30}"));
    ASSERT_EQ(cloned.key(), std::string("timeout"));
    ASSERT_EQ(cloned.value(), std::string("30"));
}

TEST(runner, "print_and_clone works with Message") {
    Message m("Carol", "hi");
    auto [str, cloned] = print_and_clone(m);
    ASSERT_EQ(str, std::string("Message{Carol: hi}"));
    ASSERT_EQ(cloned.sender(), std::string("Carol"));
    ASSERT_EQ(cloned.text(), std::string("hi"));
}

TEST(runner, "print_and_clone returns independent clone") {
    Config c("x", "y");
    auto [str, cloned] = print_and_clone(c);
    ASSERT_TRUE(&cloned != &c);
    ASSERT_EQ(cloned.format(), c.format());
}

TESTKIT_MAIN(runner)
