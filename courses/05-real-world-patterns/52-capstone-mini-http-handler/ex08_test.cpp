// Exercise 08 -- Tests (read-only)
//
// Verifies body parsing and handler that uses parsed data.

#include <testkit/testkit.h>
#include "ex08.h"

#include <string>

static testkit::TestRunner runner("05-52-ex08: JSON-like Body");

TEST(runner, "parse_body with single pair") {
    auto data = parse_body("key=value");
    ASSERT_EQ(data.size(), size_t(1));
    ASSERT_EQ(data.at("key"), std::string("value"));
}

TEST(runner, "parse_body with multiple pairs") {
    auto data = parse_body("name=Alice\nemail=alice@test.com");
    ASSERT_EQ(data.size(), size_t(2));
    ASSERT_EQ(data.at("name"), std::string("Alice"));
    ASSERT_EQ(data.at("email"), std::string("alice@test.com"));
}

TEST(runner, "parse_body skips malformed lines") {
    auto data = parse_body("good=yes\nbadline\nalso=ok");
    ASSERT_EQ(data.size(), size_t(2));
    ASSERT_EQ(data.at("good"), std::string("yes"));
    ASSERT_EQ(data.at("also"), std::string("ok"));
}

TEST(runner, "parse_body empty string returns empty map") {
    auto data = parse_body("");
    ASSERT_EQ(data.size(), size_t(0));
}

TEST(runner, "parse_body value can contain equals sign") {
    auto data = parse_body("expr=a=b");
    ASSERT_EQ(data.size(), size_t(1));
    ASSERT_EQ(data.at("expr"), std::string("a=b"));
}

TEST(runner, "handle_create_user succeeds with name and email") {
    Request req{"POST", "/users", "name=Bob\nemail=bob@test.com"};
    Response resp = handle_create_user(req);
    ASSERT_EQ(resp.status, 201);
    ASSERT_EQ(resp.body, std::string("created Bob bob@test.com"));
}

TEST(runner, "handle_create_user fails when name is missing") {
    Request req{"POST", "/users", "email=bob@test.com"};
    Response resp = handle_create_user(req);
    ASSERT_EQ(resp.status, 400);
    ASSERT_EQ(resp.body, std::string("missing field: name"));
}

TEST(runner, "handle_create_user fails when email is missing") {
    Request req{"POST", "/users", "name=Bob"};
    Response resp = handle_create_user(req);
    ASSERT_EQ(resp.status, 400);
    ASSERT_EQ(resp.body, std::string("missing field: email"));
}

TESTKIT_MAIN(runner)
