// Exercise 07 -- Tests (read-only)
//
// Verifies that config_diff returns the names of differing fields.

#include <testkit/testkit.h>
#include "ex07.h"

static testkit::TestRunner runner("05-44-ex07: Config Diffing");

TEST(runner, "identical configs have no differences") {
    ServerConfig a;
    ServerConfig b;
    auto diffs = config_diff(a, b);
    ASSERT_TRUE(diffs.empty());
}

TEST(runner, "port differs") {
    ServerConfig a;
    ServerConfig b;
    b.port = 3000;
    auto diffs = config_diff(a, b);
    ASSERT_EQ(diffs.size(), std::size_t(1));
    ASSERT_EQ(diffs[0], std::string("port"));
}

TEST(runner, "host differs") {
    ServerConfig a;
    ServerConfig b;
    b.host = "0.0.0.0";
    auto diffs = config_diff(a, b);
    ASSERT_EQ(diffs.size(), std::size_t(1));
    ASSERT_EQ(diffs[0], std::string("host"));
}

TEST(runner, "max_connections differs") {
    ServerConfig a;
    ServerConfig b;
    b.max_connections = 500;
    auto diffs = config_diff(a, b);
    ASSERT_EQ(diffs.size(), std::size_t(1));
    ASSERT_EQ(diffs[0], std::string("max_connections"));
}

TEST(runner, "all fields differ") {
    ServerConfig a;
    ServerConfig b;
    b.port = 443;
    b.host = "prod";
    b.max_connections = 9999;
    auto diffs = config_diff(a, b);
    ASSERT_EQ(diffs.size(), std::size_t(3));
    ASSERT_EQ(diffs[0], std::string("port"));
    ASSERT_EQ(diffs[1], std::string("host"));
    ASSERT_EQ(diffs[2], std::string("max_connections"));
}

TEST(runner, "port and max_connections differ") {
    ServerConfig a;
    ServerConfig b;
    b.port = 9090;
    b.max_connections = 200;
    auto diffs = config_diff(a, b);
    ASSERT_EQ(diffs.size(), std::size_t(2));
    ASSERT_EQ(diffs[0], std::string("port"));
    ASSERT_EQ(diffs[1], std::string("max_connections"));
}

TEST(runner, "diff is symmetric") {
    ServerConfig a;
    ServerConfig b;
    b.host = "other";
    auto diffs_ab = config_diff(a, b);
    auto diffs_ba = config_diff(b, a);
    ASSERT_EQ(diffs_ab.size(), diffs_ba.size());
    ASSERT_EQ(diffs_ab[0], diffs_ba[0]);
}

TEST(runner, "both non-default but equal") {
    ServerConfig a;
    a.port = 5000;
    a.host = "custom";
    ServerConfig b;
    b.port = 5000;
    b.host = "custom";
    auto diffs = config_diff(a, b);
    ASSERT_TRUE(diffs.empty());
}

TESTKIT_MAIN(runner)
