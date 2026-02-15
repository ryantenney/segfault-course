// Exercise 05 -- Tests (read-only)
//
// Verifies the Sink abstraction with MemorySink.

#include <testkit/testkit.h>
#include <memory>
#include <string>
#include "ex05.h"

static testkit::TestRunner runner("05-50-ex05: Log Sink Abstraction");

TEST(runner, "MemorySink stores written messages") {
    auto sink = std::make_shared<MemorySink>();
    sink->write("hello");
    sink->write("world");
    ASSERT_EQ(static_cast<int>(sink->entries().size()), 2);
    ASSERT_EQ(sink->entries()[0], std::string("hello"));
    ASSERT_EQ(sink->entries()[1], std::string("world"));
}

TEST(runner, "SinkLogger formats and writes to sink") {
    auto sink = std::make_shared<MemorySink>();
    SinkLogger logger(sink);
    logger.log(SinkLogLevel::Info, "started");
    ASSERT_EQ(static_cast<int>(sink->entries().size()), 1);
    ASSERT_EQ(sink->entries()[0], std::string("[INFO] started"));
}

TEST(runner, "SinkLogger filters by level") {
    auto sink = std::make_shared<MemorySink>();
    SinkLogger logger(sink, SinkLogLevel::Warn);
    logger.log(SinkLogLevel::Debug, "hidden");
    logger.log(SinkLogLevel::Info, "hidden");
    logger.log(SinkLogLevel::Warn, "visible");
    logger.log(SinkLogLevel::Error, "visible");
    ASSERT_EQ(static_cast<int>(sink->entries().size()), 2);
}

TEST(runner, "SinkLogger with Debug level passes all messages") {
    auto sink = std::make_shared<MemorySink>();
    SinkLogger logger(sink, SinkLogLevel::Debug);
    logger.log(SinkLogLevel::Debug, "d");
    logger.log(SinkLogLevel::Info, "i");
    logger.log(SinkLogLevel::Warn, "w");
    logger.log(SinkLogLevel::Error, "e");
    ASSERT_EQ(static_cast<int>(sink->entries().size()), 4);
}

TEST(runner, "MemorySink starts empty") {
    auto sink = std::make_shared<MemorySink>();
    ASSERT_TRUE(sink->entries().empty());
}

TEST(runner, "multiple loggers can share a sink") {
    auto sink = std::make_shared<MemorySink>();
    SinkLogger logger1(sink);
    SinkLogger logger2(sink, SinkLogLevel::Error);
    logger1.log(SinkLogLevel::Info, "from1");
    logger2.log(SinkLogLevel::Info, "filtered");
    logger2.log(SinkLogLevel::Error, "from2");
    ASSERT_EQ(static_cast<int>(sink->entries().size()), 2);
    ASSERT_EQ(sink->entries()[0], std::string("[INFO] from1"));
    ASSERT_EQ(sink->entries()[1], std::string("[ERROR] from2"));
}

TESTKIT_MAIN(runner)
