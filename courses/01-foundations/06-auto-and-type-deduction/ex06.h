// Exercise 06: Replace typedef with using
//
// PROBLEM:
//   C++ inherited typedef from C, but the `using` alias is strictly
//   better:
//
//     typedef std::vector<int> IntVec;       // old style
//     using IntVec = std::vector<int>;       // modern style
//
//   The `using` form reads left-to-right: "IntVec IS a vector<int>."
//   The typedef form reads inside-out, which gets confusing with
//   function pointers and arrays.
//
// TODO:
//   1. Convert each typedef to a using alias.
//   2. Implement the functions using those aliases.

#pragma once

#include <testkit/testkit.h>
#include <string>
#include <utility>
#include <vector>

// TODO: Convert this typedef to a using alias
//   typedef std::vector<int> IntVec;
// becomes:
//   using IntVec = std::vector<int>;
typedef std::vector<int> IntVec;

// TODO: Convert this typedef to a using alias
typedef std::pair<std::string, int> NameScore;

// TODO: Convert this typedef to a using alias
typedef std::vector<NameScore> Scoreboard;

// Return an IntVec containing {1, 2, 3, ..., n}
inline IntVec make_range(int n) {
    TODO();
}

// Return the NameScore with the highest score from the scoreboard.
// If the scoreboard is empty, return {"", 0}.
inline NameScore highest_score(const Scoreboard& board) {
    TODO();
}

// Return the total of all scores on the scoreboard.
inline int total_score(const Scoreboard& board) {
    TODO();
}
