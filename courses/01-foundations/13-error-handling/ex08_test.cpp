// Exercise 08 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex08.h"

static testkit::TestRunner runner("01-13-ex08: Nested Exceptions");

TEST(runner, "read_sensor returns value for valid sensors") {
    ASSERT_EQ(read_sensor("temp"), std::string("value:temp"));
    ASSERT_EQ(read_sensor("humidity"), std::string("value:humidity"));
}

TEST(runner, "read_sensor throws for broken sensor") {
    ASSERT_THROWS(read_sensor("broken"), std::runtime_error);
}

TEST(runner, "read_sensor throws with correct message") {
    try {
        read_sensor("broken");
        ASSERT_TRUE(false);
    } catch (const std::runtime_error& e) {
        ASSERT_EQ(std::string(e.what()), std::string("sensor offline"));
    }
}

TEST(runner, "process_sensor returns value for valid sensors") {
    ASSERT_EQ(process_sensor("temp"), std::string("value:temp"));
}

TEST(runner, "process_sensor throws nested exception for broken sensor") {
    try {
        process_sensor("broken");
        ASSERT_TRUE(false);
    } catch (const std::runtime_error& e) {
        ASSERT_EQ(std::string(e.what()),
                  std::string("failed to process sensor: broken"));

        // Verify there's a nested exception.
        try {
            std::rethrow_if_nested(e);
            ASSERT_TRUE(false);  // should have thrown
        } catch (const std::runtime_error& inner) {
            ASSERT_EQ(std::string(inner.what()), std::string("sensor offline"));
        }
    }
}

TEST(runner, "get_error_chain returns single message for non-nested exception") {
    try {
        throw std::runtime_error("simple error");
    } catch (const std::exception& e) {
        auto chain = get_error_chain(e);
        ASSERT_EQ(chain.size(), 1u);
        ASSERT_EQ(chain[0], std::string("simple error"));
    }
}

TEST(runner, "get_error_chain returns full chain for nested exceptions") {
    try {
        process_sensor("broken");
    } catch (const std::exception& e) {
        auto chain = get_error_chain(e);
        ASSERT_EQ(chain.size(), 2u);
        ASSERT_EQ(chain[0], std::string("failed to process sensor: broken"));
        ASSERT_EQ(chain[1], std::string("sensor offline"));
    }
}

TEST(runner, "get_error_chain handles deeply nested exceptions") {
    try {
        try {
            try {
                throw std::runtime_error("level 3");
            } catch (...) {
                std::throw_with_nested(std::runtime_error("level 2"));
            }
        } catch (...) {
            std::throw_with_nested(std::runtime_error("level 1"));
        }
    } catch (const std::exception& e) {
        auto chain = get_error_chain(e);
        ASSERT_EQ(chain.size(), 3u);
        ASSERT_EQ(chain[0], std::string("level 1"));
        ASSERT_EQ(chain[1], std::string("level 2"));
        ASSERT_EQ(chain[2], std::string("level 3"));
    }
}

TESTKIT_MAIN(runner)
