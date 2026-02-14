// Exercise 06 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex06.h"

static testkit::TestRunner runner("02-18-ex06: Custom Projection");

TEST(runner, "sort_by_age sorts ascending by age") {
    auto result = sort_by_age({{"Charlie", 30}, {"Alice", 25}, {"Bob", 28}});
    ASSERT_EQ(result.size(), 3u);
    ASSERT_EQ(result[0].name, std::string("Alice"));
    ASSERT_EQ(result[0].age, 25);
    ASSERT_EQ(result[1].name, std::string("Bob"));
    ASSERT_EQ(result[1].age, 28);
    ASSERT_EQ(result[2].name, std::string("Charlie"));
    ASSERT_EQ(result[2].age, 30);
}

TEST(runner, "sort_by_age handles single person") {
    auto result = sort_by_age({{"Solo", 42}});
    ASSERT_EQ(result.size(), 1u);
    ASSERT_EQ(result[0].name, std::string("Solo"));
}

TEST(runner, "sort_by_age preserves data") {
    auto result = sort_by_age({{"B", 10}, {"A", 5}});
    ASSERT_EQ(result[0].name, std::string("A"));
    ASSERT_EQ(result[0].age, 5);
}

TEST(runner, "find_by_name returns age when found") {
    std::vector<Person> people = {{"Alice", 25}, {"Bob", 30}, {"Charlie", 35}};
    ASSERT_EQ(find_by_name(people, "Bob"), 30);
}

TEST(runner, "find_by_name returns -1 when not found") {
    std::vector<Person> people = {{"Alice", 25}, {"Bob", 30}};
    ASSERT_EQ(find_by_name(people, "Zara"), -1);
}

TEST(runner, "find_by_name finds first element") {
    std::vector<Person> people = {{"First", 10}, {"Second", 20}};
    ASSERT_EQ(find_by_name(people, "First"), 10);
}

TEST(runner, "youngest_person returns the youngest") {
    std::vector<Person> people = {{"Charlie", 30}, {"Alice", 20}, {"Bob", 25}};
    ASSERT_EQ(youngest_person(people), std::string("Alice"));
}

TEST(runner, "youngest_person with single person") {
    std::vector<Person> people = {{"Solo", 42}};
    ASSERT_EQ(youngest_person(people), std::string("Solo"));
}

TESTKIT_MAIN(runner)
