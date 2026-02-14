// Exercise 03 -- Tests (read-only)
//
// Verifies that UniqueResource is non-copyable and works correctly.

#include <type_traits>
#include <testkit/testkit.h>
#include "ex03.h"

static testkit::TestRunner runner("03-28-ex03: Deleted Copy");

TEST(runner, "constructor initializes resource") {
    UniqueResource r("device0", 42);
    ASSERT_EQ(r.name(), std::string("device0"));
    ASSERT_EQ(r.handle(), 42);
}

TEST(runner, "resource is open after construction") {
    UniqueResource r("dev", 1);
    ASSERT_TRUE(r.is_open());
}

TEST(runner, "copy constructor is deleted") {
    // Gate: ensure the constructor works first.
    UniqueResource r("dev", 1);
    (void)r.is_open();

    ASSERT_TRUE(!std::is_copy_constructible_v<UniqueResource>);
}

TEST(runner, "copy assignment is deleted") {
    UniqueResource r("dev", 1);
    (void)r.is_open();

    ASSERT_TRUE(!std::is_copy_assignable_v<UniqueResource>);
}

TESTKIT_MAIN(runner)
