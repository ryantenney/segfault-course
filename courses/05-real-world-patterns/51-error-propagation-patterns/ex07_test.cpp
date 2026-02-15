// Exercise 07 -- Tests (read-only)
//
// Verifies collect() gathers all ok values or returns first error.

#include <testkit/testkit.h>
#include "ex07.h"

#include <string>
#include <vector>

static testkit::TestRunner runner("05-51-ex07: Collect Results");

TEST(runner, "collect empty vector returns ok with empty vector") {
    std::vector<Result<int, std::string>> results;
    auto collected = collect(results);
    ASSERT_TRUE(collected.is_ok());
    ASSERT_EQ(collected.value().size(), size_t(0));
}

TEST(runner, "collect all ok returns vector of values") {
    std::vector<Result<int, std::string>> results;
    results.push_back(Ok<int>(1));
    results.push_back(Ok<int>(2));
    results.push_back(Ok<int>(3));
    auto collected = collect(results);
    ASSERT_TRUE(collected.is_ok());
    ASSERT_EQ(collected.value().size(), size_t(3));
    ASSERT_EQ(collected.value()[0], 1);
    ASSERT_EQ(collected.value()[1], 2);
    ASSERT_EQ(collected.value()[2], 3);
}

TEST(runner, "collect returns first error") {
    std::vector<Result<int, std::string>> results;
    results.push_back(Ok<int>(1));
    results.push_back(Err<std::string>(std::string("error at 1")));
    results.push_back(Ok<int>(3));
    auto collected = collect(results);
    ASSERT_TRUE(collected.is_error());
    ASSERT_EQ(collected.error(), std::string("error at 1"));
}

TEST(runner, "collect with only errors returns the first") {
    std::vector<Result<int, std::string>> results;
    results.push_back(Err<std::string>(std::string("first")));
    results.push_back(Err<std::string>(std::string("second")));
    auto collected = collect(results);
    ASSERT_TRUE(collected.is_error());
    ASSERT_EQ(collected.error(), std::string("first"));
}

TEST(runner, "collect single ok element") {
    std::vector<Result<int, std::string>> results;
    results.push_back(Ok<int>(42));
    auto collected = collect(results);
    ASSERT_TRUE(collected.is_ok());
    ASSERT_EQ(collected.value().size(), size_t(1));
    ASSERT_EQ(collected.value()[0], 42);
}

TEST(runner, "collect single error element") {
    std::vector<Result<int, std::string>> results;
    results.push_back(Err<std::string>(std::string("only error")));
    auto collected = collect(results);
    ASSERT_TRUE(collected.is_error());
    ASSERT_EQ(collected.error(), std::string("only error"));
}

TESTKIT_MAIN(runner)
