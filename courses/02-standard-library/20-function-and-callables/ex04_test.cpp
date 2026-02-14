// Exercise 04 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex04.h"

#include <string>
#include <vector>

static testkit::TestRunner runner("02-20-ex04: Store Callbacks in a Container");

TEST(runner, "starts with zero subscribers") {
    EventBus bus;
    ASSERT_EQ(bus.subscriber_count(), 0u);
}

TEST(runner, "subscribe increases count") {
    EventBus bus;
    bus.subscribe([](const std::string&) {});
    ASSERT_EQ(bus.subscriber_count(), 1u);
    bus.subscribe([](const std::string&) {});
    ASSERT_EQ(bus.subscriber_count(), 2u);
}

TEST(runner, "notify calls all subscribers") {
    EventBus bus;
    std::vector<std::string> log_a, log_b;
    bus.subscribe([&log_a](const std::string& msg) { log_a.push_back(msg); });
    bus.subscribe([&log_b](const std::string& msg) { log_b.push_back(msg); });
    bus.notify("hello");
    ASSERT_EQ(log_a.size(), 1u);
    ASSERT_EQ(log_a[0], std::string("hello"));
    ASSERT_EQ(log_b.size(), 1u);
    ASSERT_EQ(log_b[0], std::string("hello"));
}

TEST(runner, "notify with no subscribers does nothing") {
    EventBus bus;
    bus.subscriber_count();  // gate: triggers TODO() if not implemented
    ASSERT_NO_THROW(bus.notify("silence"));
}

TEST(runner, "clear removes all subscribers") {
    EventBus bus;
    bus.subscribe([](const std::string&) {});
    bus.subscribe([](const std::string&) {});
    bus.clear();
    ASSERT_EQ(bus.subscriber_count(), 0u);
}

TEST(runner, "notify after clear invokes nothing") {
    EventBus bus;
    int call_count = 0;
    bus.subscribe([&call_count](const std::string&) { ++call_count; });
    bus.clear();
    bus.notify("gone");
    ASSERT_EQ(call_count, 0);
}

TESTKIT_MAIN(runner)
