// Exercise 02 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex02.h"

static testkit::TestRunner runner("03-26-ex02: Defaulted Equality");

TEST(runner, "identical Rects are equal") {
    exercise_ready();  // gate on TODO()
    Rect a{0.0, 0.0, 10.0, 20.0};
    Rect b{0.0, 0.0, 10.0, 20.0};
    ASSERT_TRUE(a == b);
}

TEST(runner, "Rects with different dimensions are not equal") {
    exercise_ready();
    Rect a{0.0, 0.0, 10.0, 20.0};
    Rect b{0.0, 0.0, 10.0, 25.0};
    ASSERT_FALSE(a == b);
}

TEST(runner, "Rect operator!= is synthesized") {
    exercise_ready();
    Rect a{1.0, 2.0, 3.0, 4.0};
    Rect b{1.0, 2.0, 3.0, 5.0};
    ASSERT_TRUE(a != b);
    ASSERT_FALSE(a != a);
}

TEST(runner, "identical Employees are equal") {
    exercise_ready();
    Employee a{1, "Alice", "Engineering"};
    Employee b{1, "Alice", "Engineering"};
    ASSERT_TRUE(a == b);
}

TEST(runner, "Employees with different id are not equal") {
    exercise_ready();
    Employee a{1, "Alice", "Engineering"};
    Employee b{2, "Alice", "Engineering"};
    ASSERT_FALSE(a == b);
}

TEST(runner, "Employees with different name are not equal") {
    exercise_ready();
    Employee a{1, "Alice", "Engineering"};
    Employee b{1, "Bob", "Engineering"};
    ASSERT_FALSE(a == b);
}

TEST(runner, "Employee operator!= is synthesized") {
    exercise_ready();
    Employee a{1, "Alice", "Engineering"};
    Employee b{1, "Alice", "Marketing"};
    ASSERT_TRUE(a != b);
}

TESTKIT_MAIN(runner)
