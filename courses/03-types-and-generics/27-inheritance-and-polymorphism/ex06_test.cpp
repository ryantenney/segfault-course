// Exercise 06 -- Tests (read-only)

#include <testkit/testkit.h>
#include <memory>
#include <string>

#include "ex06.h"

static testkit::TestRunner runner("03-27-ex06: Final Keyword");

TEST(runner, "Logger::log formats message") {
    exercise_ready();  // gate on TODO()
    Logger logger;
    ASSERT_EQ(logger.log("hello"), std::string("LOG: hello"));
}

TEST(runner, "Logger::log with empty message") {
    exercise_ready();
    Logger logger;
    ASSERT_EQ(logger.log(""), std::string("LOG: "));
}

TEST(runner, "TimestampLogger::log adds timestamp prefix") {
    exercise_ready();
    TimestampLogger ts_logger;
    ASSERT_EQ(ts_logger.log("event"), std::string("[TS] LOG: event"));
}

TEST(runner, "make_logger returns a base Logger") {
    auto l = make_logger();
    ASSERT_EQ(l->log("test"), std::string("LOG: test"));
}

TEST(runner, "make_timestamp_logger dispatches to TimestampLogger") {
    auto l = make_timestamp_logger();
    ASSERT_EQ(l->log("test"), std::string("[TS] LOG: test"));
}

TEST(runner, "virtual dispatch selects correct override") {
    exercise_ready();
    auto base = make_logger();
    auto derived = make_timestamp_logger();
    ASSERT_EQ(base->log("x"), std::string("LOG: x"));
    ASSERT_EQ(derived->log("x"), std::string("[TS] LOG: x"));
}

TESTKIT_MAIN(runner)
