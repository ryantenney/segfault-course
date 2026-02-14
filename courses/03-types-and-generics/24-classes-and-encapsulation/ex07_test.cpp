// Exercise 07 — Tests (read-only)
//
// Verifies static factory methods on the Temperature class.

#include <testkit/testkit.h>
#include <stdexcept>
#include <cmath>
#include "ex07.h"

static testkit::TestRunner runner("03-24-ex07: Static Factory Method");

TEST(runner, "from_celsius stores value directly") {
    auto t = Temperature::from_celsius(100.0);
    ASSERT_TRUE(std::abs(t.celsius() - 100.0) < 0.01);
}

TEST(runner, "from_fahrenheit(32) is 0 Celsius") {
    auto t = Temperature::from_fahrenheit(32.0);
    ASSERT_TRUE(std::abs(t.celsius()) < 0.01);
}

TEST(runner, "from_fahrenheit(212) is 100 Celsius") {
    auto t = Temperature::from_fahrenheit(212.0);
    ASSERT_TRUE(std::abs(t.celsius() - 100.0) < 0.01);
}

TEST(runner, "from_kelvin(273.15) is 0 Celsius") {
    auto t = Temperature::from_kelvin(273.15);
    ASSERT_TRUE(std::abs(t.celsius()) < 0.01);
}

TEST(runner, "from_kelvin(0) is -273.15 Celsius") {
    auto t = Temperature::from_kelvin(0.0);
    ASSERT_TRUE(std::abs(t.celsius() - (-273.15)) < 0.01);
}

TEST(runner, "from_kelvin rejects negative") {
    ASSERT_THROWS(Temperature::from_kelvin(-1.0), std::invalid_argument);
}

TEST(runner, "celsius getter returns correct value") {
    auto t = Temperature::from_celsius(37.0);
    ASSERT_TRUE(std::abs(t.celsius() - 37.0) < 0.01);
}

TEST(runner, "fahrenheit getter converts correctly") {
    auto t = Temperature::from_celsius(100.0);
    ASSERT_TRUE(std::abs(t.fahrenheit() - 212.0) < 0.01);
}

TEST(runner, "fahrenheit for body temperature") {
    auto t = Temperature::from_celsius(37.0);
    ASSERT_TRUE(std::abs(t.fahrenheit() - 98.6) < 0.1);
}

TEST(runner, "kelvin getter converts correctly") {
    auto t = Temperature::from_celsius(0.0);
    ASSERT_TRUE(std::abs(t.kelvin() - 273.15) < 0.01);
}

TEST(runner, "round-trip: Celsius -> Fahrenheit -> Celsius") {
    auto t1 = Temperature::from_celsius(42.0);
    auto t2 = Temperature::from_fahrenheit(t1.fahrenheit());
    ASSERT_TRUE(std::abs(t1.celsius() - t2.celsius()) < 0.01);
}

TEST(runner, "round-trip: Celsius -> Kelvin -> Celsius") {
    auto t1 = Temperature::from_celsius(-40.0);
    auto t2 = Temperature::from_kelvin(t1.kelvin());
    ASSERT_TRUE(std::abs(t1.celsius() - t2.celsius()) < 0.01);
}

TESTKIT_MAIN(runner)
