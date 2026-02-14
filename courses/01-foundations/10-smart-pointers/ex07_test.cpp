// Exercise 07 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex07.h"

static testkit::TestRunner runner("01-10-ex07: Break a Cycle with weak_ptr");

TEST(runner, "make_node creates a valid node") {
    auto n = make_node("Alpha");
    ASSERT_EQ(n->name, std::string("Alpha"));
}

TEST(runner, "link_nodes sets next and prev") {
    auto a = make_node("A");
    auto b = make_node("B");
    link_nodes(a, b);
    ASSERT_EQ(a->next->name, std::string("B"));
    ASSERT_EQ(get_prev_name(b), std::string("A"));
}

TEST(runner, "no cycle: dropping a releases memory") {
    auto a = make_node("First");
    auto b = make_node("Second");
    link_nodes(a, b);

    // a has ref count 1 (only the local variable), because b->prev is weak
    // b has ref count 2 (local variable + a->next)
    ASSERT_EQ(a.use_count(), 1L);

    a.reset(); // destroys First node
    // Now b->prev should be expired
    ASSERT_EQ(get_prev_name(b), std::string("expired"));
}

TEST(runner, "get_prev_name returns expired for unlinked node") {
    auto n = make_node("Lonely");
    ASSERT_EQ(get_prev_name(n), std::string("expired"));
}

TESTKIT_MAIN(runner)
