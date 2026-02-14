// Exercise 04 -- Tests (read-only)
//
// Verifies the Loggable CRTP mixin.

#include <testkit/testkit.h>
#include <cmath>
#include <string>
#include "ex04.h"

static testkit::TestRunner runner("03-34-ex04: Logging Mixin");

TEST(runner, "Event::to_string formats correctly") {
    Event e("click");
    ASSERT_EQ(e.to_string(), std::string("Event(click)"));
}

TEST(runner, "Event::to_string with different name") {
    Event e("submit");
    ASSERT_EQ(e.to_string(), std::string("Event(submit)"));
}

TEST(runner, "Event::log via Loggable mixin") {
    Event e("click");
    ASSERT_EQ(e.log("INFO"), std::string("[INFO] Event(click)"));
}

TEST(runner, "Event::log with different level") {
    Event e("error");
    ASSERT_EQ(e.log("ERROR"), std::string("[ERROR] Event(error)"));
}

TEST(runner, "Metric::to_string formats name and value") {
    Metric m("cpu", 85.5);
    std::string result = m.to_string();
    // Must start with "Metric(cpu="
    ASSERT_TRUE(result.substr(0, 11) == "Metric(cpu=");
    // Must end with ")"
    ASSERT_TRUE(result.back() == ')');
    // The value portion should parse to 85.5
    std::string val_str = result.substr(11, result.size() - 12);
    double val = std::stod(val_str);
    ASSERT_TRUE(std::abs(val - 85.5) < 0.01);
}

TEST(runner, "Metric::log via Loggable mixin") {
    Metric m("mem", 70.0);
    std::string result = m.log("WARN");
    ASSERT_TRUE(result.substr(0, 6) == "[WARN]");
    ASSERT_TRUE(result.find("Metric(mem=") != std::string::npos);
}

TEST(runner, "format_log_entry works with Event") {
    Event e("startup");
    std::string result = format_log_entry(e, "INFO");
    ASSERT_EQ(result, std::string("[INFO] Event(startup)"));
}

TEST(runner, "format_log_entry works with Metric") {
    Metric m("latency", 12.3);
    std::string result = format_log_entry(m, "DEBUG");
    ASSERT_TRUE(result.substr(0, 7) == "[DEBUG]");
    ASSERT_TRUE(result.find("Metric(latency=") != std::string::npos);
}

TESTKIT_MAIN(runner)
