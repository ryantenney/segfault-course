// Exercise 03: Using Declarations
//
// PROBLEM:
//   The functions below use fully-qualified names like
//   `containers::make_vector(...)` and `containers::sum(...)`.
//   This is correct, but it's verbose when you call the same
//   names repeatedly.
//
// TODO:
//   1. In the body of `test_helpers::build_and_sum()`, add targeted
//      `using` declarations to bring `make_vector` and `sum` into scope.
//   2. Implement the function to create a vector with {a, b, c} and
//      return its sum.
//
// WHY:
//   A `using` declaration (`using containers::sum;`) imports one specific
//   name into the current scope. This is the safe middle ground between
//   fully-qualifying everything and the dangerous `using namespace`.

#pragma once

#include <testkit/testkit.h>
#include <vector>
#include <numeric>

namespace containers {

inline std::vector<int> make_vector(int a, int b, int c) {
    return {a, b, c};
}

inline int sum(const std::vector<int>& v) {
    int total = 0;
    for (int x : v) total += x;
    return total;
}

inline int product(const std::vector<int>& v) {
    int result = 1;
    for (int x : v) result *= x;
    return result;
}

} // namespace containers

namespace test_helpers {

// TODO: Add `using` declarations for containers::make_vector and
// containers::sum, then use them without qualification.
inline int build_and_sum(int a, int b, int c) {
    TODO();
}

// TODO: Add a `using` declaration for containers::product,
// then use it without qualification.
inline int build_and_product(int a, int b, int c) {
    TODO();
}

} // namespace test_helpers
