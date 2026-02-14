// Exercise 04: Filter-Transform Pipeline
//
// The real power of views comes from chaining them with the pipe operator.
// Each stage lazily processes elements from the previous stage, and no
// intermediate containers are created.
//
//   auto result = vec
//       | std::views::filter([](int x) { return x > 0; })
//       | std::views::transform([](int x) { return x * x; });
//
// The result is a view -- to get a vector, iterate it and push_back,
// or use a constructor with ranges::begin/end.
//
// TODO:
//   1. Implement squares_of_evens() -- filter for even numbers, then
//      transform to their squares. Return a vector.
//   2. Implement uppercase_short_words() -- filter strings with length <= max_len,
//      then transform each to uppercase. Return a vector<string>.
//   3. Implement sum_of_positives_doubled() -- filter positive values,
//      transform by doubling, and return the sum of the results.

#pragma once

#include <algorithm>
#include <cctype>
#include <ranges>
#include <string>
#include <vector>
#include <testkit/testkit.h>

// Return the squares of all even numbers in the input.
// Use views::filter | views::transform.
inline std::vector<int> squares_of_evens(const std::vector<int>& nums) {
    TODO();
}

// Return uppercase versions of strings whose length <= max_len.
// Use views::filter | views::transform.
// Hint: to uppercase a string, transform each char with std::toupper.
inline std::vector<std::string> uppercase_short_words(
        const std::vector<std::string>& words, std::size_t max_len) {
    TODO();
}

// Filter positive values, double each, then return the sum.
inline int sum_of_positives_doubled(const std::vector<int>& nums) {
    TODO();
}
