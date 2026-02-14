// Exercise 03 — Tests (read-only)
//
// Verifies delegating constructors on the LogEntry class.

#include <testkit/testkit.h>
#include <string>
#include "ex03.h"

static testkit::TestRunner runner("03-25-ex03: Delegating Constructors");

TEST(runner, "primary constructor sets all fields") {
    LogEntry e("disk full", "ERROR", "storage", 1000);
    ASSERT_EQ(e.message(), std::string("disk full"));
    ASSERT_EQ(e.level(), std::string("ERROR"));
    ASSERT_EQ(e.source(), std::string("storage"));
    ASSERT_EQ(e.timestamp(), 1000);
}

TEST(runner, "two-arg constructor defaults source and timestamp") {
    LogEntry e("connected", "INFO");
    ASSERT_EQ(e.message(), std::string("connected"));
    ASSERT_EQ(e.level(), std::string("INFO"));
    ASSERT_EQ(e.source(), std::string("app"));
    ASSERT_EQ(e.timestamp(), 0);
}

TEST(runner, "one-arg constructor defaults level, source, timestamp") {
    LogEntry e("starting up");
    ASSERT_EQ(e.message(), std::string("starting up"));
    ASSERT_EQ(e.level(), std::string("INFO"));
    ASSERT_EQ(e.source(), std::string("app"));
    ASSERT_EQ(e.timestamp(), 0);
}

TEST(runner, "default constructor uses all defaults") {
    LogEntry e;
    ASSERT_EQ(e.message(), std::string(""));
    ASSERT_EQ(e.level(), std::string("DEBUG"));
    ASSERT_EQ(e.source(), std::string("app"));
    ASSERT_EQ(e.timestamp(), 0);
}

TEST(runner, "primary constructor with custom source") {
    LogEntry e("query slow", "WARN", "database", 500);
    ASSERT_EQ(e.source(), std::string("database"));
    ASSERT_EQ(e.timestamp(), 500);
}

TESTKIT_MAIN(runner)
