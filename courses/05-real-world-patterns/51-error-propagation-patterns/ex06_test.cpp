// Exercise 06 -- Tests (read-only)
//
// Verifies Result::context() wraps errors with descriptive messages.

#include <testkit/testkit.h>
#include "ex06.h"

#include <string>

static testkit::TestRunner runner("05-51-ex06: Error Context");

TEST(runner, "context passes through ok unchanged") {
    Result<int, std::string> r = Ok<int>(42);
    auto result = r.context("while loading");
    ASSERT_TRUE(result.is_ok());
    ASSERT_EQ(result.value(), 42);
}

TEST(runner, "context wraps error with message") {
    Result<int, std::string> r = Err<std::string>(std::string("file not found"));
    auto result = r.context("while loading config");
    ASSERT_TRUE(result.is_error());
    ASSERT_EQ(result.error().message, std::string("while loading config"));
    ASSERT_EQ(result.error().inner, std::string("file not found"));
}

TEST(runner, "context describe produces readable string") {
    Result<int, std::string> r = Err<std::string>(std::string("file not found"));
    auto result = r.context("while loading config");
    ASSERT_EQ(result.error().describe(),
              std::string("while loading config: file not found"));
}

TEST(runner, "context can be stacked for nested context") {
    Result<int, std::string> r = Err<std::string>(std::string("ENOENT"));
    auto result = r
        .context("reading database.yaml")
        .context("initializing app");
    ASSERT_EQ(result.error().describe(),
              std::string("initializing app: reading database.yaml: ENOENT"));
}

TEST(runner, "context preserves ok through stacking") {
    Result<int, std::string> r = Ok<int>(100);
    auto result = r
        .context("step 1")
        .context("step 2");
    ASSERT_TRUE(result.is_ok());
    ASSERT_EQ(result.value(), 100);
}

TESTKIT_MAIN(runner)
