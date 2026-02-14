// Exercise 06 -- Tests (read-only)
//
// Verifies that the CRTP version produces the same results as virtual dispatch.

#include <testkit/testkit.h>
#include <type_traits>
#include "ex06.h"

static testkit::TestRunner runner("03-34-ex06: CRTP vs Virtual Dispatch");

// --- Virtual (sanity checks) ---

TEST(runner, "VirtualAdd::apply returns a + b") {
    VirtualAdd op;
    ASSERT_EQ(virtual_compute(op, 3, 4), 7);
}

TEST(runner, "VirtualMultiply::apply returns a * b") {
    VirtualMultiply op;
    ASSERT_EQ(virtual_compute(op, 3, 4), 12);
}

// --- CRTP ---

TEST(runner, "CrtpAdd::apply returns a + b") {
    CrtpAdd op;
    ASSERT_EQ(op.apply(3, 4), 7);
}

TEST(runner, "CrtpMultiply::apply returns a * b") {
    CrtpMultiply op;
    ASSERT_EQ(op.apply(3, 4), 12);
}

TEST(runner, "crtp_compute with CrtpAdd") {
    CrtpAdd op;
    ASSERT_EQ(crtp_compute(op, 10, 20), 30);
}

TEST(runner, "crtp_compute with CrtpMultiply") {
    CrtpMultiply op;
    ASSERT_EQ(crtp_compute(op, 10, 20), 200);
}

TEST(runner, "CRTP and virtual give same results for addition") {
    VirtualAdd v;
    CrtpAdd c;
    ASSERT_EQ(virtual_compute(v, 100, 200), crtp_compute(c, 100, 200));
}

TEST(runner, "CRTP and virtual give same results for multiplication") {
    VirtualMultiply v;
    CrtpMultiply c;
    ASSERT_EQ(virtual_compute(v, 5, 7), crtp_compute(c, 5, 7));
}

TEST(runner, "CrtpAdd has no virtual table") {
    CrtpAdd gate;
    gate.apply(0, 0);  // gate to ensure TODO is resolved

    // CrtpAdd should not be polymorphic (no vtable).
    ASSERT_FALSE(std::is_polymorphic_v<CrtpAdd>);
}

TEST(runner, "VirtualAdd is polymorphic") {
    // Sanity check: the virtual version does have a vtable.
    ASSERT_TRUE(std::is_polymorphic_v<VirtualAdd>);
}

TESTKIT_MAIN(runner)
