// Exercise 06 — Tests (read-only)
//
// Verifies static member variable for instance counting.

#include <testkit/testkit.h>
#include <memory>
#include "ex06.h"

static testkit::TestRunner runner("03-24-ex06: Static Member Variable");

TEST(runner, "instance_count starts at zero after reset") {
    Widget::reset_count();
    ASSERT_EQ(Widget::instance_count(), 0);
}

TEST(runner, "creating a widget increments count") {
    Widget::reset_count();
    Widget w;
    w.id();  // gate
    ASSERT_EQ(Widget::instance_count(), 1);
}

TEST(runner, "multiple widgets increase count") {
    Widget::reset_count();
    Widget a;
    Widget b;
    Widget c;
    a.id();  // gate
    ASSERT_EQ(Widget::instance_count(), 3);
}

TEST(runner, "destroying a widget decrements count") {
    Widget::reset_count();
    {
        Widget w;
        w.id();  // gate
        ASSERT_EQ(Widget::instance_count(), 1);
    }
    ASSERT_EQ(Widget::instance_count(), 0);
}

TEST(runner, "dynamic allocation and deletion") {
    Widget::reset_count();
    auto w1 = std::make_unique<Widget>();
    w1->id();  // gate
    ASSERT_EQ(Widget::instance_count(), 1);
    auto w2 = std::make_unique<Widget>();
    ASSERT_EQ(Widget::instance_count(), 2);
    w1.reset();
    ASSERT_EQ(Widget::instance_count(), 1);
    w2.reset();
    ASSERT_EQ(Widget::instance_count(), 0);
}

TEST(runner, "each widget has a unique ID") {
    Widget::reset_count();
    Widget a;
    Widget b;
    Widget c;
    // IDs should all be different
    ASSERT_TRUE(a.id() != b.id());
    ASSERT_TRUE(b.id() != c.id());
    ASSERT_TRUE(a.id() != c.id());
}

TEST(runner, "instance_count is callable without an instance") {
    Widget::reset_count();
    // Static method — no instance needed
    ASSERT_EQ(Widget::instance_count(), 0);
}

TESTKIT_MAIN(runner)
