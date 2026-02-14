// Exercise 03 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex03.h"

static testkit::TestRunner runner("01-05-ex03: Enum to String");

TEST(runner, "to_string converts Direction to its name") {
    ASSERT_EQ(to_string(Direction::North), std::string_view("North"));
    ASSERT_EQ(to_string(Direction::South), std::string_view("South"));
    ASSERT_EQ(to_string(Direction::East), std::string_view("East"));
    ASSERT_EQ(to_string(Direction::West), std::string_view("West"));
}

TEST(runner, "to_arrow converts Direction to an arrow character") {
    ASSERT_EQ(to_arrow(Direction::North), '^');
    ASSERT_EQ(to_arrow(Direction::South), 'v');
    ASSERT_EQ(to_arrow(Direction::East), '>');
    ASSERT_EQ(to_arrow(Direction::West), '<');
}

TESTKIT_MAIN(runner)
