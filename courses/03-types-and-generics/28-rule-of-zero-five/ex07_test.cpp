// Exercise 07 -- Tests (read-only)
//
// Verifies that UniqueHandle is a move-only type that works in containers.

#include <type_traits>
#include <utility>
#include <testkit/testkit.h>
#include "ex07.h"

static testkit::TestRunner runner("03-28-ex07: Move-Only Type");

TEST(runner, "is not copy constructible") {
    UniqueHandle h(1, "test");
    (void)h.id();

    ASSERT_TRUE(!std::is_copy_constructible_v<UniqueHandle>);
}

TEST(runner, "is not copy assignable") {
    UniqueHandle h(1, "test");
    (void)h.id();

    ASSERT_TRUE(!std::is_copy_assignable_v<UniqueHandle>);
}

TEST(runner, "move constructor transfers ownership") {
    UniqueHandle a(42, "alpha");
    UniqueHandle b(std::move(a));

    ASSERT_EQ(b.id(), 42);
    ASSERT_EQ(b.label(), std::string("alpha"));
    ASSERT_TRUE(b.valid());
    ASSERT_FALSE(a.valid());
}

TEST(runner, "move assignment transfers ownership") {
    UniqueHandle a(1, "first");
    UniqueHandle b(2, "second");

    b = std::move(a);

    ASSERT_EQ(b.id(), 1);
    ASSERT_EQ(b.label(), std::string("first"));
    ASSERT_TRUE(b.valid());
    ASSERT_FALSE(a.valid());
}

TEST(runner, "make_handles creates correct number of handles") {
    auto handles = make_handles(5);
    ASSERT_EQ(handles.size(), 5u);
}

TEST(runner, "make_handles creates handles with correct ids") {
    auto handles = make_handles(4);
    ASSERT_EQ(handles[0].id(), 0);
    ASSERT_EQ(handles[1].id(), 1);
    ASSERT_EQ(handles[2].id(), 2);
    ASSERT_EQ(handles[3].id(), 3);
}

TEST(runner, "make_handles creates handles with correct labels") {
    auto handles = make_handles(3);
    ASSERT_EQ(handles[0].label(), std::string("handle-0"));
    ASSERT_EQ(handles[1].label(), std::string("handle-1"));
    ASSERT_EQ(handles[2].label(), std::string("handle-2"));
}

TEST(runner, "make_handles handles are valid") {
    auto handles = make_handles(3);
    ASSERT_TRUE(handles[0].valid());
    ASSERT_TRUE(handles[1].valid());
    ASSERT_TRUE(handles[2].valid());
}

TEST(runner, "make_handles with zero count returns empty vector") {
    auto handles = make_handles(0);
    ASSERT_TRUE(handles.empty());
}

TESTKIT_MAIN(runner)
