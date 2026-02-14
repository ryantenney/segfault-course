// Exercise 06 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex06.h"

static testkit::TestRunner runner("01-06-ex06: Replace typedef with using");

TEST(runner, "make_range produces 1 to n") {
    IntVec result = make_range(5);
    ASSERT_EQ(result.size(), 5u);
    ASSERT_EQ(result[0], 1);
    ASSERT_EQ(result[1], 2);
    ASSERT_EQ(result[2], 3);
    ASSERT_EQ(result[3], 4);
    ASSERT_EQ(result[4], 5);
}

TEST(runner, "make_range of 0 is empty") {
    ASSERT_TRUE(make_range(0).empty());
}

TEST(runner, "make_range of 1 is {1}") {
    IntVec result = make_range(1);
    ASSERT_EQ(result.size(), 1u);
    ASSERT_EQ(result[0], 1);
}

TEST(runner, "highest_score finds the top scorer") {
    Scoreboard board = {{"Alice", 85}, {"Bob", 92}, {"Carol", 78}};
    NameScore best = highest_score(board);
    ASSERT_EQ(best.first, "Bob");
    ASSERT_EQ(best.second, 92);
}

TEST(runner, "highest_score returns default for empty board") {
    Scoreboard board;
    NameScore best = highest_score(board);
    ASSERT_EQ(best.first, std::string(""));
    ASSERT_EQ(best.second, 0);
}

TEST(runner, "total_score sums all scores") {
    Scoreboard board = {{"Alice", 85}, {"Bob", 92}, {"Carol", 78}};
    ASSERT_EQ(total_score(board), 255);
}

TEST(runner, "total_score returns 0 for empty board") {
    Scoreboard board;
    ASSERT_EQ(total_score(board), 0);
}

TESTKIT_MAIN(runner)
