// Exercise 03 -- Tests (read-only)

#include <testkit/testkit.h>
#include <string>

#include "ex03.h"

static testkit::TestRunner runner("05-48-ex03: Multi-event Dispatcher");

TEST(runner, "listener_count is zero for unknown event") {
    Dispatcher d;
    // Gate: on() must work
    d.on("test", [] {});
    Dispatcher fresh;
    ASSERT_EQ(fresh.listener_count("anything"), std::size_t(0));
}

TEST(runner, "on registers a callback for a specific event") {
    Dispatcher d;
    d.on("click", [] {});
    ASSERT_EQ(d.listener_count("click"), std::size_t(1));
    ASSERT_EQ(d.listener_count("hover"), std::size_t(0));
}

TEST(runner, "emit calls only the listeners for that event") {
    Dispatcher d;
    bool click_called = false;
    bool hover_called = false;
    d.on("click", [&click_called] { click_called = true; });
    d.on("hover", [&hover_called] { hover_called = true; });
    d.emit("click");
    ASSERT_TRUE(click_called);
    ASSERT_FALSE(hover_called);
}

TEST(runner, "multiple listeners per event are all called") {
    Dispatcher d;
    int count = 0;
    d.on("save", [&count] { count += 1; });
    d.on("save", [&count] { count += 10; });
    d.on("save", [&count] { count += 100; });
    d.emit("save");
    ASSERT_EQ(count, 111);
}

TEST(runner, "emit on event with no listeners does nothing") {
    Dispatcher d;
    d.on("click", [] {});
    // Should not crash
    d.emit("unknown_event");
}

TEST(runner, "different events are independent") {
    Dispatcher d;
    int a = 0, b = 0;
    d.on("alpha", [&a] { ++a; });
    d.on("beta", [&b] { ++b; });
    d.emit("alpha");
    d.emit("alpha");
    d.emit("beta");
    ASSERT_EQ(a, 2);
    ASSERT_EQ(b, 1);
}

TESTKIT_MAIN(runner)
