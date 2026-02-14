// Exercise 01 — Tests (read-only)
//
// Verifies the Sensor class uses member initializer lists correctly.

#include <testkit/testkit.h>
#include <string>
#include "ex01.h"

static testkit::TestRunner runner("03-25-ex01: Member Initializer List");

TEST(runner, "sensor constructed with correct name") {
    Sensor s("Temperature", -40.0, 125.0, 1001);
    ASSERT_EQ(s.name(), std::string("Temperature"));
}

TEST(runner, "sensor has correct range") {
    Sensor s("Pressure", 0.0, 100.0, 2002);
    ASSERT_TRUE(s.min_value() == 0.0);
    ASSERT_TRUE(s.max_value() == 100.0);
}

TEST(runner, "current_value starts at zero") {
    Sensor s("Humidity", 0.0, 100.0, 3003);
    ASSERT_TRUE(s.current_value() == 0.0);
}

TEST(runner, "serial_number is preserved") {
    Sensor s("Temp", -10.0, 50.0, 42);
    ASSERT_EQ(s.serial_number(), 42);
}

TEST(runner, "record updates current value") {
    Sensor s("Temp", -40.0, 125.0, 1001);
    s.record(23.5);
    ASSERT_TRUE(s.current_value() == 23.5);
}

TEST(runner, "record clamps to max") {
    Sensor s("Temp", -40.0, 125.0, 1001);
    s.record(200.0);
    ASSERT_TRUE(s.current_value() == 125.0);
}

TEST(runner, "record clamps to min") {
    Sensor s("Temp", -40.0, 125.0, 1001);
    s.record(-100.0);
    ASSERT_TRUE(s.current_value() == -40.0);
}

TEST(runner, "record accepts boundary values") {
    Sensor s("Temp", 0.0, 100.0, 1001);
    s.record(0.0);
    ASSERT_TRUE(s.current_value() == 0.0);
    s.record(100.0);
    ASSERT_TRUE(s.current_value() == 100.0);
}

TESTKIT_MAIN(runner)
