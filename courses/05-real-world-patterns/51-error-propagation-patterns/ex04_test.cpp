// Exercise 04 -- Tests (read-only)
//
// Verifies Result::or_else() for error recovery.

#include <testkit/testkit.h>
#include "ex04.h"

#include <string>

static testkit::TestRunner runner("05-51-ex04: Monadic or_else");

inline Result<int, std::string> try_recover(const std::string& err) {
    if (err == "transient") return Ok<int>(0);  // recover with default
    return Err<std::string>(std::string("unrecoverable: " + err));
}

TEST(runner, "or_else passes through ok result unchanged") {
    Result<int, std::string> r = Ok<int>(42);
    auto result = r.or_else([](const std::string&) -> Result<int, std::string> {
        return Ok<int>(0);
    });
    ASSERT_TRUE(result.is_ok());
    ASSERT_EQ(result.value(), 42);
}

TEST(runner, "or_else calls F on error and recovers") {
    Result<int, std::string> r = Err<std::string>(std::string("transient"));
    auto result = r.or_else(try_recover);
    ASSERT_TRUE(result.is_ok());
    ASSERT_EQ(result.value(), 0);
}

TEST(runner, "or_else calls F on error and stays error") {
    Result<int, std::string> r = Err<std::string>(std::string("fatal"));
    auto result = r.or_else(try_recover);
    ASSERT_TRUE(result.is_error());
    ASSERT_EQ(result.error(), std::string("unrecoverable: fatal"));
}

TEST(runner, "or_else can be chained for multiple recovery attempts") {
    Result<int, std::string> r = Err<std::string>(std::string("retry"));
    auto result = r
        .or_else([](const std::string& e) -> Result<int, std::string> {
            if (e == "retry") return Err<std::string>(std::string("transient"));
            return Ok<int>(-1);
        })
        .or_else(try_recover);
    ASSERT_TRUE(result.is_ok());
    ASSERT_EQ(result.value(), 0);
}

TEST(runner, "or_else does not affect a successful and_then chain") {
    Result<int, std::string> r = Ok<int>(10);
    auto result = r
        .and_then([](int v) -> Result<int, std::string> {
            return Ok<int>(v * 3);
        })
        .or_else([](const std::string&) -> Result<int, std::string> {
            return Ok<int>(0);
        });
    ASSERT_TRUE(result.is_ok());
    ASSERT_EQ(result.value(), 30);
}

TEST(runner, "or_else recovers after and_then fails") {
    Result<int, std::string> r = Ok<int>(10);
    auto result = r
        .and_then([](int) -> Result<int, std::string> {
            return Err<std::string>(std::string("transient"));
        })
        .or_else(try_recover);
    ASSERT_TRUE(result.is_ok());
    ASSERT_EQ(result.value(), 0);
}

TESTKIT_MAIN(runner)
