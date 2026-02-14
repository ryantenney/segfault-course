// Exercise 05 — Tests (read-only)
//
// Verifies the IntBox RAII wrapper for dynamic allocation.

#include <testkit/testkit.h>
#include "ex05.h"

static testkit::TestRunner runner("01-09-ex05: RAII for Dynamic Allocation");

TEST(runner, "IntBox stores and retrieves value") {
    IntBox box(42);
    ASSERT_EQ(box.value(), 42);
}

TEST(runner, "IntBox::get returns non-null pointer") {
    IntBox box(10);
    ASSERT_NE(box.get(), nullptr);
    ASSERT_EQ(*box.get(), 10);
}

TEST(runner, "IntBox::set changes the value") {
    IntBox box(1);
    box.set(99);
    ASSERT_EQ(box.value(), 99);
}

TEST(runner, "destructor cleans up allocation") {
    int before = AllocTracker::active_allocations;
    {
        IntBox box(5);
        ASSERT_EQ(AllocTracker::active_allocations, before + 1);
    }
    ASSERT_EQ(AllocTracker::active_allocations, before);
}

TEST(runner, "multiple boxes track independently") {
    int before = AllocTracker::active_allocations;
    {
        IntBox a(1);
        IntBox b(2);
        ASSERT_EQ(AllocTracker::active_allocations, before + 2);
        ASSERT_EQ(a.value(), 1);
        ASSERT_EQ(b.value(), 2);
    }
    ASSERT_EQ(AllocTracker::active_allocations, before);
}

TESTKIT_MAIN(runner)
