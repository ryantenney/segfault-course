// Exercise 02 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex02.h"

static testkit::TestRunner runner("01-10-ex02: Raw to unique_ptr");

TEST(runner, "create_sensor returns a valid unique_ptr") {
    auto s = create_sensor("temp-01", 23.5);
    ASSERT_TRUE(s != nullptr);
    ASSERT_EQ(s->id, std::string("temp-01"));
    ASSERT_EQ(s->reading, 23.5);
}

TEST(runner, "read_sensor returns the reading") {
    auto s = create_sensor("pressure-01", 101.3);
    ASSERT_EQ(read_sensor(s), 101.3);
}

TEST(runner, "read_sensor returns -1 for null") {
    std::unique_ptr<Sensor> empty;
    ASSERT_EQ(read_sensor(empty), -1.0);
}

TEST(runner, "update_reading changes the sensor value") {
    auto s = create_sensor("humidity-01", 45.0);
    update_reading(s, 52.0);
    ASSERT_EQ(s->reading, 52.0);
}

TEST(runner, "release_sensor transfers ownership to raw pointer") {
    auto s = create_sensor("wind-01", 12.5);
    Sensor* raw = release_sensor(s);
    ASSERT_TRUE(s == nullptr);
    ASSERT_EQ(raw->id, std::string("wind-01"));
    ASSERT_EQ(raw->reading, 12.5);
    delete raw; // manual cleanup since we took ownership
}

TESTKIT_MAIN(runner)
