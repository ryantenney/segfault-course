// Exercise 03 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex03.h"

static testkit::TestRunner runner("01-12-ex03: Chain Optional Operations");

TEST(runner, "find_employee_department returns department for known employees") {
    auto dept = find_employee_department("Alice");
    ASSERT_TRUE(dept.has_value());
    ASSERT_EQ(dept.value(), std::string("Engineering"));

    dept = find_employee_department("Bob");
    ASSERT_TRUE(dept.has_value());
    ASSERT_EQ(dept.value(), std::string("Sales"));
}

TEST(runner, "find_employee_department returns nullopt for unknown employees") {
    ASSERT_FALSE(find_employee_department("Zara").has_value());
}

TEST(runner, "find_department_head returns head for known departments") {
    auto head = find_department_head("Engineering");
    ASSERT_TRUE(head.has_value());
    ASSERT_EQ(head.value(), std::string("Diana"));

    head = find_department_head("Sales");
    ASSERT_TRUE(head.has_value());
    ASSERT_EQ(head.value(), std::string("Eve"));
}

TEST(runner, "find_department_head returns nullopt for unknown departments") {
    ASSERT_FALSE(find_department_head("Marketing").has_value());
}

TEST(runner, "find_boss chains lookups for known employees") {
    auto boss = find_boss("Alice");
    ASSERT_TRUE(boss.has_value());
    ASSERT_EQ(boss.value(), std::string("Diana"));

    boss = find_boss("Bob");
    ASSERT_TRUE(boss.has_value());
    ASSERT_EQ(boss.value(), std::string("Eve"));

    // Charlie is also in Engineering, so boss is Diana.
    boss = find_boss("Charlie");
    ASSERT_TRUE(boss.has_value());
    ASSERT_EQ(boss.value(), std::string("Diana"));
}

TEST(runner, "find_boss returns nullopt for unknown employees") {
    ASSERT_FALSE(find_boss("Zara").has_value());
}

TESTKIT_MAIN(runner)
