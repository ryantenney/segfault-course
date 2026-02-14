// Exercise 04 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex04.h"

static testkit::TestRunner runner("03-26-ex04: Arithmetic Operators");

TEST(runner, "operator+= adds components in place") {
    Vec2 a{1.0, 2.0};
    Vec2 b{3.0, 4.0};
    a += b;
    Vec2 expected{4.0, 6.0};
    ASSERT_TRUE(a == expected);
}

TEST(runner, "operator+= returns a reference to *this") {
    Vec2 a{1.0, 1.0};
    Vec2 b{2.0, 3.0};
    Vec2& ref = (a += b);
    ASSERT_TRUE(&ref == &a);
}

TEST(runner, "operator+ returns a new vector") {
    Vec2 a{1.0, 2.0};
    Vec2 b{3.0, 4.0};
    Vec2 c = a + b;
    Vec2 expected_c{4.0, 6.0};
    Vec2 expected_a{1.0, 2.0};
    Vec2 expected_b{3.0, 4.0};
    ASSERT_TRUE(c == expected_c);
    // originals unchanged
    ASSERT_TRUE(a == expected_a);
    ASSERT_TRUE(b == expected_b);
}

TEST(runner, "operator+ works with chaining") {
    Vec2 a{1.0, 0.0};
    Vec2 b{0.0, 1.0};
    Vec2 c{2.0, 3.0};
    Vec2 result = a + b + c;
    Vec2 expected{3.0, 4.0};
    ASSERT_TRUE(result == expected);
}

TEST(runner, "operator*= scales both components") {
    Vec2 v{3.0, 4.0};
    v *= 2.0;
    Vec2 expected{6.0, 8.0};
    ASSERT_TRUE(v == expected);
}

TEST(runner, "operator*= returns a reference to *this") {
    Vec2 v{1.0, 1.0};
    Vec2& ref = (v *= 5.0);
    ASSERT_TRUE(&ref == &v);
}

TEST(runner, "operator* returns a new scaled vector") {
    Vec2 v{3.0, 4.0};
    Vec2 scaled = v * 0.5;
    Vec2 expected_scaled{1.5, 2.0};
    Vec2 expected_v{3.0, 4.0};
    ASSERT_TRUE(scaled == expected_scaled);
    // original unchanged
    ASSERT_TRUE(v == expected_v);
}

TEST(runner, "operator*= with zero produces zero vector") {
    Vec2 v{5.0, 10.0};
    v *= 0.0;
    Vec2 expected{0.0, 0.0};
    ASSERT_TRUE(v == expected);
}

TESTKIT_MAIN(runner)
