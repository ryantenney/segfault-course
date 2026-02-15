// Exercise 06 -- Tests (read-only)
//
// Verifies zero-cost disabled log levels via if constexpr.

#include <testkit/testkit.h>
#include <string>
#include "ex06.h"

static testkit::TestRunner runner("05-50-ex06: Zero-cost Disabled Logs");

TEST(runner, "debug logger captures all levels") {
    ZeroCostLogger<ZLevel::Debug> logger;
    logger.log<ZLevel::Debug>("d");
    logger.log<ZLevel::Info>("i");
    logger.log<ZLevel::Warn>("w");
    logger.log<ZLevel::Error>("e");
    ASSERT_EQ(static_cast<int>(logger.entries().size()), 4);
}

TEST(runner, "warn logger discards debug and info") {
    ZeroCostLogger<ZLevel::Warn> logger;
    logger.log<ZLevel::Debug>("d");
    logger.log<ZLevel::Info>("i");
    logger.log<ZLevel::Warn>("w");
    logger.log<ZLevel::Error>("e");
    ASSERT_EQ(static_cast<int>(logger.entries().size()), 2);
    ASSERT_EQ(logger.entries()[0], std::string("[WARN] w"));
    ASSERT_EQ(logger.entries()[1], std::string("[ERROR] e"));
}

TEST(runner, "error logger only captures errors") {
    ZeroCostLogger<ZLevel::Error> logger;
    logger.log<ZLevel::Debug>("d");
    logger.log<ZLevel::Info>("i");
    logger.log<ZLevel::Warn>("w");
    logger.log<ZLevel::Error>("e");
    ASSERT_EQ(static_cast<int>(logger.entries().size()), 1);
    ASSERT_EQ(logger.entries()[0], std::string("[ERROR] e"));
}

TEST(runner, "format includes level string") {
    ZeroCostLogger<ZLevel::Debug> logger;
    logger.log<ZLevel::Debug>("hello");
    ASSERT_EQ(logger.entries()[0], std::string("[DEBUG] hello"));
}

TEST(runner, "info logger captures info and above") {
    ZeroCostLogger<ZLevel::Info> logger;
    logger.log<ZLevel::Debug>("d");
    logger.log<ZLevel::Info>("i");
    logger.log<ZLevel::Warn>("w");
    logger.log<ZLevel::Error>("e");
    ASSERT_EQ(static_cast<int>(logger.entries().size()), 3);
}

TEST(runner, "empty logger has no entries") {
    ZeroCostLogger<ZLevel::Debug> logger;
    ASSERT_TRUE(logger.entries().empty());
}

TESTKIT_MAIN(runner)
