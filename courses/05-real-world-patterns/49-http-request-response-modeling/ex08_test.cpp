// Exercise 08 -- Tests (read-only)
//
// Verifies query string parsing and URL decoding.

#include <testkit/testkit.h>
#include <string>
#include "ex08.h"

static testkit::TestRunner runner("05-49-ex08: Query String Parsing");

TEST(runner, "url_decode plain string unchanged") {
    ASSERT_EQ(url_decode("hello"), std::string("hello"));
}

TEST(runner, "url_decode plus becomes space") {
    ASSERT_EQ(url_decode("hello+world"), std::string("hello world"));
}

TEST(runner, "url_decode percent encoding") {
    ASSERT_EQ(url_decode("hello%20world"), std::string("hello world"));
}

TEST(runner, "url_decode mixed encoding") {
    ASSERT_EQ(url_decode("a%2Bb%3Dc"), std::string("a+b=c"));
}

TEST(runner, "parse simple key=value pair") {
    auto params = parse_query("key=val");
    ASSERT_EQ(static_cast<int>(params.size()), 1);
    ASSERT_EQ(params.at("key"), std::string("val"));
}

TEST(runner, "parse multiple pairs") {
    auto params = parse_query("a=1&b=2&c=3");
    ASSERT_EQ(static_cast<int>(params.size()), 3);
    ASSERT_EQ(params.at("a"), std::string("1"));
    ASSERT_EQ(params.at("b"), std::string("2"));
    ASSERT_EQ(params.at("c"), std::string("3"));
}

TEST(runner, "parse strips leading question mark") {
    auto params = parse_query("?key=val");
    ASSERT_EQ(params.at("key"), std::string("val"));
}

TEST(runner, "parse key with no equals") {
    auto params = parse_query("flag");
    ASSERT_EQ(params.at("flag"), std::string(""));
}

TEST(runner, "parse key with equals but no value") {
    auto params = parse_query("key=");
    ASSERT_EQ(params.at("key"), std::string(""));
}

TEST(runner, "parse URL-encoded keys and values") {
    auto params = parse_query("name=John+Doe&city=New%20York");
    ASSERT_EQ(params.at("name"), std::string("John Doe"));
    ASSERT_EQ(params.at("city"), std::string("New York"));
}

TEST(runner, "parse empty string returns empty map") {
    auto params = parse_query("");
    ASSERT_TRUE(params.empty());
}

TEST(runner, "parse value containing equals sign") {
    auto params = parse_query("expr=a%3Db");
    ASSERT_EQ(params.at("expr"), std::string("a=b"));
}

TESTKIT_MAIN(runner)
