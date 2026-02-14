// Exercise 06 — Tests (read-only)
//
// Verifies the ScopeGuard RAII wrapper.

#include <testkit/testkit.h>
#include "ex06.h"

static testkit::TestRunner runner("01-09-ex06: Scope Guard");

TEST(runner, "ScopeGuard runs callable on destruction") {
    std::string log;
    {
        ScopeGuard guard([&log]() { log += "cleaned"; });
    }
    ASSERT_EQ(log, std::string("cleaned"));
}

TEST(runner, "make_scope_guard deduces type") {
    std::string log;
    {
        auto guard = make_scope_guard([&log]() { log += "done"; });
    }
    ASSERT_EQ(log, std::string("done"));
}

TEST(runner, "multiple guards run in reverse order") {
    std::string log;
    {
        auto g1 = make_scope_guard([&log]() { log += "1"; });
        auto g2 = make_scope_guard([&log]() { log += "2"; });
        auto g3 = make_scope_guard([&log]() { log += "3"; });
    }
    ASSERT_EQ(log, std::string("321"));
}

TEST(runner, "scope guard works with function pointer") {
    static int call_count = 0;
    call_count = 0;
    {
        auto increment = []() { ++call_count; };
        ScopeGuard guard(increment);
    }
    ASSERT_EQ(call_count, 1);
}

TEST(runner, "scope guard captures state correctly") {
    int counter = 0;
    {
        auto guard = make_scope_guard([&counter]() { counter += 10; });
        counter = 5;  // modify before guard runs
    }
    // guard adds 10 to the current value of 5
    ASSERT_EQ(counter, 15);
}

TESTKIT_MAIN(runner)
