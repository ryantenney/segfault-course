// Exercise 03: Transform View
//
// views::transform creates a lazy view that applies a function to each
// element as it is accessed. Like filter, no intermediate container is
// created.
//
//   auto doubled = vec | std::views::transform([](int x) { return x * 2; });
//
// The transformed view yields the result of the function for each element.
// To materialize the results, collect them into a container manually or
// use ranges::to (C++23) if available.
//
// TODO:
//   1. Implement double_values() -- return a vector where each element
//      is doubled, using views::transform.
//   2. Implement extract_lengths() -- return a vector of string lengths,
//      using views::transform on a vector of strings.
//   3. Implement negate_values() -- return a vector where each element
//      is negated, using views::transform.

#pragma once

#include <ranges>
#include <string>
#include <vector>
#include <testkit/testkit.h>

// Return a vector where each element is doubled.
inline std::vector<int> double_values(const std::vector<int>& nums) {
    TODO();
}

// Return a vector<std::size_t> containing the length of each string.
inline std::vector<std::size_t> extract_lengths(const std::vector<std::string>& words) {
    TODO();
}

// Return a vector where each element is negated (multiplied by -1).
inline std::vector<int> negate_values(const std::vector<int>& nums) {
    TODO();
}
