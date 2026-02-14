// Exercise 04 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex04.h"

static testkit::TestRunner runner("01-05-ex04: String to Enum");

TEST(runner, "from_string parses valid season names") {
    auto spring = from_string("Spring");
    ASSERT_TRUE(spring.has_value());
    ASSERT_TRUE(spring.value() == Season::Spring);

    auto summer = from_string("Summer");
    ASSERT_TRUE(summer.has_value());
    ASSERT_TRUE(summer.value() == Season::Summer);

    auto autumn = from_string("Autumn");
    ASSERT_TRUE(autumn.has_value());
    ASSERT_TRUE(autumn.value() == Season::Autumn);

    auto winter = from_string("Winter");
    ASSERT_TRUE(winter.has_value());
    ASSERT_TRUE(winter.value() == Season::Winter);
}

TEST(runner, "from_string returns nullopt for unknown strings") {
    ASSERT_FALSE(from_string("spring").has_value());  // case-sensitive
    ASSERT_FALSE(from_string("WINTER").has_value());
    ASSERT_FALSE(from_string("").has_value());
    ASSERT_FALSE(from_string("Fall").has_value());
    ASSERT_FALSE(from_string("Summertime").has_value());
}

TEST(runner, "is_valid_season checks if the name is a known season") {
    ASSERT_TRUE(is_valid_season("Spring"));
    ASSERT_TRUE(is_valid_season("Summer"));
    ASSERT_TRUE(is_valid_season("Autumn"));
    ASSERT_TRUE(is_valid_season("Winter"));
    ASSERT_FALSE(is_valid_season(""));
    ASSERT_FALSE(is_valid_season("Fall"));
    ASSERT_FALSE(is_valid_season("summer"));
}

TESTKIT_MAIN(runner)
