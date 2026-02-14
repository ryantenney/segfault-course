// Exercise 03 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex03.h"

static testkit::TestRunner runner("02-20-ex03: Function Pointer");

TEST(runner, "apply calls function pointer with correct arguments") {
    ASSERT_EQ(apply(&add_ints, 3, 4), 7);
    ASSERT_EQ(apply(&multiply_ints, 3, 4), 12);
}

TEST(runner, "select_operation returns add_ints for '+'") {
    BinaryOp op = select_operation('+');
    ASSERT_TRUE(op != nullptr);
    ASSERT_EQ(op(10, 5), 15);
}

TEST(runner, "select_operation returns multiply_ints for '*'") {
    BinaryOp op = select_operation('*');
    ASSERT_TRUE(op != nullptr);
    ASSERT_EQ(op(10, 5), 50);
}

TEST(runner, "select_operation returns nullptr for unknown op") {
    BinaryOp op = select_operation('?');
    ASSERT_TRUE(op == nullptr);
}

TEST(runner, "compute combines select and apply") {
    ASSERT_EQ(compute('+', 6, 7), 13);
    ASSERT_EQ(compute('*', 6, 7), 42);
}

TEST(runner, "compute returns 0 for invalid operation") {
    ASSERT_EQ(compute('-', 6, 7), 0);
}

TESTKIT_MAIN(runner)
