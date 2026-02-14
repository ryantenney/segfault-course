// Exercise 03 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex03.h"

static testkit::TestRunner runner("01-10-ex03: Transfer Ownership");

TEST(runner, "make_gadget creates a valid unique_ptr") {
    auto g = make_gadget("Gizmo");
    ASSERT_TRUE(g != nullptr);
    ASSERT_EQ(g->label, std::string("Gizmo"));
}

TEST(runner, "consume_gadget takes ownership and returns the label") {
    auto g = make_gadget("Doohickey");
    std::string label = consume_gadget(std::move(g));
    ASSERT_EQ(label, std::string("Doohickey"));
    ASSERT_TRUE(g == nullptr);
}

TEST(runner, "transfer_gadget moves from source to dest") {
    auto src = make_gadget("Thingamajig");
    std::unique_ptr<Gadget> dst;
    transfer_gadget(src, dst);
    ASSERT_TRUE(src == nullptr);
    ASSERT_TRUE(dst != nullptr);
    ASSERT_EQ(dst->label, std::string("Thingamajig"));
}

TEST(runner, "transfer_gadget replaces existing dest") {
    auto src = make_gadget("New");
    auto dst = make_gadget("Old");
    transfer_gadget(src, dst);
    ASSERT_TRUE(src == nullptr);
    ASSERT_EQ(dst->label, std::string("New"));
}

TESTKIT_MAIN(runner)
