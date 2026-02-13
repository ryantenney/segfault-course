// Exercise 06 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex06.h"

#include <cmath>
#include <cstring>

// Defined in ex06.cpp — gates the tests until the student completes setup.
extern void init_config();

static testkit::TestRunner runner("01-01-ex06: Extern Variables");

TEST(runner, "max_connections is 100") {
    init_config();
    ASSERT_EQ(max_connections, 100);
}

TEST(runner, "pi is approximately 3.14159") {
    init_config();
    ASSERT_TRUE(std::abs(pi - 3.14159265358979) < 1e-10);
}

TEST(runner, "app_name is SegfaultCourse") {
    init_config();
    ASSERT_TRUE(std::strcmp(app_name, "SegfaultCourse") == 0);
}

TESTKIT_MAIN(runner)
