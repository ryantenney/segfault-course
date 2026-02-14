// Exercise 02: Filter View
//
// views::filter creates a lazy view that yields only elements satisfying
// a predicate. No new container is allocated -- the view evaluates the
// predicate on-the-fly as you iterate.
//
//   auto evens = vec | std::views::filter([](int x) { return x % 2 == 0; });
//
// Because views are lazy, they compose efficiently -- you can chain
// multiple views without creating intermediate containers.
//
// TODO:
//   1. Implement filter_positives() -- return a vector containing only
//      the positive values from the input, using views::filter.
//   2. Implement filter_long_strings() -- return a vector of strings
//      longer than `min_length`, using views::filter.
//   3. Implement count_matching() -- count elements that satisfy a
//      predicate, using views::filter and std::ranges::distance.

#pragma once

#include <algorithm>
#include <functional>
#include <ranges>
#include <string>
#include <vector>
#include <testkit/testkit.h>

// Return a vector containing only positive values (> 0) from the input.
inline std::vector<int> filter_positives(const std::vector<int>& nums) {
    TODO();
}

// Return a vector of strings whose length is strictly greater than min_length.
inline std::vector<std::string> filter_long_strings(
        const std::vector<std::string>& words, std::size_t min_length) {
    TODO();
}

// Count how many elements satisfy the predicate, using views::filter.
inline std::size_t count_matching(const std::vector<int>& nums,
                                  std::function<bool(int)> pred) {
    TODO();
}
