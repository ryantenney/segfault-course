// Exercise 08 -- Tests (read-only)

#include <testkit/testkit.h>
#include <vector>

#include "ex08.h"

static testkit::TestRunner runner("05-48-ex08: Ordered Dispatch");

TEST(runner, "single listener is called") {
    OrderedEmitter e;
    bool called = false;
    e.on(0, [&called] { called = true; });
    e.emit();
    ASSERT_TRUE(called);
}

TEST(runner, "lower priority is called before higher") {
    OrderedEmitter e;
    std::vector<int> order;
    e.on(10, [&order] { order.push_back(10); });
    e.on(1,  [&order] { order.push_back(1); });
    e.on(5,  [&order] { order.push_back(5); });
    e.emit();
    ASSERT_EQ(order.size(), std::size_t(3));
    ASSERT_EQ(order[0], 1);
    ASSERT_EQ(order[1], 5);
    ASSERT_EQ(order[2], 10);
}

TEST(runner, "same priority preserves registration order") {
    OrderedEmitter e;
    std::vector<std::string> order;
    e.on(1, [&order] { order.push_back("first"); });
    e.on(1, [&order] { order.push_back("second"); });
    e.on(1, [&order] { order.push_back("third"); });
    e.emit();
    ASSERT_EQ(order.size(), std::size_t(3));
    ASSERT_EQ(order[0], std::string("first"));
    ASSERT_EQ(order[1], std::string("second"));
    ASSERT_EQ(order[2], std::string("third"));
}

TEST(runner, "mixed priorities and registration orders") {
    OrderedEmitter e;
    std::vector<int> order;
    e.on(2, [&order] { order.push_back(1); });  // prio 2, seq 0
    e.on(1, [&order] { order.push_back(2); });  // prio 1, seq 1
    e.on(2, [&order] { order.push_back(3); });  // prio 2, seq 2
    e.on(1, [&order] { order.push_back(4); });  // prio 1, seq 3
    e.emit();
    // Priority 1 first (seq 1 then seq 3), then priority 2 (seq 0 then seq 2)
    ASSERT_EQ(order.size(), std::size_t(4));
    ASSERT_EQ(order[0], 2);  // prio 1, first registered
    ASSERT_EQ(order[1], 4);  // prio 1, second registered
    ASSERT_EQ(order[2], 1);  // prio 2, first registered
    ASSERT_EQ(order[3], 3);  // prio 2, second registered
}

TEST(runner, "listener_count tracks entries") {
    OrderedEmitter e;
    e.on(0, [] {});
    e.on(5, [] {});
    e.on(3, [] {});
    ASSERT_EQ(e.listener_count(), std::size_t(3));
}

TEST(runner, "emit can be called multiple times") {
    OrderedEmitter e;
    int count = 0;
    e.on(0, [&count] { ++count; });
    e.emit();
    e.emit();
    ASSERT_EQ(count, 2);
}

TESTKIT_MAIN(runner)
