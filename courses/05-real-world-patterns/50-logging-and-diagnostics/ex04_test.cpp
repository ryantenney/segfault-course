// Exercise 04 -- Tests (read-only)
//
// Verifies structured log entry construction and formatting.

#include <testkit/testkit.h>
#include <chrono>
#include <string>
#include "ex04.h"

static testkit::TestRunner runner("05-50-ex04: Structured Log Entry");

TEST(runner, "make_entry stores level and message") {
    auto entry = make_entry(EntryLevel::Info, "hello");
    ASSERT_TRUE(entry.level == EntryLevel::Info);
    ASSERT_EQ(entry.message, std::string("hello"));
}

TEST(runner, "make_entry stores fields") {
    auto entry = make_entry(EntryLevel::Warn, "slow",
                            {{"duration", "100ms"}});
    ASSERT_EQ(static_cast<int>(entry.fields.size()), 1);
    ASSERT_EQ(entry.fields.at("duration"), std::string("100ms"));
}

TEST(runner, "make_entry sets timestamp close to now") {
    auto before = std::chrono::system_clock::now();
    auto entry = make_entry(EntryLevel::Debug, "test");
    auto after = std::chrono::system_clock::now();
    ASSERT_TRUE(entry.timestamp >= before);
    ASSERT_TRUE(entry.timestamp <= after);
}

TEST(runner, "make_entry with no fields has empty map") {
    auto entry = make_entry(EntryLevel::Error, "fail");
    ASSERT_TRUE(entry.fields.empty());
}

TEST(runner, "format_entry contains level string") {
    auto entry = make_entry(EntryLevel::Info, "test");
    auto str = format_entry(entry);
    ASSERT_TRUE(str.find("[INFO]") != std::string::npos);
}

TEST(runner, "format_entry contains message") {
    auto entry = make_entry(EntryLevel::Info, "server started");
    auto str = format_entry(entry);
    ASSERT_TRUE(str.find("server started") != std::string::npos);
}

TEST(runner, "format_entry contains fields after pipe") {
    auto entry = make_entry(EntryLevel::Info, "req",
                            {{"status", "200"}});
    auto str = format_entry(entry);
    ASSERT_TRUE(str.find("| status=200") != std::string::npos);
}

TEST(runner, "format_entry without fields has no pipe") {
    auto entry = make_entry(EntryLevel::Info, "clean");
    auto str = format_entry(entry);
    ASSERT_TRUE(str.find("|") == std::string::npos);
}

TEST(runner, "format_entry starts with timestamp-like pattern") {
    auto entry = make_entry(EntryLevel::Info, "test");
    auto str = format_entry(entry);
    // Should start with something like "2024-01-15T10:30:45"
    // At minimum check it has a 'T' in position 10
    ASSERT_TRUE(str.size() > 19);
    ASSERT_TRUE(str[4] == '-');
    ASSERT_TRUE(str[10] == 'T');
}

TESTKIT_MAIN(runner)
