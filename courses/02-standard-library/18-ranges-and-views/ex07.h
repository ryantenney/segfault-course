// Exercise 07: Compose a Multi-Stage Pipeline
//
// Views truly shine when you chain 3 or more stages together. The entire
// pipeline is lazy -- no intermediate containers are allocated. Only when
// you iterate the final view are elements pulled through each stage.
//
//   auto result = data
//       | views::filter(...)
//       | views::transform(...)
//       | views::take(n);
//
// To materialize the result into a std::vector, iterate the view and
// push_back each element, or construct the vector from the view's
// begin/end iterators.
//
// TODO:
//   1. Implement top_scores() -- given a vector of scores (ints), keep only
//      passing scores (>= 60), sort them descending, take the top `n`,
//      and return them in a vector.
//      Hint: ranges::sort mutates, so copy first, sort, then pipe the
//      sorted vector through filter | take.
//   2. Implement transform_pipeline() -- given a vector of ints, filter
//      out negatives, square each value, drop the first `skip` results,
//      and return the remainder in a vector.
//   3. Implement label_pipeline() -- given a vector of ints, filter
//      for values > threshold, transform each to "val:X" (where X is
//      the number), take at most `limit` results, and return them as
//      a vector<string>.

#pragma once

#include <algorithm>
#include <ranges>
#include <string>
#include <vector>
#include <testkit/testkit.h>

// Keep passing scores (>= 60), sort descending, take the top n.
inline std::vector<int> top_scores(std::vector<int> scores, std::size_t n) {
    TODO();
}

// Filter out negatives, square each value, drop the first `skip` results.
inline std::vector<int> transform_pipeline(const std::vector<int>& nums,
                                           std::size_t skip) {
    TODO();
}

// Filter values > threshold, format as "val:X", take at most `limit`.
inline std::vector<std::string> label_pipeline(const std::vector<int>& nums,
                                               int threshold,
                                               std::size_t limit) {
    TODO();
}
