// Exercise 07: Min/Max and Partition
//
// std::min_element and std::max_element return iterators to the smallest
// and largest elements in a range:
//
//   auto it = std::min_element(v.begin(), v.end());
//   int smallest = *it;
//
// std::partition rearranges elements so that all elements satisfying a
// predicate come before those that don't. It returns an iterator to the
// partition point (the first element that doesn't satisfy the predicate):
//
//   auto mid = std::partition(v.begin(), v.end(), pred);
//   // [begin, mid) satisfies pred
//   // [mid, end)   does not satisfy pred
//
// Note: std::partition does NOT preserve relative order. Use
// std::stable_partition if you need to keep the original order.
//
// TODO:
//   1. Implement find_min_max() — return a pair {min, max} from a vector
//      using std::min_element and std::max_element.
//   2. Implement partition_evens_first() — partition a vector so all even
//      numbers come before odd numbers. Return the count of even numbers.
//   3. Implement partition_by_threshold() — partition a vector around a
//      threshold value. Elements < threshold come first. Return vectors
//      for each partition.

#pragma once

#include <algorithm>
#include <utility>
#include <vector>
#include <testkit/testkit.h>

// Return {min_value, max_value} from the vector.
// Precondition: vec is not empty.
inline std::pair<int, int> find_min_max(const std::vector<int>& vec) {
    TODO();
}

// Partition the vector so all even numbers come before odd numbers.
// Return the number of even elements.
// Hint: use std::partition with a lambda checking x % 2 == 0.
inline int partition_evens_first(std::vector<int>& vec) {
    TODO();
}

// Partition elements into two vectors: those less than `threshold`
// and those >= threshold.
// Return {below, at_or_above}.
// Hint: use std::partition_copy with std::back_inserter.
inline std::pair<std::vector<int>, std::vector<int>>
partition_by_threshold(const std::vector<int>& vec, int threshold) {
    TODO();
}
