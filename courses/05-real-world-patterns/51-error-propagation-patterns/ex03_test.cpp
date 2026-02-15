// Exercise 03 -- Tests (read-only)
//
// Verifies Result::and_then() chains failable operations.

#include <testkit/testkit.h>
#include "ex03.h"

#include <string>

static testkit::TestRunner runner("05-51-ex03: Monadic and_then");

inline Result<int, std::string> safe_divide(int a, int b) {
    if (b == 0) return Err<std::string>(std::string("division by zero"));
    return Ok<int>(a / b);
}

inline Result<int, std::string> parse_positive(int v) {
    if (v <= 0) return Err<std::string>(std::string("not positive"));
    return Ok<int>(v);
}

TEST(runner, "and_then chains successful operations") {
    Result<int, std::string> r = Ok<int>(100);
    auto result = r.and_then([](int v) { return safe_divide(v, 5); });
    ASSERT_TRUE(result.is_ok());
    ASSERT_EQ(result.value(), 20);
}

TEST(runner, "and_then propagates inner error") {
    Result<int, std::string> r = Ok<int>(100);
    auto result = r.and_then([](int v) { return safe_divide(v, 0); });
    ASSERT_TRUE(result.is_error());
    ASSERT_EQ(result.error(), std::string("division by zero"));
}

TEST(runner, "and_then propagates outer error") {
    Result<int, std::string> r = Err<std::string>(std::string("initial fail"));
    auto result = r.and_then([](int v) { return safe_divide(v, 5); });
    ASSERT_TRUE(result.is_error());
    ASSERT_EQ(result.error(), std::string("initial fail"));
}

TEST(runner, "and_then can be chained multiple times") {
    Result<int, std::string> r = Ok<int>(100);
    auto result = r
        .and_then([](int v) { return safe_divide(v, 5); })
        .and_then([](int v) { return parse_positive(v); })
        .and_then([](int v) { return safe_divide(v, 2); });
    ASSERT_TRUE(result.is_ok());
    ASSERT_EQ(result.value(), 10);
}

TEST(runner, "chained and_then stops at first error") {
    Result<int, std::string> r = Ok<int>(100);
    auto result = r
        .and_then([](int v) { return safe_divide(v, 0); })
        .and_then([](int v) { return parse_positive(v); });
    ASSERT_TRUE(result.is_error());
    ASSERT_EQ(result.error(), std::string("division by zero"));
}

TEST(runner, "and_then can follow transform") {
    Result<int, std::string> r = Ok<int>(10);
    auto result = r
        .transform([](int v) { return v * 10; })
        .and_then([](int v) { return safe_divide(v, 5); });
    ASSERT_TRUE(result.is_ok());
    ASSERT_EQ(result.value(), 20);
}

TESTKIT_MAIN(runner)
