// Exercise 08 — Tests (read-only)
//
// Verifies correct cast choice for each scenario.

#include <testkit/testkit.h>
#include "ex08.h"

static testkit::TestRunner runner("01-08-ex08: Identify the Right Cast");

TEST(runner, "int_to_float converts with static_cast") {
    ASSERT_EQ(int_to_float(42), 42.0f);
    ASSERT_EQ(int_to_float(-7), -7.0f);
    ASSERT_EQ(int_to_float(0), 0.0f);
}

TEST(runner, "call_legacy_read uses const_cast on const data") {
    const char* msg = "AB";
    int result = call_legacy_read(msg);
    // 'A' = 65, 'B' = 66 -> sum = 131
    ASSERT_EQ(result, 131);
}

TEST(runner, "smart_print uses dynamic_cast to detect Label") {
    Label label("Important");
    Printable* p = &label;
    ASSERT_EQ(smart_print(p), std::string("[Important]"));
}

TEST(runner, "smart_print falls back to text() for non-Label") {
    PlainText plain("Hello");
    Printable* p = &plain;
    ASSERT_EQ(smart_print(p), std::string("Hello"));
}

TEST(runner, "round_trip_pointer uses reinterpret_cast") {
    double x = 3.14;
    double* recovered = round_trip_pointer(&x);
    ASSERT_EQ(recovered, &x);
    ASSERT_EQ(*recovered, 3.14);
}

TESTKIT_MAIN(runner)
