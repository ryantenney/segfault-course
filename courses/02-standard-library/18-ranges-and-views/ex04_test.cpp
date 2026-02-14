// Exercise 04 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex04.h"

static testkit::TestRunner runner("02-18-ex04: Filter-Transform Pipeline");

TEST(runner, "squares_of_evens returns squares of even numbers") {
    auto result = squares_of_evens({1, 2, 3, 4, 5, 6});
    std::vector<int> expected = {4, 16, 36};
    ASSERT_EQ(result.size(), expected.size());
    for (std::size_t i = 0; i < expected.size(); ++i) {
        ASSERT_EQ(result[i], expected[i]);
    }
}

TEST(runner, "squares_of_evens handles no even numbers") {
    auto result = squares_of_evens({1, 3, 5, 7});
    ASSERT_EQ(result.size(), 0u);
}

TEST(runner, "squares_of_evens handles negative evens") {
    auto result = squares_of_evens({-4, -2, 0, 1});
    std::vector<int> expected = {16, 4, 0};
    ASSERT_EQ(result.size(), expected.size());
    for (std::size_t i = 0; i < expected.size(); ++i) {
        ASSERT_EQ(result[i], expected[i]);
    }
}

TEST(runner, "uppercase_short_words filters and uppercases") {
    auto result = uppercase_short_words({"hi", "hello", "hey", "greetings"}, 3);
    std::vector<std::string> expected = {"HI", "HEY"};
    ASSERT_EQ(result.size(), expected.size());
    for (std::size_t i = 0; i < expected.size(); ++i) {
        ASSERT_EQ(result[i], expected[i]);
    }
}

TEST(runner, "uppercase_short_words with large max keeps all") {
    auto result = uppercase_short_words({"cat", "dog"}, 10);
    ASSERT_EQ(result.size(), 2u);
    ASSERT_EQ(result[0], std::string("CAT"));
    ASSERT_EQ(result[1], std::string("DOG"));
}

TEST(runner, "sum_of_positives_doubled sums doubled positives") {
    auto result = sum_of_positives_doubled({-3, -1, 0, 2, 5});
    // positives: 2, 5 -> doubled: 4, 10 -> sum: 14
    ASSERT_EQ(result, 14);
}

TEST(runner, "sum_of_positives_doubled returns zero for no positives") {
    auto result = sum_of_positives_doubled({-3, -1, 0});
    ASSERT_EQ(result, 0);
}

TEST(runner, "sum_of_positives_doubled handles empty input") {
    auto result = sum_of_positives_doubled({});
    ASSERT_EQ(result, 0);
}

TESTKIT_MAIN(runner)
