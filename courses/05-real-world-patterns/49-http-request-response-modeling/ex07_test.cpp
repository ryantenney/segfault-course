// Exercise 07 -- Tests (read-only)
//
// Verifies Content-Type parsing.

#include <testkit/testkit.h>
#include <string>
#include "ex07.h"

static testkit::TestRunner runner("05-49-ex07: Content-Type Parsing");

TEST(runner, "parse simple type/subtype") {
    auto ct = parse_content_type("text/html");
    ASSERT_EQ(ct.type, std::string("text"));
    ASSERT_EQ(ct.subtype, std::string("html"));
    ASSERT_TRUE(ct.params.empty());
}

TEST(runner, "media_type returns type/subtype") {
    auto ct = parse_content_type("application/json");
    ASSERT_EQ(ct.media_type(), std::string("application/json"));
}

TEST(runner, "parse with charset parameter") {
    auto ct = parse_content_type("text/html; charset=utf-8");
    ASSERT_EQ(ct.type, std::string("text"));
    ASSERT_EQ(ct.subtype, std::string("html"));
    ASSERT_EQ(static_cast<int>(ct.params.size()), 1);
    ASSERT_EQ(ct.params.at("charset"), std::string("utf-8"));
}

TEST(runner, "parse with multiple parameters") {
    auto ct = parse_content_type("multipart/form-data; boundary=abc; charset=utf-8");
    ASSERT_EQ(ct.type, std::string("multipart"));
    ASSERT_EQ(ct.subtype, std::string("form-data"));
    ASSERT_EQ(static_cast<int>(ct.params.size()), 2);
    ASSERT_EQ(ct.params.at("boundary"), std::string("abc"));
    ASSERT_EQ(ct.params.at("charset"), std::string("utf-8"));
}

TEST(runner, "parse trims whitespace around params") {
    auto ct = parse_content_type("text/plain ;  charset = utf-8 ");
    ASSERT_EQ(ct.type, std::string("text"));
    ASSERT_EQ(ct.subtype, std::string("plain"));
    ASSERT_EQ(ct.params.at("charset"), std::string("utf-8"));
}

TEST(runner, "application/json no params") {
    auto ct = parse_content_type("application/json");
    ASSERT_EQ(ct.media_type(), std::string("application/json"));
    ASSERT_TRUE(ct.params.empty());
}

TESTKIT_MAIN(runner)
