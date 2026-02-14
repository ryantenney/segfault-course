// Exercise 05 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex05.h"

static testkit::TestRunner runner("02-18-ex05: Take and Drop");

TEST(runner, "first_n takes the first n elements") {
    auto result = first_n({10, 20, 30, 40, 50}, 3);
    ASSERT_EQ(result.size(), 3u);
    ASSERT_EQ(result[0], 10);
    ASSERT_EQ(result[1], 20);
    ASSERT_EQ(result[2], 30);
}

TEST(runner, "first_n handles n larger than size") {
    auto result = first_n({10, 20}, 5);
    ASSERT_EQ(result.size(), 2u);
    ASSERT_EQ(result[0], 10);
    ASSERT_EQ(result[1], 20);
}

TEST(runner, "first_n handles n = 0") {
    auto result = first_n({10, 20, 30}, 0);
    ASSERT_EQ(result.size(), 0u);
}

TEST(runner, "skip_n drops the first n elements") {
    auto result = skip_n({10, 20, 30, 40, 50}, 2);
    ASSERT_EQ(result.size(), 3u);
    ASSERT_EQ(result[0], 30);
    ASSERT_EQ(result[1], 40);
    ASSERT_EQ(result[2], 50);
}

TEST(runner, "skip_n handles n larger than size") {
    auto result = skip_n({10, 20}, 5);
    ASSERT_EQ(result.size(), 0u);
}

TEST(runner, "skip_n handles n = 0") {
    auto result = skip_n({10, 20, 30}, 0);
    ASSERT_EQ(result.size(), 3u);
}

TEST(runner, "middle_slice extracts a slice") {
    auto result = middle_slice({10, 20, 30, 40, 50}, 1, 4);
    ASSERT_EQ(result.size(), 3u);
    ASSERT_EQ(result[0], 20);
    ASSERT_EQ(result[1], 30);
    ASSERT_EQ(result[2], 40);
}

TEST(runner, "middle_slice handles full range") {
    auto result = middle_slice({10, 20, 30}, 0, 3);
    ASSERT_EQ(result.size(), 3u);
    ASSERT_EQ(result[0], 10);
    ASSERT_EQ(result[2], 30);
}

TEST(runner, "middle_slice handles empty slice") {
    auto result = middle_slice({10, 20, 30}, 2, 2);
    ASSERT_EQ(result.size(), 0u);
}

TESTKIT_MAIN(runner)
