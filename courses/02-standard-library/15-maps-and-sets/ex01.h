// Exercise 01: Word Frequency Counter
//
// std::unordered_map<std::string, int> is the classic way to count things.
// When you write `++counts[word]`, operator[] default-constructs the value
// (0 for int) if the key doesn't exist yet, then increments it.
//
// TODO:
//   Implement count_words() which takes a vector of strings and returns
//   an unordered_map mapping each word to its number of occurrences.

#pragma once

#include <testkit/testkit.h>
#include <unordered_map>
#include <vector>
#include <string>

// Count the occurrences of each word in the input vector.
// Return an unordered_map where keys are words and values are counts.
inline std::unordered_map<std::string, int> count_words(
        const std::vector<std::string>& words) {
    TODO();
}
