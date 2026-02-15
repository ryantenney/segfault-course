// Exercise 01 -- Tests (read-only)
//
// Verifies that ServerConfig has correct default values.

#include <testkit/testkit.h>
#include "ex01.h"

static testkit::TestRunner runner("05-44-ex01: Config Struct with Defaults");

TEST(runner, "default port is 8080") {
    ServerConfig cfg;
    ASSERT_EQ(cfg.get_port(), 8080);
}

TEST(runner, "default host is localhost") {
    ServerConfig cfg;
    ASSERT_EQ(cfg.get_host(), std::string("localhost"));
}

TEST(runner, "default max_connections is 100") {
    ServerConfig cfg;
    ASSERT_EQ(cfg.get_max_connections(), 100);
}

TEST(runner, "port can be overridden via direct assignment") {
    ServerConfig cfg;
    cfg.port = 3000;
    ASSERT_EQ(cfg.get_port(), 3000);
}

TEST(runner, "host can be overridden via direct assignment") {
    ServerConfig cfg;
    cfg.host = "0.0.0.0";
    ASSERT_EQ(cfg.get_host(), std::string("0.0.0.0"));
}

TEST(runner, "max_connections can be overridden via direct assignment") {
    ServerConfig cfg;
    cfg.max_connections = 500;
    ASSERT_EQ(cfg.get_max_connections(), 500);
}

TESTKIT_MAIN(runner)
