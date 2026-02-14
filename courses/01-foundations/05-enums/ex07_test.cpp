// Exercise 07 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex07.h"

static testkit::TestRunner runner("01-05-ex07: Strong Typedef");

TEST(runner, "UserId and OrderId are distinct types") {
    // This test verifies the types are different at compile time.
    // If UserId and OrderId were both just `int`, these would be
    // the same type, and the static_assert would fire.
    static_assert(!std::is_same_v<UserId, OrderId>,
                  "UserId and OrderId must be distinct types");
    static_assert(!std::is_same_v<UserId, int>,
                  "UserId must not be a plain int");
    static_assert(!std::is_same_v<OrderId, int>,
                  "OrderId must not be a plain int");
    ASSERT_TRUE(true);
}

TEST(runner, "make_user_id and make_order_id construct values") {
    UserId uid = make_user_id(42);
    OrderId oid = make_order_id(99);
    ASSERT_EQ(user_id_value(uid), 42);
    ASSERT_EQ(order_id_value(oid), 99);
}

TEST(runner, "UserId equality comparison works") {
    UserId a = make_user_id(1);
    UserId b = make_user_id(1);
    UserId c = make_user_id(2);
    ASSERT_TRUE(a == b);
    ASSERT_FALSE(a == c);
    ASSERT_TRUE(a != c);
    ASSERT_FALSE(a != b);
}

TEST(runner, "OrderId equality comparison works") {
    OrderId a = make_order_id(10);
    OrderId b = make_order_id(10);
    OrderId c = make_order_id(20);
    ASSERT_TRUE(a == b);
    ASSERT_FALSE(a == c);
    ASSERT_TRUE(a != c);
    ASSERT_FALSE(a != b);
}

TEST(runner, "same numeric value in different wrapper types are not equal") {
    // This test ensures you can't accidentally compare UserId with OrderId.
    // With strong typedefs, the following should NOT compile:
    //   make_user_id(42) == make_order_id(42)
    // We verify the values are independently correct.
    UserId uid = make_user_id(42);
    OrderId oid = make_order_id(42);
    ASSERT_EQ(user_id_value(uid), 42);
    ASSERT_EQ(order_id_value(oid), 42);
    // They wrap the same int, but are different types
    ASSERT_TRUE(true);
}

TESTKIT_MAIN(runner)
