// Exercise 02 -- Tests (read-only)
//
// Verifies that ManagedArray works correctly with compiler-generated
// copy/move operations (Rule of Zero).

#include <type_traits>
#include <testkit/testkit.h>
#include "ex02.h"

static testkit::TestRunner runner("03-28-ex02: Rule of Zero");

TEST(runner, "constructor creates array of correct size") {
    ManagedArray a(5);
    ASSERT_EQ(a.size(), 5u);
}

TEST(runner, "elements are zero-initialized") {
    ManagedArray a(3);
    ASSERT_EQ(a[0], 0);
    ASSERT_EQ(a[1], 0);
    ASSERT_EQ(a[2], 0);
}

TEST(runner, "elements can be modified") {
    ManagedArray a(2);
    a[0] = 42;
    a[1] = 99;
    ASSERT_EQ(a[0], 42);
    ASSERT_EQ(a[1], 99);
}

TEST(runner, "copy produces independent object") {
    ManagedArray a(3);
    a[0] = 10;
    a[1] = 20;
    a[2] = 30;

    ManagedArray b(a);

    ASSERT_EQ(b.size(), 3u);
    ASSERT_EQ(b[0], 10);
    ASSERT_EQ(b[1], 20);
    ASSERT_EQ(b[2], 30);

    // Modifying original does not affect copy
    a[0] = 999;
    ASSERT_EQ(b[0], 10);
}

TEST(runner, "copy assignment works") {
    ManagedArray a(2);
    a[0] = 7;
    a[1] = 8;

    ManagedArray b(1);
    b = a;

    ASSERT_EQ(b.size(), 2u);
    ASSERT_EQ(b[0], 7);
    ASSERT_EQ(b[1], 8);
}

TEST(runner, "move leaves source in valid state") {
    ManagedArray a(3);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;

    ManagedArray b(std::move(a));

    ASSERT_EQ(b.size(), 3u);
    ASSERT_EQ(b[0], 1);
    ASSERT_EQ(b[1], 2);
    ASSERT_EQ(b[2], 3);

    // a is in a valid but unspecified state -- just check it's usable
    // (size() is safe to call on a moved-from vector)
    (void)a.size();
}

TESTKIT_MAIN(runner)
