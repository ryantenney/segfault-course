// Exercise 08 — Tests (read-only)
//
// Verifies that UniqueBuffer is non-copyable and manages memory correctly.

#include <type_traits>
#include <testkit/testkit.h>
#include "ex08.h"

static testkit::TestRunner runner("01-09-ex08: Non-Copyable RAII");

TEST(runner, "UniqueBuffer is not copy-constructible") {
    ASSERT_FALSE(std::is_copy_constructible_v<UniqueBuffer>);
}

TEST(runner, "UniqueBuffer is not copy-assignable") {
    ASSERT_FALSE(std::is_copy_assignable_v<UniqueBuffer>);
}

TEST(runner, "UniqueBuffer allocates and fills") {
    UniqueBuffer buf(5, 'A');
    ASSERT_EQ(buf.size(), 5);
    ASSERT_EQ(buf.at(0), 'A');
    ASSERT_EQ(buf.at(4), 'A');
}

TEST(runner, "UniqueBuffer::set modifies content") {
    UniqueBuffer buf(3, 'X');
    buf.set(1, 'Y');
    ASSERT_EQ(buf.at(0), 'X');
    ASSERT_EQ(buf.at(1), 'Y');
    ASSERT_EQ(buf.at(2), 'X');
}

TEST(runner, "UniqueBuffer::as_string returns contents") {
    UniqueBuffer buf(4, 'Z');
    ASSERT_EQ(buf.as_string(), std::string("ZZZZ"));
}

TEST(runner, "destructor cleans up allocation") {
    int before = BufferTracker::active;
    {
        UniqueBuffer buf(10, 'B');
        ASSERT_EQ(BufferTracker::active, before + 1);
    }
    ASSERT_EQ(BufferTracker::active, before);
}

TEST(runner, "why_no_copy explains the danger") {
    ASSERT_EQ(why_no_copy(), std::string("double free"));
}

TESTKIT_MAIN(runner)
