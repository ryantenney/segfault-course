// Exercise 04 -- Tests (read-only)

#include <testkit/testkit.h>
#include <memory>
#include <string>

#include "ex04.h"

static testkit::TestRunner runner("03-27-ex04: Virtual Destructor");

TEST(runner, "DerivedResource describe includes priority") {
    exercise_ready();  // gate on TODO()
    DerivedResource dr("cache", 5);
    ASSERT_EQ(dr.describe(), std::string("DerivedResource: cache (priority 5)"));
}

TEST(runner, "create_derived returns a valid Resource") {
    auto r = create_derived("pool", 3);
    ASSERT_EQ(r->name(), std::string("pool"));
}

TEST(runner, "virtual dispatch works through base pointer") {
    auto r = create_derived("buffer", 7);
    std::string desc = r->describe();
    ASSERT_TRUE(desc.find("DerivedResource") != std::string::npos);
    ASSERT_TRUE(desc.find("buffer") != std::string::npos);
}

TEST(runner, "derived destructor runs when deleted through base pointer") {
    exercise_ready();
    reset_cleanup();
    {
        std::unique_ptr<Resource> r = create_derived("temp", 1);
        ASSERT_FALSE(cleanup_called());
    }
    // After the unique_ptr goes out of scope, the DerivedResource
    // destructor should have been called — but only if Resource has
    // a virtual destructor.
    ASSERT_TRUE(cleanup_called());
}

TEST(runner, "derived destructor runs for direct DerivedResource too") {
    exercise_ready();
    reset_cleanup();
    {
        DerivedResource dr("direct", 0);
    }
    ASSERT_TRUE(cleanup_called());
}

TESTKIT_MAIN(runner)
