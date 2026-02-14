// Exercise 05: Take and Drop
//
// views::take(n) yields the first n elements of a range.
// views::drop(n) skips the first n elements and yields the rest.
//
//   auto first3 = vec | std::views::take(3);
//   auto rest   = vec | std::views::drop(3);
//
// If n exceeds the range size, take yields everything and drop yields
// nothing -- no out-of-bounds errors.
//
// These views compose naturally with filter and transform in pipelines.
//
// TODO:
//   1. Implement first_n() -- return a vector of the first n elements.
//   2. Implement skip_n() -- return a vector with the first n elements removed.
//   3. Implement middle_slice() -- return elements from index `start` up to
//      (but not including) index `end`. Use drop(start) | take(end - start).

#pragma once

#include <ranges>
#include <vector>
#include <testkit/testkit.h>

// Return a vector of the first n elements from nums.
inline std::vector<int> first_n(const std::vector<int>& nums, std::size_t n) {
    TODO();
}

// Return a vector with the first n elements removed.
inline std::vector<int> skip_n(const std::vector<int>& nums, std::size_t n) {
    TODO();
}

// Return elements from index `start` up to (but not including) index `end`.
// Use views::drop and views::take.
inline std::vector<int> middle_slice(const std::vector<int>& nums,
                                     std::size_t start, std::size_t end) {
    TODO();
}
