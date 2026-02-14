// Exercise 04 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex04.h"

static testkit::TestRunner runner("02-17-ex04: Filter with Remove-Erase");

TEST(runner, "remove_odds removes all odd numbers") {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6};
    remove_odds(vec);
    ASSERT_EQ(vec.size(), 3u);
    ASSERT_EQ(vec[0], 2);
    ASSERT_EQ(vec[1], 4);
    ASSERT_EQ(vec[2], 6);
}

TEST(runner, "remove_odds with all odd numbers") {
    std::vector<int> vec = {1, 3, 5};
    remove_odds(vec);
    ASSERT_TRUE(vec.empty());
}

TEST(runner, "remove_odds with no odd numbers") {
    std::vector<int> vec = {2, 4, 6};
    remove_odds(vec);
    ASSERT_EQ(vec.size(), 3u);
}

TEST(runner, "remove_empty_strings removes empties") {
    std::vector<std::string> vec = {"hello", "", "world", "", ""};
    remove_empty_strings(vec);
    ASSERT_EQ(vec.size(), 2u);
    ASSERT_EQ(vec[0], std::string("hello"));
    ASSERT_EQ(vec[1], std::string("world"));
}

TEST(runner, "remove_empty_strings with no empties") {
    std::vector<std::string> vec = {"a", "b"};
    remove_empty_strings(vec);
    ASSERT_EQ(vec.size(), 2u);
}

TEST(runner, "remove_empty_strings with all empties") {
    std::vector<std::string> vec = {"", "", ""};
    remove_empty_strings(vec);
    ASSERT_TRUE(vec.empty());
}

TEST(runner, "remove_duplicates removes consecutive duplicates after sorting") {
    std::vector<int> vec = {3, 1, 4, 1, 5, 3, 3};
    remove_duplicates(vec);
    ASSERT_EQ(vec.size(), 4u);
    ASSERT_EQ(vec[0], 1);
    ASSERT_EQ(vec[1], 3);
    ASSERT_EQ(vec[2], 4);
    ASSERT_EQ(vec[3], 5);
}

TEST(runner, "remove_duplicates with no duplicates") {
    std::vector<int> vec = {5, 3, 1};
    remove_duplicates(vec);
    ASSERT_EQ(vec.size(), 3u);
    ASSERT_EQ(vec[0], 1);
    ASSERT_EQ(vec[1], 3);
    ASSERT_EQ(vec[2], 5);
}

TEST(runner, "remove_duplicates with all same") {
    std::vector<int> vec = {7, 7, 7, 7};
    remove_duplicates(vec);
    ASSERT_EQ(vec.size(), 1u);
    ASSERT_EQ(vec[0], 7);
}

TESTKIT_MAIN(runner)
