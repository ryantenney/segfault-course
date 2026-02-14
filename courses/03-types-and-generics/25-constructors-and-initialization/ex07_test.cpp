// Exercise 07 — Tests (read-only)
//
// Verifies understanding of direct init () vs list init {}.

#include <testkit/testkit.h>
#include "ex07.h"

static testkit::TestRunner runner("03-25-ex07: Direct vs List Initialization");

TEST(runner, "direct init truncates 3.9 to 3") {
    ASSERT_EQ(direct_init_narrowing(), 3);
}

TEST(runner, "list init widens int to double") {
    ASSERT_TRUE(list_init_widening() == 42.0);
}

TEST(runner, "vector(5) creates 5 elements") {
    ASSERT_EQ(vector_direct_init_size(), 5);
}

TEST(runner, "vector{5} creates 1 element") {
    ASSERT_EQ(vector_list_init_size(), 1);
}

TEST(runner, "vector{5} contains the value 5") {
    ASSERT_EQ(vector_list_init_element(), 5);
}

TEST(runner, "vector(5) elements are zero") {
    ASSERT_EQ(vector_direct_init_element(), 0);
}

TESTKIT_MAIN(runner)
