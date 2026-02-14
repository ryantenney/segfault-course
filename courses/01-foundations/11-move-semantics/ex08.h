// Exercise 08: Move in Algorithms (std::move from <algorithm>)
//
// There are two things named "move" in C++:
//
//   1. std::move(x)             -- from <utility>, casts x to an rvalue
//   2. std::move(first, last, dest) -- from <algorithm>, bulk-moves a range
//
// The algorithm version is like std::copy, but it applies std::move to each
// element during transfer. This is useful for efficiently relocating elements
// between containers.
//
// TODO:
//   Implement the functions below using std::move (the algorithm).

#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include <testkit/testkit.h>

// Move all elements from `source` into `dest` (which must already have
// enough space). Use std::move (the algorithm from <algorithm>).
// After the move, elements in source are in a moved-from state.
inline void bulk_move(std::vector<std::string>& source,
                      std::vector<std::string>& dest) {
    TODO();
}

// Move a sub-range [from, to) of elements from `source` into a new vector.
// The new vector should contain exactly (to - from) elements.
// Elements in source[from..to) will be in a moved-from state afterward.
inline std::vector<std::string> extract_range(std::vector<std::string>& source,
                                              std::size_t from,
                                              std::size_t to) {
    TODO();
}

// Partition elements: move all strings longer than `threshold` characters
// into a "long" vector, move the rest into a "short" vector.
// Return the pair {short_strings, long_strings}.
// Hint: iterate and use std::move (the utility) on each element based on length.
inline std::pair<std::vector<std::string>, std::vector<std::string>>
partition_by_length(std::vector<std::string>& source, std::size_t threshold) {
    TODO();
}
