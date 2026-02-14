// Exercise 03: Chain Optional Operations
//
// A common pattern is chaining lookups where each step might fail. For example:
// look up a user, then look up their department, then look up the department head.
// Each step returns optional, and you must check at every stage.
//
// C++23 adds monadic operations (.and_then, .transform) but in C++20 you do
// this manually with if-checks. This exercise practices that pattern.
//
// TODO:
//   1. Implement find_employee_department() — look up which department an
//      employee belongs to.
//   2. Implement find_department_head() — look up who heads a department.
//   3. Implement find_boss() — chain the two lookups to find an employee's
//      department head. Return nullopt if any step fails.
//
//   Employee -> Department:
//     "Alice" -> "Engineering", "Bob" -> "Sales", "Charlie" -> "Engineering"
//
//   Department -> Head:
//     "Engineering" -> "Diana", "Sales" -> "Eve"

#pragma once

#include <optional>
#include <string>
#include <testkit/testkit.h>

// Look up which department an employee belongs to.
inline std::optional<std::string> find_employee_department(const std::string& employee) {
    TODO();
}

// Look up who heads a department.
inline std::optional<std::string> find_department_head(const std::string& department) {
    TODO();
}

// Chain both lookups: find the department head for a given employee.
// Return nullopt if the employee is unknown or the department has no head.
inline std::optional<std::string> find_boss(const std::string& employee) {
    TODO();
}
