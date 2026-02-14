// Exercise 03 -- Tests (read-only)
//
// All tests call the constexpr functions at RUNTIME via ASSERT_EQ.
// This way, TODO() inside the functions causes tests to be "skipped"
// rather than causing a compile-time failure (which would happen with
// static_assert).

#include <testkit/testkit.h>

#include "ex03.h"

static testkit::TestRunner runner("03-32-ex03: constexpr Function");

TEST(runner, "factorial of 0 is 1") {
    ASSERT_EQ(constexpr_factorial(0), 1);
}

TEST(runner, "factorial of 1 is 1") {
    ASSERT_EQ(constexpr_factorial(1), 1);
}

TEST(runner, "factorial of 5 is 120") {
    ASSERT_EQ(constexpr_factorial(5), 120);
}

TEST(runner, "factorial of 10 is 3628800") {
    ASSERT_EQ(constexpr_factorial(10), 3628800);
}

TEST(runner, "fibonacci of 0 is 0") {
    ASSERT_EQ(constexpr_fibonacci(0), 0);
}

TEST(runner, "fibonacci of 1 is 1") {
    ASSERT_EQ(constexpr_fibonacci(1), 1);
}

TEST(runner, "fibonacci of 10 is 55") {
    ASSERT_EQ(constexpr_fibonacci(10), 55);
}

TEST(runner, "is_prime returns false for 0 and 1") {
    ASSERT_FALSE(constexpr_is_prime(0));
    ASSERT_FALSE(constexpr_is_prime(1));
}

TEST(runner, "is_prime returns true for small primes") {
    ASSERT_TRUE(constexpr_is_prime(2));
    ASSERT_TRUE(constexpr_is_prime(3));
    ASSERT_TRUE(constexpr_is_prime(7));
    ASSERT_TRUE(constexpr_is_prime(13));
}

TEST(runner, "is_prime returns false for composites") {
    ASSERT_FALSE(constexpr_is_prime(4));
    ASSERT_FALSE(constexpr_is_prime(9));
    ASSERT_FALSE(constexpr_is_prime(15));
    ASSERT_FALSE(constexpr_is_prime(100));
}

TESTKIT_MAIN(runner)
