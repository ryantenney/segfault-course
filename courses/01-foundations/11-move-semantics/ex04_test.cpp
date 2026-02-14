// Exercise 04 -- Tests (read-only)

#include <testkit/testkit.h>
#include <utility>

#include "ex04.h"

static testkit::TestRunner runner("01-11-ex04: Move Assignment Operator");

TEST(runner, "move assignment transfers data") {
    Storage a(3);
    a.set(0, "hello");
    a.set(1, "world");

    Storage b(1);
    b = std::move(a);

    ASSERT_EQ(b.capacity(), 3u);
    ASSERT_EQ(b.get(0), std::string("hello"));
    ASSERT_EQ(b.get(1), std::string("world"));
}

TEST(runner, "move assignment leaves source empty") {
    Storage a(5);
    Storage b(2);
    b = std::move(a);
    ASSERT_TRUE(a.empty());
    ASSERT_EQ(a.capacity(), 0u);
}

TEST(runner, "move assignment replaces existing data in dest") {
    Storage a(2);
    a.set(0, "new");

    Storage b(3);
    b.set(0, "old");
    b.set(1, "stale");

    b = std::move(a);
    ASSERT_EQ(b.capacity(), 2u);
    ASSERT_EQ(b.get(0), std::string("new"));
}

TEST(runner, "self assignment is safe") {
    Storage s(3);
    s.set(0, "keep");
    s = std::move(s);
    // After self-move, should still be in a valid state.
    // The standard says the object must be valid but state is unspecified,
    // but a good implementation preserves data on self-move.
    ASSERT_EQ(s.capacity(), 3u);
}

TESTKIT_MAIN(runner)
