// Exercise 01 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex01.h"

static testkit::TestRunner runner("01-10-ex01: Create a unique_ptr");

TEST(runner, "create_widget returns a non-null unique_ptr") {
    auto w = create_widget("Sprocket");
    ASSERT_TRUE(w != nullptr);
}

TEST(runner, "created widget has the correct name") {
    auto w = create_widget("Gear");
    ASSERT_EQ(w->name, std::string("Gear"));
}

TEST(runner, "get_widget_name reads through the pointer") {
    auto w = create_widget("Bolt");
    ASSERT_EQ(get_widget_name(w), std::string("Bolt"));
}

TEST(runner, "is_valid returns true for non-null, false for null") {
    auto w = create_widget("Cog");
    ASSERT_TRUE(is_valid(w));
    std::unique_ptr<Widget> empty;
    ASSERT_FALSE(is_valid(empty));
}

TEST(runner, "reset_widget nullifies the pointer and returns the old name") {
    auto w = create_widget("Axle");
    std::string old_name = reset_widget(w);
    ASSERT_EQ(old_name, std::string("Axle"));
    ASSERT_FALSE(is_valid(w));
}

TESTKIT_MAIN(runner)
