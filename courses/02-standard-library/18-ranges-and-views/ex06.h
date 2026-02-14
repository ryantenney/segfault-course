// Exercise 06: Custom Projection
//
// Many std::ranges algorithms accept a "projection" parameter -- a
// callable that extracts or transforms each element before the algorithm
// applies its logic. This avoids writing custom comparators when you just
// want to sort/find by a specific member.
//
//   struct Person { std::string name; int age; };
//   std::ranges::sort(people, {}, &Person::age);  // sort by age ascending
//   auto it = std::ranges::find(people, "Alice", &Person::name);
//
// The second argument `{}` is the comparator (default = less). The third
// argument is the projection.
//
// TODO:
//   1. Implement sort_by_age() -- sort a vector of Person by age ascending,
//      using std::ranges::sort with a projection.
//   2. Implement find_by_name() -- find a Person by name using
//      std::ranges::find with a projection. Return the person's age,
//      or -1 if not found.
//   3. Implement youngest_person() -- find the person with the smallest
//      age using std::ranges::min_element with a projection. Return
//      their name. Assume the input is non-empty.

#pragma once

#include <algorithm>
#include <ranges>
#include <string>
#include <vector>
#include <testkit/testkit.h>

struct Person {
    std::string name;
    int age;
};

// Sort the vector by age in ascending order using a projection.
// Return the sorted vector.
inline std::vector<Person> sort_by_age(std::vector<Person> people) {
    TODO();
}

// Find a person by name using std::ranges::find with a projection.
// Return their age, or -1 if not found.
inline int find_by_name(const std::vector<Person>& people,
                        const std::string& name) {
    TODO();
}

// Return the name of the youngest person.
// Assume people is non-empty.
inline std::string youngest_person(const std::vector<Person>& people) {
    TODO();
}
