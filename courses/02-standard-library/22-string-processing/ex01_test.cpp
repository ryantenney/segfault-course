// Exercise 01 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex01.h"

static testkit::TestRunner runner("02-22-ex01: Parse Key-Value Pairs");

TEST(runner, "parse_key extracts key from key=value") {
    ASSERT_EQ(parse_key("name=Alice"), std::string("name"));
}

TEST(runner, "parse_key returns entire string when no delimiter") {
    ASSERT_EQ(parse_key("nodelimiter"), std::string("nodelimiter"));
}

TEST(runner, "parse_key handles empty key") {
    ASSERT_EQ(parse_key("=value"), std::string(""));
}

TEST(runner, "parse_key handles multiple equals signs") {
    ASSERT_EQ(parse_key("a=b=c"), std::string("a"));
}

TEST(runner, "parse_value extracts value from key=value") {
    ASSERT_EQ(parse_value("name=Alice"), std::string("Alice"));
}

TEST(runner, "parse_value returns empty when no delimiter") {
    ASSERT_EQ(parse_value("nodelimiter"), std::string(""));
}

TEST(runner, "parse_value handles empty value") {
    ASSERT_EQ(parse_value("key="), std::string(""));
}

TEST(runner, "parse_value preserves everything after first equals") {
    ASSERT_EQ(parse_value("a=b=c"), std::string("b=c"));
}

TEST(runner, "parse_pair splits into key and value") {
    auto [k, v] = parse_pair("host=localhost");
    ASSERT_EQ(k, std::string("host"));
    ASSERT_EQ(v, std::string("localhost"));
}

TEST(runner, "parse_pair handles missing delimiter") {
    auto [k, v] = parse_pair("standalone");
    ASSERT_EQ(k, std::string("standalone"));
    ASSERT_EQ(v, std::string(""));
}

TEST(runner, "parse_pair handles empty string") {
    auto [k, v] = parse_pair("");
    ASSERT_EQ(k, std::string(""));
    ASSERT_EQ(v, std::string(""));
}

TESTKIT_MAIN(runner)
