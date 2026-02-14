// Exercise 07 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex07.h"

#include <type_traits>

static testkit::TestRunner runner("01-06-ex07: Template Alias");

TEST(runner, "Pair<int> is std::pair<int, int>") {
    ASSERT_TRUE((std::is_same_v<Pair<int>, std::pair<int, int>>));
}

TEST(runner, "Pair<double> is std::pair<double, double>") {
    ASSERT_TRUE((std::is_same_v<Pair<double>, std::pair<double, double>>));
}

TEST(runner, "Table<int> is the expected type") {
    ASSERT_TRUE((std::is_same_v<Table<int>, std::vector<std::pair<std::string, int>>>));
}

TEST(runner, "make_int_pair returns the pair") {
    auto p = make_int_pair(10, 20);
    ASSERT_EQ(p.first, 10);
    ASSERT_EQ(p.second, 20);
}

TEST(runner, "sum_and_diff computes both") {
    auto p = sum_and_diff(5.0, 3.0);
    ASSERT_EQ(p.first, 8.0);
    ASSERT_EQ(p.second, 2.0);
}

TEST(runner, "table_lookup finds existing key") {
    Table<int> t = {{"alpha", 1}, {"beta", 2}, {"gamma", 3}};
    ASSERT_EQ(table_lookup(t, "beta", -1), 2);
}

TEST(runner, "table_lookup returns default for missing key") {
    Table<int> t = {{"alpha", 1}, {"beta", 2}};
    ASSERT_EQ(table_lookup(t, "delta", -1), -1);
}

TEST(runner, "table_size returns entry count") {
    Table<std::string> t = {{"name", "Alice"}, {"city", "NYC"}};
    ASSERT_EQ(table_size(t), 2);
}

TESTKIT_MAIN(runner)
