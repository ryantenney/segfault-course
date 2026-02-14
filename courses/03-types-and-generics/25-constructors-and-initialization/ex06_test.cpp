// Exercise 06 — Tests (read-only)
//
// Verifies aggregate initialization and designated initializers.

#include <testkit/testkit.h>
#include <string>
#include <type_traits>
#include "ex06.h"

static testkit::TestRunner runner("03-25-ex06: Aggregate Initialization");

TEST(runner, "NetworkConfig is an aggregate") {
    // Gate: ensure make_default_config is implemented
    auto cfg = make_default_config();
    (void)cfg;

    ASSERT_TRUE(std::is_aggregate_v<NetworkConfig>);
}

TEST(runner, "default config has correct defaults") {
    auto cfg = make_default_config();
    ASSERT_EQ(cfg.host, std::string(""));
    ASSERT_EQ(cfg.port, 80);
    ASSERT_FALSE(cfg.use_tls);
    ASSERT_EQ(cfg.max_connections, 10);
}

TEST(runner, "make_config sets host and port") {
    auto cfg = make_config("example.com", 8080);
    ASSERT_EQ(cfg.host, std::string("example.com"));
    ASSERT_EQ(cfg.port, 8080);
}

TEST(runner, "make_config keeps defaults for unset fields") {
    auto cfg = make_config("example.com", 8080);
    ASSERT_FALSE(cfg.use_tls);
    ASSERT_EQ(cfg.max_connections, 10);
}

TEST(runner, "make_secure_config sets all fields") {
    auto cfg = make_secure_config();
    ASSERT_EQ(cfg.host, std::string("secure.example.com"));
    ASSERT_EQ(cfg.port, 443);
    ASSERT_TRUE(cfg.use_tls);
    ASSERT_EQ(cfg.max_connections, 100);
}

TEST(runner, "make_tls_only_config sets only use_tls") {
    auto cfg = make_tls_only_config();
    ASSERT_EQ(cfg.host, std::string(""));
    ASSERT_EQ(cfg.port, 80);
    ASSERT_TRUE(cfg.use_tls);
    ASSERT_EQ(cfg.max_connections, 10);
}

TESTKIT_MAIN(runner)
