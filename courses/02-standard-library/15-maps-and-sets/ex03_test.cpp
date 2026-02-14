// Exercise 03 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex03.h"

static testkit::TestRunner runner("02-15-ex03: Insert or Update");

TEST(runner, "build_config creates entries from pairs") {
    auto config = build_config({
        {"host", "localhost"},
        {"port", "8080"},
        {"mode", "debug"}
    });
    ASSERT_EQ(config.size(), 3u);
    ASSERT_EQ(config.at("host"), std::string("localhost"));
    ASSERT_EQ(config.at("port"), std::string("8080"));
    ASSERT_EQ(config.at("mode"), std::string("debug"));
}

TEST(runner, "build_config last value wins on duplicate keys") {
    auto config = build_config({
        {"host", "alpha"},
        {"host", "beta"},
        {"host", "gamma"}
    });
    ASSERT_EQ(config.size(), 1u);
    ASSERT_EQ(config.at("host"), std::string("gamma"));
}

TEST(runner, "build_config with empty input returns empty map") {
    auto config = build_config({});
    ASSERT_EQ(config.size(), 0u);
}

TEST(runner, "update_setting inserts a new key") {
    std::unordered_map<std::string, std::string> config = {
        {"host", "localhost"}
    };
    update_setting(config, "port", "3000");
    ASSERT_EQ(config.size(), 2u);
    ASSERT_EQ(config.at("port"), std::string("3000"));
}

TEST(runner, "update_setting overwrites an existing key") {
    std::unordered_map<std::string, std::string> config = {
        {"host", "localhost"},
        {"port", "8080"}
    };
    update_setting(config, "port", "9090");
    ASSERT_EQ(config.size(), 2u);
    ASSERT_EQ(config.at("port"), std::string("9090"));
}

TESTKIT_MAIN(runner)
