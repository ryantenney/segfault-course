// Exercise 07: Template Alias
//
// PROBLEM:
//   typedef cannot be templated. If you want a generic type alias,
//   you must use `using` with a template parameter:
//
//     template <typename T>
//     using Vec = std::vector<T>;
//
//   Now Vec<int> is std::vector<int>, Vec<std::string> is
//   std::vector<std::string>, etc. This is called a "template alias"
//   or "alias template."
//
// TODO:
//   1. Study the two template aliases below (Pair and Table).
//   2. Write a third template alias called StringMap that maps to
//      std::vector<std::pair<std::string, T>> — same as Table<T> but
//      as practice writing your own.
//   3. Implement all four functions below.

#pragma once

#include <testkit/testkit.h>
#include <string>
#include <utility>
#include <vector>

// Example template alias: a pair where both elements have the same type
template <typename T>
using Pair = std::pair<T, T>;

// Example template alias: a simple key-value table with string keys
template <typename T>
using Table = std::vector<std::pair<std::string, T>>;

// TODO: Write a template alias StringMap<T> that is identical to Table<T>.
// This is practice — the point is writing the syntax yourself.
//
// template <typename T>
// using StringMap = ...;

// Return a Pair<int> containing {a, b}.
inline Pair<int> make_int_pair(int a, int b) {
    TODO();
}

// Return a Pair<double> containing {a + b, a - b}.
inline Pair<double> sum_and_diff(double a, double b) {
    TODO();
}

// Look up a key in a Table<int>. Return the value if found, or
// default_val if not found.
inline int table_lookup(const Table<int>& table,
                        const std::string& key, int default_val) {
    TODO();
}

// Return the number of entries in a Table<std::string>.
inline int table_size(const Table<std::string>& table) {
    TODO();
}
