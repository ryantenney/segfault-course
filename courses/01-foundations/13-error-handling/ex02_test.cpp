// Exercise 02 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex02.h"

static testkit::TestRunner runner("01-13-ex02: Custom Exception Class");

TEST(runner, "ParseError stores the line number") {
    ParseError err("test error", 42);
    ASSERT_EQ(err.line(), 42);
    ASSERT_EQ(std::string(err.what()), std::string("test error"));
}

TEST(runner, "ParseError is a std::runtime_error") {
    ParseError err("test", 1);
    // This compiles only if ParseError inherits from runtime_error.
    const std::runtime_error& base = err;
    ASSERT_EQ(std::string(base.what()), std::string("test"));
}

TEST(runner, "parse_config_line parses valid lines") {
    auto kv = parse_config_line("host=localhost", 1);
    ASSERT_EQ(kv.key, std::string("host"));
    ASSERT_EQ(kv.value, std::string("localhost"));
}

TEST(runner, "parse_config_line handles value with equals sign") {
    auto kv = parse_config_line("expr=a=b", 2);
    ASSERT_EQ(kv.key, std::string("expr"));
    ASSERT_EQ(kv.value, std::string("a=b"));
}

TEST(runner, "parse_config_line handles empty value") {
    auto kv = parse_config_line("key=", 3);
    ASSERT_EQ(kv.key, std::string("key"));
    ASSERT_EQ(kv.value, std::string(""));
}

TEST(runner, "parse_config_line throws ParseError for missing equals") {
    ASSERT_THROWS(parse_config_line("no-equals-here", 5), ParseError);
}

TEST(runner, "parse_config_line throws with correct line number") {
    try {
        parse_config_line("bad line", 7);
        ASSERT_TRUE(false);  // should not reach here
    } catch (const ParseError& e) {
        ASSERT_EQ(e.line(), 7);
        ASSERT_EQ(std::string(e.what()), std::string("missing '=' in config line"));
    }
}

TESTKIT_MAIN(runner)
