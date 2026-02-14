// Exercise 07 -- Tests (read-only)
//
// Verifies that each template instantiation has its own static counter.

#include <testkit/testkit.h>
#include <string>
#include "ex07.h"

static testkit::TestRunner runner("03-30-ex07: Static Member Per Instantiation");

// Use unique tag types to avoid contamination between tests.
struct TagA {};
struct TagB {};
struct TagC {};
struct TagD {};
struct TagE {};

TEST(runner, "counter starts at zero") {
    ASSERT_EQ(Counter<TagA>::count(), 0);
}

TEST(runner, "increment increases count") {
    Counter<TagB>::increment();
    Counter<TagB>::increment();
    Counter<TagB>::increment();
    ASSERT_EQ(Counter<TagB>::count(), 3);
}

TEST(runner, "reset sets count back to zero") {
    Counter<TagC>::increment();
    Counter<TagC>::increment();
    Counter<TagC>::reset();
    ASSERT_EQ(Counter<TagC>::count(), 0);
}

TEST(runner, "different types have independent counters") {
    Counter<TagD>::increment();
    Counter<TagD>::increment();
    Counter<TagE>::increment();

    ASSERT_EQ(Counter<TagD>::count(), 2);
    ASSERT_EQ(Counter<TagE>::count(), 1);
}

TEST(runner, "int and string instantiations are independent") {
    Counter<int>::reset();
    Counter<std::string>::reset();

    Counter<int>::increment();
    Counter<int>::increment();
    Counter<int>::increment();

    Counter<std::string>::increment();

    ASSERT_EQ(Counter<int>::count(), 3);
    ASSERT_EQ(Counter<std::string>::count(), 1);
}

TESTKIT_MAIN(runner)
