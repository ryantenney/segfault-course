// Exercise 02 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex02.h"

static testkit::TestRunner runner("01-12-ex02: Optional with value_or");

TEST(runner, "get_config_value returns the value for known keys") {
    auto host = get_config_value("host");
    ASSERT_TRUE(host.has_value());
    ASSERT_EQ(host.value(), std::string("localhost"));

    auto port = get_config_value("port");
    ASSERT_TRUE(port.has_value());
    ASSERT_EQ(port.value(), std::string("8080"));

    auto mode = get_config_value("mode");
    ASSERT_TRUE(mode.has_value());
    ASSERT_EQ(mode.value(), std::string("debug"));
}

TEST(runner, "get_config_value returns nullopt for unknown keys") {
    auto result = get_config_value("database");
    ASSERT_FALSE(result.has_value());
}

TEST(runner, "get_config_or_default returns value for known keys") {
    ASSERT_EQ(get_config_or_default("host", "fallback"),
              std::string("localhost"));
    ASSERT_EQ(get_config_or_default("port", "3000"),
              std::string("8080"));
}

TEST(runner, "get_config_or_default returns default for unknown keys") {
    ASSERT_EQ(get_config_or_default("database", "postgres"),
              std::string("postgres"));
    ASSERT_EQ(get_config_or_default("timeout", "30"),
              std::string("30"));
}

TESTKIT_MAIN(runner)
