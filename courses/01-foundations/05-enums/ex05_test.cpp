// Exercise 05 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex05.h"

static testkit::TestRunner runner("01-05-ex05: Enum as Bitflags");

TEST(runner, "Permission values are correct powers of two") {
    read_write(); // gates on TODO()
    ASSERT_EQ(static_cast<uint8_t>(Permission::None), uint8_t(0));
    ASSERT_EQ(static_cast<uint8_t>(Permission::Read), uint8_t(1));
    ASSERT_EQ(static_cast<uint8_t>(Permission::Write), uint8_t(2));
    ASSERT_EQ(static_cast<uint8_t>(Permission::Execute), uint8_t(4));
}

TEST(runner, "operator| combines flags") {
    Permission rw = Permission::Read | Permission::Write;
    ASSERT_EQ(static_cast<uint8_t>(rw), uint8_t(3));

    Permission all = Permission::Read | Permission::Write | Permission::Execute;
    ASSERT_EQ(static_cast<uint8_t>(all), uint8_t(7));
}

TEST(runner, "operator& tests flags") {
    Permission rw = Permission::Read | Permission::Write;
    ASSERT_EQ(static_cast<uint8_t>(rw & Permission::Read), uint8_t(1));
    ASSERT_EQ(static_cast<uint8_t>(rw & Permission::Execute), uint8_t(0));
}

TEST(runner, "has_permission checks individual flags") {
    Permission rw = Permission::Read | Permission::Write;
    ASSERT_TRUE(has_permission(rw, Permission::Read));
    ASSERT_TRUE(has_permission(rw, Permission::Write));
    ASSERT_FALSE(has_permission(rw, Permission::Execute));
    ASSERT_FALSE(has_permission(Permission::None, Permission::Read));
}

TEST(runner, "read_write combines Read and Write") {
    Permission rw = read_write();
    ASSERT_TRUE(has_permission(rw, Permission::Read));
    ASSERT_TRUE(has_permission(rw, Permission::Write));
    ASSERT_FALSE(has_permission(rw, Permission::Execute));
}

TEST(runner, "all_permissions combines all three flags") {
    Permission all = all_permissions();
    ASSERT_TRUE(has_permission(all, Permission::Read));
    ASSERT_TRUE(has_permission(all, Permission::Write));
    ASSERT_TRUE(has_permission(all, Permission::Execute));
}

TESTKIT_MAIN(runner)
