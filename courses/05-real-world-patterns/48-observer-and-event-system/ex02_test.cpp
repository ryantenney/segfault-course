// Exercise 02 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex02.h"

static testkit::TestRunner runner("05-48-ex02: Subscription ID");

TEST(runner, "on returns unique IDs") {
    IdEmitter e;
    uint64_t id1 = e.on([] {});
    uint64_t id2 = e.on([] {});
    ASSERT_NE(id1, id2);
}

TEST(runner, "off removes a listener") {
    IdEmitter e;
    int count = 0;
    uint64_t id = e.on([&count] { ++count; });
    ASSERT_EQ(e.listener_count(), std::size_t(1));
    bool removed = e.off(id);
    ASSERT_TRUE(removed);
    ASSERT_EQ(e.listener_count(), std::size_t(0));
    e.emit();
    ASSERT_EQ(count, 0);
}

TEST(runner, "off returns false for unknown ID") {
    IdEmitter e;
    e.on([] {});
    bool removed = e.off(9999);
    ASSERT_FALSE(removed);
    ASSERT_EQ(e.listener_count(), std::size_t(1));
}

TEST(runner, "removing one listener does not affect others") {
    IdEmitter e;
    int a = 0, b = 0, c = 0;
    e.on([&a] { ++a; });
    uint64_t id_b = e.on([&b] { ++b; });
    e.on([&c] { ++c; });
    e.off(id_b);
    e.emit();
    ASSERT_EQ(a, 1);
    ASSERT_EQ(b, 0);
    ASSERT_EQ(c, 1);
}

TEST(runner, "double-off returns false the second time") {
    IdEmitter e;
    uint64_t id = e.on([] {});
    ASSERT_TRUE(e.off(id));
    ASSERT_FALSE(e.off(id));
}

TESTKIT_MAIN(runner)
