// Exercise 08: Stateful Comparator
//
// Since lambdas can capture state, they can serve as configurable
// comparators for std::sort and other algorithms. The captured state
// controls the sorting behavior.
//
//   bool ascending = true;
//   auto cmp = [ascending](int a, int b) {
//       return ascending ? a < b : a > b;
//   };
//   std::sort(v.begin(), v.end(), cmp);
//
// This is more flexible than std::less or std::greater because the
// comparison logic can depend on runtime configuration.
//
// TODO:
//   1. Implement configurable_sort() -- sort a vector using a lambda
//      that captures `ascending`. If ascending is true, sort low-to-high;
//      otherwise sort high-to-low.
//   2. Implement priority_sort() -- sort a vector of strings. Strings
//      found in the `priority` set come first (in their original relative
//      order among priorities), followed by the rest in alphabetical order.
//      Hint: use std::stable_sort with a lambda that captures the priority
//      set and considers priority items "less than" non-priority items.
//      Between two non-priority items, compare alphabetically.
//      Between two priority items, consider them equal (stable_sort
//      preserves their original order).
//   3. Implement nth_element_sort() -- sort a vector so that elements
//      divisible by `divisor` come first (sorted ascending), followed by
//      elements not divisible by `divisor` (also sorted ascending).
//      Hint: use std::stable_sort or std::sort with a lambda comparator.

#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <testkit/testkit.h>

// Sort nums ascending if `ascending` is true, descending otherwise.
// Use a lambda that captures `ascending`.
inline std::vector<int> configurable_sort(std::vector<int> nums, bool ascending) {
    TODO();
}

// Sort strings so that priority strings come first (preserving their
// relative order), followed by non-priority strings in alphabetical order.
// Use std::stable_sort with a lambda that captures the priority set.
inline std::vector<std::string> priority_sort(
        std::vector<std::string> words,
        const std::set<std::string>& priority) {
    TODO();
}

// Sort so that elements divisible by `divisor` come first (ascending),
// followed by the rest (ascending). Use a lambda that captures `divisor`.
inline std::vector<int> nth_element_sort(std::vector<int> nums, int divisor) {
    TODO();
}
