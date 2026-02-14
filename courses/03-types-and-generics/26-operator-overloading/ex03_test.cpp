// Exercise 03 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex03.h"

static testkit::TestRunner runner("03-26-ex03: Spaceship Operator");

TEST(runner, "Version equality works") {
    exercise_ready();  // gate on TODO()
    Version a{1, 2, 3};
    Version b{1, 2, 3};
    ASSERT_TRUE(a == b);
    ASSERT_FALSE(a != b);
}

TEST(runner, "Version comparison by major") {
    exercise_ready();
    Version v1{1, 0, 0};
    Version v2{2, 0, 0};
    ASSERT_TRUE(v1 < v2);
    ASSERT_TRUE(v2 > v1);
    ASSERT_TRUE(v1 <= v2);
    ASSERT_TRUE(v2 >= v1);
}

TEST(runner, "Version comparison by minor when major is equal") {
    exercise_ready();
    Version v1{1, 2, 0};
    Version v2{1, 3, 0};
    ASSERT_TRUE(v1 < v2);
    ASSERT_FALSE(v2 < v1);
}

TEST(runner, "Version comparison by patch when major and minor are equal") {
    exercise_ready();
    Version v1{1, 2, 3};
    Version v2{1, 2, 4};
    ASSERT_TRUE(v1 < v2);
    ASSERT_TRUE(v1 <= v2);
}

TEST(runner, "FullName equality works") {
    exercise_ready();
    FullName a{"Smith", "Alice"};
    FullName b{"Smith", "Alice"};
    ASSERT_TRUE(a == b);
}

TEST(runner, "FullName sorts by last_name first") {
    exercise_ready();
    FullName alice_jones{"Jones", "Alice"};
    FullName bob_smith{"Smith", "Bob"};
    ASSERT_TRUE(alice_jones < bob_smith);  // Jones < Smith
}

TEST(runner, "FullName sorts by first_name when last_name is equal") {
    exercise_ready();
    FullName alice{"Smith", "Alice"};
    FullName bob{"Smith", "Bob"};
    ASSERT_TRUE(alice < bob);  // Alice < Bob
}

TEST(runner, "FullName greater-than and greater-than-or-equal work") {
    exercise_ready();
    FullName a{"Adams", "Zoe"};
    FullName b{"Baker", "Amy"};
    ASSERT_TRUE(b > a);
    ASSERT_TRUE(b >= a);
    ASSERT_TRUE(a >= a);
}

TESTKIT_MAIN(runner)
