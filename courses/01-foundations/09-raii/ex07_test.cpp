// Exercise 07 — Tests (read-only)
//
// Verifies that RAII destructors run during exception propagation.

#include <stdexcept>
#include <testkit/testkit.h>
#include "ex07.h"

static testkit::TestRunner runner("01-09-ex07: RAII Survives Exceptions");

TEST(runner, "function_that_throws actually throws") {
    std::string log;
    ASSERT_THROWS(function_that_throws(log), std::runtime_error);
}

TEST(runner, "destructors run during stack unwinding") {
    std::string log;
    try {
        function_that_throws(log);
    } catch (const testkit::not_implemented&) { throw; }
    catch (...) {}
    // Both resources should be released even though an exception was thrown
    ASSERT_TRUE(log.find("release:resource1") != std::string::npos);
    ASSERT_TRUE(log.find("release:resource2") != std::string::npos);
}

TEST(runner, "release order is reverse of acquire order") {
    std::string log;
    try {
        function_that_throws(log);
    } catch (const testkit::not_implemented&) { throw; }
    catch (...) {}
    // resource2 was acquired second, so it should be released first
    auto pos1 = log.find("release:resource2");
    auto pos2 = log.find("release:resource1");
    ASSERT_TRUE(pos1 < pos2);
}

TEST(runner, "demonstrate_exception_safety produces correct log") {
    std::string result = demonstrate_exception_safety();
    ASSERT_EQ(result, std::string("acquire:resource1 acquire:resource2 release:resource2 release:resource1 caught "));
}

TEST(runner, "predicted output matches actual") {
    ASSERT_EQ(predicted_exception_output(), demonstrate_exception_safety());
}

TESTKIT_MAIN(runner)
