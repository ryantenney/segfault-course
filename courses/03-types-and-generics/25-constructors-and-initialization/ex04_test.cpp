// Exercise 04 — Tests (read-only)
//
// Verifies that explicit constructors prevent implicit conversions.

#include <testkit/testkit.h>
#include <type_traits>
#include "ex04.h"

static testkit::TestRunner runner("03-25-ex04: Explicit Constructors");

TEST(runner, "Meters is not implicitly convertible from double") {
    // Gate: ensure value() is implemented
    Meters m(1.0);
    m.value();

    // If the constructor is explicit, double -> Meters is not implicit.
    ASSERT_TRUE((!std::is_convertible_v<double, Meters>));
}

TEST(runner, "Kilograms is not implicitly convertible from double") {
    Kilograms k(1.0);
    k.value();

    ASSERT_TRUE((!std::is_convertible_v<double, Kilograms>));
}

TEST(runner, "Meters can be explicitly constructed") {
    Meters m(5.5);
    ASSERT_TRUE(m.value() == 5.5);
}

TEST(runner, "Kilograms can be explicitly constructed") {
    Kilograms k(70.0);
    ASSERT_TRUE(k.value() == 70.0);
}

TEST(runner, "add_distances sums two Meters") {
    Meters a(3.0);
    Meters b(4.0);
    Meters result = add_distances(a, b);
    ASSERT_TRUE(result.value() == 7.0);
}

TEST(runner, "add_weights sums two Kilograms") {
    Kilograms a(50.0);
    Kilograms b(25.0);
    Kilograms result = add_weights(a, b);
    ASSERT_TRUE(result.value() == 75.0);
}

TEST(runner, "is_tall returns true for tall person") {
    ASSERT_TRUE(is_tall(Meters(1.9)));
}

TEST(runner, "is_tall returns false for short person") {
    ASSERT_FALSE(is_tall(Meters(1.5)));
}

TEST(runner, "is_tall boundary: 1.8 is not tall") {
    ASSERT_FALSE(is_tall(Meters(1.8)));
}

TESTKIT_MAIN(runner)
