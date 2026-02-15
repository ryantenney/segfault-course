// Exercise 04 -- Tests (read-only)
//
// Verifies that merge_config overlays only present fields.

#include <testkit/testkit.h>
#include "ex04.h"

static testkit::TestRunner runner("05-44-ex04: Merge Two Configs");

TEST(runner, "empty overlay returns base unchanged") {
    ServerConfig base;
    base.port = 3000;
    base.host = "myhost";
    base.max_connections = 50;

    ConfigOverlay overlay;
    ServerConfig result = merge_config(base, overlay);
    ASSERT_EQ(result.port, 3000);
    ASSERT_EQ(result.host, std::string("myhost"));
    ASSERT_EQ(result.max_connections, 50);
}

TEST(runner, "overlay overrides port only") {
    ServerConfig base;
    ConfigOverlay overlay;
    overlay.port = 9090;

    ServerConfig result = merge_config(base, overlay);
    ASSERT_EQ(result.port, 9090);
    ASSERT_EQ(result.host, std::string("localhost"));
    ASSERT_EQ(result.max_connections, 100);
}

TEST(runner, "overlay overrides host only") {
    ServerConfig base;
    ConfigOverlay overlay;
    overlay.host = "prod.example.com";

    ServerConfig result = merge_config(base, overlay);
    ASSERT_EQ(result.port, 8080);
    ASSERT_EQ(result.host, std::string("prod.example.com"));
    ASSERT_EQ(result.max_connections, 100);
}

TEST(runner, "overlay overrides max_connections only") {
    ServerConfig base;
    ConfigOverlay overlay;
    overlay.max_connections = 999;

    ServerConfig result = merge_config(base, overlay);
    ASSERT_EQ(result.max_connections, 999);
}

TEST(runner, "overlay overrides all fields") {
    ServerConfig base;
    ConfigOverlay overlay;
    overlay.port = 443;
    overlay.host = "secure.local";
    overlay.max_connections = 2000;

    ServerConfig result = merge_config(base, overlay);
    ASSERT_EQ(result.port, 443);
    ASSERT_EQ(result.host, std::string("secure.local"));
    ASSERT_EQ(result.max_connections, 2000);
}

TEST(runner, "overlay on non-default base") {
    ServerConfig base;
    base.port = 5000;
    base.host = "staging";
    base.max_connections = 200;

    ConfigOverlay overlay;
    overlay.host = "production";

    ServerConfig result = merge_config(base, overlay);
    ASSERT_EQ(result.port, 5000);
    ASSERT_EQ(result.host, std::string("production"));
    ASSERT_EQ(result.max_connections, 200);
}

TESTKIT_MAIN(runner)
