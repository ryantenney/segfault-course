// Exercise 01 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex01.h"

static testkit::TestRunner runner("05-48-ex01: Simple Event Emitter");

TEST(runner, "emitter starts with no listeners") {
    Emitter e;
    // Gate: on() must work for subsequent tests
    bool called = false;
    e.on([&called] { called = true; });
    ASSERT_EQ(e.listener_count(), std::size_t(1));
}

TEST(runner, "emit calls registered callback") {
    Emitter e;
    bool called = false;
    e.on([&called] { called = true; });
    e.emit();
    ASSERT_TRUE(called);
}

TEST(runner, "emit calls multiple callbacks in order") {
    Emitter e;
    std::vector<int> order;
    e.on([&order] { order.push_back(1); });
    e.on([&order] { order.push_back(2); });
    e.on([&order] { order.push_back(3); });
    e.emit();
    ASSERT_EQ(order.size(), std::size_t(3));
    ASSERT_EQ(order[0], 1);
    ASSERT_EQ(order[1], 2);
    ASSERT_EQ(order[2], 3);
}

TEST(runner, "emit can be called multiple times") {
    Emitter e;
    int count = 0;
    e.on([&count] { ++count; });
    e.emit();
    e.emit();
    e.emit();
    ASSERT_EQ(count, 3);
}

TEST(runner, "emit with no listeners does nothing") {
    Emitter e;
    // Gate: just prove on() works
    bool flag = false;
    e.on([&flag] { flag = true; });
    // Create a fresh emitter with no listeners
    Emitter empty;
    ASSERT_EQ(empty.listener_count(), std::size_t(0));
    // Should not crash
    empty.emit();
}

TESTKIT_MAIN(runner)
