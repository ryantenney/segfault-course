// Exercise 02 -- Tests (read-only)
//
// Verifies formatted log output with key-value pairs.

#include <testkit/testkit.h>
#include <string>
#include "ex02.h"

static testkit::TestRunner runner("05-50-ex02: Formatted Output");

TEST(runner, "format without fields") {
    LogMessage msg(Level::Info, "server started");
    ASSERT_EQ(msg.str(), std::string("[INFO] server started"));
}

TEST(runner, "format with one field") {
    LogMessage msg(Level::Info, "request");
    msg.field("status", "200");
    ASSERT_EQ(msg.str(), std::string("[INFO] request | status=200"));
}

TEST(runner, "format with multiple fields") {
    LogMessage msg(Level::Warn, "slow query");
    msg.field("duration", "500ms").field("table", "users");
    ASSERT_EQ(msg.str(), std::string("[WARN] slow query | duration=500ms table=users"));
}

TEST(runner, "chaining returns reference to same object") {
    LogMessage msg(Level::Debug, "test");
    auto& ref = msg.field("a", "1");
    // Both should point to the same object.
    ASSERT_TRUE(&ref == &msg);
}

TEST(runner, "different levels format correctly") {
    LogMessage d(Level::Debug, "d");
    LogMessage e(Level::Error, "e");
    ASSERT_EQ(d.str(), std::string("[DEBUG] d"));
    ASSERT_EQ(e.str(), std::string("[ERROR] e"));
}

TEST(runner, "fields preserve insertion order") {
    LogMessage msg(Level::Info, "m");
    msg.field("z", "1").field("a", "2").field("m", "3");
    ASSERT_EQ(msg.str(), std::string("[INFO] m | z=1 a=2 m=3"));
}

TESTKIT_MAIN(runner)
