// Exercise 03 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex03.h"

static testkit::TestRunner runner("01-01-ex03: Forward Declarations");

TEST(runner, "engine is not installed by default") {
    Engine e("V8", 400);
    ASSERT_TRUE(!e.is_installed());
}

TEST(runner, "engine is installed after set_car") {
    Car c("Mustang", 150);
    Engine e("V8", 400);
    e.set_car(&c);
    ASSERT_TRUE(e.is_installed());
}

TEST(runner, "engine stores correct attributes") {
    Engine e("Turbo-4", 250);
    ASSERT_EQ(e.type(), std::string("Turbo-4"));
    ASSERT_EQ(e.horsepower(), 250);
}

TEST(runner, "engine points back to the car") {
    Car c("Civic", 180);
    Engine e("i4", 180);
    e.set_car(&c);
    ASSERT_EQ(e.car()->name(), std::string("Civic"));
}

TESTKIT_MAIN(runner)
