// Exercise 04 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex04.h"

static testkit::TestRunner runner("01-13-ex04: Exception Safety with RAII");

TEST(runner, "process_data_unsafe computes sum correctly") {
    // arr = {0*2, 1*2, 2*2, 3*2, 4*2} = {0, 2, 4, 6, 8} -> sum = 20
    ASSERT_EQ(process_data_unsafe(5, 2), 20);
}

TEST(runner, "process_data_unsafe throws on zero factor") {
    ASSERT_THROWS(process_data_unsafe(5, 0), std::runtime_error);
}

TEST(runner, "process_data_unsafe handles count of 1") {
    // arr = {0*3} = {0} -> sum = 0
    ASSERT_EQ(process_data_unsafe(1, 3), 0);
}

TEST(runner, "process_data_safe computes sum correctly") {
    // arr = {0*2, 1*2, 2*2, 3*2, 4*2} = {0, 2, 4, 6, 8} -> sum = 20
    ASSERT_EQ(process_data_safe(5, 2), 20);
}

TEST(runner, "process_data_safe throws on zero factor") {
    // This is the key difference: no leak when this throws.
    ASSERT_THROWS(process_data_safe(5, 0), std::runtime_error);
}

TEST(runner, "process_data_safe handles count of 1") {
    ASSERT_EQ(process_data_safe(1, 3), 0);
}

TEST(runner, "process_data_safe handles factor of 1") {
    // arr = {0, 1, 2, 3} -> sum = 6
    ASSERT_EQ(process_data_safe(4, 1), 6);
}

TEST(runner, "both functions produce the same results") {
    for (int n = 1; n <= 10; ++n) {
        ASSERT_EQ(process_data_unsafe(n, 3), process_data_safe(n, 3));
    }
}

TESTKIT_MAIN(runner)
