// Exercise 02 -- Tests (read-only)
//
// Verifies that with_*() methods return modified copies.

#include <testkit/testkit.h>
#include "ex02.h"

static testkit::TestRunner runner("05-44-ex02: Override Methods");

TEST(runner, "with_port returns copy with new port") {
    ServerConfig base;
    ServerConfig modified = base.with_port(3000);
    ASSERT_EQ(modified.port, 3000);
    ASSERT_EQ(modified.host, std::string("localhost"));
    ASSERT_EQ(modified.max_connections, 100);
}

TEST(runner, "with_host returns copy with new host") {
    ServerConfig base;
    ServerConfig modified = base.with_host("0.0.0.0");
    ASSERT_EQ(modified.port, 8080);
    ASSERT_EQ(modified.host, std::string("0.0.0.0"));
    ASSERT_EQ(modified.max_connections, 100);
}

TEST(runner, "with_max_connections returns copy with new max") {
    ServerConfig base;
    ServerConfig modified = base.with_max_connections(500);
    ASSERT_EQ(modified.port, 8080);
    ASSERT_EQ(modified.host, std::string("localhost"));
    ASSERT_EQ(modified.max_connections, 500);
}

TEST(runner, "original config is not modified") {
    ServerConfig base;
    ServerConfig modified = base.with_port(9999);
    ASSERT_EQ(base.port, 8080);
    ASSERT_EQ(modified.port, 9999);
}

TEST(runner, "chaining with_*() calls") {
    ServerConfig cfg = ServerConfig{}
        .with_port(443)
        .with_host("secure.example.com")
        .with_max_connections(1000);
    ASSERT_EQ(cfg.port, 443);
    ASSERT_EQ(cfg.host, std::string("secure.example.com"));
    ASSERT_EQ(cfg.max_connections, 1000);
}

TEST(runner, "with_port on already modified config") {
    ServerConfig cfg = ServerConfig{}.with_host("test.local");
    ServerConfig cfg2 = cfg.with_port(5000);
    ASSERT_EQ(cfg2.host, std::string("test.local"));
    ASSERT_EQ(cfg2.port, 5000);
}

TESTKIT_MAIN(runner)
