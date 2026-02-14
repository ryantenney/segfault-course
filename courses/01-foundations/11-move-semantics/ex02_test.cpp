// Exercise 02 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex02.h"

static testkit::TestRunner runner("01-11-ex02: Move a Local into a Return Value");

TEST(runner, "make_config populates all fields") {
    auto cfg = make_config("localhost", "/api", 8080);
    ASSERT_EQ(cfg.host, std::string("localhost"));
    ASSERT_EQ(cfg.path, std::string("/api"));
    ASSERT_EQ(cfg.port, 8080);
}

TEST(runner, "make_config works with empty strings") {
    auto cfg = make_config("", "", 0);
    ASSERT_EQ(cfg.host, std::string(""));
    ASSERT_EQ(cfg.path, std::string(""));
    ASSERT_EQ(cfg.port, 0);
}

TEST(runner, "compose_message concatenates sender prefix and content") {
    auto msg = compose_message("Alice", "hello world");
    ASSERT_EQ(msg.sender, std::string("Alice"));
    ASSERT_EQ(msg.body, std::string("Alice: hello world"));
}

TEST(runner, "compose_message handles empty content") {
    auto msg = compose_message("Bot", "");
    ASSERT_EQ(msg.body, std::string("Bot: "));
}

TEST(runner, "build_messages creates paired messages") {
    std::vector<std::string> senders = {"Alice", "Bob"};
    std::vector<std::string> bodies = {"hi", "bye"};
    auto msgs = build_messages(senders, bodies);
    ASSERT_EQ(msgs.size(), 2u);
    ASSERT_EQ(msgs[0].sender, std::string("Alice"));
    ASSERT_EQ(msgs[0].body, std::string("Alice: hi"));
    ASSERT_EQ(msgs[1].sender, std::string("Bob"));
    ASSERT_EQ(msgs[1].body, std::string("Bob: bye"));
}

TESTKIT_MAIN(runner)
