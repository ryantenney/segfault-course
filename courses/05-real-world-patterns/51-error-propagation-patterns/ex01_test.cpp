// Exercise 01 -- Tests (read-only)
//
// Verifies Result<T, E> basic construction and accessors.

#include <testkit/testkit.h>
#include "ex01.h"

#include <string>

static testkit::TestRunner runner("05-51-ex01: Result Type");

TEST(runner, "ok result is_ok returns true") {
    Result<int, std::string> r = Ok<int>(42);
    ASSERT_TRUE(r.is_ok());
}

TEST(runner, "ok result is_error returns false") {
    Result<int, std::string> r = Ok<int>(42);
    ASSERT_FALSE(r.is_error());
}

TEST(runner, "ok result value returns the stored value") {
    Result<int, std::string> r = Ok<int>(42);
    ASSERT_EQ(r.value(), 42);
}

TEST(runner, "ok result error throws") {
    Result<int, std::string> r = Ok<int>(42);
    ASSERT_THROWS(r.error(), std::runtime_error);
}

TEST(runner, "error result is_ok returns false") {
    Result<int, std::string> r = Err<std::string>(std::string("bad"));
    ASSERT_FALSE(r.is_ok());
}

TEST(runner, "error result is_error returns true") {
    Result<int, std::string> r = Err<std::string>(std::string("bad"));
    ASSERT_TRUE(r.is_error());
}

TEST(runner, "error result error returns the stored error") {
    Result<int, std::string> r = Err<std::string>(std::string("bad"));
    ASSERT_EQ(r.error(), std::string("bad"));
}

TEST(runner, "error result value throws") {
    Result<int, std::string> r = Err<std::string>(std::string("bad"));
    ASSERT_THROWS(r.value(), std::runtime_error);
}

TEST(runner, "works when T and E are the same type") {
    Result<std::string, std::string> ok = Ok<std::string>(std::string("good"));
    Result<std::string, std::string> err = Err<std::string>(std::string("bad"));
    ASSERT_TRUE(ok.is_ok());
    ASSERT_TRUE(err.is_error());
    ASSERT_EQ(ok.value(), std::string("good"));
    ASSERT_EQ(err.error(), std::string("bad"));
}

TESTKIT_MAIN(runner)
