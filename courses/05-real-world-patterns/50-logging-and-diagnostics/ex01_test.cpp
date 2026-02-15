// Exercise 01 -- Tests (read-only)
//
// Verifies basic log level filtering.

#include <testkit/testkit.h>
#include <string>
#include "ex01.h"

static testkit::TestRunner runner("05-50-ex01: Basic Logger");

TEST(runner, "log at default level captures all messages") {
    BasicLogger logger;
    logger.log(LogLevel::Debug, "debug msg");
    logger.log(LogLevel::Info, "info msg");
    ASSERT_EQ(static_cast<int>(logger.messages().size()), 2);
}

TEST(runner, "log format is [LEVEL] message") {
    BasicLogger logger;
    logger.log(LogLevel::Info, "hello");
    ASSERT_EQ(logger.messages()[0], std::string("[INFO] hello"));
}

TEST(runner, "set_level filters messages below threshold") {
    BasicLogger logger;
    logger.set_level(LogLevel::Warn);
    logger.log(LogLevel::Debug, "hidden");
    logger.log(LogLevel::Info, "hidden");
    logger.log(LogLevel::Warn, "visible");
    logger.log(LogLevel::Error, "visible");
    ASSERT_EQ(static_cast<int>(logger.messages().size()), 2);
}

TEST(runner, "debug level logs everything") {
    BasicLogger logger;
    logger.set_level(LogLevel::Debug);
    logger.log(LogLevel::Debug, "d");
    logger.log(LogLevel::Info, "i");
    logger.log(LogLevel::Warn, "w");
    logger.log(LogLevel::Error, "e");
    ASSERT_EQ(static_cast<int>(logger.messages().size()), 4);
}

TEST(runner, "error level logs only errors") {
    BasicLogger logger;
    logger.set_level(LogLevel::Error);
    logger.log(LogLevel::Debug, "d");
    logger.log(LogLevel::Info, "i");
    logger.log(LogLevel::Warn, "w");
    logger.log(LogLevel::Error, "e");
    ASSERT_EQ(static_cast<int>(logger.messages().size()), 1);
    ASSERT_EQ(logger.messages()[0], std::string("[ERROR] e"));
}

TEST(runner, "format includes correct level strings") {
    BasicLogger logger;
    logger.log(LogLevel::Debug, "x");
    logger.log(LogLevel::Warn, "y");
    ASSERT_EQ(logger.messages()[0], std::string("[DEBUG] x"));
    ASSERT_EQ(logger.messages()[1], std::string("[WARN] y"));
}

TESTKIT_MAIN(runner)
