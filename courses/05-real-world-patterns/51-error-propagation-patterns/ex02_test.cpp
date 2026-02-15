// Exercise 02 -- Tests (read-only)
//
// Verifies Result::transform() maps the success value.

#include <testkit/testkit.h>
#include "ex02.h"

#include <string>

static testkit::TestRunner runner("05-51-ex02: Monadic Transform");

TEST(runner, "transform applies function to ok value") {
    Result<int, std::string> r = Ok<int>(10);
    auto doubled = r.transform([](int v) { return v * 2; });
    ASSERT_TRUE(doubled.is_ok());
    ASSERT_EQ(doubled.value(), 20);
}

TEST(runner, "transform changes the value type") {
    Result<int, std::string> r = Ok<int>(42);
    auto as_str = r.transform([](int v) {
        std::ostringstream ss;
        ss << "value=" << v;
        return ss.str();
    });
    ASSERT_TRUE(as_str.is_ok());
    ASSERT_EQ(as_str.value(), std::string("value=42"));
}

TEST(runner, "transform propagates error unchanged") {
    Result<int, std::string> r = Err<std::string>(std::string("fail"));
    auto doubled = r.transform([](int v) { return v * 2; });
    ASSERT_TRUE(doubled.is_error());
    ASSERT_EQ(doubled.error(), std::string("fail"));
}

TEST(runner, "transform can be chained") {
    Result<int, std::string> r = Ok<int>(5);
    auto result = r
        .transform([](int v) { return v + 10; })
        .transform([](int v) { return v * 2; });
    ASSERT_TRUE(result.is_ok());
    ASSERT_EQ(result.value(), 30);
}

TEST(runner, "chained transform propagates error") {
    Result<int, std::string> r = Err<std::string>(std::string("oops"));
    auto result = r
        .transform([](int v) { return v + 10; })
        .transform([](int v) { return v * 2; });
    ASSERT_TRUE(result.is_error());
    ASSERT_EQ(result.error(), std::string("oops"));
}

TESTKIT_MAIN(runner)
