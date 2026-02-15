// Exercise 03 -- Tests (read-only)
//
// Verifies parsing of key-value pairs into typed ServerConfig.

#include <testkit/testkit.h>
#include "ex03.h"

static testkit::TestRunner runner("05-44-ex03: Parse from Key-Value Pairs");

TEST(runner, "empty input returns defaults") {
    auto cfg = parse_config({});
    ASSERT_TRUE(cfg.has_value());
    ASSERT_EQ(cfg->port, 8080);
    ASSERT_EQ(cfg->host, std::string("localhost"));
    ASSERT_EQ(cfg->max_connections, 100);
}

TEST(runner, "parse port override") {
    auto cfg = parse_config({{"port", "3000"}});
    ASSERT_TRUE(cfg.has_value());
    ASSERT_EQ(cfg->port, 3000);
    ASSERT_EQ(cfg->host, std::string("localhost"));
}

TEST(runner, "parse host override") {
    auto cfg = parse_config({{"host", "0.0.0.0"}});
    ASSERT_TRUE(cfg.has_value());
    ASSERT_EQ(cfg->host, std::string("0.0.0.0"));
}

TEST(runner, "parse max_connections override") {
    auto cfg = parse_config({{"max_connections", "250"}});
    ASSERT_TRUE(cfg.has_value());
    ASSERT_EQ(cfg->max_connections, 250);
}

TEST(runner, "parse multiple overrides") {
    auto cfg = parse_config({{"port", "443"}, {"host", "secure.local"}, {"max_connections", "50"}});
    ASSERT_TRUE(cfg.has_value());
    ASSERT_EQ(cfg->port, 443);
    ASSERT_EQ(cfg->host, std::string("secure.local"));
    ASSERT_EQ(cfg->max_connections, 50);
}

TEST(runner, "invalid port returns nullopt") {
    auto cfg = parse_config({{"port", "not_a_number"}});
    ASSERT_FALSE(cfg.has_value());
}

TEST(runner, "invalid max_connections returns nullopt") {
    auto cfg = parse_config({{"max_connections", "abc"}});
    ASSERT_FALSE(cfg.has_value());
}

TEST(runner, "unknown keys are ignored") {
    auto cfg = parse_config({{"unknown_key", "value"}, {"port", "9090"}});
    ASSERT_TRUE(cfg.has_value());
    ASSERT_EQ(cfg->port, 9090);
}

TESTKIT_MAIN(runner)
