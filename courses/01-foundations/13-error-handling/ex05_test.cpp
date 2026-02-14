// Exercise 05 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex05.h"

static testkit::TestRunner runner("01-13-ex05: Convert Exceptions to Error Codes");

TEST(runner, "open_file returns content for valid filenames") {
    ASSERT_EQ(open_file("data.txt"), std::string("content of data.txt"));
    ASSERT_EQ(open_file("config.yaml"), std::string("content of config.yaml"));
}

TEST(runner, "open_file throws for empty filename") {
    ASSERT_THROWS(open_file(""), std::runtime_error);
}

TEST(runner, "open_file throws for missing file") {
    ASSERT_THROWS(open_file("missing"), std::runtime_error);
}

TEST(runner, "open_file throws for locked file") {
    ASSERT_THROWS(open_file("locked"), std::runtime_error);
}

TEST(runner, "try_open_file succeeds for valid filenames") {
    auto result = try_open_file("data.txt");
    ASSERT_TRUE(result.ok);
    ASSERT_EQ(result.content, std::string("content of data.txt"));
    ASSERT_EQ(result.error_message, std::string(""));
}

TEST(runner, "try_open_file captures empty filename error") {
    auto result = try_open_file("");
    ASSERT_FALSE(result.ok);
    ASSERT_EQ(result.content, std::string(""));
    ASSERT_EQ(result.error_message, std::string("empty filename"));
}

TEST(runner, "try_open_file captures file not found error") {
    auto result = try_open_file("missing");
    ASSERT_FALSE(result.ok);
    ASSERT_EQ(result.error_message, std::string("file not found"));
}

TEST(runner, "try_open_file captures permission denied error") {
    auto result = try_open_file("locked");
    ASSERT_FALSE(result.ok);
    ASSERT_EQ(result.error_message, std::string("permission denied"));
}

TESTKIT_MAIN(runner)
