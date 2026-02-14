// Exercise 06 -- Tests (read-only)

#include <testkit/testkit.h>
#include <utility>

#include "ex06.h"

static testkit::TestRunner runner("01-11-ex06: Move-Only Type");

TEST(runner, "constructor creates a valid handle") {
    UniqueHandle h("resource", 1);
    ASSERT_EQ(h.name(), std::string("resource"));
    ASSERT_EQ(h.id(), 1);
    ASSERT_TRUE(h.valid());
}

TEST(runner, "move constructor transfers ownership") {
    UniqueHandle a("conn", 42);
    UniqueHandle b(std::move(a));
    ASSERT_EQ(b.name(), std::string("conn"));
    ASSERT_EQ(b.id(), 42);
    ASSERT_TRUE(b.valid());
}

TEST(runner, "move constructor invalidates source") {
    UniqueHandle a("socket", 10);
    UniqueHandle b(std::move(a));
    ASSERT_FALSE(a.valid());
}

TEST(runner, "move assignment transfers ownership") {
    UniqueHandle a("file", 1);
    UniqueHandle b("temp", 2);
    b = std::move(a);
    ASSERT_EQ(b.name(), std::string("file"));
    ASSERT_EQ(b.id(), 1);
    ASSERT_TRUE(b.valid());
    ASSERT_FALSE(a.valid());
}

TEST(runner, "move-only types can be stored in a vector") {
    auto handles = make_handles(3);
    ASSERT_EQ(handles.size(), 3u);
    ASSERT_EQ(handles[0].id(), 0);
    ASSERT_EQ(handles[1].id(), 1);
    ASSERT_EQ(handles[2].id(), 2);
    ASSERT_TRUE(handles[0].valid());
}

TESTKIT_MAIN(runner)
