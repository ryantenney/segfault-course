// Exercise 02 — Tests (read-only)
//
// These tests verify that:
//   1. async_read_success calls callback with error_code=0 and "data ok".
//   2. async_read_failure calls callback with error_code=1 and empty string.

#include <testkit/testkit.h>
#include <string>
#include "ex02.h"

static testkit::TestRunner runner("04-42-ex02: Callback with Error Handling");

TEST(runner, "async_read_success reports error_code 0") {
    int ec = -1;
    async_read_success([&ec](int error_code, const std::string&) {
        ec = error_code;
    });
    ASSERT_EQ(ec, 0);
}

TEST(runner, "async_read_success provides data ok") {
    std::string result;
    async_read_success([&result](int, const std::string& data) {
        result = data;
    });
    ASSERT_EQ(result, "data ok");
}

TEST(runner, "async_read_failure reports error_code 1") {
    int ec = -1;
    async_read_failure([&ec](int error_code, const std::string&) {
        ec = error_code;
    });
    ASSERT_EQ(ec, 1);
}

TEST(runner, "async_read_failure provides empty result") {
    std::string result = "not empty";
    async_read_failure([&result](int, const std::string& data) {
        result = data;
    });
    ASSERT_EQ(result, "");
}

TEST(runner, "success and failure callbacks each called once") {
    int success_count = 0;
    int failure_count = 0;
    async_read_success([&success_count](int, const std::string&) {
        ++success_count;
    });
    async_read_failure([&failure_count](int, const std::string&) {
        ++failure_count;
    });
    ASSERT_EQ(success_count, 1);
    ASSERT_EQ(failure_count, 1);
}

TESTKIT_MAIN(runner)
