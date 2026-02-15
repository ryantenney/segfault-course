// Exercise 05 -- Tests (read-only)
//
// Verifies that validate() catches invalid configurations.

#include <testkit/testkit.h>
#include "ex05.h"

static testkit::TestRunner runner("05-44-ex05: Validation");

TEST(runner, "default config is valid") {
    ServerConfig cfg;
    auto errors = validate(cfg);
    ASSERT_TRUE(errors.empty());
}

TEST(runner, "port too low") {
    ServerConfig cfg;
    cfg.port = 0;
    auto errors = validate(cfg);
    ASSERT_EQ(errors.size(), std::size_t(1));
    ASSERT_EQ(errors[0], std::string("port out of range"));
}

TEST(runner, "port too high") {
    ServerConfig cfg;
    cfg.port = 70000;
    auto errors = validate(cfg);
    ASSERT_EQ(errors.size(), std::size_t(1));
    ASSERT_EQ(errors[0], std::string("port out of range"));
}

TEST(runner, "negative port") {
    ServerConfig cfg;
    cfg.port = -1;
    auto errors = validate(cfg);
    ASSERT_EQ(errors.size(), std::size_t(1));
    ASSERT_EQ(errors[0], std::string("port out of range"));
}

TEST(runner, "empty host") {
    ServerConfig cfg;
    cfg.host = "";
    auto errors = validate(cfg);
    ASSERT_EQ(errors.size(), std::size_t(1));
    ASSERT_EQ(errors[0], std::string("host must not be empty"));
}

TEST(runner, "max_connections zero") {
    ServerConfig cfg;
    cfg.max_connections = 0;
    auto errors = validate(cfg);
    ASSERT_EQ(errors.size(), std::size_t(1));
    ASSERT_EQ(errors[0], std::string("max_connections must be positive"));
}

TEST(runner, "max_connections too large") {
    ServerConfig cfg;
    cfg.max_connections = 10001;
    auto errors = validate(cfg);
    ASSERT_EQ(errors.size(), std::size_t(1));
    ASSERT_EQ(errors[0], std::string("max_connections too large"));
}

TEST(runner, "multiple errors accumulate") {
    ServerConfig cfg;
    cfg.port = 0;
    cfg.host = "";
    cfg.max_connections = -5;
    auto errors = validate(cfg);
    ASSERT_EQ(errors.size(), std::size_t(3));
}

TEST(runner, "boundary values are valid") {
    ServerConfig cfg;
    cfg.port = 1;
    auto errors1 = validate(cfg);
    ASSERT_TRUE(errors1.empty());

    cfg.port = 65535;
    auto errors2 = validate(cfg);
    ASSERT_TRUE(errors2.empty());

    cfg.max_connections = 1;
    auto errors3 = validate(cfg);
    ASSERT_TRUE(errors3.empty());

    cfg.max_connections = 10000;
    auto errors4 = validate(cfg);
    ASSERT_TRUE(errors4.empty());
}

TESTKIT_MAIN(runner)
