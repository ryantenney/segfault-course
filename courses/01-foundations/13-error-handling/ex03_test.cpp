// Exercise 03 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex03.h"

static testkit::TestRunner runner("01-13-ex03: Multiple Catch Blocks");

TEST(runner, "simulate_request returns ok for normal urls") {
    ASSERT_EQ(simulate_request("https://example.com"),
              std::string("ok: https://example.com"));
}

TEST(runner, "simulate_request throws TimeoutError for timeout") {
    ASSERT_THROWS(simulate_request("timeout"), TimeoutError);
}

TEST(runner, "simulate_request throws NetworkError for disconnect") {
    ASSERT_THROWS(simulate_request("disconnect"), NetworkError);
}

TEST(runner, "simulate_request throws runtime_error for unknown") {
    ASSERT_THROWS(simulate_request("unknown"), std::runtime_error);
}

TEST(runner, "TimeoutError is a NetworkError") {
    // TimeoutError should be catchable as NetworkError.
    try {
        simulate_request("timeout");
        ASSERT_TRUE(false);
    } catch (const NetworkError&) {
        ASSERT_TRUE(true);  // caught as base class
    }
}

TEST(runner, "classify_error returns timeout for TimeoutError") {
    ASSERT_EQ(classify_error("timeout"), std::string("timeout"));
}

TEST(runner, "classify_error returns network for NetworkError") {
    ASSERT_EQ(classify_error("disconnect"), std::string("network"));
}

TEST(runner, "classify_error returns runtime for runtime_error") {
    ASSERT_EQ(classify_error("unknown"), std::string("runtime"));
}

TEST(runner, "classify_error returns success for normal urls") {
    ASSERT_EQ(classify_error("https://example.com"), std::string("success"));
}

TESTKIT_MAIN(runner)
