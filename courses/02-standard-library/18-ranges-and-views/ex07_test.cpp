// Exercise 07 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex07.h"

static testkit::TestRunner runner("02-18-ex07: Multi-Stage Pipeline");

TEST(runner, "top_scores returns top n passing scores descending") {
    auto result = top_scores({85, 42, 73, 91, 55, 68, 97}, 3);
    ASSERT_EQ(result.size(), 3u);
    ASSERT_EQ(result[0], 97);
    ASSERT_EQ(result[1], 91);
    ASSERT_EQ(result[2], 85);
}

TEST(runner, "top_scores handles fewer passing than n") {
    auto result = top_scores({30, 40, 70, 80}, 5);
    ASSERT_EQ(result.size(), 2u);
    ASSERT_EQ(result[0], 80);
    ASSERT_EQ(result[1], 70);
}

TEST(runner, "top_scores handles no passing scores") {
    auto result = top_scores({10, 20, 30, 50}, 3);
    ASSERT_EQ(result.size(), 0u);
}

TEST(runner, "transform_pipeline squares non-negatives and drops first skip") {
    // non-negatives: 1, 3, 2, 5 -> squared: 1, 9, 4, 25 -> drop 2: 4, 25
    auto result = transform_pipeline({-2, 1, 3, -4, 2, 5}, 2);
    ASSERT_EQ(result.size(), 2u);
    ASSERT_EQ(result[0], 4);
    ASSERT_EQ(result[1], 25);
}

TEST(runner, "transform_pipeline with skip 0 returns all") {
    auto result = transform_pipeline({1, 2, 3}, 0);
    ASSERT_EQ(result.size(), 3u);
    ASSERT_EQ(result[0], 1);
    ASSERT_EQ(result[1], 4);
    ASSERT_EQ(result[2], 9);
}

TEST(runner, "transform_pipeline with all negatives") {
    auto result = transform_pipeline({-1, -2, -3}, 0);
    ASSERT_EQ(result.size(), 0u);
}

TEST(runner, "label_pipeline formats and limits") {
    auto result = label_pipeline({1, 5, 3, 8, 2, 7}, 3, 2);
    // values > 3: 5, 8, 7 -> formatted: "val:5", "val:8", "val:7" -> take 2
    ASSERT_EQ(result.size(), 2u);
    ASSERT_EQ(result[0], std::string("val:5"));
    ASSERT_EQ(result[1], std::string("val:8"));
}

TEST(runner, "label_pipeline with no matches") {
    auto result = label_pipeline({1, 2, 3}, 10, 5);
    ASSERT_EQ(result.size(), 0u);
}

TEST(runner, "label_pipeline limit exceeds matches") {
    auto result = label_pipeline({10, 20}, 0, 100);
    ASSERT_EQ(result.size(), 2u);
    ASSERT_EQ(result[0], std::string("val:10"));
    ASSERT_EQ(result[1], std::string("val:20"));
}

TESTKIT_MAIN(runner)
