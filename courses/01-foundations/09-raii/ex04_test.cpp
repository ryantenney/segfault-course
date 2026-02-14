// Exercise 04 — Tests (read-only)
//
// Verifies understanding of RAII destruction order.

#include <testkit/testkit.h>
#include "ex04.h"

static testkit::TestRunner runner("01-09-ex04: Prove Cleanup Order");

TEST(runner, "destruction is reverse of construction") {
    std::string log = observe_destruction_order();
    ASSERT_EQ(log, std::string("ctor:A ctor:B ctor:C dtor:C dtor:B dtor:A "));
}

TEST(runner, "predicted output matches actual") {
    ASSERT_EQ(predicted_output(), observe_destruction_order());
}

TEST(runner, "nested scopes interleave correctly") {
    std::string log = observe_nested_scopes();
    ASSERT_EQ(log, std::string("ctor:outer ctor:inner dtor:inner ctor:late dtor:late dtor:outer "));
}

TEST(runner, "predicted nested output matches actual") {
    ASSERT_EQ(predicted_nested_output(), observe_nested_scopes());
}

TESTKIT_MAIN(runner)
