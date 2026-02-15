// Exercise 05 -- Tests (read-only)
//
// Verifies Result::map_error() transforms the error type.

#include <testkit/testkit.h>
#include "ex05.h"

#include <string>

static testkit::TestRunner runner("05-51-ex05: Map Error");

// A typed error code for testing.
struct AppError {
    int code;
    std::string message;
};

TEST(runner, "map_error passes through ok unchanged") {
    Result<int, std::string> r = Ok<int>(42);
    auto result = r.map_error([](const std::string& e) {
        return AppError{500, e};
    });
    ASSERT_TRUE(result.is_ok());
    ASSERT_EQ(result.value(), 42);
}

TEST(runner, "map_error transforms the error") {
    Result<int, std::string> r = Err<std::string>(std::string("not found"));
    auto result = r.map_error([](const std::string& e) {
        return AppError{404, e};
    });
    ASSERT_TRUE(result.is_error());
    ASSERT_EQ(result.error().code, 404);
    ASSERT_EQ(result.error().message, std::string("not found"));
}

TEST(runner, "map_error changes error type from int to string") {
    Result<double, int> r = Err<int>(42);
    auto result = r.map_error([](int code) {
        std::ostringstream ss;
        ss << "error code: " << code;
        return ss.str();
    });
    ASSERT_TRUE(result.is_error());
    ASSERT_EQ(result.error(), std::string("error code: 42"));
}

TEST(runner, "map_error can be chained with transform") {
    Result<int, std::string> r = Ok<int>(5);
    auto result = r
        .transform([](int v) { return v * 10; })
        .map_error([](const std::string& e) {
            return AppError{500, e};
        });
    ASSERT_TRUE(result.is_ok());
    ASSERT_EQ(result.value(), 50);
}

TEST(runner, "map_error after failed and_then") {
    Result<int, std::string> r = Ok<int>(10);
    auto result = r
        .and_then([](int) -> Result<int, std::string> {
            return Err<std::string>(std::string("db error"));
        })
        .map_error([](const std::string& e) {
            return AppError{503, e};
        });
    ASSERT_TRUE(result.is_error());
    ASSERT_EQ(result.error().code, 503);
    ASSERT_EQ(result.error().message, std::string("db error"));
}

TESTKIT_MAIN(runner)
