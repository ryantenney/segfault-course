// Exercise 06 — Tests (read-only)
//
// Verifies static_cast for upcasts and dynamic_cast for downcasts.

#include <testkit/testkit.h>
#include "ex06.h"

static testkit::TestRunner runner("01-08-ex06: Cast in a Class Hierarchy");

TEST(runner, "car_to_vehicle upcasts correctly") {
    Car c(4);
    Vehicle* v = car_to_vehicle(&c);
    ASSERT_NE(v, nullptr);
    ASSERT_EQ(v->describe(), std::string("Car"));
}

TEST(runner, "vehicle_to_car succeeds for Car") {
    Car c(2);
    Vehicle* v = &c;
    Car* recovered = vehicle_to_car(v);
    ASSERT_NE(recovered, nullptr);
    ASSERT_EQ(recovered->doors(), 2);
}

TEST(runner, "vehicle_to_car returns nullptr for Truck") {
    Truck t(5.0);
    Vehicle* v = &t;
    Car* result = vehicle_to_car(v);
    ASSERT_EQ(result, nullptr);
}

TEST(runner, "get_doors returns door count for Car") {
    Car c(4);
    Vehicle* v = &c;
    ASSERT_EQ(get_doors(v), 4);
}

TEST(runner, "get_doors returns -1 for Truck") {
    Truck t(3.0);
    Vehicle* v = &t;
    ASSERT_EQ(get_doors(v), -1);
}

TEST(runner, "get_payload returns payload for Truck") {
    Truck t(7.5);
    Vehicle* v = &t;
    ASSERT_EQ(get_payload(v), 7.5);
}

TEST(runner, "get_payload returns -1 for Car") {
    Car c(4);
    Vehicle* v = &c;
    ASSERT_EQ(get_payload(v), -1.0);
}

TESTKIT_MAIN(runner)
